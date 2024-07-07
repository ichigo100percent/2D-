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
			texture->Create(L"../../Res/Mario/������.png");

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
			texture->Create(L"������2.png");

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
			material->SetName(L"������2");
			material->SetShader(Get<Shader>(L"Default"));
			material->SetTexture(Get<Texture>(L"Mario2"));

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
			texture->SetName(L"����");
			texture->Create(L"../../Res/Sprite/����.png");

			Add(texture->GetName(), texture);
		}
		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"��");
			texture->Create(L"../../Res/Sprite/��.png");

			Add(texture->GetName(), texture);
		}
		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"�Ҳ�");
			texture->Create(L"../../Res/Sprite/�Ҳ�.png");

			Add(texture->GetName(), texture);
		}
		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"����");
			texture->Create(L"../../Res/Sprite/ending.jpg");

			Add(texture->GetName(), texture);
		}
	}
	void ResourceManager::createMonsterTextrue()
	{
		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"����");
			texture->Create(L"../../Res/Sprite/����.png");

			Add(texture->GetName(), texture);
		}
		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"���ݾ���");
			texture->Create(L"../../Res/Sprite/���ݾ���.png");

			Add(texture->GetName(), texture);
		}
		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"����");
			texture->Create(L"../../Res/Sprite/����.png");

			Add(texture->GetName(), texture);
		}
	}
	void ResourceManager::createMarioTexture()
	{

		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"������");
			texture->Create(L"../../Res/Sprite/������.png");

			Add(texture->GetName(), texture);
		}

		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"������2");
			texture->Create(L"../../Res/Sprite/������2.png");

			Add(texture->GetName(), texture);
		}
		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"���۸�����_R");
			texture->Create(L"../../Res/Sprite/���۸�����_������.png");

			Add(texture->GetName(), texture);
		}
		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"���۸�����_L");
			texture->Create(L"../../Res/Sprite/���۸�����_����.png");

			Add(texture->GetName(), texture);
		}
		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"��������ȭ_R");
			texture->Create(L"../../Res/Sprite/��������ȭ_��.png");

			Add(texture->GetName(), texture);
		}
		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"��������ȭ_L");
			texture->Create(L"../../Res/Sprite/��������ȭ_��.png");

			Add(texture->GetName(), texture);
		}
		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"���̾����_L");
			texture->Create(L"../../Res/Sprite/���̾����_����.png");

			Add(texture->GetName(), texture);
		}
		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"���̾����_R");
			texture->Create(L"../../Res/Sprite/���̾����_������.png");

			Add(texture->GetName(), texture);
		}
		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"������_���");
			texture->Create(L"../../Res/Sprite/������_���.png");

			Add(texture->GetName(), texture);
		}
		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"���۸�����_���");
			texture->Create(L"../../Res/Sprite/���۸�����_���.png");

			Add(texture->GetName(), texture);
		}
		{
			auto texture = std::make_shared<Texture>(m_Device);
			texture->SetName(L"���̾����_���");
			texture->Create(L"../../Res/Sprite/���̾����_���.png");

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
			material->SetName(L"����");
			material->SetShader(Get<Shader>(L"Default"));
			material->SetTexture(Get<Texture>(L"����"));

			Add(material->GetName(), material);
		}
		{
			auto material = std::make_shared<Material>();
			material->SetName(L"��");
			material->SetShader(Get<Shader>(L"Default"));
			material->SetTexture(Get<Texture>(L"��"));

			Add(material->GetName(), material);
		}
		{
			auto material = std::make_shared<Material>();
			material->SetName(L"�Ҳ�");
			material->SetShader(Get<Shader>(L"Default"));
			material->SetTexture(Get<Texture>(L"�Ҳ�"));

			Add(material->GetName(), material);
		}
		{
			auto material = std::make_shared<Material>();
			material->SetName(L"����");
			material->SetShader(Get<Shader>(L"Nomal"));
			material->SetTexture(Get<Texture>(L"����"));

			Add(material->GetName(), material);
		}
	}
	void ResourceManager::createMonsterAnimation()
	{
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"����");
			animation->SetTexture(Get<Texture>(L"����"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(0.0f, 0.0f), Vector2(16.0f, 16.0f), 2, 0.1f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"��������");
			animation->SetTexture(Get<Texture>(L"����"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(32.0f, 0.0f), Vector2(16.0f, 16.0f), 1, 0.1f);

			Add(animation->GetName(), animation);
		}
	}
	void ResourceManager::createMarioAnimation()
	{
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"Mario_rightMove");
			animation->SetTexture(Get<Texture>(L"������"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(32.0f, 0.0f), Vector2(16.0f, 16.0f), 3, 0.07f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"Mario_leftMove");
			animation->SetTexture(Get<Texture>(L"������"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(80.0f, 0.0f), Vector2(-16.0f, 16.0f), 3, 0.07f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"Mario_leftIdle");
			animation->SetTexture(Get<Texture>(L"������2"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(96.0f, 0.0f), Vector2(16.0f, 16.0f), 1, 0.07f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"Mario_rightIdle");
			animation->SetTexture(Get<Texture>(L"������"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(0.0f, 0.0f), Vector2(16.0f, 16.0f), 1, 0.07f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"Mario_die");
			animation->SetTexture(Get<Texture>(L"������"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(15.0f, 0.0f), Vector2(16.0f, 16.0f), 1, 0.07f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"Mario_leftJump");
			animation->SetTexture(Get<Texture>(L"������2"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(0.0f, 0.0f), Vector2(16.0f, 16.0f), 1, 0.07f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"Mario_rightJump");
			animation->SetTexture(Get<Texture>(L"������"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(96.0f, 0.0f), Vector2(16.0f, 16.0f), 1, 0.07f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"Mario_flag");
			animation->SetTexture(Get<Texture>(L"������_���"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(0.0f, 0.0f), Vector2(16.0f, 16.0f), 1, 0.07f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"SuperMario_flag");
			animation->SetTexture(Get<Texture>(L"���۸�����_���"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(0.0f, 0.0f), Vector2(16.0f, 32.0f), 1, 0.07f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"FireMario_flag");
			animation->SetTexture(Get<Texture>(L"���̾����_���"));
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
			animation->SetTexture(Get<Texture>(L"��������ȭ_R"));
			animation->SetLoop(true);

			animation->AddKeyframe(Keyframe{ Vector2{0.f, 0.f}, Vector2{16.f, 16.f}, 0.1f });
			animation->AddKeyframe(Keyframe{ Vector2{0.f, 16.f}, Vector2{16.f, 32.f}, 0.1f });

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"SuperMario_L");
			animation->SetTexture(Get<Texture>(L"��������ȭ_L"));
			animation->SetLoop(true);

			animation->AddKeyframe(Keyframe{ Vector2{0.f, 0.f}, Vector2{16.f, 16.f}, 0.1f });
			animation->AddKeyframe(Keyframe{ Vector2{0.f, 16.f}, Vector2{16.f, 32.f}, 0.1f });

			Add(animation->GetName(), animation);
		}

		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"SuperMario_rightIdle");
			animation->SetTexture(Get<Texture>(L"���۸�����_R"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(0.0f, 0.0f), Vector2(16.0f, 32.0f), 1, 0.1f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"SuperMario_leftIdle");
			animation->SetTexture(Get<Texture>(L"���۸�����_L"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(96.0f, 0.0f), Vector2(16.0f, 32.0f), 1, 0.1f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"SuperMario_rightMove");
			animation->SetTexture(Get<Texture>(L"���۸�����_R"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(32.0f, 0.0f), Vector2(16.0f, 32.0f), 3, 0.1f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"SuperMario_leftMove");
			animation->SetTexture(Get<Texture>(L"���۸�����_L"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(32.0f, 0.0f), Vector2(16.0f, 32.0f), 3, 0.1f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"SuperMario_rightJump");
			animation->SetTexture(Get<Texture>(L"���۸�����_R"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(96.0f, 0.0f), Vector2(16.0f, 32.0f), 1, 0.1f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"SuperMario_leftJump");
			animation->SetTexture(Get<Texture>(L"���۸�����_L"));
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
			animation->SetTexture(Get<Texture>(L"���̾����_R"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(0.0f, 0.0f), Vector2(16.0f, 32.0f), 1, 0.1f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"FireMario_leftIdle");
			animation->SetTexture(Get<Texture>(L"���̾����_L"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(96.0f, 0.0f), Vector2(16.0f, 32.0f), 1, 0.1f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"FireMario_rightMove");
			animation->SetTexture(Get<Texture>(L"���̾����_R"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(32.0f, 0.0f), Vector2(16.0f, 32.0f), 3, 0.1f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"FireMario_leftMove");
			animation->SetTexture(Get<Texture>(L"���̾����_L"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(32.0f, 0.0f), Vector2(16.0f, 32.0f), 3, 0.1f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"FireMario_rightJump");
			animation->SetTexture(Get<Texture>(L"���̾����_R"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(96.0f, 0.0f), Vector2(16.0f, 32.0f), 1, 0.1f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"FireMario_leftJump");
			animation->SetTexture(Get<Texture>(L"���̾����_L"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(0.0f, 0.0f), Vector2(16.0f, 32.0f), 1, 0.1f);

			Add(animation->GetName(), animation);
		}
		{
			auto animation = std::make_shared<Animation>();
			animation->SetName(L"�Ҳɹ߽�");
			animation->SetTexture(Get<Texture>(L"�Ҳ�"));
			animation->SetLoop(true);

			animation->SetKeyFrame(Vector2(0.0f, 0.0f), Vector2(15.0f, 16.0f), 1, 0.1f);

			Add(animation->GetName(), animation);
		}
	}
}