#include "Js_Scene.h"
#include "Js_DxObject.h"

namespace Js
{
	Scene::Scene(const std::wstring _name)
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
			if (_gameObject != nullptr)
				_gameObject->Init();
		}
	}
	void Scene::Update()
	{
		for (std::shared_ptr<DxObject>& _gameObject : m_GameObjectList)
		{
			if (_gameObject != nullptr)
				_gameObject->Update();
		}
	}
	void Scene::LateUpdate()
	{
		for (std::shared_ptr<DxObject>& _gameObject : m_GameObjectList)
		{
			if (_gameObject != nullptr)
				_gameObject->LateUpdate();
		}
	}
	void Scene::Render(std::shared_ptr<Pipeline> _pipeline)
	{
		for (std::shared_ptr<DxObject>& _gameObject : m_GameObjectList)
		{
			if (_gameObject != nullptr)
				_gameObject->Render(_pipeline);
		}
	}
	void Scene::Release()
	{
		for (std::shared_ptr<DxObject>& _gameObject : m_GameObjectList)
		{
			if (_gameObject != nullptr)
				_gameObject->Release();
		}
	}
	void Scene::OnEnter()
	{

	}
	void Scene::OnExit()
	{

	}
	void Scene::AddGameObejct(std::shared_ptr<DxObject> _gameObejct)
	{
		m_GameObjectList.push_back(_gameObejct);
	}
	void Scene::RemoveGameObject(std::shared_ptr<DxObject> _gameObject)
	{
		auto iter = std::find(std::begin(m_GameObjectList), std::end(m_GameObjectList), _gameObject);

		if (iter != m_GameObjectList.end())
			m_GameObjectList.erase(iter);
	}
}