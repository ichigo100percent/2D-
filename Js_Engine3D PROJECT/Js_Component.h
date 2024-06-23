#pragma once
#include "std.h"

namespace Js
{
	class DxObject;
	class Transform;

	enum class ComponentType
	{
		Transform,
		MeshRenderer,
		Camera,
		Animator,
		// ...
		Script,

		End,
	};

	enum
	{
		FIXED_COMPONENT_COUNT = static_cast<UINT>(ComponentType::End) - 1
	};

	class Component
	{
	public:
		Component() = default;
		Component(ComponentType _type);
		virtual ~Component();

		virtual void Init() {}
		virtual void Update() {}
		virtual void LateUpdate() {}
		virtual void Render() {}
		virtual void Release() {}

		std::shared_ptr<DxObject> GetOwner();
		std::shared_ptr<Transform> GetTransform();
		ComponentType GetType() { return m_Type; }

	private:
		friend class DxObject;
		void SetOwner(std::shared_ptr<DxObject> _owner) { m_Owner = _owner; }

	protected:
		std::weak_ptr<DxObject> m_Owner;
		ComponentType m_Type;
	};
}