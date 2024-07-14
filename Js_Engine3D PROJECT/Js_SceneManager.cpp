#include "Js_SceneManager.h"
#include "Js_PlayScene.h"
#include "Js_TitleScene.h"
#include "Js_ClearScene.h"
#include "Js_TestScene.h"

namespace Js
{
	std::map<std::wstring, std::shared_ptr<Scene>>  SceneManager::m_Scenes = {};
	std::shared_ptr<Scene> SceneManager::						  m_CurrentScene = nullptr;
	std::shared_ptr<Scene> SceneManager::					      m_DontDestroyOnLoad = nullptr;


	SceneManager::SceneManager()
	{
	}

	SceneManager::~SceneManager()
	{
	}

	void SceneManager::Init()
	{		
		if (m_CurrentScene == nullptr)
			return;

		m_CurrentScene->Init();
	}

	void SceneManager::Update()
	{
		if (m_CurrentScene == nullptr)
			return;

		m_CurrentScene->Update();
	}

	void SceneManager::LateUpdate()
	{
		if (m_CurrentScene == nullptr)
			return;

		m_CurrentScene->LateUpdate();
	}

	void SceneManager::Render(std::shared_ptr<Pipeline> _pipeline)
	{
		if (m_CurrentScene == nullptr)
			return;

		m_CurrentScene->Render(_pipeline);
	}
	std::vector<std::shared_ptr<DxObject>> SceneManager::GetLayerGameObjects(enums::LayerType _type)
	{
		std::vector<std::shared_ptr<DxObject>> gameObjects = {};
		auto& ativeGameObjects = GetActiveScene()->GetGameObjects();

		for (auto& gameObject : ativeGameObjects)
		{
			if (gameObject->GetLayerType() == _type)
			{
				gameObjects.push_back(gameObject);
			}
		}
		auto& dontDetroyGameObjects = GetActiveScene()->GetGameObjects();
		
		for (auto& gameObject : dontDetroyGameObjects)
		{
			if (gameObject->GetLayerType() == _type)
			{
				gameObjects.push_back(gameObject);
			}
		}

		return gameObjects;
	}
	void SceneManager::InitailizeScene()
	{
		// Mario Scene
		/*
		CreateScene<PlayScene>(L"Play");
		CreateScene<TitleScene>(L"Title");
		CreateScene<EndingScene>(L"Ending");

		LoadScene<TitleScene>(L"Title");
		//LoadScene<EndingScene>(L"Ending");
		*/

		CreateScene<TestScene>(L"Test");
		LoadScene<TestScene>(L"Test");

	}
	void SceneManager::Destroy()
	{
		m_CurrentScene->Destroy();
		//m_DontDestroyOnLoad->Destroy();
	}
}