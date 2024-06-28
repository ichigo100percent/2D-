#pragma once
#include "Js_DxObject.h"


namespace Js
{
	class Player : public DxObject
	{
	public:
		Player(ComPtr<ID3D11Device> _device, ComPtr<ID3D11DeviceContext> _context, const std::wstring& _name = {});

		void Update() override;
	};
}