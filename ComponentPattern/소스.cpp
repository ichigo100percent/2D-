#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>
#include <memory>
#include <array>
#include <assert.h>


using namespace std;

class GameObject;

enum class Type
{
	Transform,
	Collider,
	End,
};
enum
{
	TYPE_COUNT = static_cast<int>(Type::End)
};
class Component
{
public:
	Component(Type _type) : m_Type(_type) {}
	virtual ~Component() {}

	Type GetType() { return m_Type; }
	shared_ptr<GameObject> GetOwner() { return m_Owner.lock(); }

private:
	friend GameObject;

	void SetOwner(shared_ptr<GameObject> _owner) { m_Owner = _owner; }

private:
	weak_ptr<GameObject> m_Owner;
	Type m_Type;
};

class Transform : public Component
{
public:
	Transform() : Component(Type::Transform) {}
};
class Collider : public Component
{
public:
	Collider() : Component(Type::Collider) {}
};
class Entity
{
public:
	Entity() = default;
	Entity(const string& _name) : Name(_name) {}
	virtual ~Entity() {}

	string GetName() { return Name; }

private:
	string Name = {};
};

class GameObject : public enable_shared_from_this<GameObject>, public Entity
{
public:
	GameObject() = default;
	GameObject(const string& _name) : Entity(_name) {}
	virtual ~GameObject() = default;

	template <typename T>
	shared_ptr<T> GetComponent()
	{
		for (auto& component : m_Components)
		{
			auto comp = dynamic_pointer_cast<T>(component);
			if (comp)
				return comp;
		}
		return nullptr;
	}

	shared_ptr<Component> GetComponent(Type _type)
	{
		auto index = static_cast<int>(_type);
		assert(index < TYPE_COUNT);

		return m_Components[index];
	}

	void AddComponent(shared_ptr<Component> _comp)
	{
		_comp->SetOwner(shared_from_this());
		auto index = static_cast<int>(_comp->GetType());

		if (index < TYPE_COUNT)
			m_Components[index] = _comp;
	}

private:
	array<shared_ptr<Component>, TYPE_COUNT> m_Components = {};
};

int main()
{
	shared_ptr<GameObject> player = make_shared<GameObject>("Player");
	player->AddComponent(make_shared<Transform>());
	player->AddComponent(make_shared<Collider>());

	auto tr = player->GetComponent(Type::Transform);
	auto col = player->GetComponent<Collider>();

	return 0;
}