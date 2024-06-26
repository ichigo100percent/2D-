#pragma once
#include "Js_Component.h"

namespace Js
{
	class MonoBehaviour : public Component
	{
	public:
		MonoBehaviour();
		~MonoBehaviour();

		virtual void Init() override;
		virtual void Update() override;
		virtual void LateUpdate() override;

	private:

	};
}