#pragma once
#include "std.h"

namespace Js
{
	enum KeyState
	{
		KEY_FREE = 0,	// 평상시
		KEY_UP,			// 바로 눌렀다가 오픈상태
		KEY_PUSH,		// 오픈상태에서 눌렀을 때
		KEY_HOLD,		// 누루고 있을 때(이전도 눌렀고 지금도 눌렀다.)
	};

	class Input
	{
	public:
		Input();

		static void    DebugPrint(int iKey);
		static void    DebugMousePos();
		static void	   Init();
		static void    Update(HWND hWnd);
		static DWORD   KeyCheck(DWORD dwKey);
		static void    KeyTest();

	private:
		static DWORD   KeyCode[256];
		static POINT   m_MousePos;
	};
}
