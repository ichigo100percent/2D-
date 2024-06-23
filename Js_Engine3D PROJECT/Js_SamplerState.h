#pragma once
#include "std.h"

namespace Js
{
	class SamplerState
	{
	public:
		SamplerState(ComPtr<ID3D11Device> _device);
		~SamplerState();

		void Create();

		ComPtr<ID3D11SamplerState> GetComPtr() { return m_SamplerState; }

	private:
		ComPtr<ID3D11Device> m_Device = nullptr;
		ComPtr<ID3D11SamplerState> m_SamplerState = nullptr;
	};
}
