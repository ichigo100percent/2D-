#include "Js_Core.h"
#include "Js_Time.h"
#include "Js_Input.h"

namespace Js
{
	Core::Core()
	{

	}

	void Core::Init() {}
	void Core::Update() {}
	void Core::Render() {}
	void Core::Release() {}

	bool Core::EngineInit()
	{
		Time::Init();
		Input::Init();
		Device::CreateDevice();
#ifdef _DEBUG
		{
			wf.Init();
			IDXGISurface* dxgiSurface = nullptr;
			m_SwapChain->GetBuffer(0, __uuidof(IDXGISurface),
				(void**)&dxgiSurface);
			wf.ResetDevice(dxgiSurface);
			dxgiSurface->Release();
		}
#endif
		Init();
		return true;
	}
	bool Core::EngineUpdate()
	{
		Time::Update();
		Input::Update(m_Hwnd);
		wf.Update();

		Update();
		return true;
	}
	bool Core::EngineRender()
	{
		Device::PreRender();
		//Input::DebugMousePos();
		//Input::KeyTest();
		wf.DrawText(Time::m_csBuffer, { g_Width / 4, 0 });
		Render();

		Device::PostRender();
		return true;
	}

	bool Core::EngineRelease()
	{
		Device::DeleteDeivce();
		Release();
		return true;
	}

	void Core::GameRun()
	{
		EngineInit();
		while (true)
		{
			if (Window::WindowRun() == false)
			{
				break;
			}
			EngineUpdate();
			EngineRender();
		}
		EngineRelease();
	}
}