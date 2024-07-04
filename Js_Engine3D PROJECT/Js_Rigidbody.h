#pragma once
#include "Js_Component.h"

namespace Js
{
	class Rigidbody : public Component
	{
	public:
		Rigidbody();
		virtual ~Rigidbody();

		virtual void Init() override;
		virtual void Update() override;

		void SetMass(float mass) { m_Mass = mass; }
		float GetMass() const { return m_Mass; }

		void SetGravity(const Vector3& gravity) { m_Gravity = gravity; }
		Vector3 GetGravity() const { return m_Gravity; }

		void AddForce(const Vector3& force);
		void SetVelocity(const Vector3& velocity) { m_Velocity = velocity; }
		Vector3 GetVelocity() const { return m_Velocity; }

		void SetAcceleration(const Vector3& acceleration) { m_Acceleration = acceleration; }
		Vector3 GetAcceleration() const { return m_Acceleration; }

		bool IsGrounded() const { return m_IsGrounded; }
		void SetGrounded(bool grounded) { m_IsGrounded = grounded; }

		// 점프 함수 추가
		void Jump(float force)
		{
			if (m_IsGrounded)
			{
				m_Velocity.y = force;
				m_IsGrounded = false;
			}
		}

	private:  
		Vector3 m_Force = Vector3::Zero;
		Vector3 m_Acceleration = Vector3::Zero;
		Vector3 m_Velocity = Vector3::Zero;
		Vector3 m_MaxHorizontalSpeed = Vector3(300.0f, 600.0f, 0.f);
		Vector3 m_Gravity = Vector3(0.f, -980.f, 0.f);
			  
		float m_Mass = 10.f;
		bool m_IsGrounded = false;
		float m_Friction = 5.f;

		std::shared_ptr<Transform> m_Transform = nullptr;
		float m_MaxVerticalSpeed = 10.f;
	};
}