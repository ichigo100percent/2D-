#include "Js_GeometryHelper.h"

namespace Js
{
	void GeometryHelper::CreateRectangle(std::shared_ptr<Geometry<VertexTextureData>> _geometry)
	{
		std::vector<VertexTextureData> vertices;

		vertices.resize(4);

		vertices[0].position = Vector3(-1.f, -1.f, 0.f);
		vertices[0].uv = Vector2(0.f, 1.f);
		vertices[1].position = Vector3(-1.f, 1.f, 0.f);
		vertices[1].uv = Vector2(0.f, 0.f);
		vertices[2].position = Vector3(1.f, -1.f, 0.f);
		vertices[2].uv = Vector2(1.f, 1.f);
		vertices[3].position = Vector3(1.f, 1.f, 0.f);
		vertices[3].uv = Vector2(1.f, 0.f);

		_geometry->SetVertices(vertices);

		std::vector<UINT> indices = { 0, 1, 2, 2, 1, 3 };
		_geometry->SetIndices(indices);

	}
	void GeometryHelper::CreateRectangle(std::shared_ptr<Geometry<VertexColorData>> _geometry, Color _color)
	{

	}
}