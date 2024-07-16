#pragma once
#include "Js_MonoBehaviour.h"

namespace Js
{
	class FollowObjectScript : public MonoBehaviour
	{
	public:
		FollowObjectScript(std::shared_ptr<DxObject> _target);
		virtual ~FollowObjectScript();

		virtual void Init() override;
		virtual void Update() override;

		virtual void OnCollisionEnter(std::shared_ptr<Collider> _other) override;
		virtual void OnCollisionStay(std::shared_ptr<Collider> _other) override;
		virtual void OnCollisionExit(std::shared_ptr<Collider> _other) override;

	private:
		Vector3  GetFirePos();

	private:
		std::shared_ptr<DxObject> m_Target = nullptr;
		UINT m_Length = 150;
		float m_Angle = 0.0f;
		float m_Speed = 300.0f;
	};
}
