#pragma once
#include "Js_DxObject.h"

namespace Js
{
	class TestObject : public DxObject
	{
	public:
		TestObject(ComPtr<ID3D11Device> _device, ComPtr<ID3D11DeviceContext> _context, const std::wstring& _name = {});

		void Update() override;


	};
}
