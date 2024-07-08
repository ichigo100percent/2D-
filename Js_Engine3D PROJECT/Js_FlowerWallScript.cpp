#include "Js_FlowerWallScript.h"
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
	void FlowerWallScript::Init()
	{
	}
	void FlowerWallScript::Update()
	{
	}
	void FlowerWallScript::OnCollisionEnter(std::shared_ptr<Collider> _other)
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
					if (mario->GetMarioState() == State::Jump && m_Count == 0)
					{
						auto transform = GetOwner()->GetTransform();
						auto pos = transform->GetPosition();

						std::shared_ptr<DxObject> Flower = object::Instantiate<DxObject>(L"Monster", enums::LayerType::Flower);
						{
							auto meshRender = std::make_shared<MeshRenderer>(I_Core.GetDevice(), I_Core.GetContext());
							Flower->AddComponent(meshRender);
							auto mesh = I_Resource->Get<Mesh>(L"Rectangle");
							meshRender->SetMesh(mesh);
							auto material = I_Resource->Get<Material>(L"²É");
							meshRender->SetMaterial(material);
							Flower->GetTransform()->SetScale(Flower->GetSize());
							Flower->GetTransform()->SetPosition(Vector3(pos.x, pos.y + 32, pos.z));
							auto col = std::make_shared<Collider>();
							Flower->AddComponent(col);
						}
						m_Count++;

						auto mesh = GetOwner()->GetMeshRenderer();
						auto material = I_Resource->Get<Material>(L"Block2");
						mesh->SetMaterial(material);
					}
				}
			}
		}
	}
	void FlowerWallScript::OnCollisionStay(std::shared_ptr<Collider> _other)
	{
	}
	void FlowerWallScript::OnCollisionExit(std::shared_ptr<Collider> _other)
	{
	}
}