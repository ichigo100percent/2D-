#pragma once
#include "std.h"

namespace Js
{
	class Collision
	{
	public:
		static bool RectToRect(const RECT& _rt1,const RECT& _rt2);
		static bool RectToPoint(RECT& _rt1, POINT& _pt);
	private:
	};
}
