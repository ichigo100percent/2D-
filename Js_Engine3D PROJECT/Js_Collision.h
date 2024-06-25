#pragma once
#include "std.h"
#include "Js_Component.h"

namespace Js
{
	class Collision : public Component
	{
	public:
		Collision();
		virtual ~Collision();

		virtual void Init() {}
		virtual void Update() {}

	private:

	};
}