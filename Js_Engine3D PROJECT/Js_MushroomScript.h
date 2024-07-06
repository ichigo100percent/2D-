#pragma once
#include "Js_MonoBehaviour.h"

namespace Js
{
	class MushroomScript : public MonoBehaviour
	{
	public:
		virtual void Init() override;
		virtual void Update() override;

		virtual void OnCollisionEnter(std::shared_ptr<Collider> _other) override;
		virtual void OnCollisionStay(std::shared_ptr<Collider> _other) override;
		virtual void OnCollisionExit(std::shared_ptr<Collider> _other) override;
		
	private:
		Vector3 m_Direction = Vector3(1, 0, 0);
		bool  m_IsGround = false;
		float m_Speed = 100.0f;
		float m_Gravity = -98.0f;
		float m_DeltaTime = 0.0f;

	};
}
