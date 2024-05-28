#include "pch.h"
#include "Js_WriterFont.h"

namespace Js
{
	WriterFont::WriterFont()
	{
	}
	void WriterFont::Init()
	{
		HRESULT hr;
		hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, m_pd2dFactory.GetAddressOf());
		CHECK(hr);

		hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)&m_pWriteFactory);
		hr = m_pWriteFactory->CreateTextFormat(
			L"궁서",
			nullptr,
			DWRITE_FONT_WEIGHT_THIN,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			30,
			L"ko-kr", // L"en-us"
			m_pWriteTF30.GetAddressOf());

		CHECK(hr);

		hr = m_pWriteFactory->CreateTextFormat(
			L"Gabriola",
			nullptr,
			DWRITE_FONT_WEIGHT_THIN,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			50,
			L"en-us",
			m_pWriteTF50.GetAddressOf());

		CHECK(hr);
	}
	void WriterFont::Update()
	{
	}
	void WriterFont::Render()
	{
	}
	void WriterFont::Release()
	{
		if (m_pWriteTF50)
		{
			m_pWriteTF50.Reset();
			m_pWriteTF50 = nullptr;
		}
		if (m_pDefaultColor)
		{
			m_pDefaultColor.Reset();
			m_pDefaultColor = nullptr;
		}
		if (m_pd2dFactory)
		{
			m_pd2dFactory.Reset();
			m_pd2dFactory = nullptr;
		}
		if (m_pWriteTF30)
		{
			m_pWriteTF30.Reset();
			m_pWriteTF30 = nullptr;
		}
		if (m_pWriteFactory)
		{
			m_pWriteFactory.Reset();
			m_pWriteFactory = nullptr;
		}
		if (m_pd2dRT)
		{
			m_pd2dRT.Reset();
			m_pd2dRT = nullptr;
		}
	}
	void WriterFont::ResetDevice(IDXGISurface* dxgiSurface)
	{
		D2D1_RENDER_TARGET_PROPERTIES rtp;
		rtp.type = D2D1_RENDER_TARGET_TYPE_DEFAULT;
		rtp.pixelFormat.format = DXGI_FORMAT_UNKNOWN;
		rtp.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;
		rtp.dpiX = 96;
		rtp.dpiY = 96;
		rtp.usage = D2D1_RENDER_TARGET_USAGE_NONE;
		rtp.minLevel = D2D1_FEATURE_LEVEL_DEFAULT;
		// 3d : 2D 연동가능한 렌더타켓 생성(D3D11_CREATE_DEVICE_BGRA_SUPPORT)
		HRESULT hr = m_pd2dFactory->CreateDxgiSurfaceRenderTarget(
			dxgiSurface,    
			&rtp,
			m_pd2dRT.GetAddressOf());
		CHECK(hr);
		
		D2D1_COLOR_F color = { 1,0,0,1 };//D2D1::ColorF::Yellow;
		hr = m_pd2dRT->CreateSolidColorBrush(
			color,
			m_pDefaultColor.GetAddressOf());

		CHECK(hr);
	}
	void WriterFont::DrawText(std::wstring msg, POINT pos)
	{
		m_pd2dRT->BeginDraw();
		D2D1_RECT_F layoutRect = { pos.x,pos.y, 800, 600 };
		m_pDefaultColor->SetColor({ 1,1,1,1 });
		m_pd2dRT->DrawText(msg.c_str(), msg.size(),
			m_pWriteTF30.Get(), &layoutRect, m_pDefaultColor.Get());
		m_pd2dRT->EndDraw();
	}
}

/*
namespace Js
{
	WriterFont::WriterFont()
	{
	}
	void WriterFont::Init()
	{
		HRESULT hr;
		hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pd2dFactory);

		hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)&m_pWriteFactory);
		hr = m_pWriteFactory->CreateTextFormat(
			L"궁서",
			nullptr,
			DWRITE_FONT_WEIGHT_THIN,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			30,
			L"ko-kr", // L"en-us"
			&m_pWriteTF30);

		hr = m_pWriteFactory->CreateTextFormat(
			L"Gabriola",
			nullptr,
			DWRITE_FONT_WEIGHT_THIN,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			50,
			L"en-us",
			&m_pWriteTF50);
	}
	void WriterFont::Update()
	{
	}
	void WriterFont::Render()
	{
	}
	void WriterFont::Release()
	{
		if (m_pWriteTF50)
		{
			m_pWriteTF50->Release();
			m_pWriteTF50 = nullptr;
		}
		if (m_pDefaultColor)
		{
			m_pDefaultColor->Release();
			m_pDefaultColor = nullptr;
		}
		if (m_pd2dFactory)
		{
			m_pd2dFactory->Release();
			m_pd2dFactory = nullptr;
		}
		if (m_pWriteTF30)
		{
			m_pWriteTF30->Release();
			m_pWriteTF30 = nullptr;
		}
		if (m_pWriteFactory)
		{
			m_pWriteFactory->Release();
			m_pWriteFactory = nullptr;
		}
		if (m_pd2dRT)
		{
			m_pd2dRT->Release();
			m_pd2dRT = nullptr;
		}
	}
	void WriterFont::ResetDevice(IDXGISurface* dxgiSurface)
	{
		D2D1_RENDER_TARGET_PROPERTIES rtp;
		rtp.type = D2D1_RENDER_TARGET_TYPE_DEFAULT;
		rtp.pixelFormat.format = DXGI_FORMAT_UNKNOWN;
		rtp.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;
		rtp.dpiX = 96;
		rtp.dpiY = 96;
		rtp.usage = D2D1_RENDER_TARGET_USAGE_NONE;
		rtp.minLevel = D2D1_FEATURE_LEVEL_DEFAULT;
		// 3d : 2D 연동가능한 렌더타켓 생성(D3D11_CREATE_DEVICE_BGRA_SUPPORT)
		HRESULT hr = m_pd2dFactory->CreateDxgiSurfaceRenderTarget(
			dxgiSurface,
			&rtp,
			&m_pd2dRT);

		if (FAILED(hr))
		{

		}
		D2D1_COLOR_F color = { 1,0,0,1 };//D2D1::ColorF::Yellow;
		hr = m_pd2dRT->CreateSolidColorBrush(
			color,
			&m_pDefaultColor);
		if (FAILED(hr))
		{

		}
	}
	void WriterFont::DrawText(std::wstring msg, POINT pos)
	{
		m_pd2dRT->BeginDraw();
		D2D1_RECT_F layoutRect = { pos.x,pos.y, 800, 600 };
		m_pDefaultColor->SetColor({ 1,1,0,1 });
		m_pd2dRT->DrawText(msg.c_str(), msg.size(),
			m_pWriteTF30, &layoutRect, m_pDefaultColor);
		m_pd2dRT->EndDraw();
	}
}
*/