#include "std.h"
#include "Js_PlayScene.h"
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
#include "Js_SceneManager.h"
#include "Js_SoundManager.h"
#include "Js_TitleScene.h"


// Scripts
#include "Js_FireballScript.h"
#include "Js_MoveScripts.h"
#include "Js_RotateScript.h"
#include "Js_FollowTargetScript.h"
#include "Js_PlayerScript.h"
#include "Js_MarioCameraScript.h"
#include "Js_DefaultMoveScript.h"
#include "Js_MarioScript.h"
#include "Js_WallScript.h"
#include "Js_EndLineScript.h"
#include "Js_GoombaScript.h"

namespace Js
{
	void PlayScene::Init()
	{
#pragma region ObjectInitailize

		m_Goombas.resize(10);

#pragma endregion

#pragma region Camera
		camera = object::Instantiate<DxObject>();
		{
			camera->AddComponent(std::make_shared<Camera>());
		}
#pragma endregion

#pragma region BackGround
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
		}
#pragma endregion

#pragma region Player

		player = object::Instantiate<Player>(L"Player", LayerType::Player);
		{
			auto meshRender = std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext());
			player->AddComponent(meshRender);
			auto mesh = I_Resource->Get<Mesh>(L"Rectangle");
			meshRender->SetMesh(mesh);
			auto material = I_Resource->Get<Material>(L"Default");
			meshRender->SetMaterial(material);
			player->GetTransform()->SetPosition(Vector3(-2700, -400, 0));
			player->GetTransform()->SetScale(player->GetSize());
		    //player->AddComponent(std::make_shared<MoveScript>());
		    player->AddComponent(std::make_shared<PlayerScript>());
		    player->AddComponent(std::make_shared<Rigidbody>());
			//player->AddComponent(std::make_shared<FireballScript>(player));
			auto animator = std::make_shared<Animator>();
			player->AddComponent(animator);
			auto anim = I_Resource->Get<Animation>(L"Mario_rightIdle");
			animator->SetAnimation(anim);
			auto col = std::make_shared<Collider>();
			player->AddComponent(col);
		}
#pragma endregion

#pragma region End of Wall
		std::shared_ptr<DxObject> endWall = object::Instantiate<DxObject>(L"wall", LayerType::Wall);
		{
			auto meshRender = std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext());
			endWall->AddComponent(meshRender);
			auto mesh = I_Resource->Get<Mesh>(L"Rectangle");
			meshRender->SetMesh(mesh);
			auto material = I_Resource->Get<Material>(L"Block1");
			meshRender->SetMaterial(material);
			endWall->GetTransform()->SetScale(Vector3(16, 1000, 1));
			endWall->GetTransform()->SetPosition(Vector3(-2898, -300, 0));
			auto col = std::make_shared<Collider>();
			endWall->AddComponent(col);
			endWall->AddComponent(std::make_shared<EndLineScript>());
		}
