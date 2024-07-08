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
#include "Js_MushroomWallScript.h"
#include "Js_EndLineScript.h"
#include "Js_GoombaScript.h"
#include "Js_EndPointScript.h"
#include "Js_KoopaScript.h"
#include "Js_FlowerWallScript.h"

namespace Js
{
	void PlayScene::Init()
	{
#pragma region ObjectInitailize

		m_Goombas.resize(100);

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

#pragma region Floors

		std::shared_ptr<DxObject> Floor1 = object::Instantiate<DxObject>(L"floor", LayerType::Floor);
		{
			Floor1->GetTransform()->SetScale(Vector3(992, 16, 0));
			Floor1->GetTransform()->SetPosition(Vector3(-1888, -452, 0));
			auto col = std::make_shared<Collider>();
			Floor1->AddComponent(col);
		}

		std::shared_ptr<DxObject> Floor2 = object::Instantiate<DxObject>(L"floor", LayerType::Floor);
		{
			Floor2->GetTransform()->SetScale(Vector3(16 * 15, 16, 0));
			Floor2->GetTransform()->SetPosition(Vector3(-592, -452, 0));
			auto col = std::make_shared<Collider>();
			Floor2->AddComponent(col);
		}

		std::shared_ptr<DxObject> Floor3 = object::Instantiate<DxObject>(L"floor", LayerType::Floor);
		{
			Floor3->GetTransform()->SetScale(Vector3(16 * 43, 16, 0));
			Floor3->GetTransform()->SetPosition(Vector3(400, -452, 0));
			auto col = std::make_shared<Collider>();
			Floor3->AddComponent(col);
		}

		std::shared_ptr<DxObject> Floor4 = object::Instantiate<DxObject>(L"floor", LayerType::Floor);
		{
			Floor4->GetTransform()->SetScale(Vector3(16 * 54, 16, 0));
			Floor4->GetTransform()->SetPosition(Vector3(2016, -452, 0));
			auto col = std::make_shared<Collider>();
			Floor4->AddComponent(col);
		}

#pragma endregion

#pragma region Tower

		std::shared_ptr<DxObject> tower = object::Instantiate<DxObject>(L"wall", LayerType::Wall);
		{
			tower->GetTransform()->SetScale(Vector3(32, 32, 0));
			tower->GetTransform()->SetPosition(Vector3(-2140, -400, 0));
			auto col = std::make_shared<Collider>();
			tower->AddComponent(col);
		}
		std::shared_ptr<DxObject> tower2 = object::Instantiate<DxObject>(L"wall", LayerType::Wall);
		{
			tower2->GetTransform()->SetScale(Vector3(32, 48, 0));
			tower2->GetTransform()->SetPosition(Vector3(-1850, -390, 0));
			auto col = std::make_shared<Collider>();
			tower2->AddComponent(col);
		}
		std::shared_ptr<DxObject> tower3 = object::Instantiate<DxObject>(L"wall", LayerType::Wall);
		{
			tower3->GetTransform()->SetScale(Vector3(32, 60, 0));
			tower3->GetTransform()->SetPosition(Vector3(-1538, -370, 0));
			auto col = std::make_shared<Collider>();
			tower3->AddComponent(col);
		}
		std::shared_ptr<DxObject> tower4 = object::Instantiate<DxObject>(L"wall", LayerType::Wall);
		{
			tower4->GetTransform()->SetScale(Vector3(32, 60, 0));
			tower4->GetTransform()->SetPosition(Vector3(-1116, -360, 0));
			auto col = std::make_shared<Collider>();
			tower4->AddComponent(col);
		}
		std::shared_ptr<DxObject> tower5 = object::Instantiate<DxObject>(L"wall", LayerType::Wall);
		{
			tower5->GetTransform()->SetScale(Vector3(32, 60, 0));
			tower5->GetTransform()->SetPosition(Vector3(224, -370, 0));
			auto col = std::make_shared<Collider>();
			tower5->AddComponent(col);
		}
		std::shared_ptr<DxObject> tower6 = object::Instantiate<DxObject>(L"wall", LayerType::Wall);
		{
			tower6->GetTransform()->SetScale(Vector3(32, 60, 0));
			tower6->GetTransform()->SetPosition(Vector3(874, -370, 0));
			auto col = std::make_shared<Collider>();
			tower6->AddComponent(col);
		}
		std::shared_ptr<DxObject> tower7 = object::Instantiate<DxObject>(L"wall", LayerType::Wall);
		{
			tower7->GetTransform()->SetScale(Vector3(32, 32, 0));
			tower7->GetTransform()->SetPosition(Vector3(1566, -400, 0));
			auto col = std::make_shared<Collider>();
			tower7->AddComponent(col);
		}
#pragma endregion

#pragma region NomalWall
		{
			std::shared_ptr<DxObject> wall5 = object::Instantiate<DxObject>(L"wall", LayerType::Wall);
			{
				auto meshRender = std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext());
				wall5->AddComponent(meshRender);
				auto mesh = I_Resource->Get<Mesh>(L"Rectangle");
				meshRender->SetMesh(mesh);
				auto material = I_Resource->Get<Material>(L"Block4");
				meshRender->SetMaterial(material);
				wall5->GetTransform()->SetScale(wall5->GetSize());
				wall5->GetTransform()->SetPosition(Vector3(1774, -420, 0));
				auto col = std::make_shared<Collider>();
				wall5->AddComponent(col);
				wall5->AddComponent(std::make_shared<MushroomWalllScript>());
			}

			std::vector<std::shared_ptr<DxObject>> walls(2);
			for (int i = 0; i < walls.size(); i++)
			{
				walls[i] = object::Instantiate<DxObject>(L"wall", LayerType::Wall);
				auto meshRender = std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext());
				walls[i]->AddComponent(meshRender);
				auto mesh = I_Resource->Get<Mesh>(L"Rectangle");
				meshRender->SetMesh(mesh);
				auto material = I_Resource->Get<Material>(L"Block4");
				meshRender->SetMaterial(material);
				walls[i]->GetTransform()->SetScale(walls[i]->GetSize());
				walls[i]->GetTransform()->SetPosition(Vector3(1806, -420 + i * 32, 0));
				auto col = std::make_shared<Collider>();
				walls[i]->AddComponent(col);
			}

