#include "Js_Camera.h"
#include "Js_Time.h"
namespace Js
{
	Matrix Camera::m_ViewMatrix = Matrix::Identity;

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
		Vector2 vCamDirection = { 0.0f, 1.0f };
		m_CameraPosition = m_CameraPosition + vCamDirection * 100.0f * Time::DeltaTime();
	}
	void Camera::Down()
	{
		Vector2 vCamDirection = { 0.0f, -1.0f };
		m_CameraPosition = m_CameraPosition + vCamDirection * 100.0f * Time::DeltaTime();
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