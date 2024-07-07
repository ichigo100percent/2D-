#pragma once
#include "Js_MonoBehaviour.h"
#include "Js_Fireball.h"
#include "Js_Rigidbody.h"

namespace Js
{
	class FireballScript : public MonoBehaviour
	{
	public:
		FireballScript(std::shared_ptr<DxObject> _owner, Vector3 _pos);
		virtual ~FireballScript() {}

		void Update() override;

		virtual void OnCollisionEnter(std::shared_ptr<Collider> _other) override;
		virtual void OnCollisionStay(std::shared_ptr<Collider> _other) override;
		virtual void OnCollisionExit(std::shared_ptr<Collider> _other) override;


	private:
		std::shared_ptr<DxObject> m_Owner = nullptr;
		Vector3 m_Direction = Vector3::Zero;
		Vector3 m_Velocity = Vector3::Zero;
		bool isGround = false;
	};
	//class FireballScript : public MonoBehaviour
	//{
	//public:
	//	FireballScript(std::shared_ptr<DxObject> target) : m_Player(target) , MonoBehaviour() {}
	//	virtual ~FireballScript() {}

	//	void Update() override;

	//	virtual void OnCollisionEnter(std::shared_ptr<Collider> _other) override;
	//	virtual void OnCollisionStay(std::shared_ptr<Collider> _other) override;
	//	virtual void OnCollisionExit(std::shared_ptr<Collider> _other) override;

	//	void ShootFireball();
	//private:
	//	std::weak_ptr<DxObject> m_Player;
	//	std::shared_ptr<Fireball> fireball = nullptr;
	//	float m_DeathTime = 0.f;
	//};

	
	//class FireballScript : public MonoBehaviour
	//{
	//public:
	//	FireballScript(std::shared_ptr<DxObject> _owner, Vector3 _pos);
	//	virtual ~FireballScript();

	//	void Init() override;
	//	void Update() override;

	//	virtual void OnCollisionEnter(std::shared_ptr<Collider> _other) override;
	//	virtual void OnCollisionStay(std::shared_ptr<Collider> _other) override;
	//	virtual void OnCollisionExit(std::shared_ptr<Collider> _other) override;

	//private:
	//	std::shared_ptr<DxObject> m_Owner = nullptr;
	//	Vector3 m_Direction = Vector3::Zero;
	//};
	
}