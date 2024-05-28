#include "pch.h"
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
		{
			wf.Init();
			IDXGISurface* dxgiSurface = nullptr;
			g_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface),
				(void**)&dxgiSurface);
			wf.ResetDevice(dxgiSurface);
			dxgiSurface->Release();
		}

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
		Render();
		//Input::DebugMousePos();
		//Input::KeyTest();
		wf.DrawText(Time::m_csBuffer, { 0, 0 });
		//m_Time += Time::DeltaTime();
		//OutputDebugStringA((std::to_string(m_Time) + '\n').c_str());


		Device::PostRender();
		return true;
	}

	bool Core::EngineRelease()
	{
		Release();
		Device::DeleteDeivce();
		return true;
	}

	void Core::GameRun()
	{
		EngineInit();
		while (true)
		{
			if (!EngineUpdate() || !EngineRender())
				break;
		}
		EngineRelease();
	}
}