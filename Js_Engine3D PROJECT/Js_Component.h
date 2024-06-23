#pragma once
#include "std.h"
#include "Js_DxObject.h"

namespace Js
{

	enum ComponentType
	{
		None = 0,
		Transform,
		Mesh,
		Collision,
	};

	class Component
	{
	public:
		Component(ComponentType _type) : m_Type(_type) {}
		
		std::shared_ptr<DxObject> GetOwner() {return m_GameObject.lock(); }

	private:
		ComponentType m_Type;
		std::weak_ptr<DxObject> m_GameObject;
	};
}