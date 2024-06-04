#include "Js_DxObject.h"
#include "Js_Input.h"

namespace Js
{
	DxObject::DxObject(ComPtr<ID3D11Device> _device, ComPtr<ID3D11DeviceContext> _context, const std::wstring& _name) :
		Entity(_name),
		m_Device(_device),
		m_Context(_context),
		m_VertexBuffer(nullptr),
		m_InputLayout(nullptr),
		m_VertexShader(nullptr),
		m_PixelShader(nullptr),
		m_VSBlob(nullptr),
		m_PSBlob(nullptr)
	{
	}
	void DxObject::Init()
	{
		CreateGeometry();
		CreateVertexBuffer();
		CreateIndexBuffer();
		CreateVS();
		CreateInputLayout();
		CreatePS();

		CreateRasterizerState();
		CreateSRV();
	}
	void DxObject::Render()
	{
		UINT StartSlot = 0;
		UINT NumBuffers = 1;
		UINT Stride = sizeof(VertexData);
		UINT Offset = 0;

		// IA
		m_Context->IASetVertexBuffers(StartSlot, NumBuffers, m_VertexBuffer.GetAddressOf(), &Stride, &Offset);
		m_Context->IASetIndexBuffer(m_IndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
		m_Context->IASetInputLayout(m_InputLayout.Get());
		m_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// VS
		m_Context->VSSetShader(m_VertexShader.Get(), nullptr, 0);
		
		// RS
		m_Context->RSSetState(m_RasterizerState.Get());

		// PS
		m_Context->PSSetShader(m_PixelShader.Get(), nullptr, 0);
		m_Context->PSSetShaderResources(0, 1, m_ShaderResourceView.GetAddressOf());

		// OM
		//m_Context->Draw(m_Vertices.size(), 0);
		m_Context->DrawIndexed(m_Indices.size(), 0, 0);
	}
	void DxObject::Update()
	{
	}
	void DxObject::Release()
	{
	}
	void DxObject::Move()
	{

	}
	Vector2 DxObject::ConvertScreenToNDC(Vector2& _pos)
	{
		// 0 ~ 800 -> 0 ~ 1
		_pos.x = _pos.x / g_Width;
		_pos.y = _pos.y / g_Height;
		
		// NDC 좌표계
		// 0 ~ 1 -> -1 ~ 1
		Vector2 ret;
		ret.x = _pos.x * 2.0f - 1.0f;

		return Vector2();
	}
	void DxObject::CreateGeometry()
	{
		m_Vertices.resize(4);
		m_Vertices[0].position = Vector2(-1.f, -1.f);
		m_Vertices[1].position = Vector2(-1.f, 1.f);
		m_Vertices[2].position = Vector2(1.f, -1.f);
		m_Vertices[3].position = Vector2(1.f, 1.f);

		m_Vertices[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		m_Vertices[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		m_Vertices[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		m_Vertices[3].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

		m_Vertices[0].texture = Vector2(0.0f, 1.0f);
		m_Vertices[1].texture = Vector2(0.0f, 0.0f);
		m_Vertices[2].texture = Vector2(1.0f, 1.0f);
		m_Vertices[3].texture = Vector2(1.0f, 0.0f);

		// 좌우 반전
		//m_Vertices[0].texture = Vector2(1.0f, 1.0f); 
		//m_Vertices[1].texture = Vector2(1.0f, 0.0f); 
		//m_Vertices[2].texture = Vector2(0.0f, 1.0f); 
		//m_Vertices[3].texture = Vector2(0.0f, 0.0f); 
	}
	void DxObject::CreateVertexBuffer()
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.ByteWidth = (UINT)sizeof(VertexData) * m_Vertices.size();

		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
		data.pSysMem = m_Vertices.data();

		HRESULT hr = m_Device->CreateBuffer(&desc, &data, m_VertexBuffer.GetAddressOf());

		CHECK(hr);
	}
	void DxObject::CreateIndexBuffer()
	{
		m_Indices = { 0,1,2,2,1,3 };

		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.ByteWidth = (UINT)(sizeof(UINT) * m_Indices.size());

		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
		data.pSysMem = m_Indices.data();

		HRESULT hr = m_Device->CreateBuffer(&desc, &data, m_IndexBuffer.GetAddressOf());
		
		CHECK(hr);
	}
	void DxObject::CreateInputLayout()
	{
		const D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			// RGBA = float 4개 
			{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 8, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXTURE", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		const UINT count = sizeof(layout) / sizeof(D3D11_INPUT_ELEMENT_DESC);
		HRESULT hr = m_Device->CreateInputLayout
		(
			layout,
			count,
			m_VSBlob->GetBufferPointer(),
			m_VSBlob->GetBufferSize(),
			m_InputLayout.GetAddressOf()
		);

		CHECK(hr);
	}
	void DxObject::LoadShader(const std::wstring& _path, const std::string& _name, const std::string& _version, ComPtr<ID3DBlob>& _blob)
	{
		const UINT compileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;

		HRESULT hr = D3DCompileFromFile
		(
			_path.c_str(),
			nullptr,
			D3D_COMPILE_STANDARD_FILE_INCLUDE,
			_name.c_str(),
			_version.c_str(),
			compileFlag,
			0,
			_blob.GetAddressOf(),
			nullptr
		);
		CHECK(hr);
	}
	void DxObject::CreateVS()
	{
		LoadShader(L"Default.hlsl", "VS", "vs_5_0", m_VSBlob);
		HRESULT hr =
			m_Device->CreateVertexShader
			(
				m_VSBlob->GetBufferPointer(),
				m_VSBlob->GetBufferSize(),
				nullptr,
				m_VertexShader.GetAddressOf()
			);

		CHECK(hr);
	}
	void DxObject::CreatePS()
	{
		LoadShader(L"Default.hlsl", "PS", "ps_5_0", m_PSBlob);
		HRESULT hr =
			m_Device->CreatePixelShader
			(
				m_PSBlob->GetBufferPointer(),
				m_PSBlob->GetBufferSize(),
				nullptr,
				m_PixelShader.GetAddressOf()
			);

		CHECK(hr);
	}
	void DxObject::CreateRasterizerState()
	{
		D3D11_RASTERIZER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));
		desc.FillMode = D3D11_FILL_SOLID;
		// 뒷면을 렌더링하지 않음
		desc.CullMode = D3D11_CULL_BACK;
		// 시계 방향으로 정의된 삼각형을 앞면으로 간주
		desc.FrontCounterClockwise = false;

		HRESULT hr = m_Device->CreateRasterizerState(&desc, m_RasterizerState.GetAddressOf());
		CHECK(hr);
	}
	void DxObject::CreateSamplerState()
	{
	}
	void DxObject::CreateBlendState()
	{
	}
	void DxObject::CreateSRV()
	{
		HRESULT hr = 
			CreateWICTextureFromFile(m_Device.Get(),
									L"원희.png",
									m_Texture.GetAddressOf(),
									m_ShaderResourceView.GetAddressOf());
		CHECK(hr);
	}
	void DxObject::CreateConstantBuffer()
	{
	}
}