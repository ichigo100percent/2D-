#include "Js_ResourceManager.h"
#include "Js_Material.h"

namespace Js
{
	using resourceList = std::map<std::wstring, std::shared_ptr<BaseResource>>;
	std::array<resourceList, RESOURCE_TYPE_COUNT> ResourceManager::m_Resources = {};

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
		{
			auto mesh = std::make_shared<Mesh>(m_Device);
			mesh->SetName(L"Rectangle");
			mesh->CreateDefaultRectangle();

			Add(mesh->GetName(), mesh);
		}
	}
	void ResourceManager::createDefaultShader()
	{
		{
			auto vertexShader = std::make_shared<VertexShader>(m_Device);
			vertexShader->Create(L"Default.hlsl", "VS", "vs_5_0");

			auto inputLayout = std::make_shared<InputLayout>(m_Device);
			inputLayout->Create(VertexTextureData::descs, vertexShader->GetBlob());

			auto pixelShader = std::make_shared<PixelShader>(m_Device);
			pixelShader->Create(L"Default.hlsl", "PS", "ps_5_0");

			std::shared_ptr<Shader> shader = std::make_shared<Shader>();
			shader->SetName(L"Default");
			shader->SetVertexShadaer(vertexShader);
			shader->SetPixelShader(pixelShader);
			shader->SetInputLayout(inputLayout);
			
			Add(shader->GetName(), shader);
		}
	}
	void ResourceManager::createDefaultTexture()
	{
		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"Default");
			texture->Create(L"1.bmp");

			Add(texture->GetName(), texture);
		}
		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"bg");
			texture->Create(L"bg_blue.jpg");

			Add(texture->GetName(), texture);
		}
		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"Snake");
			texture->Create(L"Snake.bmp");

			Add(texture->GetName(), texture);
		}
		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"Chicken");
			texture->Create(L"ChickenAlpha.bmp");

			Add(texture->GetName(), texture);
		}
		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"Mario");
			texture->Create(L"Mario_nomal.gif");

			Add(texture->GetName(), texture);
		}
	}
	void ResourceManager::createDefaultMaterial()
	{
		{
			auto material = std::make_shared<Material>();
			material->SetName(L"Default");
			material->SetShader(Get<Shader>(L"Default"));
			material->SetTexture(Get<Texture>(L"Default"));
			
			Add(material->GetName(), material);
		}
		{
			auto material = std::make_shared<Material>();
			material->SetName(L"bg");
			material->SetShader(Get<Shader>(L"Default"));
			material->SetTexture(Get<Texture>(L"bg"));

			Add(material->GetName(), material);
		}
	}
	void ResourceManager::createDefaultAnimation()
	{
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"SnakeAni");
			animation->SetTexture(Get<Texture>(L"Snake"));
			animation->SetLoop(true);

			animation->AddKeyframe(Keyframe{ Vector2{0.f, 0.f},  Vector2{100.f, 100.f}, 0.1f });
			animation->AddKeyframe(Keyframe{ Vector2{100.f, 0.f}, Vector2{100.f, 100.f}, 0.1f });
			animation->AddKeyframe(Keyframe{ Vector2{200.f, 0.f}, Vector2{100.f, 100.f}, 0.1f });
			animation->AddKeyframe(Keyframe{ Vector2{300.f, 0.f}, Vector2{100.f, 100.f}, 0.1f });

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"ChickenAni");
			animation->SetTexture(Get<Texture>(L"Chicken"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), 4, 0.1f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"MarioAni");
			animation->SetTexture(Get<Texture>(L"Mario"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(50.0f, 0.0f), Vector2(50.0f, 80.0f), 5, 0.1f);

			Add(animation->GetName(), animation);
		}
	}
	void ResourceManager::createDefaultSound()
	{
	}
}