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
		DefaultMoveScript::Init();
	}
	void GoombaScript::Update()
	{
		DefaultMoveScript::Update();
	}
	void GoombaScript::OnCollisionEnter(std::shared_ptr<Collider> _other)
	{
		auto type = _other->GetOwner()->GetLayerType();

		if (type == enums::LayerType::Wall && m_State == State::Move)
		{
			m_Direction = -m_Direction;
		}
		if (type == enums::LayerType::Floor && m_State == State::Move)
		{
			m_IsGround = true;
		}
		if (type == enums::LayerType::End && m_State == State::Move)
		{
			object::Destroy(GetOwner());
		}
	}
	void GoombaScript::OnCollisionStay(std::shared_ptr<Collider> _other)
	{
		DefaultMoveScript::OnCollisionStay(_other);
	}
	void GoombaScript::OnCollisionExit(std::shared_ptr<Collider> _other)
	{
		auto type = _other->GetOwner()->GetLayerType();

		if (type == enums::LayerType::Floor)
		{
			m_IsGround = false;
		}
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