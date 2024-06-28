#pragma once
#include "Js_Component.h"

namespace Js
{
	class Transform : public Component
	{
	public:
		Transform();
		~Transform();

		virtual void Init() override;
		virtual void Update() override;

		void UpdateTransform();

		// World
		Vector3 GetScale() { return m_Scale; }
		void SetScale(const Vector3& _scale);
		Vector3 GetRotation() { return m_Rotation; }
		void SetRotation(const Vector3& _rotation);
		Vector3 GetPosition() { return m_Position; }
		void SetPosition(const Vector3& _position);

		Matrix GetWorldMatrix() { return m_WorldMatrix; }
		Vector3 GetRight() { return m_WorldMatrix.Right(); }
		Vector3 GetUp() { return m_WorldMatrix.Up(); }
		Vector3 GetLook() { return m_WorldMatrix.Backward(); }
		MyRect GetRect() { return m_Rect; }

		void SetForward2D(const Vector3& direction)
		{
			float radians = atan2(direction.y, direction.x);
			m_LocalRotation.z = XMConvertToDegrees(radians);
			UpdateTransform();
		}
		Vector3 GetForward2D() const
		{
			float radians = XMConvertToRadians(m_LocalRotation.z);
			return Vector3(cos(radians), sin(radians), 0);
		}

	protected:
		// Local
		Vector3 GetLocalScale() { return m_LocalScale; }
		void SetLocalScale(const Vector3& _scale) { m_LocalScale = _scale; UpdateTransform(); }
		Vector3 GetLocalRotation() { return m_LocalRotation; }
		void SetLocalRotation(const Vector3& _rotation) { m_LocalRotation = _rotation; UpdateTransform(); }
		Vector3 GetLocalPosition() { return m_LocalPosition; }
		void SetLocalPosition(const Vector3& _position) { m_LocalPosition = _position; UpdateTransform(); }

	protected:
		Matrix       m_LocalMatrix = Matrix::Identity;
		Matrix		 m_WorldMatrix = Matrix::Identity;

		Vector3 m_Scale;
		Vector3 m_Rotation;
		Vector3 m_Position;

		Vector3 m_LocalScale	= { 1.f, 1.f, 1.f };
		Vector3 m_LocalRotation = { 0.f, 0.f, 0.f };
		Vector3 m_LocalPosition = { 0.f, 0.f, 0.f };
		Quaternion m_LocalQuaternion = { 0.f, 0.f, 0.f, 0.f };

		MyRect m_Rect = {};
	};
}
