#pragma once
#include "std.h"

namespace Js
{
	class DxObject : public Entity
	{
	public:
		DxObject(ComPtr<ID3D11Device> _device, ComPtr<ID3D11DeviceContext> _context, const std::wstring& _name = {});

		virtual void Init(JsRect& _rect, const std::wstring& _texName);
		virtual void Render();
		virtual void Update();
		virtual void Release();

		virtual DxObject& Move(float _dx, float _dy);
		Vector2& ConvertScreenToNDC(Vector2& _pos);

		virtual void CreateObject(const Vector2& _pos, const std::wstring& _texName);

		// Graphics
		virtual void CreateGeometry(JsRect& _rect);
		virtual void CreateVertexBuffer();
		virtual void CreateIndexBuffer();
		virtual void CreateInputLayout();
		virtual void LoadShader(const std::wstring& _path,
								const std::string& _name,
								const std::string& _version,
								ComPtr<ID3DBlob>& _blob);

		virtual void CreateVS();
		virtual void CreatePS();
		virtual void CreateSRV(const std::wstring& _texName);

		virtual void CreateRasterizerState();
		virtual void CreateSamplerState();
		virtual void CreateBlendState();

		virtual void CreateConstantBuffer();
	private:
		ComPtr<ID3D11Device>	     m_Device;
		ComPtr<ID3D11DeviceContext>  m_Context;


		std::vector<VertexData>      m_NdcVertices;
		Vector2						 m_Position;
		// VS
		std::vector<VertexData>		 m_Vertices;
		ComPtr<ID3D11Buffer>		 m_VertexBuffer;
		// Index
		std::vector<UINT>			 m_Indices;
		ComPtr<ID3D11Buffer>		 m_IndexBuffer;
		// Constant SRT
		TransformData				 m_TransformData;
		ComPtr<ID3D11Buffer>		 m_ConstantBuffer;

		ComPtr<ID3D11InputLayout>	 m_InputLayout;


		// PS
		ComPtr<ID3D11VertexShader>	 m_VertexShader;
		ComPtr<ID3D11PixelShader>	 m_PixelShader;
		ComPtr<ID3DBlob>			 m_VSBlob;
		ComPtr<ID3DBlob>			 m_PSBlob;

		// RS
		ComPtr<ID3D11RasterizerState> m_RasterizerState;
		// Sampler
		ComPtr<ID3D11SamplerState>    m_SamplerState;
		// Blend
		ComPtr<ID3D11BlendState>      m_BlendState;
		// SRV
		// 렌더링 파이브라인(픽셀쉐이더)에 전송 데이터
		ComPtr<ID3D11ShaderResourceView> m_ShaderResourceView;
		// 텍스처(이미지) 로드 데이터
		ComPtr<ID3D11Resource>			 m_Texture;
	};
}

