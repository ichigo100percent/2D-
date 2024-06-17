#include "Js_Collision.h"


namespace Js
{
	bool Collision::RectToRect(const RECT& _rt1, const RECT& _rt2)
	{
		LONG minX, maxX, minY, maxY;
		minX = min(_rt1.left, _rt2.left);
		maxX = max(_rt1.right, _rt2.right);
		minY = min(_rt1.top, _rt2.top);
		maxY = max(_rt1.bottom, _rt2.bottom);
		LONG sizeX, sizeY;
		sizeX = maxX - minX;
		sizeY = maxY - minY;

		LONG  rt1W, rt1H, rt2W, rt2H;
		rt1W = _rt1.right - _rt1.left;// rt1.w + rt2.w;
		rt1H = _rt1.bottom - _rt1.top;
		rt2W = _rt2.right - _rt2.left;// rt1.w + rt2.w;
		rt2H = _rt2.bottom - _rt2.top;

		if (sizeX <= (rt1W + rt2W) &&
			sizeY <= (rt1H + rt2H))
		{
			return true;
		}
		return false;
	}
	bool Collision::RectToPoint(RECT& _rt1, POINT& _pt)
	{
		if (_rt1.left <= _pt.x && _rt1.right >= _pt.x)
		{
			if (_rt1.top <= _pt.y && _rt1.bottom >= _pt.y)
			{
				return true;
			}
		}
		return false;
	}
}