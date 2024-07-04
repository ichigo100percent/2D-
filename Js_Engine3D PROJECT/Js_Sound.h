#pragma once
#include "Js_Resource.h"
#pragma warning(disable : 4353)

namespace Js
{
	class Fmod : public Entity
	{
	public:
		Fmod();
		virtual ~Fmod();

		void Init();
		void Update();
		void Render();
		void Release();

		void SetFmod(FMOD::System* _system) { m_FmodSystem = _system; }
		bool Load(const std::wstring& _fileName);
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
}
