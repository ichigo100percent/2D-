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
		DefaultMoveScript::Init();
	}
	void MushroomScript::Update()
	{
		DefaultMoveScript::Update();
	}
	void MushroomScript::OnCollisionEnter(std::shared_ptr<Collider> _other)
	{
		handleCollision(_other);
		auto type = _other->GetOwner()->GetLayerType();

		if (type == enums::LayerType::Floor && m_State == State::Move)
		{
			m_IsGround = true;
		}
	}
	void MushroomScript::OnCollisionStay(std::shared_ptr<Collider> _other)
	{
		handleCollision(_other);
	}
	void MushroomScript::OnCollisionExit(std::shared_ptr<Collider> _other)
	{
		auto type = _other->GetOwner()->GetLayerType();

		if (type == enums::LayerType::Floor)
		{
			m_IsGround = false;
		}
	}
	void MushroomScript::move()
	{

	}
	void MushroomScript::die()
	{

	}
	void MushroomScript::handleCollision(std::shared_ptr<Collider> _other)
	{
		auto type = _other->GetOwner()->GetLayerType();

		Vector3 pushVector;
		if (Collider::CheckCollision(GetOwner()->GetTransform()->GetRect(), _other->GetOwner()->GetTransform()->GetRect(), pushVector))
		{
			if (type == enums::LayerType::Wall)
			{
				GetOwner()->GetTransform()->SetPosition(GetOwner()->GetTransform()->GetPosition() + pushVector);
			}
		}
	}
}