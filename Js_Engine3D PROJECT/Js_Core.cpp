#include "Js_Core.h"
#include "Js_Time.h"
#include "Js_Input.h"

namespace Js
{
	Core::Core()
	{

	}

	Core::~Core()
	{
	}

	void Core::Init() {}
	void Core::Update() {}
	void Core::LateUpdate(){}
	void Core::Render() {}
	void Core::Release() {}

	bool Core::EngineInit()
	{
		Time::Init();
		Input::Init();
		Device::CreateDevice();
		m_Pipeline = std::make_shared<Pipeline>(GetContext());
#ifdef _DEBUG
		{
			m_DxWrite = std::make_shared<DxWrite>();
			m_DxWrite->Init();
			IDXGISurface* dxgiSurface = nullptr;
			m_SwapChain->GetBuffer(0, __uuidof(IDXGISurface),
				(void**)&dxgiSurface);
			m_DxWrite->ResetDevice(dxgiSurface);
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
		m_DxWrite->Update();

		Update();
		return true;
	}
	bool Core::EngineLateUpdate()
	{
		LateUpdate();
		return true;
	}
	bool Core::EngineRender()
	{
		Device::PreRender();
		m_DxWrite->DrawText(Time::m_csBuffer, { g_Width / 4, 0 });

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
			EngineLateUpdate();
			EngineRender();
		}
		EngineRelease();
	}
}