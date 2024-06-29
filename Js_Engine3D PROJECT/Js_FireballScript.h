#pragma once
#include "Js_MonoBehaviour.h"
#include "Js_Fireball.h"

namespace Js
{

	class FireballScript : public MonoBehaviour
	{
	public:
		FireballScript(std::shared_ptr<DxObject> target) : m_Player(target) , MonoBehaviour() {}
		virtual ~FireballScript() {}

		void Update() override;

		void ShootFireball();
	private:
		std::weak_ptr<DxObject> m_Player;
		std::shared_ptr<Fireball> fireball = nullptr;
		float m_DeathTime = 0.f;
	};
}