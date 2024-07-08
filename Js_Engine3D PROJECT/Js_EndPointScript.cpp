#include "Js_EndPointScript.h"
#include "Js_PlayerScript.h"
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
#include "Js_MushroomWallScript.h"

#include "Js_GoombaScript.h"
#include "Js_CollisionManager.h"
#include "Js_ClearScene.h"
#include "Js_SceneManager.h"

namespace Js
{
	void EndPointScript::Init()
	{
	}
	void EndPointScript::Update()
	{
		end();
	}
	void EndPointScript::OnCollisionEnter(std::shared_ptr<Collider> _other)
	{
		auto type = _other->GetOwner()->GetLayerType();

		if (type == enums::LayerType::Player)
			gameEnd = true;	
	}
	void EndPointScript::OnCollisionStay(std::shared_ptr<Collider> _other)
	{
	}
	void EndPointScript::OnCollisionExit(std::shared_ptr<Collider> _other)
	{
	}
	void EndPointScript::end()
	{
		if (gameEnd == true)
		{
			time = Time::DeltaTime();
			elapsedTime += time;

			if (elapsedTime > 5)
				SceneManager::LoadScene<EndingScene>(L"Ending");
		}
	}
}