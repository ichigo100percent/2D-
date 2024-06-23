#pragma once
#include "std.h"

namespace Js
{
	class Texture
	{
	public:
		Texture(ComPtr<ID3D11Device> _device);
		~Texture();

		void Create(const std::wstring& _texName);

		ComPtr<ID3D11ShaderResourceView> GetPtr() { return m_ShaderResourceView; }
		Vector2 GetSize() { return m_Size; }

	private:
		ComPtr<ID3D11Device>			 m_Device = nullptr;
		ComPtr<ID3D11ShaderResourceView> m_ShaderResourceView = nullptr;
		Vector2 m_Size = {};
	};
}