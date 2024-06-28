#pragma once
#include "Js_Pipeline.h"
#include "Js_DxObject.h"

namespace Js
{
	class RenderManager
	{
	public:
		RenderManager(ComPtr<ID3D11Device> _device, ComPtr<ID3D11DeviceContext> _context);
		virtual ~RenderManager();

		void Init();
		void Update();

		void PushCameraData();
		void PushTransformData();
		void PushAnimationData();

		void GatherRenderableObjects();
		void RenderObjects();

	private:
		ComPtr<ID3D11Device> m_Device = nullptr;
		ComPtr<ID3D11DeviceContext> m_Context = nullptr;
		std::shared_ptr<Pipeline> m_Pipeline = nullptr;

		std::shared_ptr<RasterizerState> m_RasterizerState = nullptr;
		std::shared_ptr<SamplerState> m_SamplerState = nullptr;
		std::shared_ptr<BlendState> m_BlendState = nullptr;

		std::vector<std::shared_ptr<DxObject>> m_RenderObject = {};

		// SRT
		TransformData m_TransformData;
		std::shared_ptr<ConstantBuffer<TransformData>> m_TransformBuffer = nullptr;

		// Camera
		CameraData m_CameraData;
		std::shared_ptr<ConstantBuffer<CameraData>> m_CameraBuffer = nullptr;

		// Animation
		AnimationData m_AnimationData;
		std::shared_ptr<ConstantBuffer<AnimationData>> m_AnimationBuffer = nullptr;
	};
}