			std::vector<std::shared_ptr<DxObject>> walls2(3);
			for (int i = 0; i < walls2.size(); i++)
			{
				walls2[i] = object::Instantiate<DxObject>(L"wall", LayerType::Wall);
				auto meshRender = std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext());
				walls2[i]->AddComponent(meshRender);
				auto mesh = I_Resource->Get<Mesh>(L"Rectangle");
				meshRender->SetMesh(mesh);
				auto material = I_Resource->Get<Material>(L"Block4");
				meshRender->SetMaterial(material);
				walls2[i]->GetTransform()->SetScale(walls2[i]->GetSize());
				walls2[i]->GetTransform()->SetPosition(Vector3(1838, -420 + i * 32, 0));
				auto col = std::make_shared<Collider>();
				walls2[i]->AddComponent(col);
			}
			std::vector<std::shared_ptr<DxObject>> walls3(4);
			for (int i = 0; i < walls3.size(); i++)
			{
				walls3[i] = object::Instantiate<DxObject>(L"wall", LayerType::Wall);
				auto meshRender = std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext());
				walls3[i]->AddComponent(meshRender);
				auto mesh = I_Resource->Get<Mesh>(L"Rectangle");
				meshRender->SetMesh(mesh);
				auto material = I_Resource->Get<Material>(L"Block4");
				meshRender->SetMaterial(material);
				walls3[i]->GetTransform()->SetScale(walls3[i]->GetSize());
				walls3[i]->GetTransform()->SetPosition(Vector3(1870, -420 + i * 32, 0));
				auto col = std::make_shared<Collider>();
				walls3[i]->AddComponent(col);
			}
			std::vector<std::shared_ptr<DxObject>> walls4(5);
			for (int i = 0; i < walls4.size(); i++)
			{
				walls4[i] = object::Instantiate<DxObject>(L"wall", LayerType::Wall);
				auto meshRender = std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext());
				walls4[i]->AddComponent(meshRender);
				auto mesh = I_Resource->Get<Mesh>(L"Rectangle");
				meshRender->SetMesh(mesh);
				auto material = I_Resource->Get<Material>(L"Block4");
				meshRender->SetMaterial(material);
				walls4[i]->GetTransform()->SetScale(walls4[i]->GetSize());
				walls4[i]->GetTransform()->SetPosition(Vector3(1902, -420 + i * 32, 0));
				auto col = std::make_shared<Collider>();
				walls4[i]->AddComponent(col);
			}
			std::vector<std::shared_ptr<DxObject>> walls5(6);
			for (int i = 0; i < walls5.size(); i++)
			{
				walls5[i] = object::Instantiate<DxObject>(L"wall", LayerType::Wall);
				auto meshRender = std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext());
				walls5[i]->AddComponent(meshRender);
				auto mesh = I_Resource->Get<Mesh>(L"Rectangle");
				meshRender->SetMesh(mesh);
				auto material = I_Resource->Get<Material>(L"Block4");
				meshRender->SetMaterial(material);
				walls5[i]->GetTransform()->SetScale(walls5[i]->GetSize());
				walls5[i]->GetTransform()->SetPosition(Vector3(1934, -420 + i * 32, 0));
				auto col = std::make_shared<Collider>();
				walls5[i]->AddComponent(col);
			}
			std::vector<std::shared_ptr<DxObject>> walls6(7);
			for (int i = 0; i < walls6.size(); i++)
			{
				walls6[i] = object::Instantiate<DxObject>(L"wall", LayerType::Wall);
				auto meshRender = std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext());
				walls6[i]->AddComponent(meshRender);
				auto mesh = I_Resource->Get<Mesh>(L"Rectangle");
				meshRender->SetMesh(mesh);
				auto material = I_Resource->Get<Material>(L"Block4");
				meshRender->SetMaterial(material);
				walls6[i]->GetTransform()->SetScale(walls6[i]->GetSize());
				walls6[i]->GetTransform()->SetPosition(Vector3(1966, -420 + i * 32, 0));
				auto col = std::make_shared<Collider>();
				walls6[i]->AddComponent(col);
			}
			std::vector<std::shared_ptr<DxObject>> walls7(8);
			for (int i = 0; i < walls7.size(); i++)
			{
				walls7[i] = object::Instantiate<DxObject>(L"wall", LayerType::Wall);
				auto meshRender = std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext());
				walls7[i]->AddComponent(meshRender);
				auto mesh = I_Resource->Get<Mesh>(L"Rectangle");
				meshRender->SetMesh(mesh);
				auto material = I_Resource->Get<Material>(L"Block4");
				meshRender->SetMaterial(material);
				walls7[i]->GetTransform()->SetScale(walls7[i]->GetSize());
				walls7[i]->GetTransform()->SetPosition(Vector3(1998, -420 + i * 32, 0));
				auto col = std::make_shared<Collider>();
				walls7[i]->AddComponent(col);
			}
		}
