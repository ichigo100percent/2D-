#include "Js_MoveScripts.h"
#include "Js_Input.h"
#include "Js_Time.h"
#include "Js_DxObject.h"
#include "Js_Transform.h"


namespace Js
{
	void MoveScript::Init()
	{
		GetOwner()->GetOrAddTransform();
		//GetOwner()->GetTransform()->SetScale(Vector3(.3f, .3f, 0));
	}
	void MoveScript::Update()
	{
		float speed = 0.5 * Time::DeltaTime();
		auto position = GetOwner()->GetTransform()->GetPosition();

		if (Input::KeyCheck('W') == KeyState::KEY_HOLD)
		{
			position.y += speed;
		}
		if (Input::KeyCheck('S') == KeyState::KEY_HOLD)
		{
			position.y -= speed;
		}
		if (Input::KeyCheck('A') == KeyState::KEY_HOLD)
		{
			position.x -= speed;
		}
		if (Input::KeyCheck('D') == KeyState::KEY_HOLD)
		{
			position.x += speed;
		}

		GetOwner()->GetTransform()->SetPosition(position);

		std::string pos; 
		pos += "This Position X : " + std::to_string(position.x) + " Y : " + std::to_string(position.y) + '\n';
		OutputDebugStringA(pos.c_str());
	}
}