#pragma once
#include "std.h"

namespace Js
{
	template <typename T>
	class ConstantBuffer
	{
	public:
		ConstantBuffer(ComPtr<ID3D11Device> _device, ComPtr<ID3D11DeviceContext> _context)
			: m_Device(_device)
			, m_Context(_context)
		{

		}
		~ConstantBuffer() {}

		void Create()
		{
			D3D11_BUFFER_DESC desc;
			ZeroMemory(&desc, sizeof(desc));
			desc.Usage = D3D11_USAGE_DYNAMIC; // CPU_Write + GPU_Read
			desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			desc.ByteWidth = sizeof(T);
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

			HRESULT hr = m_Device->CreateBuffer(&desc, nullptr, m_ConstantBuffer.GetAddressOf());
			CHECK(hr);
		}

		void CopyData(const T& _data)
		{
			D3D11_MAPPED_SUBRESOURCE subResource;
			ZeroMemory(&subResource, sizeof(subResource));

			m_Context->Map(m_ConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
			::memcpy(subResource.pData, &_data, sizeof(_data));
			m_Context->Unmap(m_ConstantBuffer.Get(), 0);
		}

		ComPtr<ID3D11Buffer> GetComPtr() { return m_ConstantBuffer; }

	private:
		ComPtr<ID3D11Device>			m_Device = nullptr;
		ComPtr<ID3D11DeviceContext>		m_Context = nullptr;
		ComPtr<ID3D11Buffer>			m_ConstantBuffer = nullptr;
	};
}