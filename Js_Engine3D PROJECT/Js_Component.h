#pragma once
#include "std.h"
#include "Js_DxObject.h"

namespace Js
{

	enum Type
	{
		None = 0,
		Transform,
		Mesh,
		Collision,
	};

	class Component
	{
	public:

	private:
		Type m_eType;
		
	};
}