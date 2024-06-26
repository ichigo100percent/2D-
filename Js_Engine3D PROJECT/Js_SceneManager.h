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
		static void Release();
		
		static void LoadScene();

		static std::shared_ptr<Scene> GetActiveScene() { return m_CurrentScene; }

	private:
		static std::map<std::wstring, std::shared_ptr<Scene>> m_SceneList;
		static std::shared_ptr<Scene> m_CurrentScene;
		static std::shared_ptr<Scene> m_DontDestroyOnLoad;
	};
}
