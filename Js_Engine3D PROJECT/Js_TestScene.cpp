#include "Js_TestScene.h"
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
#include "Js_Object.h"
#include "Js_Rigidbody.h"
#include "Js_CollisionManager.h"

#include "Js_MoveScripts.h"
#include "Js_FollowTargetScript.h"
#include "Js_FollowObjectScript.h"
#include "Js_SimpleBulletScript.h"
#include "Js_FireBulletsScript.h"


namespace Js
{
	void TestScene::Init()
	{
#pragma region Camera
		camera = object::Instantiate<DxObject>();
		{
			camera->AddComponent(std::make_shared<Camera>());
		}
#pragma endregion
#pragma region Bg
		backGround = object::Instantiate<DxObject>();
		{
			auto meshRender = std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext());
			backGround->AddComponent(meshRender);
			auto mesh = I_Resource->Get<Mesh>(L"Rectangle");
			meshRender->SetMesh(mesh);
			auto material = I_Resource->Get<Material>(L"paka");
			meshRender->SetMaterial(material);
			backGround->GetTransform()->SetScale(backGround->GetSize());
		}
#pragma endregion	
		player = object::Instantiate<DxObject>();
		{
			auto meshRender = std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext());
			player->AddComponent(meshRender);
			auto mesh = I_Resource->Get<Mesh>(L"Rectangle");
			meshRender->SetMesh(mesh);
			auto material = I_Resource->Get<Material>(L"Default");
			meshRender->SetMaterial(material);
			player->GetTransform()->SetScale(Vector3(50, 50, 0));
			player->AddComponent(std::make_shared<MoveScript>());
			player->AddComponent(std::make_shared<FireBulletsScript>());
		}
		std::shared_ptr<DxObject> followObject = object::Instantiate<DxObject>();
		{
			auto meshRender = std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext());
			followObject->AddComponent(meshRender);
			auto mesh = I_Resource->Get<Mesh>(L"Rectangle");
			meshRender->SetMesh(mesh);
			auto material = I_Resource->Get<Material>(L"Default");
			meshRender->SetMaterial(material);
			followObject->GetTransform()->SetScale(Vector3(30, 30, 0));
			followObject->AddComponent(std::make_shared<FollowObjectScript>(player));
		}

		camera->AddComponent(std::make_shared<FollowTargetScript>(player));
		Scene::Init();
	}
	void TestScene::Update()
	{
		Scene::Update();
	}
	void TestScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void TestScene::OnEnter()
	{
		Scene::OnEnter();
	}
	void TestScene::OnExit()
	{
		Scene::OnExit();
	}
}