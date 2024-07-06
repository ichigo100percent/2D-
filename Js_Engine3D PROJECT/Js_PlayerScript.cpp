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
#include "Js_WallScript.h"

#include "Js_GoombaScript.h"
#include "Js_CollisionManager.h"


namespace Js
{
    PlayerScript::PlayerScript()
    {
    }
    PlayerScript::~PlayerScript()
    {
    }
    void PlayerScript::Init()
	{
		m_Animator = GetOwner()->GetAnimator();
		m_Rigidbody = GetOwner()->GetComponent<Rigidbody>();
		m_State = State::Idle;       
	}
	void PlayerScript::Update()
	{
		if (m_Animator == nullptr)
			m_Animator = GetOwner()->GetAnimator();
		
		if (GetMarioState() != State::Die)
		{
			move();
			jump();
			idle();

			m_Rigidbody->SetGrounded(false);
		}

		die();
	}

	void PlayerScript::OnCollisionEnter(std::shared_ptr<Collider> _other)
	{
		HandleCollision(_other);
		growUp(_other);
		CollisionInteraction(_other);

		if (_other->GetOwner()->GetLayerType() == LayerType::End)
		{
			std::dynamic_pointer_cast<TitleScene>(SceneManager::LoadScene<TitleScene>(L"Title"));
		}
	}

	void PlayerScript::OnCollisionStay(std::shared_ptr<Collider> _other)
	{
		HandleCollision(_other);
	}

