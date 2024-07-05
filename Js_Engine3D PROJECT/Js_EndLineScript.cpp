#include "Js_EndLineScript.h"
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
	void EndLineScript::Init()
	{
	}
	void EndLineScript::Update()
	{
	}
	void EndLineScript::OnCollisionEnter(std::shared_ptr<Collider> _other)
	{
		auto type = _other->GetOwner()->GetLayerType();

		if (type == enums::LayerType::Player)
		{
			Vector3 pushVector;
			if (Collider::CheckCollision(_other->GetOwner()->GetTransform()->GetRect(), GetOwner()->GetTransform()->GetRect(), pushVector))
			{
				// 충돌 방향으로 밀어내기
				_other->GetOwner()->GetTransform()->SetPosition(_other->GetOwner()->GetTransform()->GetPosition() + pushVector);
			}
		}
	}
	void EndLineScript::OnCollisionStay(std::shared_ptr<Collider> _other)
	{
	}
	void EndLineScript::OnCollisionExit(std::shared_ptr<Collider> _other)
	{
	}
}