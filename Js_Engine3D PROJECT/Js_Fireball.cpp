#include "Js_Fireball.h"
#include "Js_Core.h"
#include "Js_Input.h"
#include "Js_Time.h"
#include "Js_Component.h"
#include "Js_Transform.h"
#include "Js_MonoBehaviour.h"
#include "Js_Camera.h"

namespace Js
{
	Fireball::Fireball(ComPtr<ID3D11Device> _device, ComPtr<ID3D11DeviceContext> _context, const std::wstring& _name)
		: DxObject(_device, _context, _name)
	{
	}
	void Fireball::Init()
	{
		DxObject::Init();
	}
	void Fireball::Update()
	{
		// 화염구를 지속적으로 앞으로 이동
		Vector3 position = GetTransform()->GetPosition();
		float speed = 300.0f * Time::DeltaTime();
		Vector3 forward = GetTransform()->GetForward2D(); // 2D 방향 사용
		position.x += forward.x * speed;
		position.y += forward.y * speed;
		GetTransform()->SetPosition(position);
		DxObject::Update();
	}
}