#pragma endregion

#pragma region Wall
		std::shared_ptr<DxObject> wall1 = object::Instantiate<DxObject>(L"wall", LayerType::WallEnd);
		{
			auto meshRender = std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext());
			wall1->AddComponent(meshRender);
			auto mesh = I_Resource->Get<Mesh>(L"Rectangle");
			meshRender->SetMesh(mesh);
			auto material = I_Resource->Get<Material>(L"Block3");
			meshRender->SetMaterial(material);
			wall1->GetTransform()->SetScale(wall1->GetSize());
			wall1->GetTransform()->SetPosition(Vector3(-2300, -300, 0));
			auto col = std::make_shared<Collider>();
			wall1->AddComponent(col);
		}
		std::shared_ptr<DxObject> wall2 = object::Instantiate<DxObject>(L"wall", LayerType::Wall);
		{
			auto meshRender = std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext());
			wall2->AddComponent(meshRender);
			auto mesh = I_Resource->Get<Mesh>(L"Rectangle");
			meshRender->SetMesh(mesh);
			auto material = I_Resource->Get<Material>(L"Block1");
			meshRender->SetMaterial(material);
			wall2 ->GetTransform()->SetScale(wall2->GetSize());
			wall2 ->GetTransform()->SetPosition(Vector3(-2332, -300, 0));
			auto col = std::make_shared<Collider>();
			wall2 ->AddComponent(col);
			wall2 ->AddComponent(std::make_shared<MushroomWalllScript>());
		}
		std::shared_ptr<DxObject> wall3 = object::Instantiate<DxObject>(L"wall", LayerType::Wall);
		{
			auto meshRender = std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext());
			wall3->AddComponent(meshRender);
			auto mesh = I_Resource->Get<Mesh>(L"Rectangle");
			meshRender->SetMesh(mesh);
			auto material = I_Resource->Get<Material>(L"Block3");
			meshRender->SetMaterial(material);
			wall3->GetTransform()->SetScale(wall3->GetSize());
			wall3->GetTransform()->SetPosition(Vector3(-2364, -300, 0));
			auto col = std::make_shared<Collider>();
			wall3->AddComponent(col);
		}

		std::shared_ptr<DxObject> wall4 = object::Instantiate<DxObject>(L"wall", LayerType::WallEnd);
		{
			auto meshRender = std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext());
			wall4->AddComponent(meshRender);
			auto mesh = I_Resource->Get<Mesh>(L"Rectangle");
			meshRender->SetMesh(mesh);
			auto material = I_Resource->Get<Material>(L"Block3");
			meshRender->SetMaterial(material);
			wall4->GetTransform()->SetScale(wall4->GetSize());
			wall4->GetTransform()->SetPosition(Vector3(-600, -300, 0));
			auto col = std::make_shared<Collider>();
			wall4->AddComponent(col);
		}
		std::shared_ptr<DxObject> wall5 = object::Instantiate<DxObject>(L"wall", LayerType::Wall);
		{
			auto meshRender = std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext());
			wall5->AddComponent(meshRender);
			auto mesh = I_Resource->Get<Mesh>(L"Rectangle");
			meshRender->SetMesh(mesh);
			auto material = I_Resource->Get<Material>(L"Block1");
			meshRender->SetMaterial(material);
			wall5->GetTransform()->SetScale(wall2->GetSize());
			wall5->GetTransform()->SetPosition(Vector3(-632, -300, 0));
			auto col = std::make_shared<Collider>();
			wall5->AddComponent(col);
			wall5->AddComponent(std::make_shared<MushroomWalllScript>());
		}
		std::shared_ptr<DxObject> wall6 = object::Instantiate<DxObject>(L"wall", LayerType::Wall);
		{
			auto meshRender = std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext());
			wall6->AddComponent(meshRender);
			auto mesh = I_Resource->Get<Mesh>(L"Rectangle");
			meshRender->SetMesh(mesh);
			auto material = I_Resource->Get<Material>(L"Block3");
			meshRender->SetMaterial(material);
			wall6->GetTransform()->SetScale(wall6->GetSize());
			wall6->GetTransform()->SetPosition(Vector3(-664, -300, 0));
			auto col = std::make_shared<Collider>();
			wall6->AddComponent(col);
		}
		std::shared_ptr<DxObject> wall7 = object::Instantiate<DxObject>(L"wall", LayerType::Wall);
		{
			auto meshRender = std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext());
			wall7->AddComponent(meshRender);
			auto mesh = I_Resource->Get<Mesh>(L"Rectangle");
			meshRender->SetMesh(mesh);
			auto material = I_Resource->Get<Material>(L"Block3");
			meshRender->SetMaterial(material);
			wall7->GetTransform()->SetScale(wall6->GetSize());
			wall7->GetTransform()->SetPosition(Vector3(-696, -300, 0));
			auto col = std::make_shared<Collider>();
			wall7->AddComponent(col);
		}
		std::shared_ptr<DxObject> wall8 = object::Instantiate<DxObject>(L"wall", LayerType::Wall);
		{
			auto meshRender = std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext());
			wall8->AddComponent(meshRender);
			auto mesh = I_Resource->Get<Mesh>(L"Rectangle");
			meshRender->SetMesh(mesh);
			auto material = I_Resource->Get<Material>(L"Block1");
			meshRender->SetMaterial(material);
			wall8->GetTransform()->SetScale(wall8->GetSize());
			wall8->GetTransform()->SetPosition(Vector3(0, -300, 0));
			auto col = std::make_shared<Collider>();
			wall8->AddComponent(col);
			wall8->AddComponent(std::make_shared<FlowerWallScript>());
		}

