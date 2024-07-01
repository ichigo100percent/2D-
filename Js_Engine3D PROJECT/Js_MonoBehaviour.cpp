#include "Js_MonoBehaviour.h"



namespace Js
{
	MonoBehaviour::MonoBehaviour()
		: Component(ComponentType::Script)
	{
	}
	MonoBehaviour::~MonoBehaviour()
	{
	}
	void MonoBehaviour::Init()
	{
	}
	void MonoBehaviour::Update()
	{
	}
	void MonoBehaviour::LateUpdate()
	{
	}
	void MonoBehaviour::OnCollisionEnter(std::shared_ptr<Collider> _other)
	{
	}
	void MonoBehaviour::OnCollisionStay(std::shared_ptr<Collider> _other)
	{
	}
	void MonoBehaviour::OnCollisionExit(std::shared_ptr<Collider> _other)
	{
	}
}