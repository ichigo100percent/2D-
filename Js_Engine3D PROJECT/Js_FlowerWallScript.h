#pragma once
#include "Js_MonoBehaviour.h"

namespace Js
{
	class FlowerWallScript : public MonoBehaviour
	{
	public:
		virtual void Init() override;
		virtual void Update() override;

		virtual void OnCollisionEnter(std::shared_ptr<Collider> _other) override;
		virtual void OnCollisionStay(std::shared_ptr<Collider> _other) override;
		virtual void OnCollisionExit(std::shared_ptr<Collider> _other) override;

	private:
		UINT m_Count = 0;

	};
}
