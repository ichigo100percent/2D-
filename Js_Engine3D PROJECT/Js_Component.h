#pragma once
#include "std.h"
//#include "Js_DxObject.h"

namespace Js
{
	enum ComponentType
	{
		eNone = 0,
		eTransform,
		eMesh,
		eCollision,
	};

	class Component
	{
	public:
		Component();
		virtual ~Component();

		virtual void Init() abstract;
		virtual void Update() abstract;
		
		//std::shared_ptr<DxObject> GetOwner() {return m_GameObject.lock(); }
		//ComponentType GetComponentType() { return m_Type; }

	private:
		//ComponentType m_Type;
		//std::weak_ptr<DxObject> m_GameObject;
	};
}