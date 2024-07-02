#include "Js_GoombaScript.h"
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

#include "testscene.h"
namespace Js
{
	void GoombaScript::Init()
	{
		m_Transform = GetOwner()->GetTransform();
	}
	void GoombaScript::Update()
	{
		float deltaTime = Time::DeltaTime();
		Vector3 position = m_Transform->GetPosition();

		if (!m_IsGround)
		{
			position.y += m_Gravity * deltaTime;
		}

		// 일정한 속도로 이동
		position += m_Direction * m_Speed * deltaTime;

		// 위치 업데이트
		m_Transform->SetPosition(position);
	}
	void GoombaScript::OnCollisionEnter(std::shared_ptr<Collider> _other)
	{
		auto type = _other->GetOwner()->GetLayerType();

		if (type == enums::LayerType::Player)
		{
			object::Destroy(_other->GetOwner());
		}
		if (type == enums::LayerType::Tower)
		{
			// 굼바의 이동 방향을 반대로 전환
			m_Direction = -m_Direction;
		}
		if (type == enums::LayerType::Floor)
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
			// 바닥에서 벗어났으므로 y 값이 내려가도록 함
			m_IsGround = false;
		}
	}
}