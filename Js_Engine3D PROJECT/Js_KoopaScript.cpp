#include "Js_KoopaScript.h"
#include "Js_GoombaScript.h"
#include "Js_PlayerScript.h"

#include "Js_Input.h"
#include "Js_Time.h"
#include "Js_DxObject.h"
#include "Js_Transform.h"
#include "Js_MeshRenderer.h"
#include "Js_Object.h"
#include "Js_Rigidbody.h"
#include "Js_Animation.h"
#include "Js_SceneManager.h"

#include "Js_PlayerScript.h"
#include "Js_TitleScene.h"

#include "Js_PlayScene.h"

namespace Js
{
	void KoopaScript::Init()
	{
		DefaultMoveScript::Init();
	}
	void KoopaScript::Update()
	{
		DefaultMoveScript::Update();
	}
	void KoopaScript::OnCollisionEnter(std::shared_ptr<Collider> _other)
	{
		auto type = _other->GetOwner()->GetLayerType();

		if (type == enums::LayerType::Wall && m_State == State::Move)
		{
			if (!isFacingRight)
			{
				auto anim = I_Resource->Get<Animation>(L"¾û±Ý¾û±Ý2");
				GetOwner()->GetAnimator()->SetAnimation(anim);
				m_Direction = -m_Direction;
				isFacingRight = true;
			}
			else
			{
				auto anim = I_Resource->Get<Animation>(L"¾û±Ý¾û±Ý");
				GetOwner()->GetAnimator()->SetAnimation(anim);
				m_Direction = -m_Direction;
				isFacingRight = false;
			}
		}
		if (type == enums::LayerType::Floor && m_State == State::Move)
		{
			m_IsGround = true;
		}

		if (type == enums::LayerType::Wall && m_State == State::Die)
		{
			m_Direction = -m_Direction;
		}
		if (type == enums::LayerType::Floor && m_State == State::Die)
		{
			m_IsGround = true;
		}
		if (type == enums::LayerType::End && m_State == State::Move)
		{
			object::Destroy(GetOwner());
		}
		if (type == enums::LayerType::End && m_State == State::Die)
		{
			object::Destroy(GetOwner());
		}
		if (type == enums::LayerType::Monster && m_State == State::Die)
		{
			object::Destroy(_other->GetOwner());
		}
	}
	void KoopaScript::OnCollisionStay(std::shared_ptr<Collider> _other)
	{
		DefaultMoveScript::OnCollisionStay(_other);
	}
	void KoopaScript::OnCollisionExit(std::shared_ptr<Collider> _other)
	{
		auto type = _other->GetOwner()->GetLayerType();

		if (type == enums::LayerType::Floor)
		{
			m_IsGround = false;
		}
	}
	void KoopaScript::idle()
	{
		DefaultMoveScript::idle();
		auto animator = m_Owner->GetAnimator();
		auto anim = I_Resource->Get<Animation>(L"²®Áú");
		animator->SetAnimation(anim);
	}
	void KoopaScript::die()
	{
		m_DeltaTime = Time::DeltaTime();
		Vector3	position = GetOwner()->GetTransform()->GetPosition();
		if (!m_IsGround)
		{
			position.y += m_Gravity * m_DeltaTime;
		}

		// ÀÏÁ¤ÇÑ ¼Óµµ·Î ÀÌµ¿
		position += -m_Direction * m_Speed * 3 * m_DeltaTime;

		// À§Ä¡ ¾÷µ¥ÀÌÆ®
		GetOwner()->GetTransform()->SetPosition(position);
	}
	void KoopaScript::move()
	{
		DefaultMoveScript::move();
	}
}