#pragma once
#include "std.h"
#include "Js_Pipeline.h"
#include "Js_Component.h"
#include "Js_MonoBehaviour.h"
#include "Js_MeshRenderer.h"
#include "Js_Camera.h"
#include "Js_Animator.h"
#include "Js_Collider.h"


namespace Js::object
{
	void Destroy(std::shared_ptr<DxObject> _gameObject);
}

namespace Js
{
	class DxObject : public std::enable_shared_from_this<DxObject>, public Entity
	{
		friend void object::Destroy(std::shared_ptr<DxObject> _gameObject);

	public:
		DxObject(ComPtr<ID3D11Device> _device, ComPtr<ID3D11DeviceContext> _context, const std::wstring& _name = {});
		virtual ~DxObject();

		enum class eState
		{
			Active,
			Paused,
			Dead,
			End,
		};

		virtual void Init();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(std::shared_ptr<Pipeline> _pipeline);
		virtual void Release();

		template <typename T>
		std::shared_ptr<T> GetComponent()
		{
			std::shared_ptr<T> component = nullptr;
			for (auto& comp : m_Components)
			{
				component = std::dynamic_pointer_cast<T>(comp);

				if (component)
					break;
			}
			return component;
		}

		void AddComponent(std::shared_ptr<Component> _component);
		std::shared_ptr<Transform> AddTransform();
		std::shared_ptr<Transform> GetTransform();
		std::shared_ptr<MeshRenderer> GetMeshRenderer();
		std::shared_ptr<Camera> GetCamera();
		std::shared_ptr<Animator> GetAnimator();
		std::shared_ptr<Collider> GetCollider();
		std::vector<std::shared_ptr<MonoBehaviour>>&	GetScripts();
		Vector3 GetSize();

		bool IsActive() { return m_State == eState::Active; }
		void death() { m_State = eState::Dead; }
		bool IsDead() { return m_State == eState::Dead; }
		eState GetState() { return m_State; }
		enums::LayerType GetLayerType() { return m_LayerType; }
		void SetLayerType(enums::LayerType _type) { m_LayerType = _type; }
		Vector3 GetDirection() const { return m_Direction; }
	
	private:
		std::shared_ptr<Component> GetComponent(ComponentType _type);

	protected:
		ComPtr<ID3D11Device> m_Device = nullptr;
		ComPtr<ID3D11DeviceContext> m_Context = nullptr;
		bool m_IsActive;
		eState m_State;
		Vector3 m_PreviousPosition = { 0, 0, 0 };
		Vector3 m_Direction = { 1, 0, 0 }; // 초기 이동 방향은 오른쪽
		enums::LayerType m_LayerType = enums::LayerType::None;

	protected:
		std::array<std::shared_ptr<Component>, FIXED_COMPONENT_COUNT> m_Components;
		std::vector<std::shared_ptr<MonoBehaviour>>					  m_Scripts;
	};
}
