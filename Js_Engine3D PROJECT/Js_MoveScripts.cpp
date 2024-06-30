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

	}
	void MoveScript::Update()
	{
        float speed = 500 * Time::DeltaTime();
        auto position = GetOwner()->GetTransform()->GetPosition();
        Vector3 direction(0, 0, 0);

        if (Input::KeyCheck('W') == KeyState::KEY_HOLD)
        {
            direction.y += 1;
        }
        if (Input::KeyCheck('S') == KeyState::KEY_HOLD)
        {
            direction.y -= 1;
        }
        if (Input::KeyCheck('A') == KeyState::KEY_HOLD)
        {
            direction.x -= 1;
        }
        if (Input::KeyCheck('D') == KeyState::KEY_HOLD)
        {
            direction.x += 1;
        }

        if (direction.Length() > 0)
        {
            direction.Normalize();
        }

        position += direction * speed;
        GetOwner()->GetTransform()->SetPosition(position);

        std::string pos;
        pos += "This Position X : " + std::to_string(position.x) + " Y : " + std::to_string(position.y) + '\n';
        OutputDebugStringA(pos.c_str());
	}
}