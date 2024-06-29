#include "Js_Player.h"
#include "Js_Input.h"
#include "Js_Time.h"
#include "Js_Component.h"
#include "Js_Transform.h"
#include "Js_MonoBehaviour.h"
#include "Js_Camera.h"

namespace Js
{
	Player::Player(ComPtr<ID3D11Device> _device, ComPtr<ID3D11DeviceContext> _context, const std::wstring& _name)
		: DxObject(_device, _context, _name)
	{
	}
	void Player::Update()
	{
		Vector3 currentPosition = GetTransform()->GetPosition();

		// 이동 방향 계산
		if (currentPosition != m_PreviousPosition)
		{
			m_Direction = currentPosition - m_PreviousPosition;
			m_Direction.Normalize();
			m_PreviousPosition = currentPosition;
		}
		DxObject::Update();
	}
}

