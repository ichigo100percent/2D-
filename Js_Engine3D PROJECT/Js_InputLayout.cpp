#include "Js_InputLayout.h"


namespace Js
{
	InputLayout::InputLayout(ComPtr<ID3D11Device> _device)
		: m_Device(_device)
	{
	}
	InputLayout::~InputLayout()
	{
	}
	void InputLayout::Create(const std::vector<D3D11_INPUT_ELEMENT_DESC>& _descs, ComPtr<ID3DBlob> _blob)
	{
		const UINT count = static_cast<UINT>(_descs.size());
		m_Device->CreateInputLayout(_descs.data(),
									count,
									_blob->GetBufferPointer(),
									_blob->GetBufferSize(),
								 	m_InputLayout.GetAddressOf());
	}		
}