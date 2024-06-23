#include "Js_RasterizerState.h"

namespace Js
{
	RasterizerState::RasterizerState(ComPtr<ID3D11Device> _device)
		: m_Device(_device)
	{
	}
	RasterizerState::~RasterizerState()
	{
	}
	void RasterizerState::Create()
	{
		D3D11_RASTERIZER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.FillMode = D3D11_FILL_SOLID;
		desc.CullMode = D3D11_CULL_BACK;
		desc.FrontCounterClockwise = false;

		HRESULT hr = m_Device->CreateRasterizerState(&desc, m_RasterizerState.GetAddressOf());
		CHECK(hr);
	}
}