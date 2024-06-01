#include "pch.h"
#include "Js_Device.h"


namespace Js
{
	Device::Device() :
		m_Device(nullptr),
		m_Context(nullptr),
		m_RenderTargetView(nullptr),
		m_SwapChain(nullptr),
		m_Viewport {}
	{

	}
	void Device::CreateDevice()
	{
		CreateDeviceAndSwapChain();
		CreateRenderTargetView();
		SetViewport();
	}
	void Device::CreateDeviceAndSwapChain()
	{
		DXGI_SWAP_CHAIN_DESC desc;
		ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));
		{
			desc.BufferDesc.Width = g_Width;
			desc.BufferDesc.Height = g_Height;
			desc.BufferDesc.RefreshRate.Numerator = 60;
			desc.BufferDesc.RefreshRate.Denominator = 1;
			desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			desc.SampleDesc.Count = 1;
			desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			desc.BufferCount = 1;
			desc.OutputWindow = m_Hwnd;
			desc.Windowed = true;
		}

		// dwrite 연동에 필요
		UINT Flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

		CONST D3D_FEATURE_LEVEL pFeatureLevels = D3D_FEATURE_LEVEL_11_0;
		HRESULT hr = D3D11CreateDeviceAndSwapChain
		(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			Flags,
			&pFeatureLevels,
			1,
			D3D11_SDK_VERSION,
			&desc,
			m_SwapChain.GetAddressOf(),
			m_Device.GetAddressOf(),
			nullptr,
			m_Context.GetAddressOf()
		);
		CHECK(hr);
	}
	void Device::CreateRenderTargetView()
	{
		if (m_Device != nullptr && m_SwapChain != nullptr)
		{
			ComPtr<ID3D11Texture2D> backBuffer;
			HRESULT hr = m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)backBuffer.GetAddressOf());
			CHECK(hr);

			hr = m_Device->CreateRenderTargetView(
				backBuffer.Get(),
				nullptr,
				m_RenderTargetView.GetAddressOf());

			CHECK(hr);
		}
		
	}
	void Device::SetViewport()
	{
		m_Viewport.TopLeftX = 0;
		m_Viewport.TopLeftY = 0;
		m_Viewport.Width = static_cast<float>(g_Width);
		m_Viewport.Height = static_cast<float>(g_Height);
		m_Viewport.MinDepth = 0;
		m_Viewport.Height = 1;
	}

	void Device::DeleteDeivce()
	{
		if (m_Device)
		{
			m_Device.Reset();
			m_Device = nullptr;
		}
		if (m_Context)
		{
			m_Context.Reset();
			m_Context = nullptr;
		}
		if (m_RenderTargetView)
		{
			m_RenderTargetView.Reset();
			m_RenderTargetView = nullptr;
		}
		if (m_SwapChain)
		{
			m_SwapChain.Reset();
			m_SwapChain = nullptr;
		}
	}

	void Device::PreRender()
	{
		m_Context->OMSetRenderTargets(1, m_RenderTargetView.GetAddressOf(), nullptr);
		m_Context->ClearRenderTargetView(m_RenderTargetView.Get(), clearColor);
		m_Context->RSSetViewports(1, &m_Viewport);	
	}
	void Device::PostRender()
	{
		HRESULT hr = m_SwapChain->Present(0, 0);
		CHECK(hr);
	}
}