#pragma endregion

		/*
		std::shared_ptr<DxObject> Flower = object::Instantiate<DxObject>(L"Monster", LayerType::Flower);
		{
			auto meshRender = std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext());
			Flower->AddComponent(meshRender);
			auto mesh = I_Resource->Get<Mesh>(L"Rectangle");
			meshRender->SetMesh(mesh);
			auto material = I_Resource->Get<Material>(L"²É");
			meshRender->SetMaterial(material);
			Flower->GetTransform()->SetScale(Flower->GetSize());
			Flower->GetTransform()->SetPosition(Vector3(-2600, -300, 0));
			auto col = std::make_shared<Collider>();
			Flower->AddComponent(col);
		}
		*/
#pragma region DeadLine
		std::shared_ptr<DxObject> deadLine = object::Instantiate<DxObject>(L"DeadLine", LayerType::End);
		{
			deadLine->GetTransform()->SetScale(Vector3(10000, 16, 0));
			deadLine->GetTransform()->SetPosition(Vector3(-1888, -520, 0));
			auto col = std::make_shared<Collider>();
			deadLine->AddComponent(col);
		}
#pragma endregion

#pragma region GameEndPoint
		std::shared_ptr<DxObject> flag = object::Instantiate<DxObject>(L"Flag", LayerType::EndPoint);
		{
			flag->GetTransform()->SetScale(Vector3(16, 1000, 0));
			flag->GetTransform()->SetPosition(Vector3(2380, -300, 0));
			auto col = std::make_shared<Collider>();
			flag->AddComponent(col);
			flag->AddComponent(std::make_shared<EndPointScript>());
		}

		std::shared_ptr<DxObject> endPoint = object::Instantiate<DxObject>(L"EndPoint", LayerType::Flag);
		{
			endPoint->GetTransform()->SetScale(Vector3(16, 10000, 0));
			endPoint->GetTransform()->SetPosition(Vector3(2200, -300, 0));
			auto col = std::make_shared<Collider>();
			endPoint->AddComponent(col);
		}
