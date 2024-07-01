#include "Js_BlendState.h"

namespace Js
{
	BlendState::BlendState(ComPtr<ID3D11Device> _device)
		: m_Device(_device)
	{
	}
	BlendState::~BlendState()
	{
	}
	void BlendState::Create(D3D11_RENDER_TARGET_BLEND_DESC _blendDesc, float _factor)
	{
		m_BlendFactor = _factor;

		D3D11_BLEND_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BLEND_DESC));
		desc.RenderTarget[0].BlendEnable = true;
		desc.AlphaToCoverageEnable = false;
		desc.IndependentBlendEnable = false;
		desc.RenderTarget[0] = _blendDesc;

		HRESULT hr = m_Device->CreateBlendState(&desc, m_BlendState.GetAddressOf());
		CHECK(hr);
	}
}