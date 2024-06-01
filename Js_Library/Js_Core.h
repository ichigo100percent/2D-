#pragma once
#include "Js_Device.h"
#include "Js_WriterFont.h"

namespace Js
{

	class Core : public Device , BaseCore
	{
	public:
		Core();

		virtual void Init();
		virtual void Update();
		virtual void Render();
		virtual void Release();
		void GameRun();

		bool EngineInit();
		bool EngineUpdate();
		bool EngineRender();
		bool EngineRelease();

	private:
		WriterFont wf;
	};
}