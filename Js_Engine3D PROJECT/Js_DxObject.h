#pragma once
#include "std.h"
#include "Js_Pipeline.h"
#include "Js_Transform.h"

//class Transform {};
	
namespace Js
{

	class DxObject : public Entity
	{
	public:
		DxObject(ComPtr<ID3D11Device> _device, ComPtr<ID3D11DeviceContext> _context, const std::wstring& _name = {});
		virtual ~DxObject();

		virtual void Init(const std::wstring& _texName);
		virtual void Update();
		virtual void Render(std::shared_ptr<Pipeline> _pipeline);
		virtual void Release();

		//virtual void SetWorld(const Matrix& _mat)
		//{
		//	m_MatWorld = _mat;
		//}
		//virtual void SetScale(const Vector3& _scale)
		//{
		//	m_LocalScale = _scale;
		//}
		//virtual void SetRotate(float _rotate)
		//{
		//	m_MatRotate = Matrix::CreateRotationZ(_rotate);
		//}
		//virtual void SetTranslate(const Vector3& _pos)
		//{
		//	m_MatTranslate = Matrix::CreateTranslation(_pos);
		//}
		//
		//Matrix		 m_MatWorld;     
		//Matrix	     m_MatScale;
		//Matrix	     m_MatRotate;
		//Matrix	     m_MatTranslate;
		//
		//MyRect m_Rt;
		//
		//MyRect GetAABB() const 
		//{
		//	return m_Rt;
		//}

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
		std::shared_ptr<ConstantBuffer<TransformData>> m_ConstantBuffer = nullptr;
		std::shared_ptr<Transform> m_Transform = std::make_shared<Transform>();
		//Vector3 m_LocalPosition = { 0.f, 0.f, 0.f };
		//Vector3 m_LocalRotation = { 0.f, 0.f, 0.f };
		//Vector3 m_LocalScale = { 1.f, 1.f, 1.f };
	};
}

