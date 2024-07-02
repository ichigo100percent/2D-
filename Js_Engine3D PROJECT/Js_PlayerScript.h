#pragma once
#include "Js_MonoBehaviour.h"
#include "Js_Animator.h"
#include "Js_Rigidbody.h"
namespace Js
{
	enum class State
	{
		Idle,
		Jump,
		Move,
		Die,
		End,
	};

	class PlayerScript : public MonoBehaviour
	{
	public:

		virtual void Init() override;
		virtual void Update() override;

		virtual void OnCollisionEnter(std::shared_ptr<Collider> _other) override;
		virtual void OnCollisionStay(std::shared_ptr<Collider> _other) override;
		virtual void OnCollisionExit(std::shared_ptr<Collider> _other) override;

		void HandleCollision(std::shared_ptr<Collider> _other);
	private:

	private:
		std::shared_ptr<Animator> m_Animator = nullptr;
		std::shared_ptr<Rigidbody> m_Rigidbody = nullptr;
		State m_State = State::Idle;
		bool m_CanJump = true;
		bool m_IsJump = false;
		float m_MinJumpForce = 400;
		float m_MaxJumpForce = 600;
		float m_MaxJumpDuration = 0.2f;
		float m_JumpStartTime = 0.0f;
		float m_CurrentJumpForce = 0.0f;
	};
}