#pragma endregion

#pragma region Monsters

		m_Goombas[0] = object::Instantiate<DxObject>(L"Goomba", LayerType::Monster);
		{
			auto meshRender = std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext());
			m_Goombas[0]->AddComponent(meshRender);
			auto mesh = I_Resource->Get<Mesh>(L"Rectangle");
			meshRender->SetMesh(mesh);
			auto material = I_Resource->Get<Material>(L"Block1");
			meshRender->SetMaterial(material);
			m_Goombas[0]->GetTransform()->SetScale(m_Goombas[0]->GetSize());
			m_Goombas[0]->GetTransform()->SetPosition(Vector3(-2040, -400, 0));

			auto col = std::make_shared<Collider>();
			m_Goombas[0]->AddComponent(col);

			auto animator = std::make_shared<Animator>();
			m_Goombas[0]->AddComponent(animator);
			auto anim = I_Resource->Get<Animation>(L"±À¹Ù");
			animator->SetAnimation(anim);
			m_Goombas[0]->AddComponent(std::make_shared<GoombaScript>());
		}

		m_Goombas[1] = object::Instantiate<DxObject>(L"Goomba", LayerType::Monster);
		{
			auto meshRender = std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext());
			m_Goombas[1]->AddComponent(meshRender);
			auto mesh = I_Resource->Get<Mesh>(L"Rectangle");
			meshRender->SetMesh(mesh);
			auto material = I_Resource->Get<Material>(L"Block1");
			meshRender->SetMaterial(material);
			m_Goombas[1]->GetTransform()->SetScale(m_Goombas[1]->GetSize());
			m_Goombas[1]->GetTransform()->SetPosition(Vector3(-2072, -400, 0));

			auto col = std::make_shared<Collider>();
			m_Goombas[1]->AddComponent(col);

			auto animator = std::make_shared<Animator>();
			m_Goombas[1]->AddComponent(animator);
			auto anim = I_Resource->Get<Animation>(L"±À¹Ù");
			animator->SetAnimation(anim);
			m_Goombas[1]->AddComponent(std::make_shared<GoombaScript>());
		}

		for (int i = 2; i < 5; i++)
		{
			m_Goombas[i] = object::Instantiate<DxObject>(L"Goomba", LayerType::Monster);
			{
				auto meshRender = std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext());
				m_Goombas[i]->AddComponent(meshRender);
				auto mesh = I_Resource->Get<Mesh>(L"Rectangle");
				meshRender->SetMesh(mesh);
				auto material = I_Resource->Get<Material>(L"Block1");
				meshRender->SetMaterial(material);
				m_Goombas[i]->GetTransform()->SetScale(m_Goombas[i]->GetSize());
				m_Goombas[i]->GetTransform()->SetPosition(Vector3(500 + i * 32 , -400, 0));

				auto col = std::make_shared<Collider>();
				m_Goombas[i]->AddComponent(col);

				auto animator = std::make_shared<Animator>();
				m_Goombas[i]->AddComponent(animator);
				auto anim = I_Resource->Get<Animation>(L"±À¹Ù");
				animator->SetAnimation(anim);
				m_Goombas[i]->AddComponent(std::make_shared<GoombaScript>());
			}
		}

		for (int i = 5; i < 13; i++)
		{
			m_Goombas[i] = object::Instantiate<DxObject>(L"Goomba", LayerType::Monster);
			{
				auto meshRender = std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext());
				m_Goombas[i]->AddComponent(meshRender);
				auto mesh = I_Resource->Get<Mesh>(L"Rectangle");
				meshRender->SetMesh(mesh);
				auto material = I_Resource->Get<Material>(L"Block1");
				meshRender->SetMaterial(material);
				m_Goombas[i]->GetTransform()->SetScale(m_Goombas[i]->GetSize());
				m_Goombas[i]->GetTransform()->SetPosition(Vector3(-1780 + i * 32, -400, 0));

				auto col = std::make_shared<Collider>();
				m_Goombas[i]->AddComponent(col);

				auto animator = std::make_shared<Animator>();
				m_Goombas[i]->AddComponent(animator);
				auto anim = I_Resource->Get<Animation>(L"±À¹Ù");
				animator->SetAnimation(anim);
				m_Goombas[i]->AddComponent(std::make_shared<GoombaScript>());
			}
		}

		std::shared_ptr<DxObject> koopa = object::Instantiate<DxObject>(L"koopa", LayerType::Monster);
		{
			auto meshRender = std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext());
			koopa->AddComponent(meshRender);
			auto mesh = I_Resource->Get<Mesh>(L"Rectangle");
			meshRender->SetMesh(mesh);
			auto material = I_Resource->Get<Material>(L"Block1");
			meshRender->SetMaterial(material);
			koopa ->GetTransform()->SetScale(koopa->GetSize());
			koopa ->GetTransform()->SetPosition(Vector3(-2200, -400, 0));

			auto col = std::make_shared<Collider>();
			koopa->AddComponent(col);

			auto animator = std::make_shared<Animator>();
			koopa->AddComponent(animator);
			auto anim = I_Resource->Get<Animation>(L"¾û±Ý¾û±Ý");
			animator->SetAnimation(anim);
			koopa->AddComponent(std::make_shared<KoopaScript>());
		}

		std::shared_ptr<DxObject> koopa2 = object::Instantiate<DxObject>(L"koopa", LayerType::Monster);
		{
			auto meshRender = std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext());
			koopa2->AddComponent(meshRender);
			auto mesh = I_Resource->Get<Mesh>(L"Rectangle");
			meshRender->SetMesh(mesh);
			auto material = I_Resource->Get<Material>(L"Block1");
			meshRender->SetMaterial(material);
			koopa2->GetTransform()->SetScale(koopa2->GetSize());
			koopa2->GetTransform()->SetPosition(Vector3(500, -400, 0));

			auto col = std::make_shared<Collider>();
			koopa2->AddComponent(col);

			auto animator = std::make_shared<Animator>();
			koopa2->AddComponent(animator);
			auto anim = I_Resource->Get<Animation>(L"¾û±Ý¾û±Ý");
			animator->SetAnimation(anim);
			koopa2->AddComponent(std::make_shared<KoopaScript>());
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
			auto animator = std::make_shared<Animator>();
			player->AddComponent(animator);
			auto anim = I_Resource->Get<Animation>(L"Mario_rightIdle");
			animator->SetAnimation(anim);
			auto col = std::make_shared<Collider>();
			player->AddComponent(col);
		}
