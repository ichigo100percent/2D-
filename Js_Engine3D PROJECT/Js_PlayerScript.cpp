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
#include "Js_FireballScript.h"
#include "Js_SoundManager.h"
#include "Js_KoopaScript.h"


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
		if (music)
			music->Release();
		if (effect)
			effect->Release();

		m_Animator = GetOwner()->GetAnimator();
		m_Rigidbody = GetOwner()->GetComponent<Rigidbody>();
		m_State = State::Idle;
		jumpeffectCount = 0;
		count = 0;

		music = SoundManager::Get(L"overworld.wav");
		music->Play(true);
	}
	void PlayerScript::Update()
	{
		if (m_Animator == nullptr)
			m_Animator = GetOwner()->GetAnimator();
		
		if (GetMarioState() != State::Die && !flagTouch)
		{
			move();
			jump();
			idle();
			attack();

			m_Rigidbody->SetGrounded(false);
		}
		else if (flagTouch && !flagAtGround)
		{			
			auto position = GetOwner()->GetTransform()->GetPosition();
			position.y -= 100 * Time::DeltaTime();
			GetOwner()->GetTransform()->SetPosition(position);
		}
		else if(flagAtGround)
		{
			auto position = GetOwner()->GetTransform()->GetPosition();
			position.x += 100 * Time::DeltaTime();
			GetOwner()->GetTransform()->SetPosition(position);
		}

		// 마리오 무적시간
		if (isInvincible)
		{
			CollisionManager::CollisionLayerCheck(LayerType::Player, LayerType::Monster, false);
			invincibilityTimer -= Time::DeltaTime();
			if (invincibilityTimer <= 0.0f)
			{
				CollisionManager::CollisionLayerCheck(LayerType::Player, LayerType::Monster, true);
				isInvincible = false;
			}
		}

		die();
	}

	void PlayerScript::OnCollisionEnter(std::shared_ptr<Collider> _other)
	{
		HandleCollision(_other);
		growUp(_other);
		CollisionInteraction(_other);
		endPointTouch(_other);

		if (_other->GetOwner()->GetLayerType() == LayerType::End)
		{
			m_State = State::Die;
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
			jumpeffectCount = 0;
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
				jumpeffectCount = 0;
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
					jumpeffectCount = 0;
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
					{
						effect = SoundManager::Get(L"blockbreak.wav");
						if (effect)
							effect->PlayEffect();

						if(_other->GetOwner()->GetScripts().empty())
							object::Destroy(_other->GetOwner());
					}
					else
					{
						effect = SoundManager::Get(L"blockhit.wav");
						if (effect)
							effect->PlayEffect();
					}
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
		if (Input::KeyCheck('W') == KeyState::KEY_UP)
		{
			effect = SoundManager::Get(L"jump.wav");
			if (isJump && jumpeffectCount == 0)
			{
				effect->PlayEffect();
				jumpeffectCount++;
			}
		}
    }
	void PlayerScript::attack()
	{
		if (GetMarioType() == MarioType::Fire)
		{
			if (Input::KeyCheck(VK_SPACE) == KeyState::KEY_UP)
			{
				std::shared_ptr<DxObject> fireball = object::Instantiate<DxObject>(L"Fireball", enums::LayerType::Fireball);
				{
					auto meshRender = std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext());
					fireball->AddComponent(meshRender);
					auto mesh = I_Resource->Get<Mesh>(L"Rectangle");
					meshRender->SetMesh(mesh);
					auto material = I_Resource->Get<Material>(L"Default");
					meshRender->SetMaterial(material);
					auto animator = std::make_shared<Animator>();
					auto anim = I_Resource->Get<Animation>(L"불꽃발싸");
					animator->SetAnimation(anim);
					fireball->AddComponent(animator);
					fireball->GetTransform()->SetScale(Vector3(16, 16, 0));
					auto col = std::make_shared<Collider>();
					fireball->AddComponent(col);

					Vector3 position = GetOwner()->GetTransform()->GetPosition();
					Vector3 direction = isFacingRight ? Vector3(1, 0, 0) : Vector3(-1, 0, 0);

					fireball->GetTransform()->SetPosition(Vector3(position.x, position.y + 16, position.z));
					fireball->AddComponent(std::make_shared<FireballScript>(GetOwner(), direction));
				}
				effect = SoundManager::Get(L"fireball.wav");
				if (effect)
					effect->PlayEffect();
			}
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
			CollisionManager::CollisionLayerCheck(LayerType::Player, LayerType::End, false);

			GetOwner()->GetTransform()->SetScale(Vector3(16, 16, 0));
			auto anim = I_Resource->Get<Animation>(L"Mario_die");
			m_Animator->SetAnimation(anim);
			auto veloctiy = m_Rigidbody->GetVelocity();
			veloctiy.x = 0;
			veloctiy.y = 450;
			m_Rigidbody->SetVelocity(veloctiy);
			m_Rigidbody->SetGrounded(true);

			time = Time::DeltaTime();
			elapsedTime += time;
			if (elapsedTime > 0.3)
			{
				veloctiy.y = -450;
				m_Rigidbody->SetVelocity(veloctiy);
				m_Rigidbody->SetGrounded(false);
			}

			effect = SoundManager::Get(L"death.wav");
			if (music)
				music->Release();
			if (effect && count == 0)
			{
				effect->PlayEffect();
				count++;
			}

			if (elapsedTime > 3)
			{
				std::dynamic_pointer_cast<TitleScene>(SceneManager::LoadScene<TitleScene>(L"Title"));
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
			GetOwner()->GetTransform()->SetScale(GetOwner()->GetSize());
            SetType(MarioType::Super);

			isInvincible = true;
			invincibilityTimer = 1.0f; 
			effect = SoundManager::Get(L"powerupcollect.wav");
			effect->PlayEffect();
        }
		if (type == enums::LayerType::Flower && GetMarioType() == MarioType::Super)
		{
			auto material = I_Resource->Get<Material>(L"마리오2");
			GetOwner()->GetMeshRenderer()->SetMaterial(material);
			GetOwner()->GetTransform()->SetScale(GetOwner()->GetSize());
			SetType(MarioType::Fire);

			auto anim = I_Resource->Get<Animation>(L"FireMario_rightJump");
			m_Animator->SetAnimation(anim);

			isInvincible = true;
			invincibilityTimer = 1.0f; 
			effect = SoundManager::Get(L"powerupcollect.wav");
			if(effect)
				effect->PlayEffect();
		}
    }
	void PlayerScript::endPointTouch(std::shared_ptr<Collider> _other)
	{
		auto type = _other->GetOwner()->GetLayerType();

		if (type == enums::LayerType::Flag)
		{
			music->Release();
			music = SoundManager::Get(L"flagraise.wav");
			music->Play(false);

			flagTouch = true;
			m_Rigidbody->SetGrounded(true);
			m_Rigidbody->SetVelocity(Vector3::Zero);
			CollisionManager::CollisionLayerCheck(LayerType::Player, LayerType::Flag, false);
			CollisionManager::CollisionLayerCheck(LayerType::Player, LayerType::Wall, false);
			// 애니메이션 설정

			switch (static_cast<MarioType>(m_Type))
			{
			case MarioType::Nomal:
			{
				auto anim = I_Resource->Get<Animation>(L"Mario_flag");
				m_Animator->SetAnimation(anim);
			}
			break;
			case MarioType::Super:
			{
				std::shared_ptr<Animation> anim = I_Resource->Get<Animation>(L"SuperMario_flag");
				m_Animator->SetAnimation(anim);
			}
			break;
			case MarioType::Fire:
			{
				std::shared_ptr<Animation> anim = I_Resource->Get<Animation>(L"FireMario_flag");
				m_Animator->SetAnimation(anim);
			}
			break;
			default:
				break;
			}
		}

		if (type == enums::LayerType::Floor && flagTouch)
		{
			flagAtGround = true;

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

		// x축으로 이동하면서 endPoint에 충돌시 겜오브젝트 삭제 2초뒤 신이동
		if (type == enums::LayerType::EndPoint)
		{
			object::Destroy(GetOwner());
		}
	}
    void PlayerScript::CollisionInteraction(std::shared_ptr<Collider> _other)
    {
        auto type = _other->GetOwner()->GetLayerType();
        auto scirpts = _other->GetOwner()->GetScripts();
        std::shared_ptr<GoombaScript> goomba = nullptr;
		std::shared_ptr<KoopaScript> koopa = nullptr;

        if (type == enums::LayerType::Monster)
        {
            for (auto script : scirpts)
            {
                goomba = std::dynamic_pointer_cast<GoombaScript>(script);
                if (goomba)
                    break;
            }
			if (goomba)
			{
				if (isJump && goomba)
				{
					auto velocity = m_Rigidbody->GetVelocity();
					velocity.y = 200;
					m_Rigidbody->SetVelocity(velocity);
					goomba->SetState(State::Die);
					effect = SoundManager::Get(L"stomp.wav");
					if (effect)
						effect->PlayEffect();
				}
				else if (goomba->GetState() == State::Move && GetMarioType() == MarioType::Nomal)
				{
					m_State = State::Die;
				}
				else if (goomba->GetState() == State::Move && GetMarioType() == MarioType::Super)
				{
					auto material = I_Resource->Get<Material>(L"Default");
					GetOwner()->GetMeshRenderer()->SetMaterial(material);
					GetOwner()->GetTransform()->SetScale(GetOwner()->GetSize());
					m_Type = MarioType::Nomal;
					invincibilityTimer = 1.0f;
					isInvincible = true;
					effect = SoundManager::Get(L"powerupappear.wav");
					if (effect)
						effect->PlayEffect();
				}
				else if (goomba->GetState() == State::Move && GetMarioType() == MarioType::Fire)
				{
					auto material = I_Resource->Get<Material>(L"마리오2");
					GetOwner()->GetMeshRenderer()->SetMaterial(material);
					GetOwner()->GetTransform()->SetScale(GetOwner()->GetSize());
					m_Type = MarioType::Super;
					invincibilityTimer = 1.0f;
					isInvincible = true;
					effect = SoundManager::Get(L"powerupappear.wav");
					if (effect)
						effect->PlayEffect();
				}
			}
			for (auto script : scirpts)
			{
				koopa = std::dynamic_pointer_cast<KoopaScript>(script);
				if (koopa)
					break;
			}
			if (koopa)
			{
				if (isJump && koopa && koopa->GetState() == State::Move)
				{
					auto velocity = m_Rigidbody->GetVelocity();
					velocity.y = 200;
					m_Rigidbody->SetVelocity(velocity);
					koopa->SetState(State::Idle);
					effect = SoundManager::Get(L"stomp.wav");
					if (effect)
						effect->PlayEffect();
				}
				else if (isJump && koopa->GetState() == State::Idle)
				{
					auto velocity = m_Rigidbody->GetVelocity();
					velocity.y = 200;
					m_Rigidbody->SetVelocity(velocity);
					koopa->SetState(State::Die);
					effect = SoundManager::Get(L"kick.wav");
					if (effect)
						effect->PlayEffect();
				}
				else if ((koopa->GetState() == State::Move || koopa->GetState() == State::Die ) && GetMarioType() == MarioType::Nomal)
					m_State = State::Die;
				else if ((koopa->GetState() == State::Move || koopa->GetState() == State::Die) && GetMarioType() == MarioType::Super)
				{
					auto material = I_Resource->Get<Material>(L"Default");
					GetOwner()->GetMeshRenderer()->SetMaterial(material);
					GetOwner()->GetTransform()->SetScale(GetOwner()->GetSize());
					m_Type = MarioType::Nomal;
					invincibilityTimer = 1.0f;
					isInvincible = true;
					effect = SoundManager::Get(L"powerupappear.wav");
					if (effect)
						effect->PlayEffect();
				}
				else if ((koopa->GetState() == State::Move || koopa->GetState() == State::Die) && GetMarioType() == MarioType::Fire)
				{
					auto material = I_Resource->Get<Material>(L"마리오2");
					GetOwner()->GetMeshRenderer()->SetMaterial(material);
					GetOwner()->GetTransform()->SetScale(GetOwner()->GetSize());
					m_Type = MarioType::Super;
					invincibilityTimer = 1.0f;
					isInvincible = true;
					effect = SoundManager::Get(L"powerupappear.wav");
					if (effect)
						effect->PlayEffect();
				}
			}
        }

        if (type == enums::LayerType::MunshRoom || type == enums::LayerType::Flower)
            object::Destroy(_other->GetOwner());
         
    }
}
