#pragma once
#include "Js_Component.h"
#include "Js_Pipeline.h"

namespace Js
{
	class MeshRenderer : public Component
	{
	public:
		MeshRenderer(ComPtr<ID3D11Device> _device, ComPtr<ID3D11DeviceContext> _context, const std::wstring& _name);
		virtual ~MeshRenderer();

		virtual void Init() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(std::shared_ptr<Pipeline> _pipeline) override;
		virtual void Release() override;

		Vector2 GetSize() { return m_ShaderResourceView->GetSize(); }

	private:
		ComPtr<ID3D11Device> m_Device = nullptr;

		std::shared_ptr<Geometry<VertexTextureData>> m_Geometry = nullptr;
		std::shared_ptr<VertexBuffer> m_VertexBuffer = nullptr;
		std::shared_ptr<IndexBuffer>  m_IndexBuffer = nullptr;

		std::shared_ptr<InputLayout>  m_InputLayout = nullptr;
		std::shared_ptr<VertexShader> m_VertexShader = nullptr;
		std::shared_ptr<PixelShader>  m_PixelShader = nullptr;

		std::shared_ptr<RasterizerState> m_RasterizerState = nullptr;
		std::shared_ptr<Texture> m_ShaderResourceView = nullptr;
		std::shared_ptr<SamplerState> m_SamplerState = nullptr;
		std::shared_ptr<BlendState> m_BlendState = nullptr;

		// SRT
		TransformData m_TransformData;
		std::shared_ptr<ConstantBuffer<TransformData>> m_TransformBuffer = nullptr;

		CameraData m_CameraData;
		std::shared_ptr<ConstantBuffer<CameraData>> m_CameraBuffer = nullptr;
	};
}
