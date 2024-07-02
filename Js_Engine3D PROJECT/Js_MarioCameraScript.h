#pragma once
#include "Js_MonoBehaviour.h"

namespace Js
{
	class MarioCameraScript : public MonoBehaviour
	{
	public:
		MarioCameraScript(std::shared_ptr<DxObject> target) : m_Target(target) {}
		virtual ~MarioCameraScript() {}

		virtual void LateUpdate() override;
	private:
		std::shared_ptr<DxObject> m_Target;
	};
}
