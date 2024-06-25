#pragma once
#include "std.h"

namespace Js
{
	class Camera
	{
    public:
		Camera();
		virtual ~Camera();

		void Init();
		void Update();

		void Up();
		void Down();
		void Right(float fValue);
		void Left(float fValue);

		void SetMatrix(const Matrix& _mat) { m_ViewMatrix = _mat; }
		Matrix GetMatrix() { return m_ViewMatrix; }
		void SetPosition(const Vector3& _pos) { m_CameraPosition = _pos; }
		Vector3 GetCameraPos() { return m_CameraPosition; }
			
		static Matrix  m_ViewMatrix;
    private:
		Vector3 m_CameraPosition;
	};
}