	void PlayerScript::OnCollisionExit(std::shared_ptr<Collider> _other)
	{
		auto type = _other->GetOwner()->GetLayerType();
		auto rb = GetOwner()->GetComponent<Rigidbody>();
		if (type == enums::LayerType::Floor || type == enums::LayerType::Wall || type == enums::LayerType::WallEnd)
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
				isJump = false;
				m_State = State::Idle;
				if (pushVector.y != 0)
				{
					auto velocity = rb->GetVelocity();
					velocity.y = 0; // 수직 속도를 0으로 설정
					rb->SetVelocity(velocity);
				}
			}
			else if (type == enums::LayerType::Wall || type == enums::LayerType::WallEnd)
			{
				if (pushVector.y > 0) // 플레이어가 타워 위에 있을 때
				{
					rb->SetGrounded(true);
					isJump = false; // 점프 상태 해제
					m_State = State::Idle;
					auto velocity = rb->GetVelocity();
					velocity.y = 0; // 수직 속도를 0으로 설정
					rb->SetVelocity(velocity);
				}
				else if (pushVector.y < 0) // 플레이어가 타워 아래에 있을 때
				{
					rb->SetGrounded(false);
					isJump = true; // 점프 상태로 전환
					m_State = State::Jump;
					auto velocity = rb->GetVelocity();
					if (velocity.y >= 0) // 플레이어가 위로 올라가는 중이라면
					{
						velocity.y = -200; // 즉시 아래로 떨어지게 설정
						rb->SetVelocity(velocity);
					}
					if (GetMarioType() == MarioType::Super || GetMarioType() == MarioType::Fire)
						object::Destroy(_other->GetOwner());
				}
			}
		}
	}

    void PlayerScript::idle()
    {
		if (m_State == State::Idle && !isJump && isFacingRight)
		{
			switch (static_cast<MarioType>(m_Type))
			{
			case MarioType::Nomal:
			{
				std::shared_ptr<Animation> anim = I_Resource->Get<Animation>(L"Mario_rightIdle");
				m_Animator->SetAnimation(anim);
			}
				break;
			case MarioType::Super:
			{
				std::shared_ptr<Animation> anim = I_Resource->Get<Animation>(L"SuperMario_rightIdle");
				m_Animator->SetAnimation(anim);
			}
				break;
			case MarioType::Fire:
			{
				std::shared_ptr<Animation> anim = I_Resource->Get<Animation>(L"FireMario_rightIdle");
				m_Animator->SetAnimation(anim);
			}
				break;
			default:
				break;
			}
		}
		else if (m_State == State::Idle && !isJump && !isFacingRight)
		{
			switch (static_cast<MarioType>(m_Type))
			{
			case MarioType::Nomal:
			{
				std::shared_ptr<Animation> anim = I_Resource->Get<Animation>(L"Mario_leftIdle");
				m_Animator->SetAnimation(anim);
			}
			break;
			case MarioType::Super:
			{
				std::shared_ptr<Animation> anim = I_Resource->Get<Animation>(L"SuperMario_leftIdle");
				m_Animator->SetAnimation(anim);
			}
			break;
			case MarioType::Fire:
			{
				std::shared_ptr<Animation> anim = I_Resource->Get<Animation>(L"FireMario_leftIdle");
				m_Animator->SetAnimation(anim);
			}
			break;
			default:
				break;
			}
		}
    }
    void PlayerScript::move()
    {
		if (Input::KeyCheck('A') == KeyState::KEY_HOLD)
		{
			if (!isJump)
			{
				switch (static_cast<MarioType>(m_Type))
				{
				case MarioType::Nomal:
				{
					auto anim = I_Resource->Get<Animation>(L"Mario_leftMove");
					m_Animator->SetAnimation(anim);
				}
				break;
				case MarioType::Super:
				{
					auto anim = I_Resource->Get<Animation>(L"SuperMario_leftMove");
					m_Animator->SetAnimation(anim);
				}
				break;
				case MarioType::Fire:
				{
					auto anim = I_Resource->Get<Animation>(L"FireMario_leftMove");
					m_Animator->SetAnimation(anim);
				}
				break;
				default:
					break;
				}
			}
			m_State = State::Move;
			m_Rigidbody->AddForce(Vector3(-1000, 0, 0));
			isFacingRight = false; // 왼쪽을 향하고 있음
		}
		if (Input::KeyCheck('A') == KeyState::KEY_UP)
		{
			if (!isJump)
			{
				switch (static_cast<MarioType>(m_Type))
				{
				case MarioType::Nomal:
				{
					std::shared_ptr<Animation> anim = I_Resource->Get<Animation>(L"Mario_leftIdle");
					m_Animator->SetAnimation(anim);
				}
				break;
				case MarioType::Super:
				{
					std::shared_ptr<Animation> anim = I_Resource->Get<Animation>(L"SuperMario_leftIdle");
					m_Animator->SetAnimation(anim);
				}
				break;
				case MarioType::Fire:
				{
					std::shared_ptr<Animation> anim = I_Resource->Get<Animation>(L"FireMario_leftIdle");
					m_Animator->SetAnimation(anim);
				}
				break;
				default:
					break;
				}
			}
		}
		if (Input::KeyCheck('D') == KeyState::KEY_HOLD)
		{
			if (!isJump)
			{
				switch (static_cast<MarioType>(m_Type))
				{
				case MarioType::Nomal:
				{
					auto anim = I_Resource->Get<Animation>(L"Mario_rightMove");
					m_Animator->SetAnimation(anim);
				}
				break;
				case MarioType::Super:
				{
					auto anim = I_Resource->Get<Animation>(L"SuperMario_rightMove");
					m_Animator->SetAnimation(anim);
				}
				break;
				case MarioType::Fire:
				{
					auto anim = I_Resource->Get<Animation>(L"FireMario_rightMove");
					m_Animator->SetAnimation(anim);
				}
				break;
				default:
					break;
				}
			}
			m_State = State::Move;
			m_Rigidbody->AddForce(Vector3(1000, 0, 0));
			isFacingRight = true; // 오른쪽을 향하고 있음
		}
		if (Input::KeyCheck('D') == KeyState::KEY_UP)
		{
			if (!isJump)
			{
				switch (static_cast<MarioType>(m_Type))
				{
				case MarioType::Nomal:
				{
					std::shared_ptr<Animation> anim = I_Resource->Get<Animation>(L"Mario_rightIdle");
					m_Animator->SetAnimation(anim);
				}
				break;
				case MarioType::Super:
				{
					std::shared_ptr<Animation> anim = I_Resource->Get<Animation>(L"SuperMario_rightIdle");
					m_Animator->SetAnimation(anim);
				}
				break;
				case MarioType::Fire:
				{
					std::shared_ptr<Animation> anim = I_Resource->Get<Animation>(L"FireMario_rightIdle");
					m_Animator->SetAnimation(anim);
				}
				break;
				default:
					break;
				}
			}
		}
    }
    void PlayerScript::jump()
    {
		if (Input::KeyCheck('W') == KeyState::KEY_HOLD)
		{
			if (isFacingRight)
			{
				switch (static_cast<MarioType>(m_Type))
				{
				case MarioType::Nomal:
				{
					auto anim = I_Resource->Get<Animation>(L"Mario_rightJump");
					m_Animator->SetAnimation(anim);
				}
				break;
				case MarioType::Super:
				{
					std::shared_ptr<Animation> anim = I_Resource->Get<Animation>(L"SuperMario_rightJump");
					m_Animator->SetAnimation(anim);
				}
				break;
				case MarioType::Fire:
				{
					std::shared_ptr<Animation> anim = I_Resource->Get<Animation>(L"FireMario_rightJump");
					m_Animator->SetAnimation(anim);
				}
				break;
				default:
					break;
				}
			}
			else
			{
				switch (static_cast<MarioType>(m_Type))
				{
				case MarioType::Nomal:
				{
					auto anim = I_Resource->Get<Animation>(L"Mario_leftJump");
					m_Animator->SetAnimation(anim);
				}
				break;
				case MarioType::Super:
				{
					std::shared_ptr<Animation> anim = I_Resource->Get<Animation>(L"SuperMario_leftJump");
					m_Animator->SetAnimation(anim);
				}
				break;
				case MarioType::Fire:
				{
					std::shared_ptr<Animation> anim = I_Resource->Get<Animation>(L"FireMario_leftJump");
					m_Animator->SetAnimation(anim);
				}
				break;
				default:
					break;
				}
			}
			m_Rigidbody->Jump(600.0f); // 점프 힘 설정
			isJump = true;
			m_State = State::Jump;
		}
    }
	void PlayerScript::die()
	{
		if (m_State == State::Die)
		{
			CollisionManager::CollisionLayerCheck(LayerType::Player, LayerType::Floor, false);
			CollisionManager::CollisionLayerCheck(LayerType::Player, LayerType::Monster, false);
			CollisionManager::CollisionLayerCheck(LayerType::Player, LayerType::Wall, false);
			CollisionManager::CollisionLayerCheck(LayerType::Player, LayerType::WallEnd, false);
			CollisionManager::CollisionLayerCheck(LayerType::Player, LayerType::MunshRoom, false);

			auto anim = I_Resource->Get<Animation>(L"Mario_die");
			m_Animator->SetAnimation(anim);
			auto veloctiy = m_Rigidbody->GetVelocity();
			veloctiy.x = 0;
			veloctiy.y = 450;
			m_Rigidbody->SetVelocity(veloctiy);
			m_Rigidbody->SetGrounded(true);

			time = Time::DeltaTime();
			deadTime += time;
			if (deadTime > 0.3)
			{
				veloctiy.y = -450;
				m_Rigidbody->SetVelocity(veloctiy);
				m_Rigidbody->SetGrounded(false);
			}
		}
	}

    void PlayerScript::growUp(std::shared_ptr<Collider> _other)
    {
        auto type = _other->GetOwner()->GetLayerType();

        if (type == enums::LayerType::MunshRoom && GetMarioType() == MarioType::Nomal)
        {
            auto material = I_Resource->Get<Material>(L"마리오2");
            GetOwner()->GetMeshRenderer()->SetMaterial(material);
			if (isFacingRight)
				m_Animation = I_Resource->Get<Animation>(L"SuperMario_R");
			else
				m_Animation = I_Resource->Get<Animation>(L"SuperMario_L");
			
			time = Time::DeltaTime();
			deadTime += time;
			if (deadTime > 0.3)
			{
				veloctiy.y = -450;
				m_Rigidbody->SetVelocity(veloctiy);
				m_Rigidbody->SetGrounded(false);
			}
			GetOwner()->GetTransform()->SetScale(GetOwner()->GetSize());
			GetOwner()->GetAnimator()->SetAnimation(m_Animation);
            SetType(MarioType::Super);
        }
    }
    void PlayerScript::CollisionInteraction(std::shared_ptr<Collider> _other)
    {
        auto type = _other->GetOwner()->GetLayerType();
        auto scirpts = _other->GetOwner()->GetScripts();
        std::shared_ptr<GoombaScript> goomba = nullptr;

        if (type == enums::LayerType::Monster)
        {
            for (auto script : scirpts)
            {
                goomba = std::dynamic_pointer_cast<GoombaScript>(script);
                if (goomba)
                    break;
            }
			if (m_State == State::Jump && goomba)
			{
				auto velocity = m_Rigidbody->GetVelocity();
				velocity.y = 200;
				m_Rigidbody->SetVelocity(velocity);
				goomba->SetState(State::Die);
			}
			else if (goomba->GetState() == State::Move && GetMarioType() == MarioType::Nomal)
				m_State = State::Die;
        }

        if (type == enums::LayerType::MunshRoom || type == enums::LayerType::Flower)
            object::Destroy(_other->GetOwner());
         
    }
}
