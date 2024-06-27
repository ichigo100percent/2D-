#include "Js_TitleScene.h"
#include "Js_SceneManager.h"
#include "Js_Input.h"
#include "Js_Time.h"

#include "testscene.h"

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
			auto a = std::dynamic_pointer_cast<testscene>(SceneManager::LoadScene<testscene>(L"test"));
		}

		Scene::LateUpdate();
	}
	void TitleScene::OnEnter()
	{
	}
	void TitleScene::OnExit()
	{
	}
}