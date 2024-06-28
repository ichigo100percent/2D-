#include "Js_MeshRenderer.h"
#include "Js_Camera.h"
#include "Js_Transform.h"
#include "Js_Core.h"

namespace Js
{
	MeshRenderer::MeshRenderer(ComPtr<ID3D11Device> _device, ComPtr<ID3D11DeviceContext> _context, const std::wstring _name)
		: Component(ComponentType::MeshRenderer, _name)
		, m_Device(_device)
	{
	}
	MeshRenderer::~MeshRenderer()
	{
	}
}