#pragma endregion

		m_Goombas[0] = object::Instantiate<DxObject>(L"Goomba", LayerType::Monster);
		{
			auto meshRender = std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext());
			m_Goombas[0]->AddComponent(meshRender);
			auto mesh = I_Resource->Get<Mesh>(L"Rectangle");
			meshRender->SetMesh(mesh);
			auto material = I_Resource->Get<Material>(L"Block1");
			meshRender->SetMaterial(material);
			m_Goombas[0]->GetTransform()->SetScale(m_Goombas[0]->GetSize());
			m_Goombas[0]->GetTransform()->SetPosition(Vector3(-2240, -400, 0));

			auto col = std::make_shared<Collider>();
			m_Goombas[0]->AddComponent(col);

			auto animator = std::make_shared<Animator>();
			m_Goombas[0]->AddComponent(animator);
			auto anim = I_Resource->Get<Animation>(L"굼바");
			animator->SetAnimation(anim);
			m_Goombas[0]->AddComponent(std::make_shared<GoombaScript>());
		}

		std::shared_ptr<DxObject> tower = object::Instantiate<DxObject>(L"wall", LayerType::Wall);
		{
			auto meshRender = std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext());
			tower->AddComponent(meshRender);
			auto mesh = I_Resource->Get<Mesh>(L"Rectangle");
			meshRender->SetMesh(mesh);
			auto material = I_Resource->Get<Material>(L"Block1");
			meshRender->SetMaterial(material);
			tower->GetTransform()->SetScale(tower->GetSize() * 2);
			tower->GetTransform()->SetPosition(Vector3(-2140, -400, 0));
			auto col = std::make_shared<Collider>();
			tower->AddComponent(col);
		}


		std::shared_ptr<DxObject> tower2 = object::Instantiate<DxObject>(L"wall", LayerType::Wall);
		{
			auto meshRender = std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext());
			tower2->AddComponent(meshRender);
			auto mesh = I_Resource->Get<Mesh>(L"Rectangle");
			meshRender->SetMesh(mesh);
			auto material = I_Resource->Get<Material>(L"Block3");
			meshRender->SetMaterial(material);
			tower2->GetTransform()->SetScale(tower->GetSize() * 2);
			tower2->GetTransform()->SetPosition(Vector3(-2400, -400, 0));
			auto col = std::make_shared<Collider>();
			tower2->AddComponent(col);
		}

		std::shared_ptr<DxObject> tower3 = object::Instantiate<DxObject>(L"wall", LayerType::Wall);
		{
			auto meshRender = std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext());
			tower3->AddComponent(meshRender);
			auto mesh = I_Resource->Get<Mesh>(L"Rectangle");
			meshRender->SetMesh(mesh);
			auto material = I_Resource->Get<Material>(L"Block2");
			meshRender->SetMaterial(material);
			tower3->GetTransform()->SetScale(tower3->GetSize());
			tower3->GetTransform()->SetPosition(Vector3(-2700, -300, 0));
			auto col = std::make_shared<Collider>();
			tower3->AddComponent(col);
			tower3->AddComponent(std::make_shared<WallScript>());
		}

		std::shared_ptr<DxObject> Floor1 = object::Instantiate<DxObject>(L"floor", LayerType::Floor);
		{
			//auto meshRender = std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext());
			//wall1->AddComponent(meshRender);
			//auto mesh = I_Resource->Get<Mesh>(L"Rectangle");
			//meshRender->SetMesh(mesh);
			//auto material = I_Resource->Get<Material>(L"Default");
			//meshRender->SetMaterial(material);
			Floor1->GetTransform()->SetScale(Vector3(992, 16, 0));
			Floor1->GetTransform()->SetPosition(Vector3(-1888, -452, 0));
			auto col = std::make_shared<Collider>();
			Floor1->AddComponent(col);
		}

		walls2.resize(15);
		for (int i = 0; i < walls2.size(); i++)
		{
			float width = 32 * i;
			walls2[i] = object::Instantiate<DxObject>(L"wall", LayerType::Floor);
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
			walls3[i] = object::Instantiate<DxObject>(L"wall", LayerType::Floor);
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

		monster = object::Instantiate<DxObject>(L"Monster", LayerType::Monster);
		{
			auto meshRender = std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext());
			monster->AddComponent(meshRender);
			auto mesh = I_Resource->Get<Mesh>(L"Rectangle");
			meshRender->SetMesh(mesh);
			auto material = I_Resource->Get<Material>(L"마리오2");
			meshRender->SetMaterial(material);
			monster->GetTransform()->SetScale(monster->GetSize());
			monster->GetTransform()->SetPosition(Vector3(-2864, -208, 0));
			auto col = std::make_shared<Collider>();
			monster->AddComponent(col);
		}

		std::shared_ptr<DxObject> mushroom = object::Instantiate<DxObject>(L"Monster", LayerType::MunshRoom);
		{
			auto meshRender = std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext());
			mushroom->AddComponent(meshRender);
			auto mesh = I_Resource->Get<Mesh>(L"Rectangle");
			meshRender->SetMesh(mesh);
			auto material = I_Resource->Get<Material>(L"마리오2");
			meshRender->SetMaterial(material);
			mushroom->GetTransform()->SetScale(mushroom->GetSize());
			mushroom->GetTransform()->SetPosition(Vector3(-2600, -300, 0));
			auto col = std::make_shared<Collider>();
			mushroom->AddComponent(col);
		}

		std::shared_ptr<DxObject> deadLine = object::Instantiate<DxObject>(L"DeadLine", LayerType::End);
		{
			auto meshRender = std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext());
			deadLine->AddComponent(meshRender);
			auto mesh = I_Resource->Get<Mesh>(L"Rectangle");
			meshRender->SetMesh(mesh);
			auto material = I_Resource->Get<Material>(L"Default");
			meshRender->SetMaterial(material);
			deadLine->GetTransform()->SetScale(Vector3(10000, 16, 0));
			deadLine->GetTransform()->SetPosition(Vector3(-1888, -520, 0));
			auto col = std::make_shared<Collider>();
			deadLine->AddComponent(col);
		}

		camera->AddComponent(std::make_shared<FollowTargetScript>(player));
		camera->AddComponent(std::make_shared<MarioCameraScript>(player));
		Scene::Init();
	}

	void PlayScene::Update()
	{
		Scene::Update();
	}
	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void PlayScene::Render(std::shared_ptr<Pipeline> _pipeline)
	{
		Scene::Render(_pipeline);
	}
	void PlayScene::OnEnter()
	{
		Scene::OnEnter();
		CollisionManager::CollisionLayerCheck(LayerType::Player, LayerType::End, true);
		CollisionManager::CollisionLayerCheck(LayerType::Player, LayerType::Floor, true);
		CollisionManager::CollisionLayerCheck(LayerType::Player, LayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(LayerType::Player, LayerType::Wall, true);
		CollisionManager::CollisionLayerCheck(LayerType::Player, LayerType::MunshRoom, true);

		CollisionManager::CollisionLayerCheck(LayerType::Monster, LayerType::Wall, true);
		CollisionManager::CollisionLayerCheck(LayerType::Monster, LayerType::Floor, true);

		CollisionManager::CollisionLayerCheck(LayerType::MunshRoom, LayerType::Wall, true);
		CollisionManager::CollisionLayerCheck(LayerType::MunshRoom, LayerType::Floor, true);

		SoundManager::Add(L"overworld.wav", L"overworld.wav");
		m_Sound = SoundManager::Get(L"overworld.wav");
		if (m_Sound) 
			m_Sound->Play(true);
	}
	void PlayScene::OnExit()
	{
		Scene::OnExit();

	}
}