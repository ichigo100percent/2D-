#include "Js_FlagScript.h"
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
	void FlagScript::Init()
	{
	}
	void FlagScript::Update()
	{
	}
	void FlagScript::OnCollisionEnter(std::shared_ptr<Collider> _other)
	{
		auto type = _other->GetOwner()->GetLayerType();

		if (type == enums::LayerType::Player)
		{

		}

	}
	void FlagScript::OnCollisionStay(std::shared_ptr<Collider> _other)
	{
	}
	void FlagScript::OnCollisionExit(std::shared_ptr<Collider> _other)
	{
	}
}