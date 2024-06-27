#include "Fireball.h"
#include "Js_Core.h"
#include "Js_Input.h"
#include "Js_Time.h"
#include "Js_Component.h"
#include "Js_Transform.h"
#include "Js_MonoBehaviour.h"
#include "Js_Camera.h"

namespace Js
{
	Fireball::Fireball(ComPtr<ID3D11Device> _device, ComPtr<ID3D11DeviceContext> _context, const std::wstring& _name)
		: DxObject(_device, _context, _name)
	{
	}
	void Fireball::Init()
	{
		DxObject::Init();
	}
	void Fireball::Update()
	{
		DxObject::Update();
	}
}