#pragma once
#include "std.h"

	enum ShaderScope
	{
		SS_None = 0,
		SS_VertexShader = (1 << 0),
		SS_PixelShader = (1 << 1),
		SS_Both = SS_VertexShader | SS_PixelShader
	};

namespace Js
{

	class ShaderBase
	{
	public:
		ShaderBase(ComPtr<ID3D11Device> _device);
		virtual ~ShaderBase();

		virtual void Create(const std::wstring& _path, const std::string& _name, const std::string& _version) = 0;

		ComPtr<ID3DBlob> GetBlob() { return m_Blob; }

	protected:
		void LoadShaderFromFile(const std::wstring& _path, const std::string& _name, const std::string& _version);

	protected:
		ComPtr<ID3D11Device> m_Device = nullptr;
		ComPtr<ID3DBlob> m_Blob;

		std::wstring m_Path;
		std::string  m_Name;
	};

	class VertexShader : public ShaderBase
	{
	public:
		VertexShader(ComPtr<ID3D11Device> _device);
		~VertexShader();

		void Create(const std::wstring& _path, const std::string& _name, const std::string& _version) override;

		ComPtr<ID3D11VertexShader> GetComPtr() { return m_VertexShader; }

	private:
		ComPtr<ID3D11VertexShader> m_VertexShader = nullptr;
	};

	class PixelShader : public ShaderBase
	{
	public:
		PixelShader(ComPtr<ID3D11Device> _device);
		~PixelShader();

		void Create(const std::wstring& _path, const std::string& _name, const std::string& _version) override;

		ComPtr<ID3D11PixelShader> GetComPtr() { return m_PixelShader; }
	private:
		ComPtr<ID3D11PixelShader> m_PixelShader = nullptr;
	};
}