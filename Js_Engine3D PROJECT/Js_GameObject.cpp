#include "Js_GameObject.h"

namespace Js
{
	GameObject::GameObject(ComPtr<ID3D11Device> _device, ComPtr<ID3D11DeviceContext> _context, const std::wstring& _name)
		: DxObject(_device, _context, _name)
	{

	}
		
}