#include "Js_TitleScene.h"
#include "std.h"
#include "Js_Core.h"
#include "Js_Time.h"
#include "Js_Input.h"
#include "Js_DxObject.h"
#include "Js_Component.h"
#include "Js_Transform.h"
#include "Js_Camera.h"
#include "Js_Animator.h"
#include "Js_Collider.h"
#include "Js_MeshRenderer.h"
#include "Js_Fireball.h"
#include "Js_Object.h"
#include "Js_Player.h"
#include "Js_Rigidbody.h"
#include "Js_CollisionManager.h"


// Scripts
#include "Js_FireballScript.h"
#include "Js_MoveScripts.h"
#include "Js_RotateScript.h"
#include "Js_FollowTargetScript.h"
#include "Js_PlayerScript.h"

#include "Js_PlayScene.h"

namespace Js
{
	TitleScene::TitleScene()
		: Scene()
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Init()
	{
	    std::shared_ptr<DxObject> camera = object::Instantiate<DxObject>();
		{
			camera->AddComponent(std::make_shared<Camera>());
		}
		std::shared_ptr<DxObject> bg = object::Instantiate<DxObject>(L"BackGround");
		{
			auto meshRender = std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext());
			bg->AddComponent(meshRender);
			auto mesh = I_Resource->Get<Mesh>(L"Rectangle");
			meshRender->SetMesh(mesh);
			auto material = I_Resource->Get<Material>(L"Title");
			meshRender->SetMaterial(material);
			bg->GetTransform()->SetPosition(Vector3(0, 0, 0));
			bg->GetTransform()->SetScale(Vector3(480, 240, 0));
		}
		Scene::Init();
	}
	void TitleScene::Update()
	{
		Scene::Update();
	}
	void TitleScene::LateUpdate()
	{
		if (Input::KeyCheck('N') == KeyState::KEY_PUSH)
		{
			std::dynamic_pointer_cast<PlayScene>(SceneManager::LoadScene<PlayScene>(L"Play"));
		}
		Scene::LateUpdate();
	}
	void TitleScene::OnEnter()
	{
		Scene::OnEnter();
		TitleScene::Init();
	}
	void TitleScene::OnExit()
	{
		Scene::OnExit();
	}
}