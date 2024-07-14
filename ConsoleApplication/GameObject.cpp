#include "GameObject.h"

void GameObject::AddComponent(shared_ptr<Component> _comp)
{
	_comp->SetOwner(shared_from_this());

	auto index = _comp->GetType();

	m_Components[(int)index] = _comp;
}
