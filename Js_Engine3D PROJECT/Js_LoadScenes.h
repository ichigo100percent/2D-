#pragma once
#include "Js_SceneManager.h"
#include "Js_TitleScene.h"
#include "testscene.h"


namespace Js
{
	void LoadScenes()
	{
		SceneManager::CreateScene<testscene>(L"test");
		SceneManager::CreateScene<TitleScene>(L"Title");

		//SceneManager::LoadScene<TitleScene>(L"Title");
		//SceneManager::LoadScene<testscene>(L"test");
	}
}