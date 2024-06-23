#include "Js_Component.h"
#include "Js_DxObject.h"

namespace Js
{
	Component::Component(ComponentType _type)
		: m_Type(_type)
	{
	}
	Component::~Component()
	{
	}

	std::shared_ptr<DxObject> Component::GetOwner()
	{
		return m_Owner.lock();
	}

	std::shared_ptr<Transform> Component::GetTransform()
	{
		return m_Owner.lock()->GetTransform();
	}
}