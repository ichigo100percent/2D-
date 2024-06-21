#pragma once
#include "Js_BaseMgr.h"

namespace Js
{
	class Sound : public Resource
	{
	public:
		Sound();
		~Sound();

		void Init();
		void Update();
		void Render();
		void Release();

		void SetFmod(FMOD::System* _system) { m_FmodSystem = _system; }
		bool Load(const std::wstring& _fileName) override;
		FMOD::Channel* Play(bool _loop = false);
		void PlayEffect();
		void Stop();
		void Paused();
		void VolumeUP(float _volume);
		void VolumDown(float _volume);		

	public:
		FMOD::Sound* m_Sound = nullptr;
		FMOD::Channel* m_Channel = nullptr;
		float m_Volume = 1.0f;
		UINT m_SizeMS;
		wchar_t			m_msSound[MAX_PATH] = { 0, };
		wchar_t			m_msPlay[MAX_PATH] = { 0, };

	private:
		FMOD::System* m_FmodSystem = nullptr;
	};

	class SoundMgr : public BaseManager<Sound, SoundMgr>
	{
		friend class Singleton<SoundMgr>;
	public:
		void Update() { m_FmodSystem->update(); }
		void Render() {}
		void Release()
		{
			BaseManager<Sound, SoundMgr>::Release();
			if (m_FmodSystem)
			{
				m_FmodSystem->close();
				m_FmodSystem->release();
			}
			m_FmodSystem = nullptr;
		}
	private:
		SoundMgr()
		{
			FMOD_RESULT hr = FMOD::System_Create(&m_FmodSystem);
			if (hr != FMOD_OK) return;
			// 사운드 시스템 초기화
			// MAXChannel=32 -> 동시에 가능한 일반사운드 갯수
			hr = m_FmodSystem->init(32, FMOD_INIT_NORMAL, 0);
			if (hr != FMOD_OK) return;
		}
		~SoundMgr() {}

		std::shared_ptr<Sound> CreateObject(std::wstring _path, std::wstring _name)
		{
			std::shared_ptr<Sound>  pData = std::make_shared<Sound>();
			pData->SetFmod(m_FmodSystem);
			pData->m_csName = _name;
			if (pData->Load(_path) == false)
			{
				return nullptr;
			}
			m_List.insert(std::make_pair(pData->m_csName, pData));
			return pData;
		}

	private:
		FMOD::System* m_FmodSystem = nullptr;
	};

#define SOUND	SoundMgr::Instance()
}

