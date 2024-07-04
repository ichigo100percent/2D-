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

namespace Js
{
    PlayerScript::PlayerScript(std::shared_ptr<DxObject> _player)
        : m_Player(_player)
    {
    }
    PlayerScript::~PlayerScript()
    {
    }
    void PlayerScript::Init()
	{
		m_Animator = GetOwner()->GetAnimator();
		m_Rigidbody = GetOwner()->GetComponent<Rigidbody>();
		m_State = Js::State::Idle;       
	}
    void PlayerScript::Update()
    {
        if (m_Animator == nullptr)
            m_Animator = GetOwner()->GetAnimator();

        auto rb = GetOwner()->GetComponent<Rigidbody>();
        bool isGrounded = rb->IsGrounded();
        if (Input::KeyCheck('A') == KeyState::KEY_HOLD)
        {
            if (!isJump)
            {
                auto anim = I_Resource->Get<Animation>(L"Mario_leftMove");
                m_Animator->SetAnimation(anim);
            }
            rb->AddForce(Vector3(-1000, 0, 0));
            isFacingRight = false; // 왼쪽을 향하고 있음
        }
        if (Input::KeyCheck('A') == KeyState::KEY_UP)
        {
            if (!isJump)
            {
                auto anim = I_Resource->Get<Animation>(L"Mario_leftIdle");
                m_Animator->SetAnimation(anim);
            }
        }
        if (Input::KeyCheck('D') == KeyState::KEY_HOLD)
        {
            if (!isJump)
            {
                auto anim = I_Resource->Get<Animation>(L"Mario_rightMove");
                m_Animator->SetAnimation(anim);
            }
            rb->AddForce(Vector3(1000, 0, 0));
            isFacingRight = true; // 오른쪽을 향하고 있음
        }
        if (Input::KeyCheck('D') == KeyState::KEY_UP)
        {
            if (!isJump)
            {
                auto anim = I_Resource->Get<Animation>(L"Mario_rightIdle");
                m_Animator->SetAnimation(anim);
            }
        }
        if (Input::KeyCheck('W') == KeyState::KEY_HOLD)
        {
            if (isFacingRight)
            {
                auto anim = I_Resource->Get<Animation>(L"Mario_rightJump");
                m_Animator->SetAnimation(anim);
            }
            else
            {
                auto anim = I_Resource->Get<Animation>(L"Mario_leftJump");
                m_Animator->SetAnimation(anim);
            }
            rb->Jump(600.0f); // 점프 힘 설정
            isJump = true;
        }

        rb->SetGrounded(false);
    }

    void PlayerScript::OnCollisionEnter(std::shared_ptr<Collider> _other)
    {
        HandleCollision(_other); 
        growUp(_other);
    }

    void PlayerScript::OnCollisionStay(std::shared_ptr<Collider> _other)
    {
        HandleCollision(_other);
    }

    void PlayerScript::OnCollisionExit(std::shared_ptr<Collider> _other)
    {
        auto type = _other->GetOwner()->GetLayerType();
        auto rb = GetOwner()->GetComponent<Rigidbody>();
        if (type == enums::LayerType::Floor || type == enums::LayerType::Wall)
        {
            isJump = false;
        }
    }
    void PlayerScript::HandleCollision(std::shared_ptr<Collider> _other)
    {
        auto type = _other->GetOwner()->GetLayerType();
        auto rb = GetOwner()->GetComponent<Rigidbody>();

        Vector3 pushVector;
        if (Collider::CheckCollision(GetOwner()->GetTransform()->GetRect(), _other->GetOwner()->GetTransform()->GetRect(), pushVector))
        {
            // 충돌 방향으로 밀어내기
            GetOwner()->GetTransform()->SetPosition(GetOwner()->GetTransform()->GetPosition() + pushVector);

            if (type == enums::LayerType::Floor)
            {
                rb->SetGrounded(true); // 땅에 닿았음을 표시
                if (pushVector.y != 0)
                {
                    auto velocity = rb->GetVelocity();
                    velocity.y = 0; // 수직 속도를 0으로 설정
                    rb->SetVelocity(velocity);
                }
            }
            else if (type == enums::LayerType::Wall)
            {
                if (pushVector.y > 0) // 플레이어가 타워 위에 있을 때
                {
                    rb->SetGrounded(true);
                    auto velocity = rb->GetVelocity();
                    velocity.y = 0; // 수직 속도를 0으로 설정
                    rb->SetVelocity(velocity);
                }
                else if (pushVector.y < 0) // 플레이어가 타워 아래에 있을 때
                {
                    rb->SetGrounded(false);
                    auto velocity = rb->GetVelocity();
                    if (velocity.y >= 0) // 플레이어가 위로 올라가는 중이라면
                    {
                        velocity.y = -200; // 즉시 아래로 떨어지게 설정
                        rb->SetVelocity(velocity);
                    }
                }
            }
        }
    }
    void PlayerScript::growUp(std::shared_ptr<Collider> _other)
    {
        auto type = _other->GetOwner()->GetLayerType();

        if (type == enums::LayerType::MunshRoom)
        {
            auto material = I_Resource->Get<Material>(L"마리오2");
            GetOwner()->GetMeshRenderer()->SetMaterial(material);
            GetOwner()->GetTransform()->SetScale(GetOwner()->GetSize());
            auto anim = I_Resource->Get<Animation>(L"슈퍼마리오");
            GetOwner()->GetAnimator()->SetAnimation(anim);
        }
    }
    void PlayerScript::initialize()
    {

    }
}
