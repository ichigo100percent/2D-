#pragma once
#include "std.h"

namespace Js
{
	struct VertexData
	{
		Vector3 position;
		//Vector2 uv;
	};

	class DxObject
	{
	public:
		DxObject(ComPtr<ID3D11Device> _device, ComPtr<ID3D11DeviceContext> _context);

		virtual void Init();
		virtual void Render();
		virtual void Update();
		virtual void Release();

		virtual void CreateVertexBuffer();
		virtual void CreateInputLayout();
		virtual void LoadShader(const std::wstring& _path,
			const std::string& _name,
			const std::string& _version,
			ComPtr<ID3DBlob>& _blob);

		virtual void CreateVS();
		virtual void CreatePS();

	private:
		ComPtr<ID3D11Device>	     m_Device;
		ComPtr<ID3D11DeviceContext>  m_Context;

		std::vector<VertexData>		 m_Vertices;
		ComPtr<ID3D11Buffer>		 m_VertexBuffer;
		ComPtr<ID3D11InputLayout>	 m_InputLayout;

		ComPtr<ID3D11VertexShader>	 m_VertexShader;
		ComPtr<ID3D11PixelShader>	 m_PixelShader;
		ComPtr<ID3DBlob>			 m_VSBlob;
		ComPtr<ID3DBlob>			 m_PSBlob;
	};
}

