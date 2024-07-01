#pragma once
#include "Js_Component.h"
#include "Js_DxObject.h"
#include "Js_Scene.h"
#include "Js_SceneManager.h"
#include "Js_Transform.h"

namespace Js::object
{
	template <typename T>
	static std::shared_ptr<T> Instantiate(const std::wstring& _name = L"", enums::LayerType _type = enums::LayerType::None)
	{
		auto gameObject = std::make_shared<T>(I_Core.GetDevice(), I_Core.GetContext(), _name);
		gameObject->SetLayerType(_type);
		gameObject->AddTransform();
		auto scene = SceneManager::GetActiveScene();
		scene->AddGameObject(gameObject);

		return gameObject;
	}

	static void DontDestroyOnLoad(std::shared_ptr<DxObject> _gameObject)
	{
		auto activeScene = SceneManager::GetActiveScene();
		//현재 씬에서 게임오브젝트를 지워준다.
		activeScene->EraseGameObject(_gameObject);

		//해당 게임오브젝트를 ->DontDestroy씬으로 넣어준다.
		auto dontDestroyOnLoad = SceneManager::GetDontDestroyOnLoad();
		dontDestroyOnLoad->AddGameObject(_gameObject);
	}
}
