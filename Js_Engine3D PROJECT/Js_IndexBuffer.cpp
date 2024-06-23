#include "Js_IndexBuffer.h"


namespace Js
{
	IndexBuffer::IndexBuffer(ComPtr<ID3D11Device> _device)
		: m_Device(_device)
	{
	}
	IndexBuffer::~IndexBuffer()
	{
	}
	void IndexBuffer::Create(const std::vector<UINT>& _indices)
	{
		m_Stride = sizeof(UINT);
		m_Count = static_cast<UINT>(_indices.size());

		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Usage = D3D11_USAGE_IMMUTABLE;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.ByteWidth = (UINT)(m_Stride * m_Count);

		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(data));
		data.pSysMem = _indices.data();

		HRESULT hr = m_Device->CreateBuffer(&desc, &data, m_IndexBuffer.GetAddressOf());
		CHECK(hr);
	}
}