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
		//���� ������ ���ӿ�����Ʈ�� �����ش�.
		activeScene->EraseGameObject(_gameObject);

		//�ش� ���ӿ�����Ʈ�� ->DontDestroy������ �־��ش�.
		auto dontDestroyOnLoad = SceneManager::GetDontDestroyOnLoad();
		dontDestroyOnLoad->AddGameObject(_gameObject);
	}
}
