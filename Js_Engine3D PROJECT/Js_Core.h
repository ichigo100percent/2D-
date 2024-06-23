#pragma once
#include "Js_Device.h"
#include "Js_DxWrite.h"
#include "Js_Pipeline.h"

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

	protected:
		std::shared_ptr<DxWrite> m_DxWrite = nullptr;
		std::shared_ptr<Pipeline> m_Pipeline = nullptr;
	};
}
