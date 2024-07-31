#include "Js_FollowTargetScript.h"
#include "Js_Input.h"
#include "Js_Time.h"
#include "Js_DxObject.h"
#include "Js_Transform.h"


namespace Js
{
	void FollowTargetScript::LateUpdate()
	{
        if (m_Target)
        {
            // 대상 객체의 위치를 가져와서 카메라의 위치를 업데이트
            Vector3 targetPosition = m_Target->GetTransform()->GetPosition();
            Vector3 cameraPosition = targetPosition + Vector3(0, 0, -10);
            GetTransform()->SetPosition(cameraPosition);

            // 카메라가 대상 객체를 바라보도록 업데이트
            //GetTransform()->SetRotation(Vector3(targetPosition - cameraPosition, 0, 0).Normalize());
        }
	}
}