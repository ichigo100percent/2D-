#include "Js_FollowObjectScript.h"
#include "Js_MoveScripts.h"
#include "Js_Input.h"
#include "Js_Time.h"
#include "Js_DxObject.h"
#include "Js_Transform.h"
#include "Js_MeshRenderer.h"
#include "Js_Object.h"
#include "Js_Collider.h"


#include "Js_SceneManager.h"
#include "Js_TitleScene.h"
namespace Js
{
	FollowObjectScript::FollowObjectScript(std::shared_ptr<DxObject> _target)
		: m_Target(_target)
	{
	}
	FollowObjectScript ::~FollowObjectScript()
	{
	}
	void FollowObjectScript::Init()
	{
		m_Length = 100;
		m_Angle = 0.0f;
		m_Speed = 300.0f;
	}
	void FollowObjectScript::Update()
	{
		if (m_Target)
		{
			//auto targetPos = m_Target->GetTransform()->GetPosition();
			float time = Time::DeltaTime();


			//if (Input::KeyCheck('Q') == KeyState::KEY_HOLD)
			//	m_Angle +=  time * m_Speed;

			//if (Input::KeyCheck('E') == KeyState::KEY_HOLD)
			//	m_Angle -=  time * m_Speed;

			m_Angle += time * m_Speed;

			Vector3 pos = GetFirePos();

			// 계산된 위치를 현재 객체의 위치로 설정
			GetTransform()->SetPosition(pos);
		}
	}
	void FollowObjectScript::OnCollisionEnter(std::shared_ptr<Collider> _other)
	{
	}
	void FollowObjectScript::OnCollisionStay(std::shared_ptr<Collider> _other)
	{
	}
	void FollowObjectScript::OnCollisionExit(std::shared_ptr<Collider> _other)
	{
	}
	Vector3 FollowObjectScript::GetFirePos()
	{
		Vector3 pos = m_Target->GetTransform()->GetPosition();
		auto radian = XMConvertToRadians(m_Angle);  // 각도를 라디안으로 변환
		pos.x += m_Length * cos(radian);
		pos.y += m_Length * sin(radian);

		return pos;
	}
}