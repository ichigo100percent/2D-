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
#include "Js_ResourceManager.h"

// Scripts
#include "Js_MoveScripts.h"
#include "Js_RotateScript.h"

#include "TestObject.h"

namespace Js
{

	std::shared_ptr<Scene> testscene::LoadTestScene()
	{
		camera = std::make_shared<DxObject>(I_Core.GetDevice(), I_Core.GetContext());
		{
			camera->GetOrAddTransform();
			camera->AddComponent(std::make_shared<Camera>());
			camera->AddComponent(std::make_shared<MoveScript>());
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
			t->AddComponent(std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext(), L"1.bmp"));
			t->GetOrAddTransform()->SetScale(player->GetSize());
			Scene::AddGameObejct(t);
		}
		return shared_from_this();
	}
}