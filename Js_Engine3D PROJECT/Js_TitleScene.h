#pragma once
#include "Js_Scene.h"

namespace Js
{
	class TitleScene : public Scene
	{
	public:
		TitleScene();
		~TitleScene();

		void Init() override;
		void Update() override;
		void LateUpdate() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:

	};

}

