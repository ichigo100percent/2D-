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
            // ��� ��ü�� ��ġ�� �����ͼ� ī�޶��� ��ġ�� ������Ʈ
            Vector3 targetPosition = m_Target->GetTransform()->GetPosition();
            Vector3 cameraPosition = targetPosition + Vector3(0, 0, -10);
            GetTransform()->SetPosition(cameraPosition);

            // ī�޶� ��� ��ü�� �ٶ󺸵��� ������Ʈ
            //GetTransform()->SetRotation(Vector3(targetPosition - cameraPosition, 0, 0).Normalize());
        }
	}
}