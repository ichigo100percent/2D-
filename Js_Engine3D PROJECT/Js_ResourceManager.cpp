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

		createBlockTexture();
		createMonsterTextrue();
		createMarioTexture();
		createMarioMaterial();
		createMonsterAnimation();
		createMarioAnimation();
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
			texture->Create(L"mario.png");

			Add(texture->GetName(), texture);
		}
		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"Map");
			texture->Create(L"../../Res/Sprite/map.png");

			Add(texture->GetName(), texture);
		}
		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"Mario1");
			texture->Create(L"../../Res/Mario/마리오.png");

			Add(texture->GetName(), texture);
		}
		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"Title");
			texture->Create(L"title.jpg");

			Add(texture->GetName(), texture);
		}
		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"Mario2");
			texture->Create(L"마리오2.png");

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
			material->SetName(L"Map");
			material->SetShader(Get<Shader>(L"Default"));
			material->SetTexture(Get<Texture>(L"Map"));

			Add(material->GetName(), material);
		}
		{
			auto material = std::make_shared<Material>();
			material->SetName(L"Title");
			material->SetShader(Get<Shader>(L"Default"));
			material->SetTexture(Get<Texture>(L"Title"));

			Add(material->GetName(), material);
		}
		{
			auto material = std::make_shared<Material>();
			material->SetName(L"마리오2");
			material->SetShader(Get<Shader>(L"Default"));
			material->SetTexture(Get<Texture>(L"Mario2"));

			Add(material->GetName(), material);
		}
	}
	void ResourceManager::createDefaultAnimation()
	{
		//{
		//	auto animation = std::make_shared<Animation>();
		//	animation->SetName(L"Mario1_Idle");
		//	animation->SetTexture(Get<Texture>(L"Mario1"));
		//	animation->SetLoop(true);

		//	animation->SetKeyFrame(Vector2(0.0f, 0.0f), Vector2(16.0f, 16.0f), 1, 0.1f);

		//	Add(animation->GetName(), animation);
		//}
		//{
		//	auto animation = std::make_shared<Animation>();
		//	animation->SetName(L"Mario1_Right_Move");
		//	animation->SetTexture(Get<Texture>(L"Mario1"));
		//	animation->SetLoop(true);

		//	animation->SetKeyFrame(Vector2(32.0f, 0.0f), Vector2(16.0f, 16.0f), 3, 0.07f);

		//	Add(animation->GetName(), animation);
		//}
		//{
		//	auto animation = std::make_shared<Animation>();
		//	animation->SetName(L"Mario1_Left_Move");
		//	animation->SetTexture(Get<Texture>(L"Mario1"));
		//	animation->SetLoop(true);

		//	animation->SetKeyFrame(Vector2(32.0f, 0.0f), Vector2(16.0f, 16.0f), 3, 0.07f);

		//	Add(animation->GetName(), animation);
		//}
		//{
		//	auto animation = std::make_shared<Animation>();
		//	animation->SetName(L"Mario1_Jump");
		//	animation->SetTexture(Get<Texture>(L"Mario1"));
		//	animation->SetLoop(false);

		//	animation->SetKeyFrame(Vector2(96.0f, 0.0f), Vector2(16.0f, 16.0f), 1, 0.1f);

		//	Add(animation->GetName(), animation);
		//}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"김서영");
			animation->SetTexture(Get<Texture>(L"김서영"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(0.0f, 0.0f), Vector2(16.0f, 16.0f), 7, 1.f);

			Add(animation->GetName(), animation);
		}
	}
	void ResourceManager::createDefaultSound()
	{
	}
	void ResourceManager::createBlockTexture()
	{
		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"Block1");
			texture->Create(L"../../Res/Sprite/block1.png");

			Add(texture->GetName(), texture);
		}
		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"Block2");
			texture->Create(L"../../Res/Sprite/block2.png");

			Add(texture->GetName(), texture);
		}
		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"Block3");
			texture->Create(L"../../Res/Sprite/block3.png");

			Add(texture->GetName(), texture);
		}
	}
	void ResourceManager::createMonsterTextrue()
	{
		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"굼바");
			texture->Create(L"../../Res/Sprite/굼바.png");

			Add(texture->GetName(), texture);
		}
		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"엉금엉금");
			texture->Create(L"../../Res/Sprite/엉금엉금.png");

			Add(texture->GetName(), texture);
		}
		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"껍질");
			texture->Create(L"../../Res/Sprite/껍질.png");

			Add(texture->GetName(), texture);
		}
	}
	void ResourceManager::createMarioTexture()
	{

		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"마리오");
			texture->Create(L"../../Res/Sprite/마리오.png");

			Add(texture->GetName(), texture);
		}

		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"마리오2");
			texture->Create(L"../../Res/Sprite/마리오2.png");

			Add(texture->GetName(), texture);
		}
	}
	void ResourceManager::createMarioMaterial()
	{
		{
			auto material = std::make_shared<Material>();
			material->SetName(L"Block1");
			material->SetShader(Get<Shader>(L"Default"));
			material->SetTexture(Get<Texture>(L"Block1"));

			Add(material->GetName(), material);
		}
		{
			auto material = std::make_shared<Material>();
			material->SetName(L"Block2");
			material->SetShader(Get<Shader>(L"Default"));
			material->SetTexture(Get<Texture>(L"Block2"));

			Add(material->GetName(), material);
		}
		{
			auto material = std::make_shared<Material>();
			material->SetName(L"Block3");
			material->SetShader(Get<Shader>(L"Default"));
			material->SetTexture(Get<Texture>(L"Block3"));

			Add(material->GetName(), material);
		}
	}
	void ResourceManager::createMonsterAnimation()
	{

	}
	void ResourceManager::createMarioAnimation()
	{
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"Mario_rightMove");
			animation->SetTexture(Get<Texture>(L"마리오"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(32.0f, 0.0f), Vector2(16.0f, 16.0f), 3, 0.07f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"Mario_leftMove");
			animation->SetTexture(Get<Texture>(L"마리오"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(80.0f, 0.0f), Vector2(-16.0f, 16.0f), 3, 0.07f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"Mario_leftIdle");
			animation->SetTexture(Get<Texture>(L"마리오2"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(96.0f, 0.0f), Vector2(16.0f, 16.0f), 1, 0.07f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"Mario_rightIdle");
			animation->SetTexture(Get<Texture>(L"마리오"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(0.0f, 0.0f), Vector2(16.0f, 16.0f), 1, 0.07f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"Mario_die");
			animation->SetTexture(Get<Texture>(L"마리오"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(15.0f, 0.0f), Vector2(16.0f, 16.0f), 1, 0.07f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"Mario_leftJump");
			animation->SetTexture(Get<Texture>(L"마리오2"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(0.0f, 0.0f), Vector2(16.0f, 16.0f), 1, 0.07f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"Mario_rightJump");
			animation->SetTexture(Get<Texture>(L"마리오"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(96.0f, 0.0f), Vector2(16.0f, 16.0f), 1, 0.07f);

			Add(animation->GetName(), animation);
		}
	}
}