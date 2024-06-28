#pragma once
#include "Js_MonoBehaviour.h"

namespace Js
{
	class FireballScript : public MonoBehaviour
	{
	public:
		FireballScript(std::shared_ptr<DxObject> target) : m_Player(target) , MonoBehaviour() {}
		virtual ~FireballScript() {}

		void Update() override;

		void ShootFireball();

		std::weak_ptr<DxObject> m_Player;
	};
}