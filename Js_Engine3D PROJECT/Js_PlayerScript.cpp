#include "Js_PlayerScript.h"
#include "Js_Input.h"
#include "Js_Time.h"
#include "Js_DxObject.h"
#include "Js_Transform.h"
#include "Js_MeshRenderer.h"
#include "Js_Object.h"
#include "Js_Rigidbody.h"
#include "Js_Animation.h"


namespace Js
{

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
            rb->AddForce(Vector3(-800, 0, 0));
            isFacingRight = false; // ������ ���ϰ� ����
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
            rb->AddForce(Vector3(800, 0, 0));
            isFacingRight = true; // �������� ���ϰ� ����
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
            rb->Jump(600.0f); // ���� �� ����
            isJump = true;
        }

        rb->SetGrounded(false);
    }

    void PlayerScript::OnCollisionEnter(std::shared_ptr<Collider> _other)
    {
        HandleCollision(_other);
    }

    void PlayerScript::OnCollisionStay(std::shared_ptr<Collider> _other)
    {
        HandleCollision(_other);
    }

    void PlayerScript::OnCollisionExit(std::shared_ptr<Collider> _other)
    {
        auto type = _other->GetOwner()->GetLayerType();
        auto rb = GetOwner()->GetComponent<Rigidbody>();
        if (type == enums::LayerType::Floor || type == enums::LayerType::Tower)
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
            // �浹 �������� �о��
            GetOwner()->GetTransform()->SetPosition(GetOwner()->GetTransform()->GetPosition() + pushVector);

            if (type == enums::LayerType::Floor)
            {
                rb->SetGrounded(true); // ���� ������� ǥ��
                if (pushVector.y != 0)
                {
                    auto velocity = rb->GetVelocity();
                    velocity.y = 0; // ���� �ӵ��� 0���� ����
                    rb->SetVelocity(velocity);
                }
            }
            else if (type == enums::LayerType::Tower)
            {
                if (pushVector.y > 0) // �÷��̾ Ÿ�� ���� ���� ��
                {
                    rb->SetGrounded(true);
                    auto velocity = rb->GetVelocity();
                    velocity.y = 0; // ���� �ӵ��� 0���� ����
                    rb->SetVelocity(velocity);
                }
                else if (pushVector.y < 0) // �÷��̾ Ÿ�� �Ʒ��� ���� ��
                {
                    rb->SetGrounded(false);
                    auto velocity = rb->GetVelocity();
                    if (velocity.y >= 0) // �÷��̾ ���� �ö󰡴� ���̶��
                    {
                        velocity.y = -200; // ��� �Ʒ��� �������� ����
                        rb->SetVelocity(velocity);
                    }
                }
            }
        }
    }
}
