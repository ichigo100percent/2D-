#pragma once
#include "Js_MonoBehaviour.h"
namespace Js
{
	class FollowTargetScript : public MonoBehaviour
	{
	public:
		FollowTargetScript(std::shared_ptr<DxObject> target) : m_Target(target) {}
		virtual ~FollowTargetScript() {}

		virtual void LateUpdate() override;

	private:
		std::shared_ptr<DxObject> m_Target;
	};
}
