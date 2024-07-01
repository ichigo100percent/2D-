#include "Js_Animator.h"
#include "Js_Time.h"

namespace Js
{
	Animator::Animator()
		: Component(ComponentType::Animator)
	{
	}
	Animator::~Animator()
	{
	}
	void Animator::Init()
	{
	}
	void Animator::Update()
	{
		std::shared_ptr<Animation> animation = GetCurrentAnimation();
		if (animation == nullptr)
			return;
		 
		const Keyframe& keyframe = animation->GetKeyframe(m_CurrentKeyframeIndex);
		float deltaTime = Time::DeltaTime();
		m_SumTime += deltaTime;

		if (m_SumTime >= keyframe.time)
		{
			m_CurrentKeyframeIndex++;
			UINT totalCount = animation->GetKeyframeCount();

			if (m_CurrentKeyframeIndex >= totalCount)
			{
				if (animation->IsLoop())
					m_CurrentKeyframeIndex = 0;
				else
					m_CurrentKeyframeIndex = totalCount - 1;
			}
			m_SumTime = 0.0f;
		}
	}
	void Animator::SetAnimation(std::shared_ptr<Animation> _animation)
	{
		if (m_CurrentAnimation != _animation)
		{
			m_CurrentAnimation = _animation;
			m_CurrentKeyframeIndex = 0;
			m_SumTime = 0.0f;
		}
	}
}