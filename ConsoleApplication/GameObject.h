#pragma once
#include "Component.h"


class GameObject : public enable_shared_from_this<GameObject>
{
public:
	void AddComponent(shared_ptr<Component> _comp);
	
	template <typename T>
	shared_ptr<T> GetComponent()
	{
		std::shared_ptr<T> component = nullptr;
		for (auto& comp : m_Components)
		{
			component = std::dynamic_pointer_cast<T>(comp);

			if (component)
				break;
		}
		return component;
	}

private:
	array<shared_ptr<Component>, Component_ListCount> m_Components = {};
};


