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

		//Quaternion rotationDelta = Quaternion::CreateFromYawPitchRoll(speed, speed, speed);  // ���ʹϾ����� ȸ�� ��ȯ ����
	 //   auto currentRotation =  GetOwner()->GetTransform()->GetRotation();  // ���� ȸ�� �� ��������
		//Quaternion newRotation = currentRotation * rotationDelta;  // ���� ȸ���� ȸ�� ��ȯ ����

		//GetOwner()->GetTransform()->SetRotation(newRotation);  // ���ο� ȸ�� �� ����
	}
}