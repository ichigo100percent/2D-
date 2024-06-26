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
		std::vector<std::shared_ptr<DxObject>> walls1;
		std::vector<std::shared_ptr<DxObject>> walls2;
		std::vector<std::shared_ptr<DxObject>> walls3;
		std::vector<std::shared_ptr<DxObject>> walls4;
	};
}
