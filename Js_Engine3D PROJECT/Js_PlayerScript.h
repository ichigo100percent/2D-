#pragma once
#include "Js_MonoBehaviour.h"
#include "Js_Animator.h"
#include "Js_Rigidbody.h"
namespace Js
{
	class PlayerScript : public MonoBehaviour
	{
	public:
		PlayerScript();
		virtual ~PlayerScript();

		virtual void Init() override;
		virtual void Update() override;

		virtual void OnCollisionEnter(std::shared_ptr<Collider> _other) override;
		virtual void OnCollisionStay(std::shared_ptr<Collider> _other) override;
		virtual void OnCollisionExit(std::shared_ptr<Collider> _other) override;

		void HandleCollision(std::shared_ptr<Collider> _other);
		void SetType(MarioType _type) { m_Type = _type; }
		void SetState(State _state) { m_State = _state; }
		State GetMarioState() { return m_State; }
		MarioType GetMarioType() { return m_Type; }
		bool GetJump() { return isJump; }

	private:
		void idle();
		void move();
		void jump();
		void attack();
		void die();
		void growUp(std::shared_ptr<Collider> _other);

		void CollisionInteraction(std::shared_ptr<Collider> _other);


	private:
		std::shared_ptr<Animator> m_Animator = nullptr;
		std::shared_ptr<Rigidbody> m_Rigidbody = nullptr;
		std::shared_ptr<Animation> m_Animation = nullptr;

		bool isJump = false;
		bool isFacingRight = true;
		bool isInvincible = false;
		float time = 0.0f;
		float deadTime = 0.0f;
		float invincibilityTimer = 0.0f;

	private:
		State m_State = State::Idle;
		MarioType m_Type = MarioType::Nomal;
	};
}
