#include "Js_RenderManager.h"
#include "Js_Camera.h"
#include "Js_Transform.h"
#include "Js_Core.h"
#include "Js_Component.h"
#include "Js_DxObject.h"
#include "Js_MeshRenderer.h"
#include "Js_SceneManager.h"

namespace Js
{
	RenderManager::RenderManager(ComPtr<ID3D11Device> _device, ComPtr<ID3D11DeviceContext> _context)
		: m_Device(_device)
		, m_Context(_context)
	{
	}
	RenderManager::~RenderManager()
	{
	}
	void RenderManager::Init()
	{
		m_Pipeline = std::make_shared<Pipeline>(m_Context);

		m_TransformBuffer = std::make_shared<ConstantBuffer<TransformData>>(m_Device, m_Context);
		m_TransformBuffer->Create();
		m_CameraBuffer = std::make_shared<ConstantBuffer<CameraData>>(m_Device, m_Context);
		m_CameraBuffer->Create();
		m_AnimationBuffer = std::make_shared<ConstantBuffer<AnimationData>>(m_Device, m_Context);
		m_AnimationBuffer->Create();

		m_RasterizerState = std::make_shared<RasterizerState>(m_Device);
		m_RasterizerState->Create();
		m_SamplerState = std::make_shared<SamplerState>(m_Device);
		m_SamplerState->Create();
		m_BlendState = std::make_shared<BlendState>(m_Device);
		m_BlendState->Create();
	}
	void RenderManager::Update()
	{
	}
	void RenderManager::PushCameraData()
	{
		m_CameraData.matView = Camera::s_ViewMatrix;
		m_CameraData.matProjection = Camera::s_ProjectionMatrix;
		m_CameraBuffer->CopyData(m_CameraData);
	}
	void RenderManager::PushTransformData()
	{
		m_TransformBuffer->CopyData(m_TransformData);
	}
	void RenderManager::PushAnimationData()
	{
		m_AnimationBuffer->CopyData(m_AnimationData);
	}
	void RenderManager::GatherRenderableObjects()
	{
		m_RenderObject.clear();
		auto& gameObjects = SceneManager::GetActiveScene()->GetGameObjects();
		for (const std::shared_ptr<DxObject>& gameObject : gameObjects)
		{
			std::shared_ptr<MeshRenderer> meshRenderer = gameObject->GetMeshRenderer();
			if (meshRenderer)
				m_RenderObject.push_back(gameObject);
		}
	}
	void RenderManager::RenderObjects()
	{
		for (const auto& gameObject : m_RenderObject)
		{
			auto meshRenderer = gameObject->GetMeshRenderer();
			if (meshRenderer == nullptr)
				continue;

			auto transform = gameObject->GetTransform();
			if (transform == nullptr)
				continue;

			m_TransformData.matWorld = transform->GetWorldMatrix();
			PushTransformData();

			auto animator = gameObject->GetAnimator();
			if (animator)
			{
				auto keyframe = animator->GetCurrentKeyFrame();
				m_AnimationData.spriteOffset = keyframe.offset;
				m_AnimationData.spriteSize = keyframe.size;
				m_AnimationData.textureSize = animator->GetCurrentAnimation()->GetTextureSize();
				m_AnimationData.useAnimation = 1.f;

				PushAnimationData();

				m_Pipeline->SetConstantBuffer(2, SS_VertexShader, m_AnimationBuffer);
				m_Pipeline->SetTexture(0, SS_PixelShader, animator->GetCurrentAnimation()->GetTexture());
			}
			else
			{
				m_AnimationData.spriteOffset = Vector2::Zero;
				m_AnimationData.spriteSize = Vector2::Zero;
				m_AnimationData.textureSize = Vector2::Zero;
				m_AnimationData.useAnimation = 0.f;

				PushAnimationData();

				m_Pipeline->SetConstantBuffer(2, SS_VertexShader, m_AnimationBuffer);
				if(meshRenderer)
					m_Pipeline->SetTexture(0, SS_PixelShader, meshRenderer->GetTexture());
			}
			PipelineInfo info;
			info.inputLayout = meshRenderer->GetInputLayout();
			info.vertexShader = meshRenderer->GetVertexShader();
			info.pixelShader = meshRenderer->GetPixelShaer();
			info.rasterizerState = m_RasterizerState;
			info.blendState = m_BlendState;
			m_Pipeline->UpdatePipeline(info);

			m_Pipeline->SetVertexBuffer(meshRenderer->GetMesh()->GetVertexBuffer());
			m_Pipeline->SetIndexBuffer(meshRenderer->GetMesh()->GetIndexBuffer());

			m_Pipeline->SetConstantBuffer(1, SS_VertexShader, m_TransformBuffer);
			m_Pipeline->SetConstantBuffer(0, SS_VertexShader, m_CameraBuffer);

			//m_Pipeline->SetSamplerState(0, SS_PixelShader, m_SamplerState);
			m_Pipeline->DrawIndexed(meshRenderer->GetMesh()->GetIndexBuffer()->GetCount(), 0, 0);
			//m_Pipeline->SetTexture(0, SS_PixelShader, meshRenderer->GetTexture());
		}
	}
}