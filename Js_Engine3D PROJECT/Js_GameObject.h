#pragma once
#include "Js_DxObject.h"

namespace Js
{
	class GameObject : public DxObject
	{
	public:
		GameObject(ComPtr<ID3D11Device> _device, ComPtr<ID3D11DeviceContext> _context, const std::wstring& _name = {});

		void SetPosition(const Vector3& _pos) { m_LocalPosition = _pos; }
		Vector3 GetPosition() { return m_LocalPosition; }

	protected:
	};
}
