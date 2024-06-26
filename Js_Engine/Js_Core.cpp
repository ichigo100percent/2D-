#include "Js_Core.h"
#include "Js_Time.h"
#include "Js_Input.h"
#include "Js_TextureMgr.h"
#include "Js_ShaderMgr.h"
#include "Js_SoundMgr.h"

namespace Js
{
	bool Core::s_GameRun = true;

	Core::Core()
	{

	}

	Core::~Core()
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
		TEXTURE.Set(m_Device.Get(), m_Context.Get());
		SHADER.Set(m_Device.Get(), m_Context.Get());
		SOUND.Set(nullptr, nullptr);

#ifdef _DEBUG
		{
			wf->Init();
			IDXGISurface* dxgiSurface = nullptr;
			m_SwapChain->GetBuffer(0, __uuidof(IDXGISurface),
				(void**)&dxgiSurface);
			wf->ResetDevice(dxgiSurface);
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
		wf->Update();
		SOUND.Update();
		Update();
		return true;
	}
	bool Core::EngineRender()
	{
		Device::PreRender();
		//Input::DebugMousePos();
		//Input::KeyTest();
		Render();
		wf->DrawText(Time::m_csBuffer, { g_Width / 4, 0 });

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
		while (s_GameRun)
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