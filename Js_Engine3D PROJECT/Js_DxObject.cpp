#include "Js_DxObject.h"
#include "Js_Input.h"
#include "Js_Time.h"
#include "Js_Component.h"
#include "Js_Transform.h"
#include "Js_MonoBehaviour.h"
#include "Js_Camera.h"


namespace Js::object
{
	void Destory(std::shared_ptr<DxObject> _gameObject)
	{
		if (_gameObject != nullptr)
			_gameObject->death();
	}
}

namespace Js
{
	DxObject::DxObject(ComPtr<ID3D11Device> _device, ComPtr<ID3D11DeviceContext> _context, const std::wstring& _name) 
		: Entity(_name),
		  m_Device(_device),
		  m_Context(_context),
		  m_State(eState::Active),
		  m_IsActive(true)
	{
	}
	DxObject::~DxObject()
	{
	}
	void DxObject::Init()
	{
		for (std::shared_ptr<Component>& component : m_Components)
		{
			if (component == nullptr)
				continue;

			component->Init();
		}
		for (std::shared_ptr<MonoBehaviour>& script : m_Scripts)
		{
			if (script == nullptr)
				continue;

			script->Init();
		}

		m_IsActive = true; // 초기화가 끝나면 활성 상태로 설정
		OutputDebugStringA("DxObject initialized.\n");
	}
	void DxObject::Update()
	{
		for (std::shared_ptr<Component>& component : m_Components)
		{
			if (component == nullptr)
				continue;

			component->Update();

		}
		for (std::shared_ptr<MonoBehaviour>& script : m_Scripts)
		{
			if (script == nullptr)
				continue;

			script->Update();
		}
	}
	void DxObject::LateUpdate()
	{
		for (std::shared_ptr<Component>& component : m_Components)
		{
			if (component == nullptr)
				continue;

			component->LateUpdate();
		}
		for (std::shared_ptr<MonoBehaviour>& script : m_Scripts)
		{
			if (script == nullptr)
				continue;

			script->LateUpdate();
		}
	}
	void DxObject::Render(std::shared_ptr<Pipeline> _pipeline)
	{
		for (std::shared_ptr<Component>& component : m_Components)
		{
			if (component == nullptr)
				continue;

			component->Render(_pipeline);
		}
		for (std::shared_ptr<MonoBehaviour>& script : m_Scripts)
		{
			if (script == nullptr)
				continue;

			script->Render(_pipeline);
		}
	}
	void DxObject::Release()
	{
		for (std::shared_ptr<Component>& component : m_Components)
		{
			if (component)
				component->Release();
		}
		for (std::shared_ptr<MonoBehaviour>& script : m_Scripts)
		{
			if (script)
				script->Release();
		}
	}
	std::shared_ptr<Component> DxObject::GetComponent(ComponentType _type)
	{
		UINT index = static_cast<UINT>(_type);
		assert(index < FIXED_COMPONENT_COUNT);

		return m_Components[index];
	}
	void DxObject::AddComponent(std::shared_ptr<Component> _component)
	{
		_component->SetOwner(shared_from_this());
		
		UINT index = static_cast<UINT>(_component->GetType());

		if (index == static_cast<UINT>(ComponentType::Script))
		{
			m_Scripts.push_back(std::dynamic_pointer_cast<MonoBehaviour>(_component));
		}
		else if(index <= FIXED_COMPONENT_COUNT)
		{
			m_Components[index] = _component;
		}
	}
	std::shared_ptr<Transform> DxObject::GetTransform()
	{
		std::shared_ptr<Component> component = GetComponent(ComponentType::Transform);
		return std::dynamic_pointer_cast<Transform>(component);
	}
	std::shared_ptr<MeshRenderer> DxObject::GetMeshRenderer()
	{
		std::shared_ptr<Component> component = GetComponent(ComponentType::MeshRenderer);
		return std::dynamic_pointer_cast<MeshRenderer>(component);
	}
	std::shared_ptr<Camera> DxObject::GetCamera()
	{
		std::shared_ptr<Component> component = GetComponent(ComponentType::Camera);
		return std::dynamic_pointer_cast<Camera>(component);
	}
	std::shared_ptr<Animator> DxObject::GetAnimator()
	{
		std::shared_ptr<Component> component = GetComponent(ComponentType::Animator);
		return std::dynamic_pointer_cast<Animator>(component);
	}
	std::shared_ptr<Collider> DxObject::GetCollider()
	{
		std::shared_ptr<Component> component = GetComponent(ComponentType::Collider);
		return std::dynamic_pointer_cast<Collider>(component);
	}
	std::vector<std::shared_ptr<MonoBehaviour>>& DxObject::GetScripts()
	{
		return m_Scripts;
	}
	std::shared_ptr<Transform> DxObject::AddTransform()
	{
		if (GetTransform() == nullptr)
		{
			std::shared_ptr<Transform> transform = std::make_shared<Transform>();
			AddComponent(transform);
		}
		return GetTransform();
	}
	Vector3 DxObject::GetSize()
	{		
		UINT index = static_cast<UINT>(ComponentType::MeshRenderer);
		if (m_Components[index])
		{
			auto size = GetMeshRenderer()->GetTexture()->GetSize();
			return Vector3(size.x, size.y, 0);
		}
		return Vector3::Zero;
	}
}
