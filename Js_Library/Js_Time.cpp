#include "pch.h"
#include "Js_Time.h"
namespace Js
{
	LARGE_INTEGER Time::CpuFrequency = {};
	LARGE_INTEGER Time::PrevFrequency = {};
	LARGE_INTEGER Time::CurrentFrequency = {};
	std::wstring  Time::m_csBuffer;

	float Time::DeltaTimeValue = 0.0f;
	float Time::GameTimeTick = 0.0f;
	float Time::SecondTime = 0.0f;
	int   Time::FPS = 0;
	int	  Time::dw_FPS = 0;

	void Time::Init()
	{
		//cpu 고유 진동수
		QueryPerformanceFrequency(&CpuFrequency);

		//프로그램이 시작 했을 때 현재 진동수
		QueryPerformanceCounter(&PrevFrequency);
	}

	void Time::Update()
	{
		QueryPerformanceCounter(&CurrentFrequency);


		float differenceFrequency
			= static_cast<float>(CurrentFrequency.QuadPart - PrevFrequency.QuadPart);

		DeltaTimeValue = differenceFrequency / static_cast<float>(CpuFrequency.QuadPart);
		GameTimeTick += DeltaTimeValue;

		SecondTime += DeltaTimeValue;
		if (SecondTime >= 1.0f)
		{
			dw_FPS = FPS;
			SecondTime = SecondTime - 1.0f;
			FPS = 0;
		}
		FPS++;

		PrevFrequency.QuadPart = CurrentFrequency.QuadPart;	

		TCHAR msgKey[MAX_PATH] = { 0, };
		int firstTwoDigits = dw_FPS / 100;
		_stprintf_s(msgKey,
			L"FPS=%02d   GameTimer=%0.1f\n",
			firstTwoDigits, (float)GameTimeTick);
		m_csBuffer = msgKey;
	}
}