#pragma once
#include "Js_Scene.h"

namespace Js
{
	class EndingScene : public Scene
	{
	public:
		EndingScene();
		~EndingScene();

		void Init() override;
		void Update() override;
		void LateUpdate() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:

	};
}