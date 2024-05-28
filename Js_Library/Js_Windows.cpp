#include "pch.h"
#include "Js_Windows.h"

namespace Js
{

	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		return 0;
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

	BOOL Window::CreateWin(HINSTANCE _hInstance, const int& _width, const int& _height)
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
			return FALSE;

		m_Hwnd = hwnd;

		ShowWindow(hwnd, SW_SHOW);

		return TRUE;
	}
	BOOL Window::WindowRun()
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
				return TRUE;
			}
		}
		return FALSE;
	}
}