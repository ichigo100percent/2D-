#pragma once
#include "Js_Component.h"
#include "Js_Animation.h"


namespace Js
{
	class Animator :public Component
	{
	public:
		Animator();
		virtual ~Animator();

		virtual void Init() override;
		virtual void Update() override;

		void SetAnimation(std::shared_ptr<Animation> _animation);
		std::shared_ptr<Animation> GetCurrentAnimation() { return m_CurrentAnimation; }
		Keyframe GetCurrentKeyFrame() { return m_CurrentAnimation->GetKeyframe(m_CurrentKeyframeIndex); }

	private:
		std::shared_ptr<Animation> m_CurrentAnimation = nullptr;
		UINT m_CurrentKeyframeIndex = 0;
		float m_SumTime = 0.0f;
	};
}
