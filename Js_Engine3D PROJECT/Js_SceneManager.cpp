#include "Js_SceneManager.h"
#include "testscene.h"

namespace Js
{
	std::map<std::wstring, std::shared_ptr<Scene>>  SceneManager::m_Scenes = {};
	std::shared_ptr<Scene> SceneManager::						  m_CurrentScene = nullptr;
	std::shared_ptr<Scene> SceneManager::					      m_DontDestroyOnLoad = nullptr;


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
}