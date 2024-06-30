#include "Js_PlayerScript.h"
#include "Js_Input.h"
#include "Js_Time.h"
#include "Js_DxObject.h"
#include "Js_Transform.h"
#include "Js_MeshRenderer.h"
#include "Js_Object.h"
#include "Js_Rigidbody.h"

namespace Js
{

	void PlayerScript::Init()
	{
	}
	void PlayerScript::Update()
	{
		auto rb = GetOwner()->GetComponent<Rigidbody>();
		rb->SetGrounded(true);

		if (Input::KeyCheck('A') == KeyState::KEY_HOLD)
		{
			rb->AddForce(Vector3(-1000, 0, 0));
		}
		if (Input::KeyCheck('D') == KeyState::KEY_HOLD)
		{
			rb->AddForce(Vector3(1000, 0, 0));
		}
	}
}