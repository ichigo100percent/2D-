#include "Js_Camera.h"

namespace Js
{
	Camera::Camera()
	{
	}
	Camera::~Camera()
	{
	}
	void Camera::Init()
	{
	}
	void Camera::Update()
	{
		m_ViewMatrix = Matrix::CreateTranslation(m_CameraPosition);
;	}
	void Camera::Up()
	{
	}
	void Camera::Down()
	{
	}
	void Camera::Right(float fValue)
	{
		m_CameraPosition.x += fValue;
	}
	void Camera::Left(float fValue)
	{
		m_CameraPosition.x -= fValue;
	}
}