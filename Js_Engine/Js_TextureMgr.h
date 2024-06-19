#pragma once
#include "Js_BaseMgr.h"

namespace Js
{
	class Texture : public Resource
	{
	public:
		void Release() override;
		bool Load(ComPtr<ID3D11Device> _device, const std::wstring& _fileName) override;

		//ComPtr<ID3D11Resource> GetTexture() { return m_Texture; }
		//ComPtr<ID3D11ShaderResourceView> GetSRV() { return m_ShaderResourceView; }
		//std::wstring GetName() { return m_csName; }

		//void SetTexture(ComPtr<ID3D11Resource> _texture) { m_Texture = _texture; }
		//void SetSRV(ComPtr<ID3D11ShaderResourceView> _srv) { m_ShaderResourceView = _srv; }
		//void SetName(std::wstring _name) { m_csName = _name; }

	public:
		std::wstring m_csName;
		// ShaderResourceView
		// 렌더링 파이브라인(픽셀쉐이더)에 전송 데이터
		ComPtr<ID3D11ShaderResourceView> m_ShaderResourceView;
		// 텍스처(이미지) 로드 데이터
		ComPtr<ID3D11Resource>			 m_Texture;
	};


	class TexMgr : public BaseManager<Texture, TexMgr>
	{
		friend class Singleton<TexMgr>;
	private:
		TexMgr() {}
	};

#define TEXTURE   TexMgr::Instance()
}
