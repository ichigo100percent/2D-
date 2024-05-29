#include "pch.h"
#include "Js_Windows.h"

Js::Window* g_pWindow = nullptr;
namespace Js
{
	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
			// ���α׷��� Ȱ��ȭ(��Ŀ��)
		case WM_ACTIVATE:
		{
			if (LOWORD(wParam) == WA_INACTIVE)
			{
				// ���ø����̼� ����
				if (g_pWindow != nullptr)
					g_pWindow->SetActive(false); 
			}
			else
			{
				// ���ø����̼� ����
				if (g_pWindow != nullptr)
					g_pWindow->SetActive(true);
			}
		}return 0;
		case WM_DESTROY:
			PostQuitMessage(0);// WM_QUIT
			return 0;
		}
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	Window::Window()
		: m_Hwnd{}
		, m_HInstance{}
		, m_isActive(false)
	{
		g_pWindow = this;
	}
	void Window::CreateRegisterClass(HINSTANCE _hInstance)
	{
		WNDCLASS wc = { };
		wc.lpfnWndProc = WndProc;			// ���ּ�(�Ǵ� ��ȭ��ȣ)
		wc.hInstance = m_HInstance;		    // �ֹι�ȣ
		wc.lpszClassName = L"Js_Game";		// �̸�
		wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
		RegisterClass(&wc);

		m_HInstance = _hInstance;
	}

	bool Window::CreateWin(HINSTANCE _hInstance, const int& _width, const int& _height)
	{
		CreateRegisterClass(_hInstance);
		// ������ Ŭ���� ����
		HWND hwnd = CreateWindowEx(0
			, L"Js_Game"
			, L"Game"
			, WS_OVERLAPPEDWINDOW
			, CW_USEDEFAULT
			, 0
			, _width
			, _height
			, NULL
			, NULL
			, m_HInstance
			, NULL);

		if (hwnd == NULL)
			return false;

		m_Hwnd = hwnd;

		ShowWindow(hwnd, SW_SHOW);

		return true;
	}
	bool Window::WindowRun()
	{
		MSG msg = { };

		while (WM_QUIT != msg.message)
		{
			if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				return true;
			}
		}
		return false;
	}
}