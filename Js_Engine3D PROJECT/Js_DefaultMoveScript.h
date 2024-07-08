#pragma once
#include "Js_MonoBehaviour.h"
#include "Js_Transform.h"

namespace Js
{
	class DefaultMoveScript : public MonoBehaviour
	{
	public:

		virtual void Init() override;
		virtual void Update() override;

		virtual void OnCollisionEnter(std::shared_ptr<Collider> _other) override;
		virtual void OnCollisionStay(std::shared_ptr<Collider> _other) override;
		virtual void OnCollisionExit(std::shared_ptr<Collider> _other) override;

		void SetState(State _state) { m_State = _state; }
		State GetState() { return m_State; }

	protected:
		virtual void move();
		virtual void die();
		virtual void idle();

	protected:
		std::shared_ptr<DxObject> m_Owner = nullptr;
		Vector3 m_Direction = Vector3(-1, 0, 0);
		bool  m_IsGround = false;
		float m_Speed = 100.0f;
		float m_Gravity = -98.0f;
		float m_DeltaTime = 0.0f;
		float m_DieTime = 0.0f;

		State m_State = State::Move;
	};
}
