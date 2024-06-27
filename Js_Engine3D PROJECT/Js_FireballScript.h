#pragma once
#include "Js_MonoBehaviour.h"

namespace Js
{
	class FireballScript : public MonoBehaviour
	{
	public:

		void Init() override;
		void Update() override;

		void ShootFireball();
	};
}