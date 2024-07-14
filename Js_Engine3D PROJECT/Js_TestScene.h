#pragma once
#include "Js_Scene.h"

namespace Js
{
	class TestScene : public Scene
	{
	public:

		void Init() override;
		void Update() override;
		void LateUpdate() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
		std::shared_ptr<DxObject> camera = nullptr;
		std::shared_ptr<DxObject> backGround = nullptr;
		std::shared_ptr<DxObject> player = nullptr;
	};

}

