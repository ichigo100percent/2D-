#pragma once
#include "std.h"

namespace Js
{
	class BlendState
	{
	public:
		BlendState(ComPtr<ID3D11Device> _device);
		~BlendState();

		void Create(D3D11_RENDER_TARGET_BLEND_DESC _blendDesc =
			{
				true,
				D3D11_BLEND_SRC_ALPHA,
				D3D11_BLEND_INV_SRC_ALPHA,
				D3D11_BLEND_OP_ADD,
				D3D11_BLEND_ONE,
				D3D11_BLEND_ZERO,
				D3D11_BLEND_OP_ADD,
				D3D11_COLOR_WRITE_ENABLE_ALL
			}, float _factor = 0.f);

		const float* GetBlendFactor() { return &m_BlendFactor; }
		UINT GetSampleMask() { return m_SampleMask; }
		ComPtr<ID3D11BlendState> GetComPtr() { return m_BlendState; }

	private:
		ComPtr<ID3D11Device> m_Device;
		ComPtr<ID3D11BlendState> m_BlendState;
		float m_BlendFactor = 0.f;
		UINT m_SampleMask = 0xFFFFFFFF;
	};
}
