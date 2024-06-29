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
	void Animation::SetKeyFrame(const Vector2& _offset, const Vector2 _size, UINT _length, float _time)
	{
		for (UINT i = 0; i < _length; i++)
		{
			Keyframe keyframe;
			keyframe.offset = Vector2(_offset.x + (_size.x * i), _offset.y);
			keyframe.size = _size;
			keyframe.time = _time;

			AddKeyframe(keyframe);
		}
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