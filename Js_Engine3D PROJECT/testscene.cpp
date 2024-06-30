#include "testscene.h"
#include "std.h"
#include "Js_Core.h"
#include "Js_Time.h"
#include "Js_Input.h"
#include "Js_DxObject.h"
#include "Js_Component.h"
#include "Js_Transform.h"
#include "Js_Camera.h"
#include "Js_Animator.h"
#include "Js_Collision.h"
#include "Js_MeshRenderer.h"
#include "Js_Fireball.h"
#include "Js_Object.h"
#include "Js_Player.h"
#include "Js_Rigidbody.h"

// Scripts
#include "Js_FireballScript.h"
#include "Js_MoveScripts.h"
#include "Js_RotateScript.h"
#include "Js_FollowTargetScript.h"
#include "Js_PlayerScript.h"

namespace Js
{
	void testscene::Init()
	{
		camera = object::Instantiate<DxObject>();
		{
			camera->AddComponent(std::make_shared<Camera>());
			camera->Init();
		}

		bg = object::Instantiate<DxObject>(L"BackGround");
		{
			auto meshRender = std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext());
			bg->AddComponent(meshRender);
			auto mesh = I_Resource->Get<Mesh>(L"Rectangle");
			meshRender->SetMesh(mesh);
			auto material = I_Resource->Get<Material>(L"Map");
			meshRender->SetMaterial(material);
			bg->GetTransform()->SetPosition(Vector3(0, 0, 0));
			bg->GetTransform()->SetScale(bg->GetSize());
			bg->GetSize();
		}

		player = object::Instantiate<Player>(L"Player");
		{
			auto meshRender = std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext());
			player->AddComponent(meshRender);
			auto mesh = I_Resource->Get<Mesh>(L"Rectangle");
			meshRender->SetMesh(mesh);
			auto material = I_Resource->Get<Material>(L"Default");
			meshRender->SetMaterial(material);
			player->GetTransform()->SetPosition(Vector3(-2700, -240, 0));
			player->GetTransform()->SetScale(player->GetSize());
			player->AddComponent(std::make_shared<MoveScript>());
			//player->AddComponent(std::make_shared<PlayerScript>());
			//player->AddComponent(std::make_shared<Rigidbody>());
			player->AddComponent(std::make_shared<FireballScript>(player));
			
			auto animator = std::make_shared<Animator>();
			player->AddComponent(animator);
			auto anim = I_Resource->Get<Animation>(L"Mario1_Move");
			animator->SetAnimation(anim);
		}

		walls1.resize(62);
		for (int i = 0; i < walls1.size(); i++)
		{
			float width = 32 * i;
			walls1[i] = object::Instantiate<DxObject>(L"wall");
			{
				auto meshRender = std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext());
				walls1[i]->AddComponent(meshRender);
				auto mesh = I_Resource->Get<Mesh>(L"Rectangle");
				meshRender->SetMesh(mesh);
				auto material = I_Resource->Get<Material>(L"Default");
				meshRender->SetMaterial(material);
				walls1[i]->GetTransform()->SetScale(walls1[i]->GetSize());
				walls1[i]->GetTransform()->SetPosition(Vector3(-2864 + width, -272, 0));
			}
		}



		walls2.resize(15);
		for (int i = 0; i < walls2.size(); i++)
		{
			float width = 32 * i;
			walls2[i] = object::Instantiate<DxObject>(L"wall");
			{
				auto meshRender = std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext());
				walls2[i]->AddComponent(meshRender);
				auto mesh = I_Resource->Get<Mesh>(L"Rectangle");
				meshRender->SetMesh(mesh);
				auto material = I_Resource->Get<Material>(L"Default");
				meshRender->SetMaterial(material);
				walls2[i]->GetTransform()->SetScale(walls2[i]->GetSize());
				walls2[i]->GetTransform()->SetPosition(Vector3(-816 + width, -272, 0));
			}
		}

		walls3.resize(43);
		for (int i = 0; i < walls3.size(); i++)
		{
			float width = 32 * i;
			walls3[i] = object::Instantiate<DxObject>(L"wall");
			{
				auto meshRender = std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext());
				walls3[i]->AddComponent(meshRender);
				auto mesh = I_Resource->Get<Mesh>(L"Rectangle");
				meshRender->SetMesh(mesh);
				auto material = I_Resource->Get<Material>(L"Default");
				meshRender->SetMaterial(material);
				walls3[i]->GetTransform()->SetScale(walls3[i]->GetSize());
				walls3[i]->GetTransform()->SetPosition(Vector3(-272 + width, -272, 0));
			}
		}

		walls4.resize(54);
		for (int i = 0; i < walls4.size(); i++)
		{
			float width = 32 * i;
			walls4[i] = object::Instantiate<DxObject>(L"wall");
			{
				auto meshRender = std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext());
				walls4[i]->AddComponent(meshRender);
				auto mesh = I_Resource->Get<Mesh>(L"Rectangle");
				meshRender->SetMesh(mesh);
				auto material = I_Resource->Get<Material>(L"Default");
				meshRender->SetMaterial(material);
				walls4[i]->GetTransform()->SetScale(walls4[i]->GetSize());
				walls4[i]->GetTransform()->SetPosition(Vector3(1170 + width, -240, 0));
			}
		}

		monster = object::Instantiate<DxObject>(L"Monster");
		{
			auto meshRender = std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext());
			monster->AddComponent(meshRender);
			auto mesh = I_Resource->Get<Mesh>(L"Rectangle");
			meshRender->SetMesh(mesh);
			auto material = I_Resource->Get<Material>(L"Default");
			meshRender->SetMaterial(material);
			monster->GetTransform()->SetScale(monster->GetSize());
			monster->GetTransform()->SetPosition(Vector3(-2864, -272, 0));
		}

		camera->AddComponent(std::make_shared<FollowTargetScript>(player));
		Scene::Init();
	}

	void testscene::Update()
	{
		Scene::Update();
	}
	void testscene::LateUpdate()
	{
		Vector3 pushVector;
		if (Collision::CheckCollision(player->GetTransform()->GetRect(), monster->GetTransform()->GetRect(), pushVector))
		{
			OutputDebugStringA("Collision detected!\n");
			// 충돌 방향으로 밀어내기
			player->GetTransform()->SetPosition(player->GetTransform()->GetPosition() + pushVector);
		}

		//if (CheckCollision(player->GetTransform()->GetRect(), monster->GetTransform()->GetRect()))
		//{
		//	object::Destory(monster);
		//}
		Scene::LateUpdate();
	}
	void testscene::Render(std::shared_ptr<Pipeline> _pipeline)
	{
		Scene::Render(_pipeline);
	}
	void testscene::OnEnter()
	{
	}
}