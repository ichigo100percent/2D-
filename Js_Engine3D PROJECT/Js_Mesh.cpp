#include "Js_Mesh.h"

namespace Js
{
	Mesh::Mesh(ComPtr<ID3D11Device> _device)
		: BaseResource(ResourceType::Mesh)
		, m_Device(_device)
	{
	}
	Mesh::~Mesh()
	{
	}
	void Mesh::CreateDefaultRectangle()
	{
		m_Geometry = std::make_shared<Geometry<VertexTextureData>>();
		GeometryHelper::CreateRectangle(m_Geometry);

		m_VertexBuffer = std::make_shared<VertexBuffer>(m_Device);
		m_VertexBuffer->Create(m_Geometry->GetVertices());

		m_IndexBuffer = std::make_shared<IndexBuffer>(m_Device);
		m_IndexBuffer->Create(m_Geometry->GetIndices());
	}
}