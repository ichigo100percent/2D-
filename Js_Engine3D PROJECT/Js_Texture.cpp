#include "Js_Texture.h"

namespace Js
{
	Texture::Texture(ComPtr<ID3D11Device> _device)
		: BaseResource(ResourceType::Texture),
		  m_Device(_device)
	{
	}
	Texture::~Texture()
	{
	}
	void Texture::Create(const std::wstring& _texName)
	{
		DirectX::TexMetadata md;
		DirectX::ScratchImage img;
		HRESULT hr = ::LoadFromWICFile(_texName.c_str(), WIC_FLAGS_NONE, &md, img);
		CHECK(hr);

		hr = ::CreateShaderResourceView(m_Device.Get(), img.GetImages(), img.GetImageCount(), md, m_ShaderResourceView.GetAddressOf());
		CHECK(hr);

		m_Size.x = md.width;
		m_Size.y = md.height;
	}
}