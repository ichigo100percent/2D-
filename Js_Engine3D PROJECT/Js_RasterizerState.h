#pragma once
#include "std.h"

namespace Js
{
	class RasterizerState
	{
	public:
		RasterizerState(ComPtr<ID3D11Device> _device);
		~RasterizerState();

		void Create();

		ComPtr< ID3D11RasterizerState> GetComPtr() { return m_RasterizerState; }

	private:
		ComPtr<ID3D11Device>		  m_Device = nullptr;
		ComPtr<ID3D11RasterizerState> m_RasterizerState = nullptr;
	};
}