#pragma once
#include "Js_BaseMgr.h"

namespace Js
{
	class Shader : public Resource
	{
	public:
		void Set(ComPtr<ID3D11Device> _device) override { m_Device = _device; }
		void Release() override;
		bool Load(const std::wstring& _fileName) override;

		void LoadShader(const std::wstring& _path, const std::string& _name, const std::string& _version, ComPtr<ID3DBlob>& _blob);
		bool CreateVs(ComPtr<ID3D11Device> _device, const std::wstring& _name);
		bool CreatePS(ComPtr<ID3D11Device> _device ,const std::wstring& _name);

	public:
		ComPtr<ID3D11Device> m_Device;

		std::wstring m_csName;
		ComPtr<ID3D11VertexShader>	 m_VertexShader;
		ComPtr<ID3D11PixelShader>	 m_PixelShader;
		ComPtr<ID3DBlob>			 m_VSBlob;
		ComPtr<ID3DBlob>			 m_PSBlob;
	};

	class ShaderMgr : public BaseManager<Shader, ShaderMgr>
	{
		friend class Singleton<ShaderMgr>;
	private:
		ShaderMgr() {}
	};

#define SHADER	ShaderMgr::Instance()
}
