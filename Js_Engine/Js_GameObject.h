#pragma once
#include "Js_DxObject.h"

namespace Js
{
	class GameObject : public DxObject
	{
	public:
		GameObject(ComPtr<ID3D11Device> _device, ComPtr<ID3D11DeviceContext> _context, const std::wstring& _name = {});

		virtual void CreateObject(const Vector2& _pos, const std::wstring& _texName) override;

	private:

	};
}
