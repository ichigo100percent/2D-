#include "Js_RotateScript.h"
#include "Js_Input.h"
#include "Js_Time.h"
#include "Js_DxObject.h"
#include "Js_Transform.h"

namespace Js
{
	void RotateScript::Init()
	{
		GetOwner()->AddTransform();
	}
	void RotateScript::Update()
	{
		float speed = 50 * Time::DeltaTime();

		//Quaternion rotationDelta = Quaternion::CreateFromYawPitchRoll(speed, speed, speed);  // 쿼터니언으로 회전 변환 생성
	 //   auto currentRotation =  GetOwner()->GetTransform()->GetRotation();  // 현재 회전 값 가져오기
		//Quaternion newRotation = currentRotation * rotationDelta;  // 현재 회전에 회전 변환 적용

		//GetOwner()->GetTransform()->SetRotation(newRotation);  // 새로운 회전 값 설정
	}
}