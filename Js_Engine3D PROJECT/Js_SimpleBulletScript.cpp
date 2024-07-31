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
		// ���� �Ѿ��� ��ġ�� �����ɴϴ�.
		auto pos = GetOwner()->GetTransform()->GetPosition();

		// �Ѿ��� ��ġ�� ������Ʈ�մϴ�.
		pos += m_Velocity * m_Speed * Time::DeltaTime();

		// �Ѿ��� ��ġ�� �����մϴ�.
		GetOwner()->GetTransform()->SetPosition(pos);

		// �ð� ����� ������Ʈ�մϴ�.
		float delta = Time::DeltaTime();
		m_Time += delta;

		// 3�ʰ� ������ �Ѿ��� �����մϴ�.
		if (m_Time > 3)
			object::Destroy(GetOwner());
	}

	void SimpleBulletScript::SetNormalizedDirection(Vector3 _dir)
	{
		m_Velocity = XMVector3Normalize(_dir); // ���� ���͸� ����ȭ�մϴ�.
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