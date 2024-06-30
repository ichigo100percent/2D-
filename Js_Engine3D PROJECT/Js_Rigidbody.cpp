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
		// ���� ���ӵ� ���
		m_Acceleration = m_Force / m_Mass;
		m_Velocity += m_Acceleration * Time::DeltaTime();

		// ���� ����� ���� ó��
		if (m_IsGrounded)
		{
			// ���� ���� ���¿����� ���� ������ �ӵ��� 0���� ����ϴ�.
			m_Velocity.y = 0.0f;

			// ���� ���� �ӵ� ����
			Vector3 horizontalVelocity = Vector3(m_Velocity.x, 0.0f, m_Velocity.z);
			if (horizontalVelocity.Length() > m_MaxHorizontalSpeed.y)
			{
				horizontalVelocity.Normalize();
				horizontalVelocity *= m_MaxHorizontalSpeed;
				m_Velocity.x = horizontalVelocity.x;
				m_Velocity.z = horizontalVelocity.z;
			}

			// ������ ����
			Vector3 friction = -m_Velocity;
			friction.Normalize();
			friction *= m_Friction * m_Mass * Time::DeltaTime();

			// ���������� ���� �ӵ� ���ҷ��� ���� �ӵ����� ū ���
			if (friction.Length() >= m_Velocity.Length())
			{
				m_Velocity = Vector3::Zero;
			}
			else
			{
				m_Velocity += friction;
			}
		}
		else
		{
			// ���߿� ���� �� �߷� ����
			m_Velocity += m_Gravity * Time::DeltaTime();
		}

		// ��ġ ������Ʈ
		Vector3 pos = m_Transform->GetPosition();
		pos += m_Velocity * Time::DeltaTime();
		m_Transform->SetPosition(pos);

		// �� �ʱ�ȭ
		m_Force = Vector3::Zero;
		/*
		//f(��) = m(����) * a(���ӵ�)
		//a = f / m
		m_Acceleration = m_Force / m_Mass;

		//�ӵ��� ���Ӹ� ���Ѵ�
		m_Velocity += m_Acceleration * Time::DeltaTime();

		if (m_IsGrounded)
		{
			//�� ���� ������
			Vector3 gravity = m_Gravity;
			gravity.Normalize();

			float dot = Dot(m_Velocity, gravity);
			m_Velocity -= gravity * dot;
		}
		else
		{
			//���߿� ������
			m_Velocity += m_Gravity * Time::DeltaTime();
		}

		//�ִ� �ӵ� ����
		Vector3 gravity = m_Gravity;
		gravity.Normalize();
		float dot = Dot(m_Velocity, gravity);
		gravity = gravity * dot;

		Vector3 sideVelocity = m_Velocity - gravity;
		if (m_LimitedVelocity.y < gravity.Length())
		{
			gravity.Normalize();
			gravity *= Time::DeltaTime();
		}
		if (m_LimitedVelocity.x < sideVelocity.Length())
		{
			sideVelocity.Normalize();
			sideVelocity *= m_LimitedVelocity.x;
		}
		m_Velocity = gravity + sideVelocity;


		if (!(m_Velocity == Vector3::Zero))
		{
			//�ӵ��� �ݴ�������� ������ �ۿ�
			Vector3 friction = -m_Velocity;
			friction.Normalize();
			friction = friction * m_Friction* m_Mass * Time::DeltaTime();

			//���������� ���� �ӵ� ���ҷ��� ���� �ӵ����� ū ���
			if (m_Velocity.Length() <= friction.Length())
			{
				//����
				m_Velocity = Vector3::Zero;
			}
			else
			{
				m_Velocity += friction;
			}
		}

		// Update position
		Vector3 pos = m_Transform->GetPosition();
		pos += m_Velocity * Time::DeltaTime();
		m_Transform->SetPosition(pos);

		// Reset force
		m_Force = Vector3::Zero;
		*/
	}
	void Rigidbody::AddForce(const Vector3& force)
	{
		m_Force += force;
	}
}