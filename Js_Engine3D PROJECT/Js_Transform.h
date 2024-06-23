#pragma once
#include "Js_Component.h"

namespace Js
{
	class Transform : public Component
	{
	public:
		Transform();

		void Init();
		void Update();



	private:
		Vector3 m_LocalScale	= { 1.f, 1.f, 1.f };
		Vector3 m_LocalRotation = { 0.f, 0.f, 0.f };
		Vector3 m_LocalPosition = { 0.f, 0.f, 0.f };
	};
}
