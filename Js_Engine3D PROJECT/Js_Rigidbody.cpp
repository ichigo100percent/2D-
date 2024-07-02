#include "Js_Rigidbody.h"
#include "Js_Transform.h"
#include "Js_DxObject.h"
#include "Js_Time.h"

namespace Js
{
	static float Dot(const Vector3& a, const Vector3& b) noexcept
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(reinterpret_cast<const XMFLOAT3*>(&a));
		XMVECTOR v2 = XMLoadFloat3(reinterpret_cast<const XMFLOAT3*>(&b));
		XMVECTOR X = XMVector3Dot(v1, v2);
		return XMVectorGetX(X);
	};

	Rigidbody::Rigidbody()
		: Component(ComponentType::Rigidbody)
	{
	}
	Rigidbody::~Rigidbody()
	{
	}
	void Rigidbody::Init()
	{
		m_Transform = GetOwner()->GetTransform();

	}
	void Rigidbody::Update()
	{
		// F = m * a
		// a = F / m
		m_Acceleration = m_Force / m_Mass;

		// 속도에 가속도를 더한다
		m_Velocity += m_Acceleration * Time::DeltaTime();

		// 중력 적용
		if (!m_IsGrounded)
		{
			m_Velocity += m_Gravity * Time::DeltaTime();
		}

		// 최대 속도 제한
		Vector3 gravity = m_Gravity;
		gravity.Normalize();
		float dot = Dot(m_Velocity, gravity);
		gravity = gravity * dot;

		Vector3 sideVelocity = m_Velocity - gravity;
		if (m_MaxHorizontalSpeed.y < gravity.Length())
		{
			gravity.Normalize();
			gravity *= m_MaxHorizontalSpeed.y;
		}
		if (m_MaxHorizontalSpeed.x < sideVelocity.Length())
		{
			sideVelocity.Normalize();
			sideVelocity *= m_MaxHorizontalSpeed.x;
		}
		m_Velocity = gravity + sideVelocity;

		// 마찰력 적용
		if (m_Velocity != Vector3::Zero)
		{
			Vector3 friction = -m_Velocity;
			friction.Normalize();
			friction *= m_Friction * m_Mass * Time::DeltaTime();

			if (m_Velocity.Length() <= friction.Length())
			{
				m_Velocity = Vector3::Zero; // 속도가 마찰력보다 작으면 멈춤
			}
			else
			{
				m_Velocity += friction;
			}
		}

		// 위치 업데이트
		Vector3 pos = m_Transform->GetPosition();
		pos += m_Velocity * Time::DeltaTime();
		m_Transform->SetPosition(pos);

		// 초기화
		m_Force = Vector3::Zero;
		////f(힘) = m(질량) * a(가속도)
		////a = f / m
		//m_Acceleration = m_Force / m_Mass;

		////속도에 가속를 더한다
		//m_Velocity += m_Acceleration * Time::DeltaTime();

		//if (m_IsGrounded)
		//{
		//	//땅 위에 있을때
		//	Vector3 gravity = m_Gravity;
		//	gravity.Normalize();

		//	float dot = Dot(m_Velocity, gravity);
		//	m_Velocity -= gravity * dot;
		//}
		//else
		//{
		//	//공중에 있을때
		//	m_Velocity += m_Gravity * Time::DeltaTime();
		//}

		//// 최대 속도 제한
		//Vector3 gravity = m_Gravity;
		//gravity.Normalize();
		//float dot = Dot(m_Velocity, gravity);
		//gravity = gravity * dot;

		//Vector3 sideVelocity = m_Velocity - gravity;
		//if (m_MaxHorizontalSpeed.y < gravity.Length())
		//{
		//	gravity.Normalize();
		//	gravity *= Time::DeltaTime();
		//}
		//if (m_MaxHorizontalSpeed.x < sideVelocity.Length())
		//{
		//	sideVelocity.Normalize();
		//	sideVelocity *= m_MaxHorizontalSpeed.x;
		//}
		//m_Velocity = gravity + sideVelocity;


		//if (!(m_Velocity == Vector3::Zero))
		//{
		//	//속도에 반대방향으로 마찰력 작용
		//	Vector3 friction = -m_Velocity;
		//	friction.Normalize();
		//	friction = friction * m_Friction* m_Mass * Time::DeltaTime();

		//	//마찰력으로 인한 속도 감소량이 현재 속도보다 큰 경우
		//	if (m_Velocity.Length() <= friction.Length())
		//	{
		//		//멈춤
		//		m_Velocity = Vector3::Zero;
		//	}
		//	else
		//	{
		//		m_Velocity += friction;
		//	}
		//}
		//// Update position
		//Vector3 pos = m_Transform->GetPosition();
		//pos += m_Velocity * Time::DeltaTime();
		//m_Transform->SetPosition(pos);

		//// Reset force
		//m_Force = Vector3::Zero;
		

	}
	void Rigidbody::AddForce(const Vector3& force)
	{
		m_Force += force;
	}
}