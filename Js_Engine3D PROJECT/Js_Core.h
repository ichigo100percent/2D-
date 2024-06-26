#pragma once
#include "Js_Device.h"
#include "Js_DxWrite.h"
#include "Js_Pipeline.h"
#include "Js_ResourceManager.h"

namespace Js
{
	class Core : public Device, public BaseCore
	{
	public:
		Core();
		virtual ~Core();

		static Core& Instance()
		{
			static Core ret;
			return ret;
		}

		virtual void Init();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
		virtual void Release();
		
		void GameRun();

	private:
		bool EngineInit();
		bool EngineUpdate();
		bool EngineLateUpdate();
		bool EngineRender();
		bool EngineRelease();

		std::shared_ptr<Pipeline> GetPipeline() { return m_Pipeline; }
		std::shared_ptr<ResourceManager> GetResource() { return m_Resource; }

	protected:
		std::shared_ptr<DxWrite>  m_DxWrite = nullptr;
		std::shared_ptr<Pipeline> m_Pipeline = nullptr;
		std::shared_ptr<ResourceManager> m_Resource = nullptr;
	};

#define I_Core	Core::Instance()
#define I_Resource Core::Instance().GetResource()
}
