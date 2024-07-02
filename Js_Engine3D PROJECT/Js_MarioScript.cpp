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
        m_JumpForce = 250.0f; // ���� ��
        m_IsGrounded = false; // �ٴڿ� ��� �ִ��� ����
        m_Friction = 50.0f; // ������
        m_Mass = 1.0f; // �������� ���� (����: kg)

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
            m_Direction.x = max(m_Direction.x, -m_Speed); // �ִ� �ӵ� ����
        }
        if (Input::KeyCheck('D') == KeyState::KEY_HOLD)
        {
            m_Direction.x += (m_Acceleration / m_Mass) * deltaTime; // ������ ���� ���ӵ�
            m_Direction.x = min(m_Direction.x, m_Speed); // �ִ� �ӵ� ����
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
        else if (type == enums::LayerType::Floor)
        {
            // �ٴڿ� ������Ƿ� y ���� ����
            m_IsGrounded = true;
            m_Direction.y = 0; // �߷��� �ʱ�ȭ�Ͽ� �� �̻� �Ʒ��� �������� �ʵ��� ��
        }
    }

    void MarioScript::OnCollisionStay(std::shared_ptr<Collider> _other)
    {
    }

    void MarioScript::OnCollisionExit(std::shared_ptr<Collider> _other)
    {
        auto type = _other->GetOwner()->GetLayerType();

        if (type == enums::LayerType::Floor)
        {
            // �ٴڿ��� ������Ƿ� y ���� ���������� ��
            m_IsGrounded = false;
        }
    }
}