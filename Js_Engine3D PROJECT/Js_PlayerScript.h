#pragma once
#include "Js_MonoBehaviour.h"

namespace Js
{
	class PlayerScript : public MonoBehaviour
	{
	public:

		virtual void Init() override;
		virtual void Update() override;
	private:

	};
}
