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


	private:
		void CreateGeometry();
		void CreateInputLayout();
		void CreateVS();
		void CreatePS();

		void CreateRasterizerState();
		void CreateSamplerState();
		void CreateBlendState();
		void CreateSRV(const std::wstring& _texName);

		void CreateConstantBuffer();

		void LoadShaderFromFile(const wstring& path, const string& name, const string& version, ComPtr<ID3DBlob>& blob);
	protected:
		ComPtr<ID3D11Device> _device = nullptr;
		ComPtr<ID3D11DeviceContext> _deviceContext = nullptr;

		// Geometry
		vector<VertexData> _vertices;
		ComPtr<ID3D11Buffer> _vertexBuffer = nullptr;
		vector<UINT> _indices;
		ComPtr<ID3D11Buffer> _indexBuffer = nullptr;
		ComPtr<ID3D11InputLayout> _inputLayout = nullptr;

		// VS
		ComPtr<ID3D11VertexShader> _vertexShader = nullptr;
		ComPtr<ID3DBlob> _vsBlob = nullptr;

		// RS
		ComPtr<ID3D11RasterizerState> _rasterizerState = nullptr;

		// PS
		ComPtr<ID3D11PixelShader> _pixelShader = nullptr;
		ComPtr<ID3DBlob> _psBlob = nullptr;

		// SRV
		ComPtr<ID3D11ShaderResourceView> _shaderResourveView = nullptr;


		ComPtr<ID3D11SamplerState> _samplerState = nullptr;
		ComPtr<ID3D11BlendState> _blendState = nullptr;
		// [ CPU<->RAM ] [GPU<->VRAM]
	private:
		// SRT
		TransformData _transformData;
		ComPtr<ID3D11Buffer> _constantBuffer;
	};
}

