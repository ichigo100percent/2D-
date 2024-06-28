#pragma once
#include "Js_Component.h"
#include "Js_Pipeline.h"
#include "Js_Material.h"
#include "Js_Mesh.h"


namespace Js
{

	class MeshRenderer : public Component
	{
		friend class RenderManager;
	public:
		MeshRenderer(ComPtr<ID3D11Device> _device, ComPtr<ID3D11DeviceContext> _context, const std::wstring _name = {});
		virtual ~MeshRenderer();

		void SetMaterial(std::shared_ptr<Material> _material) { m_Material = _material; }
		void SetShader(std::shared_ptr<Shader> _shader) { m_Material->SetShader(_shader); }
		void SetMesh(std::shared_ptr<Mesh> _mesh) { m_Mesh = _mesh; }
		void SetTexture(std::shared_ptr<Texture> _texture) { m_Material->SetTexture(_texture); };

		std::shared_ptr<Mesh> GetMesh() { return m_Mesh; }
		std::shared_ptr<Material> GetMaterial() { return m_Material; }

		auto GetVertexShader() { return GetMaterial()->GetShader()->GetVertexShader(); }
		auto GetPixelShaer() { return GetMaterial()->GetShader()->GetPixelShader(); }
		auto GetInputLayout() { return GetMaterial()->GetShader()->GetInputLayout(); }
		auto GetTexture() { return GetMaterial()->GetTexture(); }

	private:
		ComPtr<ID3D11Device> m_Device = nullptr;
		std::shared_ptr<Mesh> m_Mesh = nullptr;
		std::shared_ptr<Material> m_Material = nullptr;
	};
}
