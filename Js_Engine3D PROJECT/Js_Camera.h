#pragma once
#include "Js_Component.h"

namespace Js
{
	enum class ProjectionType
	{
		Perspective, // ���� ����
		Orthographic, // ���� ����
	};

	class Camera : public Component
	{
	public:
		Camera();
		virtual ~Camera();
 
		virtual void Init() override;
		virtual void Update() override;

		void UpdateMatrix();

		void SetProjectionType(ProjectionType _type) { m_Type = _type; }
		ProjectionType GetProjectionType() { return m_Type; }

		Matrix GetViewMatrix() const;
		Matrix GetProjectionMatrix() const;
		void SetProjectionMatrix(const Matrix& _projectionMatrix);

	private:
		ProjectionType m_Type = ProjectionType::Orthographic;

	public:
		static Matrix m_sViewMatrix;
		static Matrix m_sProjectionMatrix;
	};
}
