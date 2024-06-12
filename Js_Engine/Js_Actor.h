#pragma once
#include "Js_DxObject.h"

namespace Js
{
	class Actor : public DxObject
	{
	public:
		Actor(ComPtr<ID3D11Device> _device, ComPtr<ID3D11DeviceContext> _context, const std::wstring& _name = {});

		virtual void Update() override;
		virtual void Render() override;

		virtual Actor& Move(float _dx, float _dy);
		virtual void CreateObject(const Vector2& _pos, const std::wstring& _texName);

	protected:
		Vector2						 m_Position{};
		JsRect						 m_Rt;
	};
}
