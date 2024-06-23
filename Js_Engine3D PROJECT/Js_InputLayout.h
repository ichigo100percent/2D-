#pragma once
#include "std.h"

namespace Js
{
	class InputLayout
	{
	public:
		InputLayout(ComPtr<ID3D11Device> _device);
		~InputLayout();

		void Create(const std::vector<D3D11_INPUT_ELEMENT_DESC>& _descs, ComPtr<ID3DBlob> _blob);

		ComPtr<ID3D11InputLayout> GetComPtr() { return m_InputLayout; }

	private:
		ComPtr<ID3D11Device> m_Device = nullptr;
		ComPtr<ID3D11InputLayout> m_InputLayout = nullptr;
	};
}