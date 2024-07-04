#include "Js_Sound.h"

namespace Js
{
	Fmod::Fmod()
	{
	}
	Fmod::~Fmod()
	{
	}
	void Fmod::Init()
	{
	}
	void Fmod::Update()
	{
	}
	void Fmod::Render()
	{
	}
	void Fmod::Release()
	{
	}
	bool Fmod::Load(const std::wstring& _fileName)
	{
		// 1개의 사운드 파일 단위로 1개의 채널이 만들어 진다.
		m_Volume = 0.5f; // 0 ~ 1

		FMOD_RESULT hr = m_FmodSystem->createSound(to_wm(_fileName).c_str(), FMOD_DEFAULT, 0, &m_Sound);

		if (FMOD_OK == hr)
		{
			return true;
		}

		return false;
	}
	FMOD::Channel* Fmod::Play(bool _loop)
	{
		// 채널 : 실행되는 사운드 제어를 담당한다.
		FMOD::Channel* channel = nullptr;
		FMOD_RESULT hr = m_FmodSystem->playSound(m_Sound,
			nullptr, false, &channel);

		m_Channel = channel;
		if (hr == FMOD_OK)
		{
			m_Channel->setVolume(m_Volume);
			m_Sound->getLength(&m_SizeMS, FMOD_TIMEUNIT_MS);
			_stprintf_s(m_msSound,
				L"전체시간[%02d:%02d:%02d]",
				m_SizeMS / 1000 / 60,
				m_SizeMS / 1000 % 60,
				m_SizeMS / 10 / 60);

			if (_loop)
			{
				m_Channel->setMode(FMOD_LOOP_NORMAL); // 무한반복
			}
			else
			{
				m_Channel->setMode(FMOD_LOOP_OFF);
			}
		}
		return m_Channel;
	}
	void Fmod::PlayEffect()
	{
		// 채널 : 실행되는 사운드 제어를 담당한다.
		FMOD::Channel* pChannel = nullptr;
		FMOD_RESULT hr = m_FmodSystem->playSound(m_Sound,
			nullptr, false, &pChannel);
		assert(FMOD_OK(hr));
	}
	void Fmod::Stop()
	{
	}
	void Fmod::Paused()
	{
	}
	void Fmod::VolumeUP(float _volume)
	{
	}
	void Fmod::VolumDown(float _volume)
	{
	}
}