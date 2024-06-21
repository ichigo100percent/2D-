#include "Js_SoundMgr.h"

namespace Js
{
	Sound::Sound()
	{
	}
	Sound::~Sound()
	{
	}
	void Sound::Init()
	{
	}
	void Sound::Update()
	{
		if (m_Channel == nullptr) return;
		unsigned int ms;
		m_Channel->getPosition(&ms, FMOD_TIMEUNIT_MS);
		_stprintf_s(m_msSound,
			L"��ü�ð�[%02d:%02d:%02d]\n",
			ms / 1000 / 60,
			ms / 1000 % 60,
			ms / 10 / 60);
		OutputDebugString(m_msSound);
	}
	void Sound::Render()
	{
	}
	void Sound::Release()
	{
	}
	bool Sound::Load(const std::wstring& _fileName)
	{
		// 1���� ���� ���� ������ 1���� ä���� ����� ����.
		m_Volume = 0.5f; // 0 ~ 1
		
		FMOD_RESULT hr = m_FmodSystem->createSound(to_wm(_fileName).c_str(), FMOD_DEFAULT, 0, &m_Sound);

		if (FMOD_OK == hr)
		{
			return true;
		}

		return false;
	}
	FMOD::Channel* Sound::Play(bool _loop)
	{
		// ä�� : ����Ǵ� ���� ��� ����Ѵ�.
		FMOD::Channel* channel = nullptr;
		FMOD_RESULT hr = m_FmodSystem->playSound(m_Sound,
			nullptr, false, &channel);

		m_Channel = channel;
		if (hr == FMOD_OK)
		{
			m_Channel->setVolume(m_Volume);
			m_Sound->getLength(&m_SizeMS, FMOD_TIMEUNIT_MS);
			_stprintf_s(m_msSound,
				L"��ü�ð�[%02d:%02d:%02d]",
				m_SizeMS / 1000 / 60,
				m_SizeMS / 1000 % 60,
				m_SizeMS / 10 / 60);

			if (_loop)
			{
				m_Channel->setMode(FMOD_LOOP_NORMAL); // ���ѹݺ�
			}
			else
			{
				m_Channel->setMode(FMOD_LOOP_OFF);
			}
		}
		return m_Channel;
	}
	void Sound::PlayEffect()
	{
		// ä�� : ����Ǵ� ���� ��� ����Ѵ�.
		FMOD::Channel* pChannel = nullptr;
		FMOD_RESULT hr = m_FmodSystem->playSound(m_Sound,
			nullptr, false, &pChannel);
		assert(FMOD_OK(hr));
	}
	void Sound::Stop()
	{
	}
	void Sound::Paused()
	{
	}
	void Sound::VolumeUP(float _volume)
	{
	}
	void Sound::VolumDown(float _volume)
	{
	}
}