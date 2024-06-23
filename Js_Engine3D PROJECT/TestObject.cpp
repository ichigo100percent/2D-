#include "TestObject.h"
#include "Js_Time.h"
#include "Js_Input.h"

namespace Js
{
	TestObject::TestObject(ComPtr<ID3D11Device> _device, ComPtr<ID3D11DeviceContext> _context, const std::wstring& _name)
		: DxObject(_device, _context, _name)
	{
	}
}