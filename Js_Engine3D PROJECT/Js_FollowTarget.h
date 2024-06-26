#pragma once
#include "Js_MonoBehaviour.h"
namespace Js
{
	class FollowTarget : public MonoBehaviour
	{
	public:
		FollowTarget(std::shared_ptr<DxObject> target) : m_Target(target) {}
		virtual ~FollowTarget() {}

		virtual void LateUpdate() override;

	private:
		std::shared_ptr<DxObject> m_Target;
	};
}
