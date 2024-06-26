#include "Js_SceneManager.h"
#include "testscene.h"
#include "Js_TitleScene.h"

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
		CreateScene<testscene>(L"test");
		CreateScene<TitleScene>(L"Title");

		LoadScene<TitleScene>(L"Title");
		//LoadScene<testscene>(L"test");
	}
	void SceneManager::Destroy()
	{
		m_CurrentScene->Destroy();
		//m_DontDestroyOnLoad->Destroy();
	}
}