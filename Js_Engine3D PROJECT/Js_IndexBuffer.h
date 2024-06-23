#pragma once
#include "std.h"

namespace Js
{
	class IndexBuffer
	{
	public:
		IndexBuffer(ComPtr<ID3D11Device> _device);
		~IndexBuffer();


		void Create(const std::vector<UINT>& _indices);

		ComPtr<ID3D11Buffer> GetComPtr() { return m_IndexBuffer; }
		UINT GetStride() { return m_Stride; }
		UINT GetOffset() { return m_Offset; }
		UINT GetCount() { return m_Count; }

	private:
		ComPtr<ID3D11Device> m_Device = nullptr;
		ComPtr<ID3D11Buffer> m_IndexBuffer = nullptr;

		UINT m_Stride = 0;
		UINT m_Offset = 0;
		UINT m_Count  = 0;
	};
}