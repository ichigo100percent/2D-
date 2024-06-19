#pragma once
#include "Js_BaseMgr.h"


namespace Js
{
	class Shader : public Resource
	{
	public:
		void Release() override;
		bool Load(ComPtr<ID3D11Device> _device, const std::wstring& _fileName) override;
	private:
		ComPtr<ID3D11VertexShader>	 m_VertexShader;
		ComPtr<ID3D11PixelShader>	 m_PixelShader;
		ComPtr<ID3DBlob>			 m_VSBlob;
		ComPtr<ID3DBlob>			 m_PSBlob;
	};

	//class ShaderMgr : public BaseManager<Shader, ShaderMgr>
	//{
	//	friend
	//private:
	//};
}