#pragma endregion

		camera->AddComponent(std::make_shared<FollowTargetScript>(player));
		camera->AddComponent(std::make_shared<MarioCameraScript>(player));

		SoundManager::Add(L"../../Res/sounds/music/overworld.wav", L"overworld.wav");
		SoundManager::Add(L"../../Res/sounds/music/gamewon.wav", L"gamewon.wav");

		SoundManager::Add(L"../../Res/sounds/effects/flagraise.wav", L"flagraise.wav");
		SoundManager::Add(L"../../Res/sounds/effects/death.wav", L"death.wav");
		SoundManager::Add(L"../../Res/sounds/effects/jump.wav", L"jump.wav");
		SoundManager::Add(L"../../Res/sounds/effects/powerupcollect.wav", L"powerupcollect.wav");
		SoundManager::Add(L"../../Res/sounds/effects/blockhit.wav", L"blockhit.wav");
		SoundManager::Add(L"../../Res/sounds/effects/blockbreak.wav", L"blockbreak.wav");
		SoundManager::Add(L"../../Res/sounds/effects/fireball.wav", L"fireball.wav");
		SoundManager::Add(L"../../Res/sounds/effects/stomp.wav", L"stomp.wav");
		SoundManager::Add(L"../../Res/sounds/effects/kick.wav", L"kick.wav");
		SoundManager::Add(L"../../Res/sounds/effects/powerupappear.wav", L"powerupappear.wav");
		
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
	void PlayScene::Release()
	{
		Scene::Release();
	}
	void PlayScene::OnEnter()
	{
		Scene::OnEnter();
		PlayScene::Init();


		CollisionManager::CollisionLayerCheck(LayerType::Player, LayerType::End, true);
		CollisionManager::CollisionLayerCheck(LayerType::Player, LayerType::Floor, true);
		CollisionManager::CollisionLayerCheck(LayerType::Player, LayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(LayerType::Player, LayerType::Wall, true);
		CollisionManager::CollisionLayerCheck(LayerType::Player, LayerType::WallEnd, true);
		CollisionManager::CollisionLayerCheck(LayerType::Player, LayerType::MunshRoom, true);
		CollisionManager::CollisionLayerCheck(LayerType::Player, LayerType::Flower, true);
		CollisionManager::CollisionLayerCheck(LayerType::Player, LayerType::Flag, true);
		CollisionManager::CollisionLayerCheck(LayerType::Player, LayerType::EndPoint, true);
		CollisionManager::CollisionLayerCheck(LayerType::Player, LayerType::ItemWall, true);
		
		CollisionManager::CollisionLayerCheck(LayerType::Monster, LayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(LayerType::Monster, LayerType::Wall, true);
		CollisionManager::CollisionLayerCheck(LayerType::Monster, LayerType::Floor, true);
		CollisionManager::CollisionLayerCheck(LayerType::Monster, LayerType::Fireball, true);
		CollisionManager::CollisionLayerCheck(LayerType::Monster, LayerType::End, true);

		CollisionManager::CollisionLayerCheck(LayerType::MunshRoom, LayerType::Wall, true);
		CollisionManager::CollisionLayerCheck(LayerType::MunshRoom, LayerType::WallEnd, true);
		CollisionManager::CollisionLayerCheck(LayerType::MunshRoom, LayerType::Floor, true);

		CollisionManager::CollisionLayerCheck(LayerType::Fireball, LayerType::Floor, true);
		CollisionManager::CollisionLayerCheck(LayerType::Fireball, LayerType::Wall, true);
	}
	void PlayScene::OnExit()
	{
		Scene::OnExit();
		SoundManager::Clear();
	}
}