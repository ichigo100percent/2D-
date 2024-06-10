#pragma once
#include "std.h"

namespace Js
{
	template <typename T>
	class Geometry
	{
	public:
		Geometry() {}
		~Geometry() {}



	private:
		std::vector<T> m_Vertices;
		std::vector<UINT> m_Indices;
	};
}

