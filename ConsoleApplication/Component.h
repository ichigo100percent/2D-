#pragma once
#include "Çì´õ.h"


enum class ComponentType
{
	Transform,
	Animator,
	Mesh,
	End,
};

enum
{
	Component_ListCount = static_cast<int>(ComponentType::End)
};

class Component
{
public:
	Component(ComponentType _type) : m_Type(_type) {}
	virtual ~Component() {}

	ComponentType GetType() { return m_Type; }
	shared_ptr<class GameObject> GetOwner() { return m_Owner.lock(); }

private:
	friend GameObject;

	void SetOwner(shared_ptr<class GameObject> _obj) { m_Owner = _obj; }

private:
	weak_ptr<class GameObject> m_Owner;
	ComponentType m_Type;
};

class Transform : public Component
{
public:
	Transform() : Component(ComponentType::Transform) {}

};

class Animator : public Component
{
public:
	Animator() : Component(ComponentType::Animator) {}
};