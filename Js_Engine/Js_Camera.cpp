#include "Js_Camera.h"
#include "Js_Time.h"
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
	void Camera::move(Vector3 _offset)
	{
		m_CameraPosition += -_offset;
	}
	void Camera::SetTransform(Vector3 _pos)
	{
		m_ViewMatrix.CreateTranslation(_pos);
	}
}