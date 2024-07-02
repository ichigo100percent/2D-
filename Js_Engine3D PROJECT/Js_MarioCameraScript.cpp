#include "Js_MarioCameraScript.h"
#include "Js_Input.h"
#include "Js_Time.h"
#include "Js_DxObject.h"
#include "Js_Transform.h"
namespace Js
{
	void MarioCameraScript::LateUpdate()
	{
        if (m_Target)
        {
            // 대상 객체의 위치를 가져옴
            Vector3 targetPosition = m_Target->GetTransform()->GetPosition();

            // 카메라의 X 위치를 대상 객체의 X 위치에 따라 조정
            // 슈퍼마리오 스타일: 플레이어가 화면 중앙보다 오른쪽으로 가면 카메라 이동
            float cameraX = targetPosition.x;

            // 맵의 왼쪽 경계값
            float mapLeftBoundary = -2800.0f;

            // 카메라가 맵의 왼쪽 경계를 넘지 않도록 함
            if (cameraX < mapLeftBoundary + 320.0f) // 320은 카메라의 절반 너비 가정
            {
                cameraX = mapLeftBoundary + 320.0f;
            }

            // 카메라의 Y 및 Z 위치는 고정
            float cameraY = -260.0f; // 적절한 Y 값 설정
            float cameraZ = -10.0f; // 적절한 Z 값 설정

            // 카메라의 위치를 업데이트
            Vector3 cameraPosition = Vector3(cameraX, cameraY, cameraZ);
            GetTransform()->SetPosition(cameraPosition);

            // 카메라가 대상 객체를 바라보도록 업데이트 (필요시)
            //GetTransform()->SetRotation(Vector3(targetPosition - cameraPosition, 0, 0).Normalize());
        }
	}
}