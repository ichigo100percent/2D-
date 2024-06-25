#pragma once
#include "Js_Device.h"
#include "Js_DxWrite.h"

namespace Js
{
	class Core : public Device, BaseCore
	{
	public:
		Core();
		virtual ~Core();

		virtual void Init();
		virtual void Update();
		virtual void Render();
		virtual void Release();
		void GameRun();

		bool EngineInit();
		bool EngineUpdate();
		bool EngineRender();
		bool EngineRelease();

		static bool    s_GameRun;
	private:
		std::shared_ptr<DxWrite> wf = std::make_shared<DxWrite>();
	};
}
