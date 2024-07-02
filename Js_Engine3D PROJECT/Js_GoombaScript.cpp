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

		// ������ �ӵ��� �̵�
		position += m_Direction * m_Speed * deltaTime;

		// ��ġ ������Ʈ
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
			// ������ �̵� ������ �ݴ�� ��ȯ
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
			// �ٴڿ��� ������Ƿ� y ���� ���������� ��
			m_IsGround = false;
		}
	}
}