#include "Js_SoundManager.h"


namespace Js
{
	FMOD::System* SoundManager::m_FmodSystem = nullptr;
	std::map<std::wstring, std::shared_ptr<Fmod>> SoundManager::m_SoundList = {};

	SoundManager::SoundManager()
	{
	}
	SoundManager::~SoundManager()
	{
	}
	void SoundManager::Init()
	{
		FMOD_RESULT hr = FMOD::System_Create(&m_FmodSystem);
		if (hr != FMOD_OK) return;
		// ���� �ý��� �ʱ�ȭ
		// MAXChannel=32 -> ���ÿ� ������ �Ϲݻ��� ����
		hr = m_FmodSystem->init(32, FMOD_INIT_NORMAL, 0);
		if (hr != FMOD_OK) return;
	}
	void SoundManager::Update()
	{
		m_FmodSystem->update();
	}
	void SoundManager::Release()
	{
	}
}