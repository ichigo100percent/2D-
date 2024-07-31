#include "Js_SimpleBulletScript.h"
#include "Js_Input.h"
#include "Js_Time.h"
#include "Js_DxObject.h"
#include "Js_Transform.h"
#include "Js_MeshRenderer.h"
#include "Js_Object.h"
#include "Js_Collider.h"

namespace Js
{
	SimpleBulletScript::SimpleBulletScript()
	{
	}
	SimpleBulletScript::~SimpleBulletScript()
	{
	}
	void SimpleBulletScript::Init()
	{
	}
	void SimpleBulletScript::Update()
	{
		// 현재 총알의 위치를 가져옵니다.
		auto pos = GetOwner()->GetTransform()->GetPosition();

		// 총알의 위치를 업데이트합니다.
		pos += m_Velocity * m_Speed * Time::DeltaTime();

		// 총알의 위치를 설정합니다.
		GetOwner()->GetTransform()->SetPosition(pos);

		// 시간 경과를 업데이트합니다.
		float delta = Time::DeltaTime();
		m_Time += delta;

		// 3초가 지나면 총알을 삭제합니다.
		if (m_Time > 3)
			object::Destroy(GetOwner());
	}

	void SimpleBulletScript::SetNormalizedDirection(Vector3 _dir)
	{
		m_Velocity = XMVector3Normalize(_dir); // 방향 벡터를 정규화합니다.
	}
	void SimpleBulletScript::OnCollisionEnter(std::shared_ptr<Collider> _other)
	{
	}
	void SimpleBulletScript::OnCollisionStay(std::shared_ptr<Collider> _other)
	{
	}
	void SimpleBulletScript::OnCollisionExit(std::shared_ptr<Collider> _other)
	{
	}
}