#pragma once
#include "Js_MonoBehaviour.h"
#include "Js_Transform.h"

namespace Js
{
	class GoombaScript : public MonoBehaviour
	{
	public:

		virtual void Init() override;
		virtual void Update() override;

		virtual void OnCollisionEnter(std::shared_ptr<Collider> _other) override;
		virtual void OnCollisionStay(std::shared_ptr<Collider> _other) override;
		virtual void OnCollisionExit(std::shared_ptr<Collider> _other) override;

	private:
		std::shared_ptr<Transform> m_Transform = nullptr;
		Vector3 m_Direction = Vector3(-1, 0, 0);
		bool  m_IsGround = false;
		float m_Speed = 100.0f;
		float m_Gravity = -98.0f;
	};
}
