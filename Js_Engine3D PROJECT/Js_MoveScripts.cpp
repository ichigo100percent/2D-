#include "Js_MoveScripts.h"
#include "Js_Input.h"
#include "Js_Time.h"
#include "Js_DxObject.h"
#include "Js_Transform.h"
#include "Js_MeshRenderer.h"
#include "Js_Object.h"

#include "Js_FireballScript.h"

namespace Js
{
	void MoveScript::Init()
	{
		GetOwner()->GetOrAddTransform();
	}
	void MoveScript::Update()
	{
		float speed = 100 * Time::DeltaTime();
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
		if (Input::KeyCheck(VK_SPACE) == KeyState::KEY_PUSH)
		{
			shoot();
		}
		GetOwner()->GetTransform()->SetPosition(position);
		std::string pos; 
		pos += "This Position X : " + std::to_string(position.x) + " Y : " + std::to_string(position.y) + '\n';
		OutputDebugStringA(pos.c_str());
	}
	void MoveScript::shoot()
	{
		std::shared_ptr<DxObject> fireball = object::Instantiate<DxObject>();
		{
			fireball->GetOrAddTransform();
			fireball->AddComponent(std::make_shared<FireballScript>());
			fireball->AddComponent(std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext(), L"1.bmp"));
			fireball->GetOrAddTransform()->SetScale(fireball->GetSize());
			fireball->Init();
		}
	}
}