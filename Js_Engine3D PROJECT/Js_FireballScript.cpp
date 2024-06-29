#include "Js_FireballScript.h"
#include "Js_Core.h"
#include "Js_DxObject.h"
#include "Js_Input.h"
#include "Js_Time.h"
#include "Js_Transform.h"
#include "Js_SceneManager.h"
#include "Js_Object.h"
#include "Js_Fireball.h"
#include "Js_Player.h"

namespace Js
{
	void FireballScript::Update()
	{
        m_DeathTime += Time::DeltaTime();

		if (Input::KeyCheck(VK_SPACE) == KeyState::KEY_PUSH)
		{
			ShootFireball();
		}
        if (m_DeathTime > 3.f)
        {
            if(fireball)
                object::Destory(fireball);
        }
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
            fireball->GetTransform()->SetScale(fireball->GetSize());

            fireball->GetTransform()->SetPosition(offsetPosition);
            fireball->GetTransform()->SetForward2D(playerDirection);
        }

	}
}