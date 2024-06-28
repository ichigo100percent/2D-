#pragma once
#include "std.h"
#include "Js_Core.h"
#include "Js_DxObject.h"

namespace Js
{
	class Scene : public Entity
	{
	public:
		Scene(const std::wstring& _name = {});
		~Scene();

		virtual void Init();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(std::shared_ptr<Pipeline> _pipeline);

		virtual void Destroy();
		virtual void OnEnter();
		virtual void OnExit();

		void AddGameObject(std::shared_ptr<DxObject> _gameObject);
		void EraseGameObject(std::shared_ptr<DxObject> _gameObject);
		std::vector<std::shared_ptr<DxObject>>& GetGameObjects() { return m_GameObjectList; }

	private:
		void findDeadGameObjects(OUT std::vector<std::shared_ptr<DxObject>>& _gameObjs);
		void deleteGameObjects(std::vector<std::shared_ptr<DxObject>> _gameObjs);
		void eraseDeadGameObject();

	private:
		std::vector<std::shared_ptr<DxObject>>  m_GameObjectList;
	};
}