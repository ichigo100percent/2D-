#include "Js_Scene.h"

namespace Js
{

	Scene::Scene(const std::wstring& _name)
		: Entity(_name)
	{
	}
	Scene::~Scene()
	{
	}
	void Scene::Init()
	{
		for (std::shared_ptr<DxObject>& _gameObject : m_GameObjectList)
		{
			if (_gameObject == nullptr)
				continue;
			if (_gameObject->IsActive() == false)
				continue;

			_gameObject->Init();
		}
	}
	void Scene::Update()
	{
		//for (int i = 0; i < m_GameObjectList.size(); i++)
		//{
		//	if (m_GameObjectList[i] == nullptr)
		//		continue;
		//	if (m_GameObjectList[i]->IsActive() == false)
		//		continue;

		//	m_GameObjectList[i]->Update();
		//}

		for (std::shared_ptr<DxObject>& _gameObject : m_GameObjectList)
		{
			if (_gameObject == nullptr)
				continue;
			//if (_gameObject->IsActive() == false)
			//	continue;
			_gameObject->Update();
		}
	}
	void Scene::LateUpdate()
	{
		for (std::shared_ptr<DxObject>& _gameObject : m_GameObjectList)
		{
			if (_gameObject == nullptr)
				continue;
			if (_gameObject->IsActive() == false)
				continue;

			_gameObject->LateUpdate();
		}
	}
	void Scene::Render(std::shared_ptr<Pipeline> _pipeline)
	{
		for (std::shared_ptr<DxObject>& _gameObject : m_GameObjectList)
		{
			if (_gameObject == nullptr)
				continue;
			if (_gameObject->IsActive() == false)
				continue;

			_gameObject->Render(_pipeline);
		}
	}
	void Scene::OnEnter()
	{
	}
	void Scene::OnExit()
	{
	}
	void Scene::Destroy()
	{
		std::vector<std::shared_ptr<DxObject>> deleteObjects = {};
		findDeadGameObjects(deleteObjects);
		eraseDeadGameObject();
		deleteGameObjects(deleteObjects);
	}
	void Scene::AddGameObject(std::shared_ptr<DxObject> _gameObject)
	{
		if (_gameObject == nullptr)
			return;

		m_GameObjectList.push_back(_gameObject);
	}
	void Scene::EraseGameObject(std::shared_ptr<DxObject> _gameObject)
	{
		std::erase_if(m_GameObjectList,
			[=](std::shared_ptr<DxObject> gameObject)
			{
				return gameObject == _gameObject;
			});
	}
	void Scene::findDeadGameObjects(OUT std::vector<std::shared_ptr<DxObject>>& _gameObjs)
	{
		for (std::shared_ptr<DxObject> gameObj : m_GameObjectList)
		{
			DxObject::eState active = gameObj->GetState();
			if (active == DxObject::eState::Dead)
				_gameObjs.push_back(gameObj);
		}
	}
	void Scene::deleteGameObjects(std::vector<std::shared_ptr<DxObject>> _gameObjs)
	{
		for (std::shared_ptr<DxObject> obj : _gameObjs)
		{
			obj.reset();
			obj = nullptr;
		}
	}
	void Scene::eraseDeadGameObject()
	{
		std::erase_if(m_GameObjectList,
			[](std::shared_ptr<DxObject> gameObj)
			{
				return (gameObj)->IsDead();
			});
	}

}