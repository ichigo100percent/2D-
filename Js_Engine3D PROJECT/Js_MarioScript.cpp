#include "Js_MarioScript.h"
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
    void MarioScript::Init()
    {
        m_Transform = GetOwner()->GetTransform();
        m_Direction = Vector3(0, 0, 0);
        m_Speed = 200.0f; // �������� �ִ� �ӵ�
        m_Acceleration = 100.0f; // �������� ���ӵ�
        m_Gravity = -500.0f; // �߷� ���ӵ�
        m_JumpForce = MinJumpForce; // �⺻ ���� ��
        m_IsGrounded = false; // �ٴڿ� ��� �ִ��� ����
        m_Friction = 50.0f; // ������
        m_Mass = 1.0f; // �������� ���� (����: kg)
        m_JumpTime = 0.0f; // ���� ��ư�� ������ �ð� �ʱ�ȭ
    }

    void MarioScript::Update()
    {
        float deltaTime = Time::DeltaTime();
        Vector3 position = m_Transform->GetPosition();

        // �߷� ����
        if (!m_IsGrounded)
        {
            m_Direction.y += (m_Gravity / m_Mass) * deltaTime; // ������ ���� �߷� ���ӵ�
        }

        // �̵� �Է� ó��
        if (Input::KeyCheck('A') == KeyState::KEY_HOLD)
        {
            m_Direction.x -= (m_Acceleration / m_Mass) * deltaTime; // ������ ���� ���ӵ�
            m_Direction.x = std::max(m_Direction.x, -m_Speed); // �ִ� �ӵ� ����
        }
        if (Input::KeyCheck('D') == KeyState::KEY_HOLD)
        {
            m_Direction.x += (m_Acceleration / m_Mass) * deltaTime; // ������ ���� ���ӵ�
            m_Direction.x = std::min(m_Direction.x, m_Speed); // �ִ� �ӵ� ����
        }

        // ������ ����
        if (Input::KeyCheck('A') == KeyState::KEY_UP || Input::KeyCheck('D') == KeyState::KEY_UP)
        {
            m_Direction.x -= m_Direction.x * (m_Friction / m_Mass) * deltaTime; // ������ ���� ������
        }

        // ���� �Է� ó��
        if (Input::KeyCheck('W') == KeyState::KEY_HOLD && m_IsGrounded)
        {
            m_Direction.y = m_JumpForce / m_Mass; // ������ ���� ���� ��
            m_IsGrounded = false;
        }

        // ��ġ ������Ʈ
        position += m_Direction * deltaTime;
        m_Transform->SetPosition(position);
    }

    void MarioScript::OnCollisionEnter(std::shared_ptr<Collider> _other)
    {
        auto type = _other->GetOwner()->GetLayerType();

        if (type == enums::LayerType::Monster)
        {
            object::Destroy(_other->GetOwner());
        }
        if (type == enums::LayerType::Floor || type == enums::LayerType::Wall)
        {
            // �ٴ� �Ǵ� ���� ������Ƿ� y ���� ����
            m_IsGrounded = true;
            m_Direction.y = 0; // �߷��� �ʱ�ȭ�Ͽ� �� �̻� �Ʒ��� �������� �ʵ��� ��
        }
    }

    void MarioScript::OnCollisionStay(std::shared_ptr<Collider> _other)
    {
        auto type = _other->GetOwner()->GetLayerType();

        if (type == enums::LayerType::Wall)
        {
            HandleCollision(_other);
        }
    }

    void MarioScript::OnCollisionExit(std::shared_ptr<Collider> _other)
    {
        auto type = _other->GetOwner()->GetLayerType();

        if (type == enums::LayerType::Floor || type == enums::LayerType::Wall)
        {
            // �� �ڵ�� �ٴڿ� ���� ���� �������� �ʵ��� ����
            if (!IsGroundedOnFloor())
            {
                m_IsGrounded = false;
            }
        }
    }

    void MarioScript::HandleCollision(std::shared_ptr<Collider> _other)
    {
        auto type = _other->GetOwner()->GetLayerType();

        Vector3 pushVector;
        if (Collider::CheckCollision(GetOwner()->GetTransform()->GetRect(), _other->GetOwner()->GetTransform()->GetRect(), pushVector))
        {
            // �浹 �������� �о��
            GetOwner()->GetTransform()->SetPosition(GetOwner()->GetTransform()->GetPosition() + pushVector);

            if (type == enums::LayerType::Wall)
            {
                if (pushVector.y > 0) // �÷��̾ �� ���� ���� ��
                {
                    m_IsGrounded = true;
                    m_Direction.y = 0;
                }
                else if (pushVector.y < 0) // �÷��̾ �� �Ʒ��� ���� ��
                {
                    m_IsGrounded = false;

                    if (m_Direction.y >= 0) // �÷��̾ ���� �ö󰡴� ���̶��
                    {
                        m_Direction.y = -200; // ��� �Ʒ��� �������� ����
                    }
                }
            }
        }
    }

    bool MarioScript::IsGroundedOnFloor()
    {
        // ���� �ٴڿ� ����ִ��� ���θ� Ȯ���ϴ� ������ �߰��մϴ�.
        // ��: ���� ��ü�� y ��ġ�� �ٴ� ������ �ִ��� Ȯ��
        // �� �Լ��� �ʿ信 ���� ������ �����ؾ� �մϴ�.
        //return m_Transform->GetPosition().y <= FloorLevel;
        return false;
    }
}