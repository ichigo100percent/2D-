#pragma once
#include "std.h"

namespace Js
{
	class DxObject : public Entity
	{
	public:
		DxObject(ComPtr<ID3D11Device> _device, ComPtr<ID3D11DeviceContext> _context, const std::wstring& _name = {});
		virtual ~DxObject();
		
		virtual void Update();
		virtual void Render();
		virtual void PreRender();
		virtual void PostRender();
	
		virtual void UpdateVertexBuffer();
		Vector3& ConvertScreenToNDC(const Vector3& _pos);

		// Graphics
		virtual void CreateGeometry(const RECT& _rect);
		virtual void CreateVertexBuffer();
		virtual void CreateIndexBuffer();
		virtual void CreateInputLayout();
		virtual void CreateSRV(const std::wstring& _texName);

		virtual void CreateRasterizerState();
		virtual void CreateBlendState();


		const ComPtr<ID3D11Device> GetDevice() const { return m_Device; }
		const ComPtr<ID3D11DeviceContext> GetContext() const { return m_Context; }

	public:
		ComPtr<ID3D11Device>	     m_Device;
		ComPtr<ID3D11DeviceContext>  m_Context;
	protected:


		std::vector<VertexData>		 m_Vertices;
		std::vector<VertexData>      m_List;
		std::vector<VertexData>      m_NdcVertices;
		// VS
		ComPtr<ID3D11Buffer>		 m_VertexBuffer;
		// Index
		std::vector<UINT>			 m_Indices;
		ComPtr<ID3D11Buffer>		 m_IndexBuffer;
		// Constant SRT
		TransformData				 m_TransformData;
		ComPtr<ID3D11Buffer>		 m_ConstantBuffer;
		ComPtr<ID3D11InputLayout>	 m_InputLayout;

		// Shader
		std::shared_ptr<class Shader> m_Shader;

		// RS
		ComPtr<ID3D11RasterizerState> m_RasterizerState;
		// Sampler
		ComPtr<ID3D11SamplerState>    m_SamplerState;
		// Blend
		ComPtr<ID3D11BlendState>      m_BlendState;

		// ShaderResourceView
		// 렌더링 파이브라인(픽셀쉐이더)에 전송 데이터
		ComPtr<ID3D11ShaderResourceView> m_ShaderResourceView;
		// 텍스처(이미지) 로드 데이터
		std::shared_ptr<class Texture> m_Texture;
	};
}

