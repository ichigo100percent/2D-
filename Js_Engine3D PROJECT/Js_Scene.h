#pragma once
#include "std.h"
#include "Js_DxObject.h"
#include "Js_Core.h"

namespace Js
{
	class Scene : public std::enable_shared_from_this<Scene>, public Entity
	{
	public:
		Scene(const std::wstring _name = {});
		virtual ~Scene();

		virtual void Init();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(std::shared_ptr<Pipeline> _pipeline);
		virtual void Release();

		virtual void OnEnter();
		virtual void OnExit();

		void AddGameObejct(std::shared_ptr<DxObject> _gameObejct);
		void RemoveGameObject(std::shared_ptr<DxObject> _gameObject);

		const std::vector<std::shared_ptr<DxObject>>& GetGameObjectList() { return m_GameObjectList; }

	protected:
		std::vector<std::shared_ptr<DxObject>> m_GameObjectList;
	};
}
