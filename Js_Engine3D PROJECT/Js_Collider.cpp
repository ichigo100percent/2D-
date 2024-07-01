#include "Js_Collider.h"
#include "Js_DxObject.h"
#include "Js_MonoBehaviour.h"

namespace Js
{
	UINT Collider::CollisionID = 1;

	Collider::Collider()
		: Component(ComponentType::Collider)
		, m_ID(CollisionID++)
		, m_Rect{}
	{
	}
	Collider::~Collider()
	{
	}
	void Collider::Init()
	{

	}
	void Collider::Update()
	{
	}
	void Collider::LateUpdate()
	{
	}
	void Collider::OnCollisionEnter(std::shared_ptr<Collider> _other)
	{
		std::vector<std::shared_ptr<MonoBehaviour>>& scripts = GetOwner()->GetScripts();

		for (auto& script : scripts)
		{
			if (script)
				script->OnCollisionEnter(_other);
		}
	}
	void Collider::OnCollisionStay(std::shared_ptr<Collider> _other)
	{
		std::vector<std::shared_ptr<MonoBehaviour>>& scripts = GetOwner()->GetScripts();

		for (auto& script : scripts)
		{
			if (script)
				script->OnCollisionStay(_other);
		}
	}
	void Collider::OnCollisionExit(std::shared_ptr<Collider> _other)
	{
		std::vector<std::shared_ptr<MonoBehaviour>>& scripts = GetOwner()->GetScripts();

		for (auto& script : scripts)
		{
			if (script)
				script->OnCollisionExit(_other);
		}
	}
}