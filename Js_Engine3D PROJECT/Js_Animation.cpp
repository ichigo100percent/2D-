#include "Js_Animation.h"

namespace Js
{
	Animation::Animation()
		: BaseResource(ResourceType::Animation)
	{
	}
	Animation::~Animation()
	{
	}
	Vector2 Animation::GetTextureSize()
	{
		return m_Texture->GetSize();
	}
	const Keyframe& Animation::GetKeyframe(UINT _index)
	{
		return m_Keyframes[_index];
	}
	UINT Animation::GetKeyframeCount()
	{
		return static_cast<UINT>(m_Keyframes.size());
	}
	void Animation::AddKeyframe(const Keyframe& _keyframe)
	{
		m_Keyframes.push_back(_keyframe);
	}
}