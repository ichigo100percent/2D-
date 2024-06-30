#pragma once
#include "std.h"
#include "Js_Component.h"
#include "Js_Transform.h"

namespace Js
{
	class Collision
	{
	public:
		static bool CheckCollision(const MyRect& rect1, const MyRect& rect2)
		{
			// 두 사각형이 충돌하는지 확인
			if (rect1.left < rect2.right &&
				rect1.right > rect2.left &&
				rect1.top > rect2.bottom &&
				rect1.bottom < rect2.top)
			{
				return true;
			}
			return false;
		}
		static bool CheckCollision(const MyRect& rect1, const MyRect& rect2, Vector3& pushVector)
		{
			// 충돌 감지
			if (rect1.left < rect2.right &&
				rect1.right > rect2.left &&
				rect1.top > rect2.bottom &&
				rect1.bottom < rect2.top)
			{

				// 충돌 방향 계산
				float overlapLeft = rect2.right - rect1.left;
				float overlapRight = rect1.right - rect2.left;
				float overlapTop = rect2.bottom - rect1.top;
				float overlapBottom = rect1.bottom - rect2.top;

				float overlapX = (std::abs(overlapLeft) < std::abs(overlapRight)) ? overlapLeft : -overlapRight;
				float overlapY = (std::abs(overlapTop) < std::abs(overlapBottom)) ? overlapTop : -overlapBottom;

				if (std::abs(overlapX) < std::abs(overlapY))
					pushVector = Vector3(overlapX, 0, 0);
				else
					pushVector = Vector3(0, overlapY, 0);

				return true;
			}
			return false;
		}

	};
}