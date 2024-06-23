#pragma once
#include "std.h"

namespace Js
{
	class VertexBuffer
	{
	public:
		VertexBuffer(ComPtr<ID3D11Device> _device);
		~VertexBuffer();

		template <typename T>
		void Create(const std::vector<T>& _vertices)
		{
			m_Stride = sizeof(T);
			m_Count = static_cast<UINT>(_vertices.size());

			D3D11_BUFFER_DESC desc;
			ZeroMemory(&desc, sizeof(desc));
			desc.Usage = D3D11_USAGE_IMMUTABLE;
			desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			desc.ByteWidth = (UINT)(m_Stride * m_Count);

			D3D11_SUBRESOURCE_DATA data;
			ZeroMemory(&data, sizeof(data));
			data.pSysMem = _vertices.data();

			HRESULT hr = m_Device->CreateBuffer(&desc, &data, m_VertexBuffer.GetAddressOf());
			CHECK(hr);
		}

		ComPtr<ID3D11Buffer> GetComPtr() { return m_VertexBuffer; }
		UINT GetStride() { return m_Stride; }
		UINT GetOffset() { return m_Offset; }
		UINT GetCount() { return m_Count; }

	private:
		ComPtr<ID3D11Device> m_Device = nullptr;
		ComPtr<ID3D11Buffer> m_VertexBuffer = nullptr;

		UINT m_Stride = 0;
		UINT m_Offset = 0;
		UINT m_Count  = 0;
	};
}