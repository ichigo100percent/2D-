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
	DWORD Time::dw_FPS = {};

	void Time::Init()
	{
		//cpu ���� ������
		QueryPerformanceFrequency(&CpuFrequency);

		//���α׷��� ���� ���� �� ���� ������
		QueryPerformanceCounter(&PrevFrequency);
	}

	void Time::Update()
	{
		QueryPerformanceCounter(&CurrentFrequency);

		//dw��������������
		float differenceFrequency
			= static_cast<float>(CurrentFrequency.QuadPart - PrevFrequency.QuadPart);
		//��������������
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
		_stprintf_s(msgKey,
			L"FPS=%ld, GameTimer=%10.4f SPF=%d\n",
			dw_FPS, GameTimeTick,
			differenceFrequency);
		m_csBuffer = msgKey;
	}
}