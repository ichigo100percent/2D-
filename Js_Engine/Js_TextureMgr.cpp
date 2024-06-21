#include "Js_TextureMgr.h"

namespace Js
{
	void Texture::Release()
	{
		if(m_ShaderResourceView) m_ShaderResourceView.Reset();
		if(m_Texture) m_Texture.Reset();
	}
	bool Texture::Load(const std::wstring& _fileName)
	{
		HRESULT hr =
			CreateWICTextureFromFile(m_Device.Get(),
				_fileName.c_str(),
				m_Texture.GetAddressOf(),
				m_ShaderResourceView.GetAddressOf());

		if (FAILED(hr))
		{
			hr = DirectX::CreateDDSTextureFromFile(m_Device.Get(),
				_fileName.c_str(),
				m_Texture.GetAddressOf(),
				m_ShaderResourceView.GetAddressOf());

			if (FAILED(hr))
				return false;
		}

		ID3D11Texture2D* pTex = (ID3D11Texture2D*)m_Texture.Get();
		pTex->GetDesc(&td);
		m_Size.x = td.Width;
		m_Size.y = td.Height;

		return true;
	}
}