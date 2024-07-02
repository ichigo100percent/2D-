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
            // ��� ��ü�� ��ġ�� ������
            Vector3 targetPosition = m_Target->GetTransform()->GetPosition();

            // ī�޶��� X ��ġ�� ��� ��ü�� X ��ġ�� ���� ����
            // ���۸����� ��Ÿ��: �÷��̾ ȭ�� �߾Ӻ��� ���������� ���� ī�޶� �̵�
            float cameraX = targetPosition.x;

            // ���� ���� ��谪
            float mapLeftBoundary = -2800.0f;

            // ī�޶� ���� ���� ��踦 ���� �ʵ��� ��
            if (cameraX < mapLeftBoundary + 320.0f) // 320�� ī�޶��� ���� �ʺ� ����
            {
                cameraX = mapLeftBoundary + 320.0f;
            }

            // ī�޶��� Y �� Z ��ġ�� ����
            float cameraY = -260.0f; // ������ Y �� ����
            float cameraZ = -10.0f; // ������ Z �� ����

            // ī�޶��� ��ġ�� ������Ʈ
            Vector3 cameraPosition = Vector3(cameraX, cameraY, cameraZ);
            GetTransform()->SetPosition(cameraPosition);

            // ī�޶� ��� ��ü�� �ٶ󺸵��� ������Ʈ (�ʿ��)
            //GetTransform()->SetRotation(Vector3(targetPosition - cameraPosition, 0, 0).Normalize());
        }
	}
}