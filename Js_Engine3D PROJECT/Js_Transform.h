#pragma once
#include "Js_Component.h"

namespace Js
{
	class Transform : public Component
	{
	public:
		Transform();

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
		MyRect GetRect() { return m_Rect; }

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

		Vector3 m_Right;
		Vector3 m_Up;
		Vector3 m_Look;

		MyRect m_Rect = {};
	};
}
