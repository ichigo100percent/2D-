#pragma once
#include "Js_Geometry.h"
#include "Js_VertexData.h"

namespace Js
{
	class GeometryHelper
	{
	public:
		static void CreateRectangle(std::shared_ptr<Geometry<VertexTextureData>> _geometry);
		static void CreateRectangle(std::shared_ptr<Geometry<VertexColorData>> _geometry, Color _color);
	};
}