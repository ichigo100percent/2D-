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
	void GoombaScript::Init()
	{
		m_Owner = GetOwner();
		m_Transform = GetOwner()->GetTransform();
	}
	void GoombaScript::Update()
	{

		switch (m_State)
		{
		case State::Move:
			move();
			break;
		case State::Die:
			die();
			break;
		default:
			break;
		}
	}
	void GoombaScript::OnCollisionEnter(std::shared_ptr<Collider> _other)
	{
		auto type = _other->GetOwner()->GetLayerType();

		if (type == enums::LayerType::Tower && m_State == State::Move)
		{
			m_Direction = -m_Direction;
		}
		if (type == enums::LayerType::Floor && m_State == State::Move)
		{
			m_IsGround = true;
		}
	}
	void GoombaScript::OnCollisionStay(std::shared_ptr<Collider> _other)
	{

	}
	void GoombaScript::OnCollisionExit(std::shared_ptr<Collider> _other)
	{
		auto type = _other->GetOwner()->GetLayerType();

		if (type == enums::LayerType::Floor)
		{
			m_IsGround = false;
		}
	}
	void GoombaScript::move()
	{
		m_DeltaTime = Time::DeltaTime();
		Vector3 position = m_Transform->GetPosition();

		if (!m_IsGround)
		{
			position.y += m_Gravity * m_DeltaTime;
		}

		// 일정한 속도로 이동
		position += m_Direction * m_Speed * m_DeltaTime;

		// 위치 업데이트
		m_Transform->SetPosition(position);
	}
	void GoombaScript::die()
	{
		auto animator = m_Owner->GetAnimator();
		auto anim = I_Resource->Get<Animation>(L"굼바죽음");
		animator->SetAnimation(anim);

		m_DeltaTime = Time::DeltaTime();
		m_DieTime += m_DeltaTime; // 누적 시간 업데이트

		if (m_DieTime > 0.1f)
		{
			object::Destroy(m_Owner);
		}
	}
}