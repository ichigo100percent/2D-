#include "Js_ShaderMgr.h"

namespace Js
{
	void Shader::Release()
	{
		if(m_VertexShader) m_VertexShader.Reset();
		if(m_PixelShader) m_PixelShader.Reset();
		if(m_VSBlob) m_VSBlob.Reset();
		if(m_PSBlob) m_PSBlob.Reset();
	}
	bool Shader::Load(const std::wstring& _fileName)
	{
		if (!CreateVs(m_Device, _fileName)) return false;
		if (!CreatePS(m_Device, _fileName)) return false;

		return true;
	}
	void Shader::LoadShader(const std::wstring& _path, const std::string& _name, const std::string& _version, ComPtr<ID3DBlob>& _blob)
	{
		const UINT compileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;

		HRESULT hr = D3DCompileFromFile
		(
			_path.c_str(),
			nullptr,
			D3D_COMPILE_STANDARD_FILE_INCLUDE,
			_name.c_str(),
			_version.c_str(),
			compileFlag,
			0,
			_blob.GetAddressOf(),
			nullptr
		);
		CHECK(hr);
	}

	bool Shader::CreateVs(ComPtr<ID3D11Device> _device, const std::wstring& _name)
	{
		LoadShader(_name, "VS", "vs_5_0", m_VSBlob);
		HRESULT hr =
			_device->CreateVertexShader
			(
				m_VSBlob->GetBufferPointer(),
				m_VSBlob->GetBufferSize(),
				nullptr,
				m_VertexShader.GetAddressOf()
			);

		if (FAILED(hr))
			return false;

		return true;
	}

	bool Shader::CreatePS(ComPtr<ID3D11Device> _device, const std::wstring& _name)
	{
		LoadShader(_name, "PS", "ps_5_0", m_PSBlob);
		HRESULT hr =
			_device->CreatePixelShader
			(
				m_PSBlob->GetBufferPointer(),
				m_PSBlob->GetBufferSize(),
				nullptr,
				m_PixelShader.GetAddressOf()
			);

		if (FAILED(hr))
			return false;

		return true;
	}
}