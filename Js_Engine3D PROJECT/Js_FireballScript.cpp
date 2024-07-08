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
        float gravity = -980.0f * Time::DeltaTime();
        auto position = GetOwner()->GetTransform()->GetPosition();

        // 방향에 따라 위치 업데이트
        position.x += m_Direction.x * speed;
        position.y += gravity;

        if (!isGround)
        {
            m_Velocity.y += gravity; // 중력 적용
        }

        position.y += m_Velocity.y * Time::DeltaTime();

        GetOwner()->GetTransform()->SetPosition(position);
    }

    void FireballScript::OnCollisionEnter(std::shared_ptr<Collider> _other)
    {
        if (_other->GetOwner()->GetLayerType() == LayerType::Floor)
        {
            isGround = true;

            // 바닥에 닿으면 튀게 만들기, 속도를 줄임
            m_Velocity.y = 1250.0f; // 위로 튀어 오르게 설정 (중력 반대 방향 속도)
            isGround = false;
        }
        if (_other->GetOwner()->GetLayerType() == LayerType::Wall)
        {
            object::Destroy(GetOwner());
        }
        if (_other->GetOwner()->GetLayerType() == LayerType::Monster)
        {
            object::Destroy(_other->GetOwner());
            object::Destroy(GetOwner());
        }
    }
    void FireballScript::OnCollisionStay(std::shared_ptr<Collider> _other)
    {
    }
    void FireballScript::OnCollisionExit(std::shared_ptr<Collider> _other)
    {

    }
}