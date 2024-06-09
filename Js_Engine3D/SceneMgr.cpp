#include "SceneMgr.h"

namespace Js
{
	SceneMap			   SceneMgr::m_Scenes = {};
	std::shared_ptr<Scene> SceneMgr::m_ActiveScene = nullptr;

	void SceneMgr::Init()
	{
	}
	void SceneMgr::Update()
	{
	}
	void SceneMgr::Render()
	{
	}
	void SceneMgr::Release()
	{
	}
}