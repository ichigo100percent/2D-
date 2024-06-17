#pragma once
#include "Js_Actor.h"

namespace Js
{
	class PlayerObject : public Actor
	{
	public:
		PlayerObject(ComPtr<ID3D11Device> _device, ComPtr<ID3D11DeviceContext> _context, const std::wstring& _name = {});

		virtual void CreateGeometry(const RECT& _rect) override;

	private:

	};
}
