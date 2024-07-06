#include "Js_Core.h"
#include "Js_Time.h"
#include "Js_Input.h"
#include "Js_SceneManager.h"
#include "Js_SoundManager.h"
#include "Js_CollisionManager.h"

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
		m_Resource = std::make_shared<ResourceManager>(GetDevice());
		m_Resource->Init();
		m_Render = std::make_shared<RenderManager>(GetDevice(), GetContext());
		m_Render->Init();
		CollisionManager::Init();
		SoundManager::Init();
		SceneManager::InitailizeScene();
		SceneManager::Init();

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
		SceneManager::Update();
		CollisionManager::Update();
		Update();
		return true;
	}
	bool Core::EngineLateUpdate()
	{
		SceneManager::LateUpdate();
		CollisionManager::LateUpdate();
		LateUpdate();
		return true;
	}
	bool Core::EngineRender()
	{
		Device::PreRender();
		m_Render->PushCameraData();
		m_Render->GatherRenderableObjects();
		m_Render->RenderObjects();
		SceneManager::Render(GetPipeline());
		Render();

		m_DxWrite->DrawText(Time::m_csBuffer, { g_Width / 4, 0 });
		Device::PostRender();
		return true;
	}

	bool Core::EngineRelease()
	{
		Device::DeleteDeivce();
		Release();
		return true;
	}

	void Core::Destroy()
	{
		SceneManager::Destroy();
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
			Destroy();
		}
		EngineRelease();
	}
}