#pragma once
#include "std.h"

using namespace std;

namespace Js
{
	class DxObject : public Entity
	{
	public:
		DxObject(ComPtr<ID3D11Device> _device, ComPtr<ID3D11DeviceContext> _context, const std::wstring& _name = {});
		virtual ~DxObject();

		virtual void Update();
		virtual void Render();
		virtual void Release();

		virtual void CreateObject(const std::wstring& _texName);

	protected:
		void CreateGeometry();
		void CreateInputLayout();
		void CreateVS();
		void CreatePS();

		void CreateRasterizerState();
		void CreateSamplerState();
		void CreateBlendState();
		void CreateSRV(const std::wstring& _texName);

		void CreateConstantBuffer();

		void LoadShaderFromFile(const wstring& _path, const string& _name, const string& _version, ComPtr<ID3DBlob>& _blob);

	protected:
		ComPtr<ID3D11Device> m_Device = nullptr;
		ComPtr<ID3D11DeviceContext> m_Context = nullptr;

		// Geometry
		vector<VertexData> m_Vertices;
		ComPtr<ID3D11Buffer> m_VertexBuffer = nullptr;
		vector<UINT> m_Indices;
		ComPtr<ID3D11Buffer> m_IndexBuffer = nullptr;
		ComPtr<ID3D11InputLayout> _inputLayout = nullptr;

		// VS
		ComPtr<ID3D11VertexShader> m_VertexShader = nullptr;
		ComPtr<ID3DBlob> m_VsBlob = nullptr;

		// RS
		ComPtr<ID3D11RasterizerState> _rasterizerState = nullptr;

		// PS
		ComPtr<ID3D11PixelShader> m_PixelShader = nullptr;
		ComPtr<ID3DBlob> m_PsBlob = nullptr;

		// SRV
		ComPtr<ID3D11ShaderResourceView> m_ShaderResourveView = nullptr;


		ComPtr<ID3D11SamplerState> m_SamplerState = nullptr;
		ComPtr<ID3D11BlendState> m_BlendState = nullptr;
		// [ CPU<->RAM ] [GPU<->VRAM]

		// SRT
		TransformData m_TransformData;
		ComPtr<ID3D11Buffer> m_ConstantBuffer;

		Vector3 m_LocalPosition = { 0.f, 0.f, 0.f };
		Vector3 m_LocalRotation = { 0.f, 0.f, 0.f };
		Vector3 m_LocalScale = { 1.f, 1.f, 1.f };
	};
}

