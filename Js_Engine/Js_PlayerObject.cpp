#include "Js_PlayerObject.h"
#include "Js_Input.h"
#include "Js_Time.h"

namespace Js
{
	PlayerObject::PlayerObject(ComPtr<ID3D11Device> _device, ComPtr<ID3D11DeviceContext> _context, const std::wstring& _name)
		: Actor(_device, _context, _name)
	{
	}
	void PlayerObject::CreateGeometry(const RECT& _rect)
	{
		DxObject::CreateGeometry(_rect);

		POINT imgSize = { 1420, 80 };
		RECT  texRt = { 0, 0, 55, 80 };

		m_Vertices[0].texture = { (float)texRt.left / (float)imgSize.x, (float)texRt.bottom / (float)imgSize.y };
		m_Vertices[1].texture = { (float)texRt.left / (float)imgSize.x, (float)texRt.top / (float)imgSize.y };
		m_Vertices[2].texture = { (float)texRt.right / (float)imgSize.x, (float)texRt.bottom / (float)imgSize.y };
		m_Vertices[3].texture = { (float)texRt.right / (float)imgSize.x, (float)texRt.top / (float)imgSize.y };

		//POINT  imgSize = { 400, 300 };
		//RECT	texRt = { 91, 2, 91 + 40, 1 + 59 };
		//m_Vertices[0].texture = { (float)texRt.left / (float)imgSize.x, (float)texRt.bottom / (float)imgSize.y };
		//m_Vertices[1].texture = { (float)texRt.left / (float)imgSize.x, (float)texRt.top / (float)imgSize.y };
		//m_Vertices[2].texture = { (float)texRt.right / (float)imgSize.x, (float)texRt.bottom / (float)imgSize.y };
		//m_Vertices[3].texture = { (float)texRt.right / (float)imgSize.x, (float)texRt.top / (float)imgSize.y };

		m_List = m_Vertices;

		m_LocalPosition.x = (_rect.left + _rect.right) * 0.5f;
		m_LocalPosition.y = (_rect.bottom + _rect.top) * 0.5f;
		m_LocalPosition.z = 0;

		Vector3 Center = -m_LocalPosition;
		SetCenterMove(Center);
		SetTranslate(m_LocalPosition);
		m_Rt = _rect;
	}
	void PlayerObject::Update()
	{
		m_Offset = Vector3::Zero;
		if (Input::KeyCheck('W') == KeyState::KEY_HOLD)
		{
			Move(Vector3(0.f, -1.f, 0));
		}
		if (Input::KeyCheck('S') == KeyState::KEY_HOLD)
		{
			; Move(Vector3(0.f, 1.f, 0));
		}
		if (Input::KeyCheck('A') == KeyState::KEY_HOLD)
		{
			Move(Vector3(-1.f, 0.f, 0));
		}
		if (Input::KeyCheck('D') == KeyState::KEY_HOLD)
		{
			Move(Vector3(1.f, 0.f, 0));
		}

		Actor::Update();
	}
}