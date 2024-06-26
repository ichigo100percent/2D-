#include "Js_ResourceManager.h"
#include "Js_Texture.h"

namespace Js
{
	ResourceManager::ResourceManager(ComPtr<ID3D11Device> _device)
		: m_Device(_device)
	{
	}
	void ResourceManager::Init()
	{
		createDefaultMesh();
		createDefaultShader();
		createDefaultTexture();
		createDefaultMaterial();
		createDefaultAnimation();
		createDefaultSound();
	}
	void ResourceManager::createDefaultMesh()
	{
	}
	void ResourceManager::createDefaultShader()
	{
	}
	void ResourceManager::createDefaultTexture()
	{
		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"bg_blue");
			texture->Create(L"bg_blue.jpg");
			Add(texture->GetName(), texture);
		}
	}
	void ResourceManager::createDefaultMaterial()
	{
	}
	void ResourceManager::createDefaultAnimation()
	{
	}
	void ResourceManager::createDefaultSound()
	{
	}
}