#include "Js_Transform.h"

namespace Js
{
	Vector3 ToEulerAngles(Quaternion q)
	{
		Vector3 angles;

		// roll (x-axis rotation)
		double sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
		double cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
		angles.x = std::atan2(sinr_cosp, cosr_cosp);

		// pitch (y-axis rotation)
		double sinp = std::sqrt(1 + 2 * (q.w * q.y - q.x * q.z));
		double cosp = std::sqrt(1 - 2 * (q.w * q.y - q.x * q.z));
		angles.y = 2 * std::atan2(sinp, cosp) - 3.14159f / 2;

		// yaw (z-axis rotation)
		double siny_cosp = 2 * (q.w * q.z + q.x * q.y);
		double cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
		angles.z = std::atan2(siny_cosp, cosy_cosp);

		return angles;
	}


	Transform::Transform()
	{
	}
	void Transform::Init()
	{
	}
	void Transform::Update()
	{
	}
	void Transform::UpdateTransform()
	{
		Matrix matScale = Matrix::CreateScale(m_LocalScale);
		Matrix matRotation = Matrix::CreateRotationX(m_LocalRotation.x);
		matRotation *= Matrix::CreateRotationY(m_LocalRotation.y);
		matRotation *= Matrix::CreateRotationZ(m_LocalRotation.z);
		Matrix matTranslation = Matrix::CreateTranslation(m_LocalPosition);

		m_LocalMatrix = matScale * matRotation * matTranslation;
		m_WorldMatrix = m_LocalMatrix;

		Quaternion quat;
		m_WorldMatrix.Decompose(m_Scale, quat, m_Position);
		m_Rotation = ToEulerAngles(quat);

		m_Right = Vector3::TransformNormal(Vector3::Right, m_WorldMatrix);
		m_Up = Vector3::TransformNormal(Vector3::Up, m_WorldMatrix);
		m_Look = Vector3::TransformNormal(Vector3::Backward, m_WorldMatrix);

		//// AABB 업데이트
		//m_Rt.left = m_LocalPosition.x - m_LocalScale.x;
		//m_Rt.right = m_LocalPosition.x + m_LocalScale.x;
		//m_Rt.top = m_LocalPosition.y + m_LocalScale.y;
		//m_Rt.bottom = m_LocalPosition.y - m_LocalScale.y;
	}
	void Transform::SetScale(const Vector3& _worldScale)
	{
		SetLocalScale(_worldScale);
	}
	void Transform::SetRotation(const Vector3& _worldRotation)
	{
		SetLocalRotation(_worldRotation);
	}
	void Transform::SetPosition(const Vector3& _worldPosition)
	{
		SetLocalPosition(_worldPosition);
	}
}