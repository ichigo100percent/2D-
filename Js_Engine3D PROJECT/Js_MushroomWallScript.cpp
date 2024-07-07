#include "Js_MushroomWallScript.h"
#include "Js_PlayerScript.h"

#include "Js_Input.h"
#include "Js_Time.h"
#include "Js_DxObject.h"
#include "Js_Transform.h"
#include "Js_MeshRenderer.h"
#include "Js_Object.h"
#include "Js_Rigidbody.h"
#include "Js_Animation.h"
#include "Js_SceneManager.h"

#include "Js_PlayerScript.h"
#include "Js_TitleScene.h"
#include "Js_MushroomScript.h"

#include "Js_PlayScene.h"

namespace Js
{
	void MushroomWalllScript::Init()
	{
	}
	void MushroomWalllScript::Update()
	{
	}
	void MushroomWalllScript::OnCollisionEnter(std::shared_ptr<Collider> _other)
	{
		auto other = _other->GetOwner();
		auto scripts = other->GetScripts();
		auto pos = GetOwner()->GetTransform()->GetPosition();

		if (other->GetLayerType() == enums::LayerType::Player)
		{
			for (auto& script : scripts)
			{
				auto mario = std::dynamic_pointer_cast<PlayerScript>(script);
				if (mario)
				{
					if (mario->GetMarioType() == MarioType::Nomal && mario->GetMarioState() == State::Jump && m_Count == 0)
					{
						auto transform = GetOwner()->GetTransform();
					
						// 버섯 생성 및 위치 초기화
						std::shared_ptr<DxObject> mushroom = object::Instantiate<DxObject>(L"Mushroom", enums::LayerType::MunshRoom);
						{
							auto meshRender = std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext());
							mushroom->AddComponent(meshRender);
							auto mesh = I_Resource->Get<Mesh>(L"Rectangle");
							meshRender->SetMesh(mesh);
							auto material = I_Resource->Get<Material>(L"버섯");
							meshRender->SetMaterial(material);
							mushroom->AddTransform();
							mushroom->GetTransform()->SetScale(mushroom->GetSize());
							mushroom->GetTransform()->SetPosition(Vector3(pos.x, pos.y + 33.f, 0));
							auto col = std::make_shared<Collider>();
							mushroom->AddComponent(col);
							mushroom->AddComponent(std::make_shared<MushroomScript>());
						}
						m_Count++;
					}
				}
			}
		}
		
	}
	void MushroomWalllScript::OnCollisionStay(std::shared_ptr<Collider> _other)
	{
	}
	void MushroomWalllScript::OnCollisionExit(std::shared_ptr<Collider> _other)
	{
	}
}