#pragma once
#include "std.h"
#include "Js_Geometry.h"
#include "Js_GeometryHelper.h"
#include "Js_VertexData.h"
#include "Js_VertexBuffer.h"
#include "Js_IndexBuffer.h"
#include "Js_InputLayout.h"
#include "Js_ShaderBase.h"
#include "Js_ConstantBuffer.h"
#include "Js_Texture.h"
#include "Js_RasterizerState.h"
#include "Js_SamplerState.h"
#include "Js_BlendState.h"

namespace Js
{
	struct PipelineInfo
	{
		std::shared_ptr<InputLayout> inputLayout;
		std::shared_ptr<VertexShader> vertexShader;
		std::shared_ptr<PixelShader> pixelShader;
		std::shared_ptr<RasterizerState> rasterizerState;
		std::shared_ptr<BlendState> blendState;
		D3D11_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	};


	class Pipeline
	{
	public:
		Pipeline(ComPtr<ID3D11DeviceContext> _context);
		~Pipeline();

		void UpdatePipeline(PipelineInfo _info);

		void SetVertexBuffer(std::shared_ptr<VertexBuffer> _buffer);
		void SetIndexBuffer(std::shared_ptr<IndexBuffer> _buffer);

		template<typename T>
		void SetConstantBuffer(UINT _slot, UINT _scope, std::shared_ptr<ConstantBuffer<T>> _buffer)
		{
			if (_scope & SS_VertexShader)
				m_Context->VSSetConstantBuffers(_slot, 1, _buffer->GetComPtr().GetAddressOf());

			if (_scope & SS_PixelShader)
				m_Context->PSSetConstantBuffers(_slot, 1, _buffer->GetComPtr().GetAddressOf());
		}

		void SetTexture(UINT _slot, UINT _scope, std::shared_ptr<Texture> _texture);
		void SetSamplerState(UINT _slot, UINT _scope, std::shared_ptr<SamplerState> _samplerState);

		void Draw(UINT _vertexCount, UINT _startVertexLocation);
		void DrawIndexed(UINT _indexCount, UINT _startIndexLocation, UINT _baseVertexLocation);

	private:
		ComPtr<ID3D11DeviceContext> m_Context = nullptr;
	};
}
