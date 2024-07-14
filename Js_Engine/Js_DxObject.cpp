#include "Js_DxObject.h"
#include "Js_Input.h"
#include "Js_Time.h"
#include "Js_TextureMgr.h"
#include "Js_ShaderMgr.h"

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
		PreRender();
		PostRender();
	}
	void DxObject::PreRender()
	{
		UpdateVertexBuffer();
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
		m_Context->VSSetShader(m_Shader->m_VertexShader.Get(), nullptr, 0);

		// RS
		m_Context->RSSetState(m_RasterizerState.Get());

		// PS
		m_Context->PSSetShader(m_Shader->m_PixelShader.Get(), nullptr, 0);
		m_Context->PSSetShaderResources(0, 1, m_ShaderResourceView.GetAddressOf());

		// OM
		m_Context->OMSetBlendState(m_BlendState.Get(), nullptr, 0xFFFFFFFF);
	}
	void DxObject::PostRender()
	{
		// OM
		m_Context->DrawIndexed(m_Indices.size(), 0, 0);
	}
	void DxObject::Update()
	{
	}
	void DxObject::UpdateVertexBuffer()
	{
		for (int i = 0; i < m_Vertices.size(); i++)
		{
			m_NdcVertices[i].position = ConvertScreenToNDC(m_List[i].position);
			m_NdcVertices[i].color = m_List[i].color;
			m_NdcVertices[i].texture = m_List[i].texture;
		}

		if (m_VertexBuffer != nullptr)
		{
			m_Context->UpdateSubresource(m_VertexBuffer.Get(), 0, NULL, m_NdcVertices.data(), 0, 0);
		}
	}
	Vector3& DxObject::ConvertScreenToNDC(const Vector3& _pos)
	{
		// 스크린 좌표계를 NDC 좌표계로 변환
		// 0 ~ 800 -> 0 ~ 1
		float normalizedX = _pos.x / g_Width;
		float normalizedY = _pos.y / g_Height;

		// NDC 좌표계
		// 0 ~ 1 -> -1 ~ 1
		Vector3 ret;
		ret.x = normalizedX * 2.0f - 1.0f;
		ret.y = -(normalizedY * 2.0f - 1.0f);
		ret.z = 0;
		// -1 ~ 1  -> 0 ~ +1 (이 부분은 필요에 따라 주석 해제)
		// ret.x = ret.x * 0.5f + 0.5f;
		// ret.y = ret.y * 0.5f + 0.5f;

		return ret;
	}

	void DxObject::CreateGeometry(const RECT& _rect)
	{
		m_Vertices.resize(4);
		m_NdcVertices.resize(4);	   
		m_Vertices[0].position = Vector3(_rect.left,_rect.bottom, 0);
		m_Vertices[1].position = Vector3(_rect.left, _rect.top, 0);
		m_Vertices[2].position = Vector3(_rect.right, _rect.bottom, 0);
		m_Vertices[3].position = Vector3(_rect.right, _rect.top, 0);

		m_Vertices[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		m_Vertices[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		m_Vertices[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		m_Vertices[3].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

		m_Vertices[0].texture = Vector2(0.0f, 1.0f);
		m_Vertices[1].texture = Vector2(0.0f, 0.0f);
		m_Vertices[2].texture = Vector2(1.0f, 1.0f);
		m_Vertices[3].texture = Vector2(1.0f, 0.0f);


		m_List = m_Vertices;
		m_NdcVertices = m_Vertices;
		UpdateVertexBuffer();
	}
	void DxObject::CreateVertexBuffer()
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.ByteWidth = (UINT)sizeof(VertexData) * m_NdcVertices.size();

		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
		data.pSysMem = m_NdcVertices.data();

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
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXTURE", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		const UINT count = sizeof(layout) / sizeof(D3D11_INPUT_ELEMENT_DESC);
		HRESULT hr = m_Device->CreateInputLayout
		(
			layout,
			count,
			m_Shader->m_VSBlob->GetBufferPointer(),
			m_Shader->m_VSBlob->GetBufferSize(),
			m_InputLayout.GetAddressOf()
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
	void DxObject::CreateBlendState()
	{
		D3D11_BLEND_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BLEND_DESC));
		desc.AlphaToCoverageEnable = true;
		desc.IndependentBlendEnable = false;

		desc.RenderTarget[0].BlendEnable = true;
		desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		HRESULT hr = m_Device->CreateBlendState(&desc, m_BlendState.GetAddressOf());
		CHECK(hr);
	}
	void DxObject::CreateSRV(const std::wstring& _texName)
	{
		m_Texture = TEXTURE.Load(_texName);

		if (m_Texture != nullptr)
			m_ShaderResourceView = m_Texture->m_ShaderResourceView;
	}
}