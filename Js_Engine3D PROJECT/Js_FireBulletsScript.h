#pragma once
#include "Js_MonoBehaviour.h"

namespace Js
{
	class FireBulletsScript : public MonoBehaviour
	{
	public:

		virtual void Init() override;
		virtual void Update() override;

		virtual void OnCollisionEnter(std::shared_ptr<Collider> _other) override;
		virtual void OnCollisionStay(std::shared_ptr<Collider> _other) override;
		virtual void OnCollisionExit(std::shared_ptr<Collider> _other) override;
	private:
		int cnt;
		float angle;
	};
}
