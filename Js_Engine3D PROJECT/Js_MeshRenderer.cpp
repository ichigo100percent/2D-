#include "Js_MeshRenderer.h"
#include "Js_Camera.h"
#include "Js_Transform.h"
#include "Js_Core.h"

namespace Js
{
	MeshRenderer::MeshRenderer(ComPtr<ID3D11Device> _device, ComPtr<ID3D11DeviceContext> _context, const std::wstring& _name)
		: Component(ComponentType::MeshRenderer, _name)
		, m_Device(_device)
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

		m_TransformBuffer = std::make_shared<ConstantBuffer<TransformData>>(m_Device, _context);
		m_TransformBuffer->Create();

		m_CameraBuffer = std::make_shared<ConstantBuffer<CameraData>>(m_Device, _context);
		m_CameraBuffer->Create();

		m_RasterizerState = std::make_shared<RasterizerState>(m_Device);
		m_RasterizerState->Create();

		m_ShaderResourceView = std::make_shared<Texture>(m_Device);
		if (_name.size())
			m_ShaderResourceView->Create(_name);

		m_SamplerState = std::make_shared<SamplerState>(m_Device);
		m_SamplerState->Create();

		m_BlendState = std::make_shared<BlendState>(m_Device);
		m_BlendState->Create();
	}
	MeshRenderer::~MeshRenderer()
	{
	}
	void MeshRenderer::Init()
	{
	}
	void MeshRenderer::Update()
	{
		m_CameraData.matView = Camera::s_ViewMatrix;
		m_CameraData.matProjection = Camera::s_ProjectionMatrix;
		m_CameraBuffer->CopyData(m_CameraData);

		m_TransformData.matWorld = GetTransform()->GetWorldMatrix();
		m_TransformBuffer->CopyData(m_TransformData);
	}
	void MeshRenderer::LateUpdate()
	{
	}
	void MeshRenderer::Render(std::shared_ptr<Pipeline> _pipeline)
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
		_pipeline->SetConstantBuffer(0, SS_VertexShader, m_CameraBuffer);
		_pipeline->SetConstantBuffer(1, SS_VertexShader, m_TransformBuffer);
		_pipeline->SetTexture(0, SS_PixelShader, m_ShaderResourceView);
		_pipeline->SetSamplerState(0, SS_PixelShader, m_SamplerState);
		_pipeline->DrawIndexed(m_Geometry->GetIndexCount(), 0, 0);
	}
	void MeshRenderer::Release()
	{
	}
}