#pragma once
#include "std.h"
#include "Js_DxObject.h"
namespace Js
{
	class Scene : public Entity
	{
	public:
		Scene();

		virtual void Init();
		virtual void Update();
		virtual void Render();
		virtual void Release();

		virtual void OnEnter();
		virtual void OnExit();

	private:
		std::vector<DxObject> m_GameObjects{};
	};
}
