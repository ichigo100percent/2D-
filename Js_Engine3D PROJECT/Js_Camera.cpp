#include "Js_Camera.h"
#include "Js_DxObject.h"
#include "Js_Transform.h"
#include "Js_Time.h"
#include "Js_Input.h"
namespace Js
{
	Matrix Camera::s_ViewMatrix = Matrix::Identity;
	Matrix Camera::s_ProjectionMatrix = Matrix::Identity;

	Camera::Camera()
		: Component(ComponentType::Camera)
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
		UpdateMatrix();
	}
	void Camera::UpdateMatrix()
	{
		Vector3 eyePosition = GetTransform()->GetPosition();
		Vector3 focusPosition = eyePosition + GetTransform()->GetLook();
		Vector3 upDirection = GetTransform()->GetUp();
		s_ViewMatrix = XMMatrixLookAtLH(eyePosition, focusPosition, upDirection);
		//m_sViewMatrix = GetTransform()->GetWorldMatrix().Invert();

		if (m_Type == ProjectionType::Orthographic)
		{
			s_ProjectionMatrix = XMMatrixOrthographicLH(800, 480, 0.f, 1.f);
		}
		else
			s_ProjectionMatrix = XMMatrixPerspectiveFovLH(XM_PI / 4.f, 800.f / 600.f, 1.f, 100.f);
	}
}