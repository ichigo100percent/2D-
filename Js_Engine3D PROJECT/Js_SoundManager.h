#pragma once
#include "Js_Sound.h"

namespace Js
{
	class SoundManager
	{
	public:
		SoundManager();
		virtual ~SoundManager();

		static void Init();
		static void Update();
		static void Release();

		static void Add(const std::wstring& _path, const std::wstring& _name)
		{
			std::shared_ptr<Fmod> sound = std::make_shared<Fmod>();
			sound->SetFmod(m_FmodSystem);
			sound->SetName(_name);

			if (sound->Load(_path) == false)
				return;

			m_SoundList.insert(std::make_pair(sound->GetName(), sound));
		}
		static std::shared_ptr<Fmod> Get(const std::wstring& _name)
		{
			auto sound = m_SoundList.find(_name);

			if (sound != m_SoundList.end())
				return sound->second;

			return nullptr;
		}

	private:
		static FMOD::System* m_FmodSystem;
		static std::map<std::wstring, std::shared_ptr<Fmod>> m_SoundList;
	};
}
