#pragma once
#include "Js_Windows.h"


namespace Js
{
	class Device : public Window
	{
	public:
		Device();

		void CreateDevice();
		void CreateDeviceAndSwapChain();
		void CreateRenderTargetView();
		void SetViewport();
		void DeleteDeivce();
		void PreRender();
		void PostRender();

		ComPtr<ID3D11Device> GetDevice() { return m_Device; }
		ComPtr<ID3D11DeviceContext> GetContext() { return m_Context; }

	protected:
		ComPtr<ID3D11Device>			m_Device;
		ComPtr<ID3D11DeviceContext>		m_Context;
		ComPtr<ID3D11RenderTargetView>	m_RenderTargetView;
		ComPtr<IDXGISwapChain>			m_SwapChain;

		D3D11_VIEWPORT m_Viewport;
		float clearColor[4] = { 0.5f, 0.5f, 0.5f, 1.f };
	};
}
