#include "Js_FireBulletsScript.h"
#include "Js_SimpleBulletScript.h"
#include "Js_Input.h"
#include "Js_Time.h"
#include "Js_DxObject.h"
#include "Js_Transform.h"
#include "Js_MeshRenderer.h"
#include "Js_Object.h"
#include "Js_Collider.h"

namespace Js
{
	void FireBulletsScript::Init()
	{
		angle = 90.0f;
		cnt = 11;
	}
	void FireBulletsScript::Update()
	{
        if (Input::KeyCheck(VK_SPACE) == KeyState::KEY_HOLD)
        {
            float gap = 6.0f; // 각 총알 간의 각도 차이
            float startAngle = angle - ((cnt - 1) * gap) / 2; // 첫 번째 총알의 각도
            Vector3 playerPos = GetOwner()->GetTransform()->GetPosition(); // 주인공의 위치

            for (int i = 0; i < cnt; ++i)
            {
                std::shared_ptr<DxObject> bullet = object::Instantiate<DxObject>();
                {
                    auto meshRender = std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext());
                    bullet->AddComponent(meshRender);
                    auto mesh = I_Resource->Get<Mesh>(L"Rectangle");
                    meshRender->SetMesh(mesh);
                    auto material = I_Resource->Get<Material>(L"Default");
                    meshRender->SetMaterial(material);
                    bullet->GetTransform()->SetScale(Vector3(10, 10, 0));
                    bullet->GetTransform()->SetPosition(playerPos); // 총알의 초기 위치를 주인공의 위치로 설정

                    auto bulletScript = std::make_shared<SimpleBulletScript>();
                    bullet->AddComponent(bulletScript);

                    // 발사 방향 설정
                    float currentAngle = startAngle + i * gap;
                    float radian = XMConvertToRadians(currentAngle); // 각도를 라디안으로 변환
                    Vector3 direction = Vector3(std::cos(radian), std::sin(radian), 0.0f);
                    bulletScript->SetNormalizedDirection(direction);
                }
            }
        }
	}
	void FireBulletsScript::OnCollisionEnter(std::shared_ptr<Collider> _other)
	{
	}
	void FireBulletsScript::OnCollisionStay(std::shared_ptr<Collider> _other)
	{
	}
	void FireBulletsScript::OnCollisionExit(std::shared_ptr<Collider> _other)
	{
	}
}