#include "Js_Input.h"
namespace Js
{
	DWORD Input::KeyCode[256] = {};
	POINT Input::m_MousePos = {};

	Input::Input()
	{

	}

	void    Input::DebugPrint(int iKey)
	{
#ifdef _DEBUG
		static int iPushCounter = 0;
		TCHAR msgKey[MAX_PATH] = { 0, };
		_stprintf_s(msgKey, L"KEY=%d(%d)\n", iKey, iPushCounter++);
		OutputDebugString(msgKey);
#endif
	}
	void    Input::DebugMousePos()
	{
#ifdef _DEBUG
		TCHAR msgKey[MAX_PATH] = { 0, };
		_stprintf_s(msgKey, L"Mouse X=%d, Y=%d\n",
			m_MousePos.x, m_MousePos.y);
		OutputDebugString(msgKey);
#endif
	}

	void    Input::Init()
	{
		ZeroMemory(&KeyCode, sizeof(DWORD) * 256);
	}

	void    Input::Update(HWND hWnd)
	{
		// 화면좌표계를 반환한다.
		GetCursorPos(&m_MousePos);
		// 클라이언트 좌표계로 변환한다.
		ScreenToClient(hWnd, &m_MousePos);

		for (int iKey = 0; iKey < 255; iKey++)
		{
			//			GetKeyState(iKey);
						// iKey에 해당하는 키의 상태를 반환받고
			SHORT sKey = GetAsyncKeyState(iKey);
			// 8     0     0    0
			// 1000  0000  0000 0000
			//         & 
			// 1000  0000  0000 0000
			if (sKey & 0x8000) // 눌렀다.
			{
				// 이전프레임에서 
				if (KeyCode[iKey] == KEY_FREE ||
					KeyCode[iKey] == KEY_UP)
				{
					KeyCode[iKey] = KEY_PUSH;
				}
				else
				{
					KeyCode[iKey] = KEY_HOLD;
				}
			}
			else // 현재 프레임에서는 눌러지지 않았다.
			{
				// 이전프레임에서 
				if (KeyCode[iKey] == KEY_PUSH ||
					KeyCode[iKey] == KEY_HOLD)
				{
					KeyCode[iKey] = KEY_UP;
				}
				else
				{
					KeyCode[iKey] = KEY_FREE;
				}
			}
		}

	}
	void    Input::KeyTest()
	{
		/*
		 * VK_0 - VK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
		 * 0x3A - 0x40 : unassigned
		 * VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
		 */
		if (KeyCode['A'] == KEY_PUSH)
		{
			DebugPrint('A');
		}
		if (KeyCode['A'] == KEY_HOLD)
		{
			DebugPrint('A');
		}
		if (KeyCode['A'] == KEY_UP)
		{
			DebugPrint('A');
		}
	}
	DWORD   Input::KeyCheck(DWORD dwKey)
	{
		return KeyCode[dwKey];
	}
}