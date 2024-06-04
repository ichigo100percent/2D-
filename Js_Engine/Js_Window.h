#pragma once
#include "std.h"

namespace Js
{
	class Window
	{
	public:
		Window();
		virtual ~Window();

		void CreateRegisterClass(HINSTANCE _hInstance);
		bool CreateWin(HINSTANCE _hInstance, const int& _width, const int& _height);
		bool WindowRun();

		HWND GetHWND() const { return m_Hwnd; }
		HINSTANCE GetHINSTANCE() const { return m_HInstance; }
		void SetActive(bool _isActive) { m_isActive = _isActive; }
		bool GetActive() const { return m_isActive; }

	protected:
		HWND		m_Hwnd;
		HINSTANCE	m_HInstance;
		bool        m_isActive;
	};
}