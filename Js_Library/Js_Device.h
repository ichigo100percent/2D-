#pragma once
#include "Js_Windows.h"

using namespace Microsoft::WRL;

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


	protected:
		//ComPtr<ID3D11Device>			m_Device;
		//ComPtr<ID3D11DeviceContext>		m_Context;
		//ComPtr<ID3D11RenderTargetView>	m_RenderTargetView;
		//ComPtr<IDXGISwapChain>			m_SwapChain;

		ID3D11Device* g_pd3dDevice = nullptr;
		ID3D11DeviceContext* g_pContext = nullptr;
		IDXGISwapChain* g_pSwapChain = nullptr;
		ID3D11RenderTargetView* g_pRTV = nullptr;

		D3D11_VIEWPORT viewport = { 0 };
	};
}
