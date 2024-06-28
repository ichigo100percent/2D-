#pragma once
#include "Js_DxObject.h"

namespace Js
{
	class Fireball : public DxObject
	{
	public:
        Fireball(ComPtr<ID3D11Device> _device, ComPtr<ID3D11DeviceContext> _context, const std::wstring& _name = {});

        virtual void Init() override;
        virtual void Update() override;

    private:
        float speed = 10.0f; // 파이어볼 속도
	};
}
