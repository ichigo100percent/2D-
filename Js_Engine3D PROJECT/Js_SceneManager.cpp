#include "Js_SceneManager.h"
#include "testscene.h"

namespace Js
{
	std::map<std::wstring, std::shared_ptr<Scene>>  SceneManager::m_SceneList = {};
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

	void SceneManager::Release()
	{
		if (m_CurrentScene == nullptr)
			return;

		m_CurrentScene->Release();
	}

	void SceneManager::LoadScene()
	{
		auto t = std::make_shared<testscene>();

		m_CurrentScene = std::dynamic_pointer_cast<testscene>(t->LoadTestScene());
		Init();
	}

}