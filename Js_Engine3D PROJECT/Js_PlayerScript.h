#pragma once
#include "Js_MonoBehaviour.h"
#include "Js_Animator.h"
#include "Js_Rigidbody.h"
namespace Js
{
	class PlayerScript : public MonoBehaviour
	{
	public:
		PlayerScript(std::shared_ptr<DxObject> _player);
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

	private:
		void idle();
		void move();
		void jump();
		void die();
		void growUp(std::shared_ptr<Collider> _other);

		void CollisionInteraction(std::shared_ptr<Collider> _other);
		void animationSwitch(MarioType _type);

	private:
		std::shared_ptr<DxObject> m_Player = nullptr;
		std::shared_ptr<Animator> m_Animator = nullptr;
		std::shared_ptr<Rigidbody> m_Rigidbody = nullptr;
		std::shared_ptr<Animation> m_Animation = nullptr;

		bool isJump = false;
		bool isFacingRight = true;
		float time = 0.0f;

	private:
		State m_State = State::Idle;
		MarioType m_Type = MarioType::Nomal;
	};
}
