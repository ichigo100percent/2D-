#include "Js_DxObject.h"
#include "Js_Input.h"
#include "Js_Time.h"

namespace Js
{
	DxObject::DxObject(ComPtr<ID3D11Device> _device, ComPtr<ID3D11DeviceContext> _context, const std::wstring& _name) :
		Entity(_name),
		m_Device(_device), 
		m_Context(_context)
	{
		
	}
	DxObject::~DxObject()
	{
	}
	void DxObject::Render()
	{
		UINT stride = sizeof(VertexData);
		UINT offset = 0;

		// IA
		m_Context->IASetVertexBuffers(0, 1, m_VertexBuffer.GetAddressOf(), &stride, &offset);
		m_Context->IASetIndexBuffer(m_IndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
		m_Context->IASetInputLayout(_inputLayout.Get());
		m_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// VS
		m_Context->VSSetShader(m_VertexShader.Get(), nullptr, 0);
		m_Context->VSSetConstantBuffers(0, 1, m_ConstantBuffer.GetAddressOf());

		// RS
		m_Context->RSSetState(_rasterizerState.Get());

		// PS
		m_Context->PSSetShader(m_PixelShader.Get(), nullptr, 0);
		m_Context->PSSetShaderResources(0, 1, m_ShaderResourveView.GetAddressOf());

		// OM

		//m_Context->Draw(m_Vertices.size(), 0);
		m_Context->DrawIndexed(m_Indices.size(), 0, 0);
	}
	void DxObject::Update()
	{
		float speed = 1 * Time::DeltaTime();
		// Scale Rotation Translation
		if (Input::KeyCheck('W') == KeyState::KEY_HOLD)
		{
			m_LocalPosition.y += speed;
		}
		if (Input::KeyCheck('S') == KeyState::KEY_HOLD)
		{
			m_LocalPosition.y -= speed;
		}
		if (Input::KeyCheck('A') == KeyState::KEY_HOLD)
		{
			m_LocalPosition.x -= speed;
		}
		if (Input::KeyCheck('D') == KeyState::KEY_HOLD)
		{
			m_LocalPosition.x += speed;
		}
	
		Matrix matScale = Matrix::CreateScale(m_LocalScale / 3);
		Matrix matRotation = Matrix::CreateRotationX(m_LocalRotation.x);
		matRotation *= Matrix::CreateRotationY(m_LocalRotation.y);
		matRotation *= Matrix::CreateRotationZ(m_LocalRotation.z);
		Matrix matTranslation = Matrix::CreateTranslation(m_LocalPosition);

		Matrix matWorld = matScale * matRotation * matTranslation; // SRT
		m_TransformData.matWorld = matWorld;

		D3D11_MAPPED_SUBRESOURCE subResource;
		ZeroMemory(&subResource, sizeof(subResource));

		m_Context->Map(m_ConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
		::memcpy(subResource.pData, &m_TransformData, sizeof(m_TransformData));
		m_Context->Unmap(m_ConstantBuffer.Get(), 0);

		std::string pos; 
		pos += std::to_string(m_LocalPosition.x) + " " + to_string(m_LocalPosition.y) + '\n';
		OutputDebugStringA(pos.c_str());
	}
	void DxObject::Release()
	{
	}
	void DxObject::CreateObject(const std::wstring& _texName)
	{
		CreateGeometry();
		CreateVS();
		CreateInputLayout();
		CreatePS();

		CreateSRV(_texName);
		CreateConstantBuffer();
	}


	void DxObject::CreateGeometry()
	{
		// VertexData
		{
			m_Vertices.resize(4);

			m_Vertices[0].position = Vector3(-0.5f, -0.5f, 0.f);
			m_Vertices[0].uv = Vector2(0.f, 1.f);
			m_Vertices[1].position = Vector3(-0.5f, 0.5f, 0.f);
			m_Vertices[1].uv = Vector2(0.f, 0.f);
			m_Vertices[2].position = Vector3(0.5f, -0.5f, 0.f);
			m_Vertices[2].uv = Vector2(1.f, 1.f);
			m_Vertices[3].position = Vector3(0.5f, 0.5f, 0.f);
			m_Vertices[3].uv = Vector2(1.f, 0.f);
		}

		// VertexBuffer
		{
			D3D11_BUFFER_DESC desc;
			ZeroMemory(&desc, sizeof(desc));
			desc.Usage = D3D11_USAGE_IMMUTABLE;
			desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			desc.ByteWidth = (UINT)(sizeof(VertexData) * m_Vertices.size());

			D3D11_SUBRESOURCE_DATA data;
			ZeroMemory(&data, sizeof(data));
			data.pSysMem = m_Vertices.data();

			HRESULT hr = m_Device->CreateBuffer(&desc, &data, m_VertexBuffer.GetAddressOf());
			CHECK(hr);
		}

		// Index
		{
			m_Indices = { 0, 1, 2, 2, 1, 3 };
		}

		// IndexBuffer
		{
			D3D11_BUFFER_DESC desc;
			ZeroMemory(&desc, sizeof(desc));
			desc.Usage = D3D11_USAGE_IMMUTABLE;
			desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			desc.ByteWidth = (UINT)(sizeof(UINT) * m_Indices.size());

			D3D11_SUBRESOURCE_DATA data;
			ZeroMemory(&data, sizeof(data));
			data.pSysMem = m_Indices.data();

			HRESULT hr = m_Device->CreateBuffer(&desc, &data, m_IndexBuffer.GetAddressOf());
			CHECK(hr);
		}
	}


	void DxObject::CreateInputLayout()
	{
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		const UINT count = sizeof(layout) / sizeof(D3D11_INPUT_ELEMENT_DESC);
		m_Device->CreateInputLayout(layout, count, m_VsBlob->GetBufferPointer(), m_VsBlob->GetBufferSize(), _inputLayout.GetAddressOf());
	}
	void DxObject::LoadShaderFromFile(const wstring& _path, const string& _name, const string& _version, ComPtr<ID3DBlob>& _blob)
	{
		const UINT compileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;

		HRESULT hr = ::D3DCompileFromFile(
			_path.c_str(),
			nullptr,
			D3D_COMPILE_STANDARD_FILE_INCLUDE,
			_name.c_str(),
			_version.c_str(),
			compileFlag,
			0,
			_blob.GetAddressOf(),
			nullptr);

		CHECK(hr);
	}
	void DxObject::CreateVS()
	{
		LoadShaderFromFile(L"Default.hlsl", "VS", "vs_5_0", m_VsBlob);
		HRESULT hr = m_Device->CreateVertexShader(m_VsBlob->GetBufferPointer(), m_VsBlob->GetBufferSize(), nullptr, m_VertexShader.GetAddressOf());
		CHECK(hr);
	}
	void DxObject::CreatePS()
	{
		LoadShaderFromFile(L"Default.hlsl", "PS", "ps_5_0", m_PsBlob);
		HRESULT hr = m_Device->CreatePixelShader(m_PsBlob->GetBufferPointer(), m_PsBlob->GetBufferSize(), nullptr, m_PixelShader.GetAddressOf());
		CHECK(hr);
	}
	void DxObject::CreateRasterizerState()
	{
	}
	void DxObject::CreateSamplerState()
	{
	}
	void DxObject::CreateBlendState()
	{
	}
	void DxObject::CreateSRV(const std::wstring& _texName)
	{
		DirectX::TexMetadata md;
		DirectX::ScratchImage img;
		HRESULT hr = ::LoadFromWICFile(_texName.c_str(), WIC_FLAGS_NONE, &md, img);
		CHECK(hr);

		hr = ::CreateShaderResourceView(m_Device.Get(), img.GetImages(), img.GetImageCount(), md, m_ShaderResourveView.GetAddressOf());
		CHECK(hr);
	}
	void DxObject::CreateConstantBuffer()
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Usage = D3D11_USAGE_DYNAMIC; // CPU_Write + GPU_Read
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.ByteWidth = sizeof(TransformData);
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		HRESULT hr = m_Device->CreateBuffer(&desc, nullptr, m_ConstantBuffer.GetAddressOf());
		CHECK(hr);
	}
}