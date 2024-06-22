#include "TestObject.h"
#include "Js_Time.h"

namespace Js
{
	TestObject::TestObject(ComPtr<ID3D11Device> _device, ComPtr<ID3D11DeviceContext> _context, const std::wstring& _name)
		: DxObject(_device, _context, _name)
	{
	}
	void TestObject::Update()
	{
		Matrix matScale = Matrix::CreateScale(m_LocalScale);
		Matrix matRotation = Matrix::CreateRotationX(m_LocalRotation.x);
		matRotation *= Matrix::CreateRotationY(m_LocalRotation.y);
		matRotation *= Matrix::CreateRotationZ(m_LocalRotation.z);
		Matrix matTranslation = Matrix::CreateTranslation(m_LocalPosition);

		Matrix matWorld = matScale * matRotation * matTranslation; // SRT
		m_TransformData.matWorld = matWorld;

		D3D11_MAPPED_SUBRESOURCE subResource;
		ZeroMemory(&subResource, sizeof(subResource));

		m_Context->Map(m_ConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
		::memcpy(subResource.pData, &m_TransformData, sizeof(m_TransformData));
		m_Context->Unmap(m_ConstantBuffer.Get(), 0);

		// Update AABB
		m_AABB.left = m_LocalPosition.x - 0.5f * m_LocalScale.x;
		m_AABB.right = m_LocalPosition.x + 0.5f * m_LocalScale.x;
		m_AABB.top = m_LocalPosition.y + 0.5f * m_LocalScale.y;
		m_AABB.bottom = m_LocalPosition.y - 0.5f * m_LocalScale.y;

	}
}