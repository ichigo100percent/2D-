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
		m_sViewMatrix = GetTransform()->GetWorldMatrix().Invert();
	}

	Matrix Camera::GetViewMatrix() const
	{
		return m_sViewMatrix;
	}

	Matrix Camera::GetProjectionMatrix() const
	{
		return m_sProjectionMatrix;
	}

	void Camera::SetProjectionMatrix(const Matrix& _projectionMatrix)
	{
		m_sProjectionMatrix = _projectionMatrix;
	}
}
		//m_sProjectionMatrix = XMMatrixOrthographicLH(g_Width, g_Height, 0.f, 1.f);
		//m_sProjectionMatrix = XMMatrixOrthographicLH(8, 6, 0.f, 1.f);