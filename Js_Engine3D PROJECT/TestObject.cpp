#include "TestObject.h"
#include "Js_Time.h"
#include "Js_Input.h"

namespace Js
{
	TestObject::TestObject(ComPtr<ID3D11Device> _device, ComPtr<ID3D11DeviceContext> _context, const std::wstring& _name)
		: DxObject(_device, _context, _name)
	{
	}
	//void TestObject::Update()
	//{
	//	//Matrix matScale = Matrix::CreateScale(m_LocalScale);
	//	//Matrix matRotation = Matrix::CreateRotationX(m_LocalRotation.x);
	//	//matRotation *= Matrix::CreateRotationY(m_LocalRotation.y);
	//	//matRotation *= Matrix::CreateRotationZ(m_LocalRotation.z);
	//	//Matrix matTranslation = Matrix::CreateTranslation(m_LocalPosition);

	//	//Matrix matWorld = matScale * matRotation * matTranslation; // SRT
	//	//m_TransformData.matWorld = matWorld;

	//	//// AABB 업데이트
	//	//m_Rt.left = m_LocalPosition.x - m_LocalScale.x;
	//	//m_Rt.right = m_LocalPosition.x + m_LocalScale.x;
	//	//m_Rt.top = m_LocalPosition.y + m_LocalScale.y;
	//	//m_Rt.bottom = m_LocalPosition.y - m_LocalScale.y;

	//	//m_ConstantBuffer->CopyData(m_TransformData);
	//}
}