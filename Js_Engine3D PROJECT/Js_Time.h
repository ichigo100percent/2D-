#pragma once
#include "std.h"

namespace Js
{
	class Time
	{
	public:
		static void Init();
		static void Update();

		static float DeltaTime() { return DeltaTimeValue; }
		static float GetGameTime() { return GameTimeTick; }

	public:
		static std::wstring   m_csBuffer;

	private:
		static LARGE_INTEGER CpuFrequency;
		static LARGE_INTEGER PrevFrequency;
		static LARGE_INTEGER CurrentFrequency;
		static float DeltaTimeValue;
		static float GameTimeTick;
		static float SecondTime;
		static int FPS;
		static DWORD dw_FPS;
	};
}

