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
        m_Speed = 200.0f; // 마리오의 최대 속도
        m_Acceleration = 100.0f; // 마리오의 가속도
        m_Gravity = -500.0f; // 중력 가속도
        m_JumpForce = MinJumpForce; // 기본 점프 힘
        m_IsGrounded = false; // 바닥에 닿고 있는지 여부
        m_Friction = 50.0f; // 마찰력
        m_Mass = 1.0f; // 마리오의 질량 (단위: kg)
        m_JumpTime = 0.0f; // 점프 버튼을 누르는 시간 초기화
    }

    void MarioScript::Update()
    {
        float deltaTime = Time::DeltaTime();
        Vector3 position = m_Transform->GetPosition();

        // 중력 적용
        if (!m_IsGrounded)
        {
            m_Direction.y += (m_Gravity / m_Mass) * deltaTime; // 질량에 따른 중력 가속도
        }

        // 이동 입력 처리
        if (Input::KeyCheck('A') == KeyState::KEY_HOLD)
        {
            m_Direction.x -= (m_Acceleration / m_Mass) * deltaTime; // 질량에 따른 가속도
            m_Direction.x = std::max(m_Direction.x, -m_Speed); // 최대 속도 제한
        }
        if (Input::KeyCheck('D') == KeyState::KEY_HOLD)
        {
            m_Direction.x += (m_Acceleration / m_Mass) * deltaTime; // 질량에 따른 가속도
            m_Direction.x = std::min(m_Direction.x, m_Speed); // 최대 속도 제한
        }

        // 마찰력 적용
        if (Input::KeyCheck('A') == KeyState::KEY_UP || Input::KeyCheck('D') == KeyState::KEY_UP)
        {
            m_Direction.x -= m_Direction.x * (m_Friction / m_Mass) * deltaTime; // 질량에 따른 마찰력
        }

        // 점프 입력 처리
        if (Input::KeyCheck('W') == KeyState::KEY_HOLD && m_IsGrounded)
        {
            m_Direction.y = m_JumpForce / m_Mass; // 질량에 따른 점프 힘
            m_IsGrounded = false;
        }

        // 위치 업데이트
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
            // 바닥 또는 벽에 닿았으므로 y 값을 고정
            m_IsGrounded = true;
            m_Direction.y = 0; // 중력을 초기화하여 더 이상 아래로 내려가지 않도록 함
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
            // 이 코드는 바닥에 있을 때는 수행하지 않도록 수정
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
            // 충돌 방향으로 밀어내기
            GetOwner()->GetTransform()->SetPosition(GetOwner()->GetTransform()->GetPosition() + pushVector);

            if (type == enums::LayerType::Wall)
            {
                if (pushVector.y > 0) // 플레이어가 벽 위에 있을 때
                {
                    m_IsGrounded = true;
                    m_Direction.y = 0;
                }
                else if (pushVector.y < 0) // 플레이어가 벽 아래에 있을 때
                {
                    m_IsGrounded = false;

                    if (m_Direction.y >= 0) // 플레이어가 위로 올라가는 중이라면
                    {
                        m_Direction.y = -200; // 즉시 아래로 떨어지게 설정
                    }
                }
            }
        }
    }

    bool MarioScript::IsGroundedOnFloor()
    {
        // 현재 바닥에 닿아있는지 여부를 확인하는 로직을 추가합니다.
        // 예: 현재 객체의 y 위치가 바닥 레벨에 있는지 확인
        // 이 함수는 필요에 따라 적절히 구현해야 합니다.
        //return m_Transform->GetPosition().y <= FloorLevel;
        return false;
    }
}