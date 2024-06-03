#pragma once
#include "Scene.h"

namespace Js
{
	using SceneMap = std::map<std::wstring, std::shared_ptr<Scene>>;
	using SceneIter = std::map<std::wstring, std::shared_ptr<Scene>>::iterator;

	class SceneMgr
	{
	public:
		
		static void Init();
		static void Update();
		static void Render();
		static void Release();

	private:
		static SceneMap		m_Scenes;
		static std::shared_ptr<Scene> m_ActiveScene;
	};
}
