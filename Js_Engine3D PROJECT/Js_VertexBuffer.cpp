#include "Js_VertexBuffer.h"


namespace Js
{
	VertexBuffer::VertexBuffer(ComPtr<ID3D11Device> _device)
		: m_Device(_device)
	{
	}
	VertexBuffer::~VertexBuffer()
	{
	}
}