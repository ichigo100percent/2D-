#include "Js_Actor.h"
#include "Js_Input.h"
#include "Js_Time.h"

namespace Js
{
	Actor::Actor(ComPtr<ID3D11Device> _device, ComPtr<ID3D11DeviceContext> _context, const std::wstring& _name)
		: DxObject(_device, _context, _name)
	{
	}
	void Actor::Update()
	{
		float speed = 100 * Time::DeltaTime();
		if (Input::KeyCheck('W') == KeyState::KEY_HOLD)
		{
			Move(0, -speed);
		}
		if (Input::KeyCheck('S') == KeyState::KEY_HOLD)
		{
			Move(0, speed);
		}
		if (Input::KeyCheck('A') == KeyState::KEY_HOLD)
		{
			Move(-speed, 0);
		}
		if (Input::KeyCheck('D') == KeyState::KEY_HOLD)
		{
			Move(speed, 0);
		}

		std::string pos;
		pos += "X = " + std::to_string((int)m_Position.x) + " Y = " + std::to_string((int)m_Position.y) + "\n";
		OutputDebugStringA(pos.c_str());
	}
	void Actor::Render()
	{
		DxObject::Render();
	}
	Actor& Actor::Move(float _dx, float _dy)
	{
		for (auto& pos : m_Vertices)
		{
			pos.position += { _dx, _dy };
		}
		m_Position += { _dx, _dy };

		std::transform(std::begin(m_Vertices), std::end(m_Vertices), std::begin(m_NdcVertices),
			[&](VertexData& _data)
			{
				return VertexData(ConvertScreenToNDC(_data.position), _data.color, _data.texture);
			});

		m_Context->UpdateSubresource(m_VertexBuffer.Get(), 0, NULL, m_NdcVertices.data(), 0, 0);

		return *this;
	}
	void Actor::CreateObject(const Vector2& _pos, const std::wstring& _texName)
	{
		m_Position = _pos;
		m_Rt = { (_pos.x - (100 * .5f)), (_pos.y - (100 * .5f)), 100, 100 };

		CreateGeometry(m_Rt);
		CreateVertexBuffer();
		CreateIndexBuffer();
		CreateVS();
		CreateInputLayout();
		CreatePS();

		CreateRasterizerState();
		CreateSRV(_texName);
	}
}