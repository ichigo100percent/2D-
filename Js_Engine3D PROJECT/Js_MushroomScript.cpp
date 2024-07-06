#include "Js_MushroomScript.h"
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


namespace Js
{
	void MushroomScript::Init()
	{

	}
	void MushroomScript::Update()
	{
		m_DeltaTime = Time::DeltaTime();
		Vector3	position = GetOwner()->GetTransform()->GetPosition();

		if (!m_IsGround)
		{
			position.y += m_Gravity * m_DeltaTime;
		}
		else
		{
			// ������ �ӵ��� �̵�
			position += m_Direction * m_Speed * m_DeltaTime;
		}

		// ��ġ ������Ʈ
		GetOwner()->GetTransform()->SetPosition(position);
	}
	void MushroomScript::OnCollisionEnter(std::shared_ptr<Collider> _other)
	{
		auto type = _other->GetOwner()->GetLayerType();
		

		if (type == enums::LayerType::Wall || type == enums::LayerType::WallEnd)
		{
			m_IsGround = true;
		}
		if (type == enums::LayerType::Floor)
		{
			m_IsGround = true;
			m_Direction = Vector3(-1, 0, 0);
		}
	}
	void MushroomScript::OnCollisionStay(std::shared_ptr<Collider> _other)
	{
	}
	void MushroomScript::OnCollisionExit(std::shared_ptr<Collider> _other)
	{
		auto type = _other->GetOwner()->GetLayerType();

		if (type == enums::LayerType::WallEnd)
		{
			m_IsGround = false;
			// ������ ������ �� �밢���� �ƴ� �������� �������� �ϱ� ���� y �������θ� �̵�
			m_Direction = Vector3(0, -1, 0);
		}

	}
}