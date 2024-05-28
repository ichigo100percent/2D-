#pragma once
namespace Js
{
	class Window
	{
	public:
		void CreateRegisterClass(HINSTANCE _hInstance);
		BOOL CreateWin(HINSTANCE _hInstance, const int& _width, const int& _height);
		BOOL WindowRun();

		HWND GetHWND() { return m_Hwnd; }
		HINSTANCE GetHINSTANCE() { return m_HInstance; }
		void SetActive(bool _isActive) { m_isActive = _isActive; }
		bool GetActive() { return m_isActive; }
	protected:
		HWND		m_Hwnd;
		HINSTANCE	m_HInstance;
		bool        m_isActive;
	};
}
