#include "testscene.h"
#include "std.h"
#include "Js_Core.h"
#include "Js_Time.h"
#include "Js_Input.h"
#include "Js_DxObject.h"
#include "Js_Component.h"
#include "Js_Transform.h"
#include "Js_Camera.h"
#include "Js_MeshRenderer.h"


// Scripts
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

	void testscene::Update()
	{
		Scene::Update();
	}
	void testscene::LateUpdate()
	{
		Scene::LateUpdate();
		Vector3 pushVector;
		if (CheckCollision(player->GetTransform()->GetRect(), t->GetTransform()->GetRect(), pushVector)) {
			OutputDebugStringA("Collision detected!\n");

			// 충돌 방향으로 밀어내기
			player->GetTransform()->SetPosition(player->GetTransform()->GetPosition() + pushVector);
		}
	}
	std::shared_ptr<Scene> testscene::LoadTestScene()
	{
		camera = std::make_shared<DxObject>(I_Core.GetDevice(), I_Core.GetContext());
		{
			camera->GetOrAddTransform();
			camera->AddComponent(std::make_shared<Camera>());
			camera->Init();
			Scene::AddGameObejct(camera);
		}
		bg = std::make_shared<DxObject>(I_Core.GetDevice(), I_Core.GetContext(), L"bg_blue.jpg");
		{
			bg->AddComponent(std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext(), L"bg_blue.jpg"));
			bg->GetOrAddTransform()->SetScale(bg->GetSize());
			bg->Init();
			Scene::AddGameObejct(bg);
		}

		player = std::make_shared<DxObject>(I_Core.GetDevice(), I_Core.GetContext(), L"1.bmp");
		{
			player->AddComponent(std::make_shared<MoveScript>());
			player->AddComponent(std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext(), L"1.bmp"));
			player->GetOrAddTransform()->SetScale(player->GetSize());
			Scene::AddGameObejct(player);
		}
		t = std::make_shared<DxObject>(I_Core.GetDevice(), I_Core.GetContext(), L"1.bmp");
		{
			t->AddComponent(std::make_shared<MeshRenderer>(I_Core.GetDevice(), Core::GetContext(), L"1.bmp"));
			t->GetOrAddTransform()->SetScale(player->GetSize());
			Scene::AddGameObejct(t);
		}
		camera->AddComponent(std::make_shared<FollowTargetScript>(player));
		return shared_from_this();
	}
}