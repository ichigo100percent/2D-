#pragma once
#include "Js_DefaultMoveScript.h"

namespace Js
{
	class KoopaScript : public DefaultMoveScript
	{
	public:
		virtual void Init() override;
		virtual void Update() override;

		virtual void OnCollisionEnter(std::shared_ptr<Collider> _other) override;
		virtual void OnCollisionStay(std::shared_ptr<Collider> _other) override;
		virtual void OnCollisionExit(std::shared_ptr<Collider> _other) override;

	private:	
		void idle() override;
		void die() override;
		void move() override;
		bool isFacingRight = false;
	};
}
