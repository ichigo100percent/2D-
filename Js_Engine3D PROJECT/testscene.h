#pragma once
#include "Js_Scene.h"

namespace Js
{
	class testscene : public Scene
	{
	public:
		void Init() override;
		void Update() override;
		void LateUpdate() override;
		void Render(std::shared_ptr<Pipeline> _pipeline) override;

		void OnEnter() override;

		std::shared_ptr<DxObject> camera;
		std::shared_ptr<DxObject> bg;
		std::shared_ptr<DxObject> player;
		std::shared_ptr<DxObject> monster;
	};
}
