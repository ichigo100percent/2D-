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
#include "Js_MeshRenderer.h"
#include "Js_Fireball.h"
#include "Js_Object.h"
#include "Js_Player.h"

// Scripts
#include "Js_FireballScript.h"
#include "Js_MoveScripts.h"
#include "Js_RotateScript.h"
#include "Js_FollowTargetScript.h"


namespace Js
{
	bool CheckCollision(const MyRect& rect1, const MyRect& rect2)
	{
		// 두 사각형이 충돌하는지 확인
		if (rect1.left < rect2.right &&
			rect1.right > rect2.left &&
			rect1.top > rect2.bottom &&
			rect1.bottom < rect2.top)
		{
			return true; 
		}
		return false; 
	}
	bool CheckCollision(const MyRect& rect1, const MyRect& rect2, Vector3& pushVector)
	{
		// 충돌 감지
		if (rect1.left < rect2.right &&
			rect1.right > rect2.left &&
			rect1.top > rect2.bottom &&
			rect1.bottom < rect2.top)
		{

			// 충돌 방향 계산
			float overlapLeft = rect2.right - rect1.left;
			float overlapRight = rect1.right - rect2.left;
			float overlapTop = rect2.bottom - rect1.top;
			float overlapBottom = rect1.bottom - rect2.top;

			float overlapX = (std::abs(overlapLeft) < std::abs(overlapRight)) ? overlapLeft : -overlapRight;
			float overlapY = (std::abs(overlapTop) < std::abs(overlapBottom)) ? overlapTop : -overlapBottom;

			if (std::abs(overlapX) < std::abs(overlapY))
				pushVector = Vector3(overlapX, 0, 0);
			else 
				pushVector = Vector3(0, overlapY, 0);
			
			return true;				
		}
		return false;
	}
	
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
			auto material = I_Resource->Get<Material>(L"bg");
			meshRender->SetMaterial(material);
			bg->GetTransform()->SetScale(bg->GetSize());
		}

		player = object::Instantiate<Player>(L"Player");
		{
			auto meshRender = std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext());
			player->AddComponent(meshRender);
			auto mesh = I_Resource->Get<Mesh>(L"Rectangle");
			meshRender->SetMesh(mesh);
			auto material = I_Resource->Get<Material>(L"Default");
			meshRender->SetMaterial(material);
			player->GetTransform()->SetScale(player->GetSize());
			player->AddComponent(std::make_shared<MoveScript>());
			player->AddComponent(std::make_shared<FireballScript>(player));
			
			auto animator = std::make_shared<Animator>();
			player->AddComponent(animator);
			auto anim = I_Resource->Get<Animation>(L"SnakeAni");
			animator->SetAnimation(anim);
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
			monster->GetTransform()->SetPosition(Vector3(300, 300, 0));
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
		//Vector3 pushVector;
		//if (CheckCollision(player->GetTransform()->GetRect(), monster->GetTransform()->GetRect(), pushVector))
		//{
		//	OutputDebugStringA("Collision detected!\n");
		//	// 충돌 방향으로 밀어내기
		//	player->GetTransform()->SetPosition(player->GetTransform()->GetPosition() + pushVector);
		//}

		if (CheckCollision(player->GetTransform()->GetRect(), monster->GetTransform()->GetRect()))
		{
			object::Destory(monster);
		}
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