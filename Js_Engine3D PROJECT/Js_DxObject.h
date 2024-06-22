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

		virtual void CreateObject(const std::wstring& _texName, const MyRect& _rt);

		void DrawAABB()
		{
			// Create a wireframe rectangle using DirectX
			Vector2 size = Vector2(m_AABB.right - m_AABB.left, m_AABB.top - m_AABB.bottom); // Calculate AABB size

			// Define vertices for a wireframe rectangle
			std::vector<VertexData> vertices = {
				{Vector3(m_AABB.left, m_AABB.top, 0.f), Vector2(0.f, 0.f)},
				{Vector3(m_AABB.left + size.x, m_AABB.top, 0.f), Vector2(1.f, 0.f)},
				{Vector3(m_AABB.left + size.x, m_AABB.bottom, 0.f), Vector2(1.f, 1.f)},
				{Vector3(m_AABB.left, m_AABB.bottom, 0.f), Vector2(0.f, 1.f)},
				{Vector3(m_AABB.left, m_AABB.top, 0.f), Vector2(0.f, 0.f)} // Close the rectangle
			};

			UINT stride = sizeof(VertexData);
			UINT offset = 0;

			// Create a temporary vertex buffer
			ComPtr<ID3D11Buffer> tempVertexBuffer;
			D3D11_BUFFER_DESC desc;
			ZeroMemory(&desc, sizeof(desc));
			desc.Usage = D3D11_USAGE_IMMUTABLE;
			desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			desc.ByteWidth = (UINT)(sizeof(VertexData) * vertices.size());

			D3D11_SUBRESOURCE_DATA data;
			ZeroMemory(&data, sizeof(data));
			data.pSysMem = vertices.data();

			HRESULT hr = m_Device->CreateBuffer(&desc, &data, tempVertexBuffer.GetAddressOf());
			CHECK(hr);

			// Set IA parameters for rendering the rectangle
			m_Context->IASetVertexBuffers(0, 1, tempVertexBuffer.GetAddressOf(), &stride, &offset);
			m_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP); // Use line strip for wireframe

			// Draw the rectangle
			m_Context->Draw(vertices.size(), 0);
		}
		MyRect m_AABB;

		MyRect GetAABB() const {
			return m_AABB;
		}

	protected:
		void CreateGeometry(const MyRect& _rt);
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
		Vector3 m_LocalScale = { 0.3f, 0.3f, 0.3f };
	};
}

