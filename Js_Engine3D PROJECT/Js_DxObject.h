#pragma once
#include "std.h"
#include "Js_Pipeline.h"
#include "Js_Component.h"
#include "Js_MonoBehaviour.h"
#include "Js_MeshRenderer.h"
#include "Js_Camera.h"



namespace Js::object
{
	void Destory(std::shared_ptr<DxObject> _gameObject);
}

namespace Js
{
	class DxObject : public std::enable_shared_from_this<DxObject>, public Entity
	{
		friend void object::Destory(std::shared_ptr<DxObject> _gameObject);

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

		std::shared_ptr<Component> GetComponent(ComponentType _type);
		void AddComponent(std::shared_ptr<Component> _component);
		std::shared_ptr<Transform> GetOrAddTransform();
		std::shared_ptr<Transform> GetTransform();
		std::shared_ptr<MeshRenderer> GetMeshRenderer();
		std::shared_ptr<Camera> GetCamera();
		std::shared_ptr<MonoBehaviour> GetScript();
		Vector3 GetSize();

		bool IsActive() { return m_IsActive; }
		void death() { m_State = eState::Dead; }
		bool IsDead() { return m_State == eState::Dead; }
		eState GetState() { return m_State; }

	protected:
		ComPtr<ID3D11Device> m_Device = nullptr;
		ComPtr<ID3D11DeviceContext> m_Context = nullptr;
		bool m_IsActive;
		eState m_State;

	protected:
		std::array<std::shared_ptr<Component>, FIXED_COMPONENT_COUNT> m_Components;
		std::vector<std::shared_ptr<MonoBehaviour>>					  m_Scripts;
	};
}
