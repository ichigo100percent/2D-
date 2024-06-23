#pragma once
#include "std.h"

namespace Js
{
	template<typename T>
	class Geometry
	{
	public:
		Geometry() {}
		~Geometry() {}

		UINT GetVertexCount() { return static_cast<UINT>(m_Vertices.size()); }
		void* GetVertexData() { return m_Vertices.data(); }
		const std::vector<T>& GetVertices() { return m_Vertices; }

		UINT GetIndexCount() { return static_cast<UINT>(m_Indices.size()); }
		void* GetIndexData() { return m_Indices.data(); }
		const std::vector<UINT>& GetIndices() { return m_Indices; }

		void AddVertex(const T& _vertex) { m_Vertices.push_back(_vertex); }
		void AddVertices(const std::vector<T>& _vertices) { m_Vertices.insert(m_Vertices.end(), _vertices.begin(), _vertices.end()); }
		void SetVertices(const std::vector<T>& _vertices) { m_Vertices = _vertices; }

		void AddIndex(UINT index) { m_Indices.push_back(index); }
		void AddIndices(const std::vector<UINT>& _indices) { m_Indices.insert(m_Indices.end(), _indices.begin(), _indices.end()); }
		void SetIndices(const std::vector<UINT>& _indices) { m_Indices = _indices; }

	private:
		std::vector<T> m_Vertices;
		std::vector<UINT> m_Indices;
	};
}