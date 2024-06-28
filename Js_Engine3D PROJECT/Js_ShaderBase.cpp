#include "Js_ShaderBase.h"

namespace Js
{
	ShaderBase::ShaderBase(ComPtr<ID3D11Device> _device)
		: m_Device(_device)
	{
	}
	ShaderBase::~ShaderBase()
	{
	}
	void ShaderBase::LoadShaderFromFile(const std::wstring& _path, const std::string& _name, const std::string& _version)
	{
		m_Path = _path;
		m_Name = _name;

		const UINT compileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;

		HRESULT hr = ::D3DCompileFromFile(	_path.c_str(),
											nullptr,
											D3D_COMPILE_STANDARD_FILE_INCLUDE,
											_name.c_str(),
											_version.c_str(),
											compileFlag,
											0,
											m_Blob.GetAddressOf(),
											nullptr);

		CHECK(hr);
	}
	VertexShader::VertexShader(ComPtr<ID3D11Device> _device)
		: ShaderBase(_device)
	{
	}
	VertexShader::~VertexShader()
	{
	}
	void VertexShader::Create(const std::wstring& _path, const std::string& _name, const std::string& _version)
	{
		LoadShaderFromFile(_path, _name, _version);
		HRESULT hr = m_Device->CreateVertexShader(m_Blob->GetBufferPointer(), m_Blob->GetBufferSize(), nullptr, m_VertexShader.GetAddressOf());
		CHECK(hr);
	}
	PixelShader::PixelShader(ComPtr<ID3D11Device> _device)
		: ShaderBase(_device)
	{
	}
	PixelShader::~PixelShader()
	{
	}
	void PixelShader::Create(const std::wstring& _path, const std::string& _name, const std::string& _version)
	{
		LoadShaderFromFile(_path, _name, _version);
		HRESULT hr = m_Device->CreatePixelShader(m_Blob->GetBufferPointer(), m_Blob->GetBufferSize(), nullptr, m_PixelShader.GetAddressOf());
		CHECK(hr);
	}
}