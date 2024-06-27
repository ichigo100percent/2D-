#pragma once
#include "Js_Scene.h"


namespace Js
{
	class SceneManager
	{
	public:
	
		static void Init();
		static void Update();
		static void LateUpdate();
		static void Render(std::shared_ptr<Pipeline> _pipeline);

		template <typename T>
		static std::shared_ptr<T> CreateScene(const std::wstring& _name)
		{
			std::shared_ptr<T> scene = std::make_shared<T>();
			scene->SetName(_name);
			m_CurrentScene = scene;
			scene->Init();

			m_Scenes.insert(std::make_pair(_name, scene));

			return scene;
		}

		template <typename T>
		static std::shared_ptr<Scene> LoadScene(const std::wstring& _name)
		{
			if (m_CurrentScene)
				m_CurrentScene->OnExit();

			auto iter = m_Scenes.find(_name);

			if (iter != m_Scenes.end())
			{
				m_CurrentScene = std::dynamic_pointer_cast<T>(iter->second);
				m_CurrentScene->OnEnter();

				return iter->second;
			}

			return nullptr;
		}
		static std::shared_ptr<Scene> GetActiveScene() { return m_CurrentScene; }
		static std::shared_ptr<Scene> GetDontDestroyOnLoad() { return m_DontDestroyOnLoad; }
	private:
		static std::map<std::wstring, std::shared_ptr<Scene>> m_Scenes;
		static std::shared_ptr<Scene> m_CurrentScene;
		static std::shared_ptr<Scene> m_DontDestroyOnLoad;
	};
}
