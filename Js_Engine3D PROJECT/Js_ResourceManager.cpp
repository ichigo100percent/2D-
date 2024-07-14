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
		createSuperMarioAnimation();
		createFireMarioAnimation();
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

		{
			auto vertexShader = std::make_shared<VertexShader>(m_Device);
			vertexShader->Create(L"Nomal.hlsl", "VS", "vs_5_0");

			auto inputLayout = std::make_shared<InputLayout>(m_Device);
			inputLayout->Create(VertexTextureData::descs, vertexShader->GetBlob());

			auto pixelShader = std::make_shared<PixelShader>(m_Device);
			pixelShader->Create(L"Nomal.hlsl", "PS", "ps_5_0");

			std::shared_ptr<Shader> shader = std::make_shared<Shader>();
			shader->SetName(L"Nomal");
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
			texture->SetName(L"paka");
			texture->Create(L"paka.jpg");

			Add(texture->GetName(), texture);
		}
		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"dopa");
			texture->Create(L"dopa.jpg");

			Add(texture->GetName(), texture);
		}
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
			texture->Create(L"../../Res/Mario/¸¶¸®¿À.png");

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
			texture->Create(L"¸¶¸®¿À2.png");

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
			material->SetName(L"¸¶¸®¿À2");
			material->SetShader(Get<Shader>(L"Default"));
			material->SetTexture(Get<Texture>(L"Mario2"));

			Add(material->GetName(), material);
		}
		{
			auto material = std::make_shared<Material>();
			material->SetName(L"paka");
			material->SetShader(Get<Shader>(L"Nomal"));
			material->SetTexture(Get<Texture>(L"paka"));

			Add(material->GetName(), material);
		}
		{
			auto material = std::make_shared<Material>();
			material->SetName(L"dopa");
			material->SetShader(Get<Shader>(L"Nomal"));
			material->SetTexture(Get<Texture>(L"dopa"));

			Add(material->GetName(), material);
		}
	}
	void ResourceManager::createDefaultAnimation()
	{

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
		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"Block4");
			texture->Create(L"../../Res/Sprite/block4.png");

			Add(texture->GetName(), texture);
		}
		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"¹ö¼¸");
			texture->Create(L"../../Res/Sprite/¹ö¼¸.png");

			Add(texture->GetName(), texture);
		}
		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"²É");
			texture->Create(L"../../Res/Sprite/²É.png");

			Add(texture->GetName(), texture);
		}
		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"ºÒ²É");
			texture->Create(L"../../Res/Sprite/ºÒ²É.png");

			Add(texture->GetName(), texture);
		}
		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"¿£µù");
			texture->Create(L"../../Res/Sprite/ending.jpg");

			Add(texture->GetName(), texture);
		}
	}
	void ResourceManager::createMonsterTextrue()
	{
		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"±À¹Ù");
			texture->Create(L"../../Res/Sprite/±À¹Ù.png");

			Add(texture->GetName(), texture);
		}
		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"¾û±Ý¾û±Ý");
			texture->Create(L"../../Res/Sprite/¾û±Ý¾û±Ý.png");

			Add(texture->GetName(), texture);
		}
		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"²®Áú");
			texture->Create(L"../../Res/Sprite/²®Áú.png");

			Add(texture->GetName(), texture);
		}
	}
	void ResourceManager::createMarioTexture()
	{

		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"¸¶¸®¿À");
			texture->Create(L"../../Res/Sprite/¸¶¸®¿À.png");

			Add(texture->GetName(), texture);
		}

		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"¸¶¸®¿À2");
			texture->Create(L"../../Res/Sprite/¸¶¸®¿À2.png");

			Add(texture->GetName(), texture);
		}
		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"½´ÆÛ¸¶¸®¿À_R");
			texture->Create(L"../../Res/Sprite/½´ÆÛ¸¶¸®¿À_¿À¸¥ÂÊ.png");

			Add(texture->GetName(), texture);
		}
		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"½´ÆÛ¸¶¸®¿À_L");
			texture->Create(L"../../Res/Sprite/½´ÆÛ¸¶¸®¿À_¿ÞÂÊ.png");

			Add(texture->GetName(), texture);
		}
		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"¸¶¸®¿ÀÁøÈ­_R");
			texture->Create(L"../../Res/Sprite/¸¶¸®¿ÀÁøÈ­_¿À.png");

			Add(texture->GetName(), texture);
		}
		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"¸¶¸®¿ÀÁøÈ­_L");
			texture->Create(L"../../Res/Sprite/¸¶¸®¿ÀÁøÈ­_¿Þ.png");

			Add(texture->GetName(), texture);
		}
		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"ÆÄÀÌ¾î¸¶¸®¿À_L");
			texture->Create(L"../../Res/Sprite/ÆÄÀÌ¾î¸¶¸®¿À_¿ÞÂÊ.png");

			Add(texture->GetName(), texture);
		}
		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"ÆÄÀÌ¾î¸¶¸®¿À_R");
			texture->Create(L"../../Res/Sprite/ÆÄÀÌ¾î¸¶¸®¿À_¿À¸¥ÂÊ.png");

			Add(texture->GetName(), texture);
		}
		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"¸¶¸®¿À_±ê¹ß");
			texture->Create(L"../../Res/Sprite/¸¶¸®¿À_±ê¹ß.png");

			Add(texture->GetName(), texture);
		}
		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"½´ÆÛ¸¶¸®¿À_±ê¹ß");
			texture->Create(L"../../Res/Sprite/½´ÆÛ¸¶¸®¿À_±ê¹ß.png");

			Add(texture->GetName(), texture);
		}
		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"ÆÄÀÌ¾î¸¶¸®¿À_±ê¹ß");
			texture->Create(L"../../Res/Sprite/ÆÄÀÌ¾î¸¶¸®¿À_±ê¹ß.png");

			Add(texture->GetName(), texture);
		}
	}
	void ResourceManager::createSuperMarioTexture()
	{

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
		{
			auto material = std::make_shared<Material>();
			material->SetName(L"Block4");
			material->SetShader(Get<Shader>(L"Default"));
			material->SetTexture(Get<Texture>(L"Block4"));

			Add(material->GetName(), material);
		}
		{
			auto material = std::make_shared<Material>();
			material->SetName(L"¹ö¼¸");
			material->SetShader(Get<Shader>(L"Default"));
			material->SetTexture(Get<Texture>(L"¹ö¼¸"));

			Add(material->GetName(), material);
		}
		{
			auto material = std::make_shared<Material>();
			material->SetName(L"²É");
			material->SetShader(Get<Shader>(L"Default"));
			material->SetTexture(Get<Texture>(L"²É"));

			Add(material->GetName(), material);
		}
		{
			auto material = std::make_shared<Material>();
			material->SetName(L"ºÒ²É");
			material->SetShader(Get<Shader>(L"Default"));
			material->SetTexture(Get<Texture>(L"ºÒ²É"));

			Add(material->GetName(), material);
		}
		{
			auto material = std::make_shared<Material>();
			material->SetName(L"¿£µù");
			material->SetShader(Get<Shader>(L"Nomal"));
			material->SetTexture(Get<Texture>(L"¿£µù"));

			Add(material->GetName(), material);
		}
	}
	void ResourceManager::createMonsterAnimation()
	{
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"±À¹Ù");
			animation->SetTexture(Get<Texture>(L"±À¹Ù"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(0.0f, 0.0f), Vector2(16.0f, 16.0f), 2, 0.1f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"±À¹ÙÁ×À½");
			animation->SetTexture(Get<Texture>(L"±À¹Ù"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(32.0f, 0.0f), Vector2(16.0f, 16.0f), 1, 0.1f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"²®Áú");
			animation->SetTexture(Get<Texture>(L"²®Áú"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(0.0f, 0.0f), Vector2(16.0f, 16.0f), 1, 0.1f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"¾û±Ý¾û±Ý");
			animation->SetTexture(Get<Texture>(L"¾û±Ý¾û±Ý"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(0.0f, 0.0f), Vector2(16.0f, 24.0f), 2, 0.1f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"¾û±Ý¾û±Ý2");
			animation->SetTexture(Get<Texture>(L"¾û±Ý¾û±Ý"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(32.0f, 0.0f), Vector2(16.0f, 24.0f), 2, 0.1f);

			Add(animation->GetName(), animation);
		}
	}
	void ResourceManager::createMarioAnimation()
	{
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"Mario_rightMove");
			animation->SetTexture(Get<Texture>(L"¸¶¸®¿À"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(32.0f, 0.0f), Vector2(16.0f, 16.0f), 3, 0.07f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"Mario_leftMove");
			animation->SetTexture(Get<Texture>(L"¸¶¸®¿À"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(80.0f, 0.0f), Vector2(-16.0f, 16.0f), 3, 0.07f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"Mario_leftIdle");
			animation->SetTexture(Get<Texture>(L"¸¶¸®¿À2"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(96.0f, 0.0f), Vector2(16.0f, 16.0f), 1, 0.07f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"Mario_rightIdle");
			animation->SetTexture(Get<Texture>(L"¸¶¸®¿À"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(0.0f, 0.0f), Vector2(16.0f, 16.0f), 1, 0.07f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"Mario_die");
			animation->SetTexture(Get<Texture>(L"¸¶¸®¿À"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(15.0f, 0.0f), Vector2(16.0f, 16.0f), 1, 0.07f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"Mario_leftJump");
			animation->SetTexture(Get<Texture>(L"¸¶¸®¿À2"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(0.0f, 0.0f), Vector2(16.0f, 16.0f), 1, 0.07f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"Mario_rightJump");
			animation->SetTexture(Get<Texture>(L"¸¶¸®¿À"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(96.0f, 0.0f), Vector2(16.0f, 16.0f), 1, 0.07f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"Mario_flag");
			animation->SetTexture(Get<Texture>(L"¸¶¸®¿À_±ê¹ß"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(0.0f, 0.0f), Vector2(16.0f, 16.0f), 1, 0.07f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"SuperMario_flag");
			animation->SetTexture(Get<Texture>(L"½´ÆÛ¸¶¸®¿À_±ê¹ß"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(0.0f, 0.0f), Vector2(16.0f, 32.0f), 1, 0.07f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"FireMario_flag");
			animation->SetTexture(Get<Texture>(L"ÆÄÀÌ¾î¸¶¸®¿À_±ê¹ß"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(0.0f, 0.0f), Vector2(16.0f, 32.0f), 1, 0.07f);

			Add(animation->GetName(), animation);
		}
	}
	void ResourceManager::createSuperMarioAnimation()
	{
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"SuperMario_R");
			animation->SetTexture(Get<Texture>(L"¸¶¸®¿ÀÁøÈ­_R"));
			animation->SetLoop(true);

			animation->AddKeyframe(Keyframe{ Vector2{0.f, 0.f}, Vector2{16.f, 16.f}, 0.1f });
			animation->AddKeyframe(Keyframe{ Vector2{0.f, 16.f}, Vector2{16.f, 32.f}, 0.1f });

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"SuperMario_L");
			animation->SetTexture(Get<Texture>(L"¸¶¸®¿ÀÁøÈ­_L"));
			animation->SetLoop(true);

			animation->AddKeyframe(Keyframe{ Vector2{0.f, 0.f}, Vector2{16.f, 16.f}, 0.1f });
			animation->AddKeyframe(Keyframe{ Vector2{0.f, 16.f}, Vector2{16.f, 32.f}, 0.1f });

			Add(animation->GetName(), animation);
		}

		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"SuperMario_rightIdle");
			animation->SetTexture(Get<Texture>(L"½´ÆÛ¸¶¸®¿À_R"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(0.0f, 0.0f), Vector2(16.0f, 32.0f), 1, 0.1f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"SuperMario_leftIdle");
			animation->SetTexture(Get<Texture>(L"½´ÆÛ¸¶¸®¿À_L"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(96.0f, 0.0f), Vector2(16.0f, 32.0f), 1, 0.1f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"SuperMario_rightMove");
			animation->SetTexture(Get<Texture>(L"½´ÆÛ¸¶¸®¿À_R"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(32.0f, 0.0f), Vector2(16.0f, 32.0f), 3, 0.1f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"SuperMario_leftMove");
			animation->SetTexture(Get<Texture>(L"½´ÆÛ¸¶¸®¿À_L"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(32.0f, 0.0f), Vector2(16.0f, 32.0f), 3, 0.1f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"SuperMario_rightJump");
			animation->SetTexture(Get<Texture>(L"½´ÆÛ¸¶¸®¿À_R"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(96.0f, 0.0f), Vector2(16.0f, 32.0f), 1, 0.1f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"SuperMario_leftJump");
			animation->SetTexture(Get<Texture>(L"½´ÆÛ¸¶¸®¿À_L"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(0.0f, 0.0f), Vector2(16.0f, 32.0f), 1, 0.1f);

			Add(animation->GetName(), animation);
		}
	}
	void ResourceManager::createFireMarioAnimation()
	{
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"FireMario_rightIdle");
			animation->SetTexture(Get<Texture>(L"ÆÄÀÌ¾î¸¶¸®¿À_R"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(0.0f, 0.0f), Vector2(16.0f, 32.0f), 1, 0.1f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"FireMario_leftIdle");
			animation->SetTexture(Get<Texture>(L"ÆÄÀÌ¾î¸¶¸®¿À_L"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(96.0f, 0.0f), Vector2(16.0f, 32.0f), 1, 0.1f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"FireMario_rightMove");
			animation->SetTexture(Get<Texture>(L"ÆÄÀÌ¾î¸¶¸®¿À_R"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(32.0f, 0.0f), Vector2(16.0f, 32.0f), 3, 0.1f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"FireMario_leftMove");
			animation->SetTexture(Get<Texture>(L"ÆÄÀÌ¾î¸¶¸®¿À_L"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(32.0f, 0.0f), Vector2(16.0f, 32.0f), 3, 0.1f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"FireMario_rightJump");
			animation->SetTexture(Get<Texture>(L"ÆÄÀÌ¾î¸¶¸®¿À_R"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(96.0f, 0.0f), Vector2(16.0f, 32.0f), 1, 0.1f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"FireMario_leftJump");
			animation->SetTexture(Get<Texture>(L"ÆÄÀÌ¾î¸¶¸®¿À_L"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(0.0f, 0.0f), Vector2(16.0f, 32.0f), 1, 0.1f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"ºÒ²É¹ß½Î");
			animation->SetTexture(Get<Texture>(L"ºÒ²É"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(0.0f, 0.0f), Vector2(15.0f, 16.0f), 1, 0.1f);

			Add(animation->GetName(), animation);
		}
	}
}