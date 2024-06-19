#include "Js_TextureMgr.h"

namespace Js
{
	void Texture::Release()
	{
		m_ShaderResourceView.Reset();
		m_Texture.Reset();
	}
	bool Texture::Load(ComPtr<ID3D11Device> _device, const std::wstring& _fileName)
	{
		HRESULT hr =
			CreateWICTextureFromFile(_device.Get(),
				_fileName.c_str(),
				m_Texture.GetAddressOf(),
				m_ShaderResourceView.GetAddressOf());

		if (FAILED(hr))
		{
			return false;
		}
		return true;
	}
}