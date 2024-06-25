#pragma once
#include "std.h"
#include "Js_Pipeline.h"
#include "Js_Component.h"
#include "Js_MonoBehaviour.h"
#include "Js_Camera.h"

namespace Js
{
	class DxObject : public std::enable_shared_from_this<DxObject>, public Entity
	{
	public:
		DxObject(ComPtr<ID3D11Device> _device, ComPtr<ID3D11DeviceContext> _context, const std::wstring& _name = {});
		virtual ~DxObject();

		virtual void Init();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(std::shared_ptr<Pipeline> _pipeline);
		virtual void Release();

		std::shared_ptr<Component> GetComponent(ComponentType _type);
		void AddComponent(std::shared_ptr<Component> _component);
		std::shared_ptr<Transform> GetOrAddTransform();
		std::shared_ptr<Transform> GetTransform();
		std::shared_ptr<Camera> GetCamera();
		Vector3 GetSize();

	protected:
		ComPtr<ID3D11Device> m_Device = nullptr;
		ComPtr<ID3D11DeviceContext> m_Context = nullptr;

		// Geometry
		std::shared_ptr<Geometry<VertexTextureData>> m_Geometry = nullptr;
		std::shared_ptr<VertexBuffer> m_VertexBuffer = nullptr;
		std::shared_ptr<IndexBuffer>  m_IndexBuffer = nullptr;
		std::shared_ptr<InputLayout>  m_InputLayout = nullptr;
		
		// Shader
		std::shared_ptr<VertexShader> m_VertexShader = nullptr;
		std::shared_ptr<PixelShader>  m_PixelShader  = nullptr;

		std::shared_ptr<RasterizerState> m_RasterizerState = nullptr;
		std::shared_ptr<Texture> m_ShaderResourceView = nullptr;
		std::shared_ptr<SamplerState> m_SamplerState = nullptr;
		std::shared_ptr<BlendState> m_BlendState = nullptr;

	protected:
		// SRT
		TransformData m_TransformData;
		std::shared_ptr<ConstantBuffer<TransformData>> m_TransformBuffer = nullptr;
		
		CameraData m_CameraData;
		std::shared_ptr<ConstantBuffer<CameraData>> m_CameraBuffer = nullptr;

	protected:
		std::array<std::shared_ptr<Component>, FIXED_COMPONENT_COUNT> m_Components;
		std::vector<std::shared_ptr<MonoBehaviour>>					  m_Scripts;
	};
}

