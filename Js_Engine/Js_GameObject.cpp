#include "Js_GameObject.h"

namespace Js
{
	GameObject::GameObject(ComPtr<ID3D11Device> _device,
								 ComPtr<ID3D11DeviceContext> _context,
								 const std::wstring& _name)
		: DxObject(_device, _context, _name)
	{
	}
	void GameObject::CreateObject(const Vector2& _pos, const std::wstring& _texName)
	{
		m_Position = _pos;
		JsRect rt = { 0, 0, g_Width, g_Height };

		CreateGeometry(rt);
		CreateVertexBuffer();
		CreateIndexBuffer();
		CreateVS();
		CreateInputLayout();
		CreatePS();

		CreateRasterizerState();
		CreateSRV(_texName);
	}
}