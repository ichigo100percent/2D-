#pragma once
#include "Js_Resource.h"
#include "Js_Texture.h"

namespace Js
{
	struct Keyframe
	{
		Keyframe() = default;
		Keyframe(const Vector2& _offset, const Vector2& _size, float _time)
			: offset(_offset), size(_size), time(_time)
		{
		}
		Vector2 offset = Vector2::Zero;
		Vector2 size = Vector2::Zero;
		float   time = 0.f;
	};


	class Animation : public BaseResource
	{
	public:
		Animation();
		virtual ~Animation();

		Vector2 GetTextureSize();

		const Keyframe& GetKeyframe(UINT _index);
		UINT GetKeyframeCount();
		void AddKeyframe(const Keyframe& keyframe);

		void SetLoop(bool _loop) { m_Loop = _loop; }
		bool IsLoop() { return m_Loop; }

		void SetTexture(std::shared_ptr<Texture> _texture) { m_Texture = _texture; }
		std::shared_ptr<Texture> GetTexture() { return m_Texture; }

	private:
		bool m_Loop = false;
		std::shared_ptr<Texture> m_Texture;
		std::vector<Keyframe> m_Keyframes;
	};
}