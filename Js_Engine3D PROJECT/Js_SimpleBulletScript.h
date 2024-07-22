#pragma once
#include "Js_MonoBehaviour.h"

namespace Js
{
	class SimpleBulletScript : public MonoBehaviour
	{
	public:
		SimpleBulletScript();
		virtual ~SimpleBulletScript();

		virtual void Init() override;
		virtual void Update() override;

		void SetNormalizedDirection(Vector3 _dir);

		virtual void OnCollisionEnter(std::shared_ptr<Collider> _other) override;
		virtual void OnCollisionStay(std::shared_ptr<Collider> _other) override;
		virtual void OnCollisionExit(std::shared_ptr<Collider> _other) override;

	private:
		float m_Time = 0.0f;
		float m_Speed = 700.f;
		Vector3 m_Velocity = Vector3::Zero;
	};
}