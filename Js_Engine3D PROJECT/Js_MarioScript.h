#pragma once
#include "Js_MonoBehaviour.h"

namespace Js
{
	class MarioScript : public MonoBehaviour
	{
	public:

        virtual void Init() override;
        virtual void Update() override;

        virtual void OnCollisionEnter(std::shared_ptr<Collider> _other) override;
        virtual void OnCollisionStay(std::shared_ptr<Collider> _other) override;
        virtual void OnCollisionExit(std::shared_ptr<Collider> _other) override;

    private:
        std::shared_ptr<Transform> m_Transform;
        Vector3 m_Direction;
        float m_Speed;
        float m_Acceleration;
        float m_Gravity;
        float m_JumpForce;
        bool m_IsGrounded;
        float m_Friction;
        float m_Mass;
	};
}
