#pragma once
#include "Js_Scene.h"
#include "Js_Sound.h"

namespace Js
{
	class PlayScene: public Scene
	{
	public:
		void Init() override;
		void Update() override;
		void LateUpdate() override;
		void Render(std::shared_ptr<Pipeline> _pipeline) override;
		void Release() override;

		void OnEnter() override;
		void OnExit() override;

		std::shared_ptr<DxObject> camera;
		std::shared_ptr<DxObject> bg;
		std::shared_ptr<DxObject> player;
		std::shared_ptr<DxObject> monster;
		std::shared_ptr<DxObject> mushRoom;
		std::vector<std::shared_ptr<DxObject>> m_Goombas;

		std::vector<std::shared_ptr<DxObject>> walls1;
		std::vector<std::shared_ptr<DxObject>> walls2;
		std::vector<std::shared_ptr<DxObject>> walls3;
		std::vector<std::shared_ptr<DxObject>> walls4;

		std::shared_ptr<Fmod> m_Sound = nullptr;
	};
}
