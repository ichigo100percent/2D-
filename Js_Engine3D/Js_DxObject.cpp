#include "Js_DxObject.h"
#include "Js_Input.h"
#include "Js_Time.h"

namespace Js
{
	DxObject::DxObject(ComPtr<ID3D11Device> _device, ComPtr<ID3D11DeviceContext> _context, const std::wstring& _name) :
		Entity(_name),
		_device(_device),
		_deviceContext(_context)
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
		_deviceContext->IASetVertexBuffers(0, 1, _vertexBuffer.GetAddressOf(), &stride, &offset);
		_deviceContext->IASetIndexBuffer(_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
		_deviceContext->IASetInputLayout(_inputLayout.Get());
		_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// VS
		_deviceContext->VSSetShader(_vertexShader.Get(), nullptr, 0);
		_deviceContext->VSSetConstantBuffers(0, 1, _constantBuffer.GetAddressOf());

		// RS
		_deviceContext->RSSetState(_rasterizerState.Get());

		// PS
		_deviceContext->PSSetShader(_pixelShader.Get(), nullptr, 0);
		_deviceContext->PSSetShaderResources(0, 1, _shaderResourveView.GetAddressOf());
		_deviceContext->PSSetSamplers(0, 1, _samplerState.GetAddressOf());

		// OM

		//_deviceContext->Draw(_vertices.size(), 0);
		_deviceContext->DrawIndexed(_indices.size(), 0, 0);
	}
	void DxObject::Update()
	{
		float speed = 1 * Time::DeltaTime();
		// Scale Rotation Translation
		if (Input::KeyCheck('W') == KeyState::KEY_HOLD)
		{
			_transformData.offset.y += speed;
		}
		if (Input::KeyCheck('S') == KeyState::KEY_HOLD)
		{
			_transformData.offset.y -= speed;
		}
		if (Input::KeyCheck('A') == KeyState::KEY_HOLD)
		{
			_transformData.offset.x -= speed;
		}
		if (Input::KeyCheck('D') == KeyState::KEY_HOLD)
		{
			_transformData.offset.x += speed;
		}

		D3D11_MAPPED_SUBRESOURCE subResource;
		ZeroMemory(&subResource, sizeof(subResource));

		_deviceContext->Map(_constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
		::memcpy(subResource.pData, &_transformData, sizeof(_transformData));
		_deviceContext->Unmap(_constantBuffer.Get(), 0);

		std::string pos; 
		pos += std::to_string(_transformData.offset.x) + " " + to_string(_transformData.offset.y) + '\n';
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
			_vertices.resize(4);

			_vertices[0].position = Vector3(-0.5f, -0.5f, 0.f);
			_vertices[0].uv = Vector2(0.f, 1.f);
			_vertices[1].position = Vector3(-0.5f, 0.5f, 0.f);
			_vertices[1].uv = Vector2(0.f, 0.f);
			_vertices[2].position = Vector3(0.5f, -0.5f, 0.f);
			_vertices[2].uv = Vector2(1.f, 1.f);
			_vertices[3].position = Vector3(0.5f, 0.5f, 0.f);
			_vertices[3].uv = Vector2(1.f, 0.f);
		}

		// VertexBuffer
		{
			D3D11_BUFFER_DESC desc;
			ZeroMemory(&desc, sizeof(desc));
			desc.Usage = D3D11_USAGE_IMMUTABLE;
			desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			desc.ByteWidth = (UINT)(sizeof(VertexData) * _vertices.size());

			D3D11_SUBRESOURCE_DATA data;
			ZeroMemory(&data, sizeof(data));
			data.pSysMem = _vertices.data();

			HRESULT hr = _device->CreateBuffer(&desc, &data, _vertexBuffer.GetAddressOf());
			CHECK(hr);
		}

		// Index
		{
			_indices = { 0, 1, 2, 2, 1, 3 };
		}

		// IndexBuffer
		{
			D3D11_BUFFER_DESC desc;
			ZeroMemory(&desc, sizeof(desc));
			desc.Usage = D3D11_USAGE_IMMUTABLE;
			desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			desc.ByteWidth = (UINT)(sizeof(UINT) * _indices.size());

			D3D11_SUBRESOURCE_DATA data;
			ZeroMemory(&data, sizeof(data));
			data.pSysMem = _indices.data();

			HRESULT hr = _device->CreateBuffer(&desc, &data, _indexBuffer.GetAddressOf());
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
		_device->CreateInputLayout(layout, count, _vsBlob->GetBufferPointer(), _vsBlob->GetBufferSize(), _inputLayout.GetAddressOf());
	}
	void DxObject::LoadShaderFromFile(const wstring& path, const string& name, const string& version, ComPtr<ID3DBlob>& blob)
	{
		const UINT compileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;

		HRESULT hr = ::D3DCompileFromFile(
			path.c_str(),
			nullptr,
			D3D_COMPILE_STANDARD_FILE_INCLUDE,
			name.c_str(),
			version.c_str(),
			compileFlag,
			0,
			blob.GetAddressOf(),
			nullptr);

		CHECK(hr);
	}
	void DxObject::CreateVS()
	{
		LoadShaderFromFile(L"Default.hlsl", "VS", "vs_5_0", _vsBlob);
		HRESULT hr = _device->CreateVertexShader(_vsBlob->GetBufferPointer(), _vsBlob->GetBufferSize(), nullptr, _vertexShader.GetAddressOf());
		CHECK(hr);
	}
	void DxObject::CreatePS()
	{
		LoadShaderFromFile(L"Default.hlsl", "PS", "ps_5_0", _psBlob);
		HRESULT hr = _device->CreatePixelShader(_psBlob->GetBufferPointer(), _psBlob->GetBufferSize(), nullptr, _pixelShader.GetAddressOf());
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

		hr = ::CreateShaderResourceView(_device.Get(), img.GetImages(), img.GetImageCount(), md, _shaderResourveView.GetAddressOf());
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

		HRESULT hr = _device->CreateBuffer(&desc, nullptr, _constantBuffer.GetAddressOf());
		CHECK(hr);
	}
}