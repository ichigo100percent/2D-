#include "Js_FireballScript.h"
#include "Js_Fireball.h"
#include "Js_PlayerScript.h"
#include "Js_Input.h"
#include "Js_Time.h"
#include "Js_DxObject.h"
#include "Js_Transform.h"
#include "Js_MeshRenderer.h"
#include "Js_Object.h"
#include "Js_Rigidbody.h"
#include "Js_Animation.h"
#include "Js_Player.h"
#include "Js_SceneManager.h"
#include "Js_PlayScene.h"
#include "Js_TitleScene.h"
#include "Js_MushroomWallScript.h"

#include "Js_GoombaScript.h"
#include "Js_CollisionManager.h"

namespace Js
{
    FireballScript::FireballScript(std::shared_ptr<DxObject> _owner, Vector3 _pos)
        : m_Owner(_owner) , m_Direction(_pos)
    {
    }
    void FireballScript::Update()
    {
		float speed = 500 * Time::DeltaTime();
		float gravity = -300.0f * Time::DeltaTime();
		auto position = GetOwner()->GetTransform()->GetPosition();

		// ���⿡ ���� ��ġ ������Ʈ
		position.x += m_Direction.x * speed;
		position.y += gravity;

		GetOwner()->GetTransform()->SetPosition(position);
    }
    void FireballScript::OnCollisionEnter(std::shared_ptr<Collider> _other)
    {
        if (_other->GetOwner()->GetLayerType() == LayerType::Floor)
        {
			// y�� ����
			auto position = GetOwner()->GetTransform()->GetPosition();
			position.y += 30.0f; // ���� ���� ����
			GetOwner()->GetTransform()->SetPosition(position);
        }
    }
    void FireballScript::OnCollisionStay(std::shared_ptr<Collider> _other)
    {
    }
    void FireballScript::OnCollisionExit(std::shared_ptr<Collider> _other)
    {
    }

    /*
	void FireballScript::Update()
	{
        m_DeathTime += Time::DeltaTime();

		if (Input::KeyCheck(VK_SPACE) == KeyState::KEY_PUSH)
		{
			ShootFireball();
		}
	}
    void FireballScript::OnCollisionEnter(std::shared_ptr<Collider> _other)
    {
        if (_other->GetOwner()->GetLayerType() == LayerType::Monster)
        {
            object::Destroy(fireball);
        }
    }
    void FireballScript::OnCollisionStay(std::shared_ptr<Collider> _other)
    {
    }
    void FireballScript::OnCollisionExit(std::shared_ptr<Collider> _other)
    {
    }
	void FireballScript::ShootFireball()
	{
        auto player = m_Player.lock();
        if (!player)
            return;

        // �÷��̾��� ��ġ�� ���� ��������
        Vector3 playerPosition = player->GetTransform()->GetPosition();
        Vector3 playerDirection = player->GetDirection();
        Vector3 playerSize = player->GetTransform()->GetScale();

        // �÷��̾� ũ�⸸ŭ ������ ��ġ ���
        Vector3 offsetPosition = playerPosition + (playerDirection * playerSize.Length());

        // Fireball ��ü ���� �� �ʱ�ȭ
        fireball = object::Instantiate<Fireball>(L"Fireball");
        {
            auto meshRender = std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext());
            fireball->AddComponent(meshRender);
            auto mesh = I_Resource->Get<Mesh>(L"Rectangle");
            meshRender->SetMesh(mesh);
            auto material = I_Resource->Get<Material>(L"Default");
            meshRender->SetMaterial(material);
            fireball->GetTransform()->SetScale(Vector3(16, 16, 0));

            fireball->GetTransform()->SetPosition(offsetPosition);
            fireball->GetTransform()->SetForward2D(playerDirection);

            auto animator = std::make_shared<Animator>();
            auto anim = I_Resource->Get<Animation>(L"�Ҳɹ߽�");
            animator->SetAnimation(anim);
            fireball->AddComponent(animator);
        }

	}
    */

    

    //FireballScript::FireballScript(std::shared_ptr<DxObject> _owner, Vector3 _pos)
    //    : m_Owner(_owner)
    //    , m_Direction(_pos)
    //{
    //}

    //FireballScript::~FireballScript()
    //{
    //}

    //void FireballScript::Init()
    //{     
    //    
    //}

    //void FireballScript::Update()
    //{
    //    float speed = 500 * Time::DeltaTime();
    //    float gravity = -500.0f * Time::DeltaTime();
    //    auto position = GetOwner()->GetTransform()->GetPosition();

    //    // ���⿡ ���� ��ġ ������Ʈ
    //    position.x += m_Direction.x * speed;
    //    position.y += gravity;

    //    GetOwner()->GetTransform()->SetPosition(position);
    //}

    //void FireballScript::OnCollisionEnter(std::shared_ptr<Collider> _other)
    //{
    //    auto type = _other->GetOwner()->GetLayerType();

    //    if (type == enums::LayerType::Floor)
    //    {
    //        // y�� ����
    //        auto position = GetOwner()->GetTransform()->GetPosition();
    //        position.y += 300.0f; // ���� ���� ����
    //        GetOwner()->GetTransform()->SetPosition(position);
    //    }
    //}

    //void FireballScript::OnCollisionStay(std::shared_ptr<Collider> _other)
    //{
    //}

    //void FireballScript::OnCollisionExit(std::shared_ptr<Collider> _other)
    //{
    //}
    //

    
}