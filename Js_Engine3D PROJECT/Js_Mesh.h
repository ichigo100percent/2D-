#pragma once
#include "Js_Resource.h"
#include "Js_Pipeline.h"

namespace Js
{
	class Mesh : public BaseResource
	{
	public:
		Mesh(ComPtr<ID3D11Device> _device);
		~Mesh();

		void CreateDefaultRectangle();

		std::shared_ptr<VertexBuffer> GetVertexBuffer() { return m_VertexBuffer; }
		std::shared_ptr<IndexBuffer> GetIndexBuffer() { return m_IndexBuffer; }

	private:
		ComPtr<ID3D11Device> m_Device = nullptr;

		std::shared_ptr<Geometry<VertexTextureData>> m_Geometry = nullptr;
		std::shared_ptr<VertexBuffer> m_VertexBuffer = nullptr;
		std::shared_ptr<IndexBuffer>  m_IndexBuffer = nullptr;
	};
}