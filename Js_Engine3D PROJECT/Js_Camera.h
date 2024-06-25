#pragma once
#include "Js_Component.h"

namespace Js
{
	enum class ProjectionType
	{
		Perspective,  // 원근 투영
		Orthographic, // 직교 투영
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

	private:
		ProjectionType m_Type = ProjectionType::Orthographic;

	public:
		static Matrix s_ViewMatrix;
		static Matrix s_ProjectionMatrix;
	};
}
