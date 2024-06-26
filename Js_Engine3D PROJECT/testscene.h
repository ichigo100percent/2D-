#pragma once
#include "Js_Scene.h"

namespace Js
{
	class testscene : public Scene
	{
	public:
		void Update() override;
		void LateUpdate() override;

		std::shared_ptr<Scene> LoadTestScene();

		std::shared_ptr<DxObject> camera;
		std::shared_ptr<DxObject> bg;
		std::shared_ptr<DxObject> player;
		std::shared_ptr<DxObject> t;
	};
}
