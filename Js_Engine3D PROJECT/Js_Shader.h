#pragma once
#include "Js_Resource.h"
#include "Js_Pipeline.h"
namespace Js
{
	class Shader : public BaseResource
	{
	public:
		Shader();
		virtual ~Shader();

		void SetVertexShadaer(std::shared_ptr<VertexShader> _vertexShader) { m_VertexShader = _vertexShader; }
		void SetPixelShader(std::shared_ptr<PixelShader> _pixelShader) { m_PixelShader = _pixelShader; }
		void SetInputLayout(std::shared_ptr<InputLayout> _inputLayout) { m_InputLayout = _inputLayout; }

		std::shared_ptr<VertexShader> GetVertexShader() { return m_VertexShader; }
		std::shared_ptr<PixelShader> GetPixelShader() { return m_PixelShader; }
		std::shared_ptr<InputLayout> GetInputLayout() { return m_InputLayout; }

	private:
		std::shared_ptr<VertexShader> m_VertexShader = nullptr;
		std::shared_ptr<PixelShader>  m_PixelShader = nullptr;
		std::shared_ptr<InputLayout>  m_InputLayout = nullptr;
	};
}