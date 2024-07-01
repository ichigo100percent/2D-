#pragma once
#include "Js_Component.h"
#include "Js_Collider.h"

namespace Js
{
	
	class MonoBehaviour : public Component
	{
	public:
		MonoBehaviour();
		~MonoBehaviour();

		virtual void Init() override;
		virtual void Update() override;
		virtual void LateUpdate() override;

		virtual void OnCollisionEnter(std::shared_ptr<Collider> _other);
		virtual void OnCollisionStay(std::shared_ptr<Collider> _other);
		virtual void OnCollisionExit(std::shared_ptr<Collider> _other);

	private:

	};
}