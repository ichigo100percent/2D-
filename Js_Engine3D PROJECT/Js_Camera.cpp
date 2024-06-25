#include "Js_Camera.h"
#include "Js_DxObject.h"
#include "Js_Transform.h"
#include "Js_Time.h"
#include "Js_Input.h"
namespace Js
{
	Matrix Camera::m_sViewMatrix = Matrix::Identity;
	Matrix Camera::m_sProjectionMatrix = Matrix::Identity;

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
		m_sViewMatrix = XMMatrixLookAtLH(eyePosition, focusPosition, upDirection);
		//m_sViewMatrix = GetTransform()->GetWorldMatrix().Invert();

		//auto pos = GetTransform()->GetPosition();
		//m_sViewMatrix = Matrix::CreateTranslation(pos);
		//m_sProjectionMatrix = XMMatrixOrthographicLH(g_Width, g_Height, 0.f, 1.f);
		m_sProjectionMatrix = XMMatrixOrthographicLH(1280, 720, 0.f, 1.f);
	}
}