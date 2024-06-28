#pragma once
#include "Js_Resource.h"
#include "Js_Shader.h"
#include "Js_Texture.h"


namespace Js
{
	class Material : public BaseResource
	{
	public:
		Material();
		virtual ~Material();

		auto GetShader() { return m_Shader; }
		auto GetTexture() { return m_Textrue; }

		void SetShader(std::shared_ptr<Shader> _shader) { m_Shader = _shader; }
		void SetTexture(std::shared_ptr<Texture> _texture) { m_Textrue = _texture; }

	private:
		std::shared_ptr<Shader> m_Shader = nullptr;
		std::shared_ptr<Texture> m_Textrue = nullptr;
	};
}