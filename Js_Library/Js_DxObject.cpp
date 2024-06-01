#include "pch.h"
#include "Js_DxObject.h"


namespace Js
{
	DxObject::DxObject(ComPtr<ID3D11Device> _device, ComPtr<ID3D11DeviceContext> _context) :
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
		CreateVertexBuffer();
		CreateVS();
		CreateInputLayout();

	}
	void DxObject::Render()
	{
	}
	void DxObject::Update()
	{
	}
	void DxObject::Release()
	{
	}
	void DxObject::CreateVertexBuffer()
	{
		m_Vertices.resize(3);
		m_Vertices[0].position = Vector3(-0.5f, -0.5f, 0);
		m_Vertices[1].position = Vector3(-0.5, 0.5f, 0);
		m_Vertices[2].position = Vector3(0.5, -0.5f, 0);

		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.ByteWidth = sizeof(Vertex) * m_Vertices.size();

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = m_Vertices.data();

		HRESULT hr = m_Device->CreateBuffer(&desc, &sd, m_VertexBuffer.GetAddressOf());

		CHECK(hr);
	}
	void DxObject::CreateInputLayout()
	{
		const D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POS", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },

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
		LoadShader(L"VS.txt", "VSMain", "vs_5_0", m_VSBlob);
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
	void DxObject::CreatePixelShader()
	{
	}
}