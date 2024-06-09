#pragma once
#include "std.h"


namespace Js
{
	class DxObject {};

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
