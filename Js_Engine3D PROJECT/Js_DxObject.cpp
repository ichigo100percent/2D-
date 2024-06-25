#include "Js_DxObject.h"
#include "Js_Input.h"
#include "Js_Time.h"
#include "Js_Component.h"
#include "Js_Transform.h"
#include "Js_MonoBehaviour.h"
#include "Js_Camera.h"

namespace Js
{
	DxObject::DxObject(ComPtr<ID3D11Device> _device, ComPtr<ID3D11DeviceContext> _context, const std::wstring& _name) 
		: Entity(_name),
		  m_Device(_device),
		  m_Context(_context)
	{
		m_Geometry = std::make_shared<Geometry<VertexTextureData>>();
		GeometryHelper::CreateRectangle(m_Geometry);

		m_VertexBuffer = std::make_shared<VertexBuffer>(m_Device);
		m_VertexBuffer->Create(m_Geometry->GetVertices());

		m_IndexBuffer = std::make_shared<IndexBuffer>(m_Device);
		m_IndexBuffer->Create(m_Geometry->GetIndices());

		m_VertexShader = std::make_shared<VertexShader>(m_Device);
		m_VertexShader->Create(L"Default.hlsl", "VS", "vs_5_0");

		m_InputLayout = std::make_shared<InputLayout>(m_Device);
		m_InputLayout->Create(VertexTextureData::descs, m_VertexShader->GetBlob());

		m_PixelShader = std::make_shared<PixelShader>(m_Device);
		m_PixelShader->Create(L"Default.hlsl", "PS", "ps_5_0");

		m_ConstantBuffer = std::make_shared<ConstantBuffer<TransformData>>(m_Device, m_Context);
		m_ConstantBuffer->Create();

		m_RasterizerState = std::make_shared<RasterizerState>(m_Device);
		m_RasterizerState->Create();

		m_ShaderResourceView = std::make_shared<Texture>(m_Device);
		if (_name.size() > 0)
		{
			m_ShaderResourceView->Create(_name);
		}

		m_SamplerState = std::make_shared<SamplerState>(m_Device);
		m_SamplerState->Create();

		m_BlendState = std::make_shared<BlendState>(m_Device);
		m_BlendState->Create();
	}
	DxObject::~DxObject()
	{
	}
	void DxObject::Init()
	{
		for (std::shared_ptr<Component>& component : m_Components)
		{
			if (component)
				component->Init();
		}
		for (std::shared_ptr<MonoBehaviour>& script : m_Scripts)
		{
			if (script)
				script->Init();
		}
	}
	void DxObject::Update()
	{
		for (std::shared_ptr<Component>& component : m_Components)
		{
			if (component)
				component->Update();
		}
		for (std::shared_ptr<MonoBehaviour>& script : m_Scripts)
		{
			if (script)
				script->Update();
		}

		Matrix viewMatrix = Camera::m_sViewMatrix;
		Matrix projection = Camera::m_sProjectionMatrix;
		//m_TransformData.matWorld = GetOrAddTransform()->GetWorldMatrix();// *viewMatrix;//* projection;
		//m_ConstantBuffer->CopyData(m_TransformData);

		if (m_Components[0])
		{
			m_TransformData.matWorld = GetOrAddTransform()->GetWorldMatrix() * viewMatrix * projection;
			m_ConstantBuffer->CopyData(m_TransformData);
		}
		else
		{
			m_TransformData.matWorld = GetOrAddTransform()->GetWorldMatrix();// *viewMatrix;//* projection;
			m_ConstantBuffer->CopyData(m_TransformData);
		}
	}
	void DxObject::LateUpdate()
	{
		for (std::shared_ptr<Component>& component : m_Components)
		{
			if (component)
				component->LateUpdate();
		}
		for (std::shared_ptr<MonoBehaviour>& script : m_Scripts)
		{
			if (script)
				script->LateUpdate();
		}
	}
	void DxObject::Render(std::shared_ptr<Pipeline> _pipeline)
	{
		PipelineInfo info;
		info.inputLayout = m_InputLayout;
		info.vertexShader = m_VertexShader;
		info.pixelShader = m_PixelShader;
		info.rasterizerState = m_RasterizerState;
		info.blendState = m_BlendState;
		_pipeline->UpdatePipeline(info);

		_pipeline->SetVertexBuffer(m_VertexBuffer);
		_pipeline->SetIndexBuffer(m_IndexBuffer);
		_pipeline->SetConstantBuffer(0, SS_VertexShader, m_ConstantBuffer);
		_pipeline->SetTexture(0, SS_PixelShader, m_ShaderResourceView);
		_pipeline->SetSamplerState(0, SS_PixelShader, m_SamplerState);
		_pipeline->DrawIndexed(m_Geometry->GetIndexCount(), 0, 0);
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
		if (index < FIXED_COMPONENT_COUNT)
		{
			m_Components[index] = _component;
		}
		else
		{
			m_Scripts.push_back(std::dynamic_pointer_cast<MonoBehaviour>(_component));
		}
	}
	std::shared_ptr<Transform> DxObject::GetTransform()
	{
		std::shared_ptr<Component> component = GetComponent(ComponentType::Transform);
		return std::dynamic_pointer_cast<Transform>(component);
	}
	std::shared_ptr<Transform> DxObject::GetOrAddTransform()
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
		auto size = m_ShaderResourceView->GetSize();
		return Vector3(size.x, size.y, 0);
	}
}