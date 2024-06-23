#include "Js_Pipeline.h"


namespace Js
{
	Pipeline::Pipeline(ComPtr<ID3D11DeviceContext> _context)
		: m_Context(_context)
	{
	}
	Pipeline::~Pipeline()
	{
	}
	void Pipeline::UpdatePipeline(PipelineInfo _info)
	{
		// IA
		m_Context->IASetInputLayout(_info.inputLayout->GetComPtr().Get());
		m_Context->IASetPrimitiveTopology(_info.topology);

		// VS
		if (_info.vertexShader)
			m_Context->VSSetShader(_info.vertexShader->GetComPtr().Get(), nullptr, 0);

		// RS
		if(_info.rasterizerState)
			m_Context->RSSetState(_info.rasterizerState->GetComPtr().Get());

		// PS
		if (_info.pixelShader)
			m_Context->PSSetShader(_info.pixelShader->GetComPtr().Get(), nullptr, 0);

		// OM
		if (_info.blendState)
			m_Context->OMSetBlendState(_info.blendState->GetComPtr().Get(), _info.blendState->GetBlendFactor(), _info.blendState->GetSampleMask());
	}
	void Pipeline::SetVertexBuffer(std::shared_ptr<VertexBuffer> _buffer)
	{
		UINT stride = _buffer->GetStride();
		UINT offset = _buffer->GetOffset();

		m_Context->IASetVertexBuffers(0, 1, _buffer->GetComPtr().GetAddressOf(), &stride, &offset);
	}
	void Pipeline::SetIndexBuffer(std::shared_ptr<IndexBuffer> _buffer)
	{
		m_Context->IASetIndexBuffer(_buffer->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);
	}
	void Pipeline::SetTexture(UINT _slot, UINT _scope, std::shared_ptr<Texture> _texture)
	{
		if(_scope & SS_VertexShader)
			m_Context->VSSetShaderResources(_slot, 1, _texture->GetComPtr().GetAddressOf());

		if (_scope & SS_PixelShader)
			m_Context->PSSetShaderResources(_slot, 1, _texture->GetComPtr().GetAddressOf());
	}
	void Pipeline::SetSamplerState(UINT _slot, UINT _scope, std::shared_ptr<SamplerState> _samplerState)
	{
		if (_scope & SS_VertexShader)
			m_Context->VSSetSamplers(0, 1, _samplerState->GetComPtr().GetAddressOf());

		if (_scope & SS_PixelShader)
			m_Context->PSSetSamplers(0, 1, _samplerState->GetComPtr().GetAddressOf());
	}
	void Pipeline::Draw(UINT _vertexCount, UINT _startVertexLocation)
	{
		m_Context->Draw(_vertexCount, _startVertexLocation);
	}
	void Pipeline::DrawIndexed(UINT _indexCount, UINT _startIndexLocation, UINT _baseVertexLocation)
	{
		m_Context->DrawIndexed(_indexCount, _startIndexLocation, _baseVertexLocation);
	}
}