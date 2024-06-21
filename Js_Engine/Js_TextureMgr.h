#pragma once
#include "Js_BaseMgr.h"

namespace Js
{
	class Texture : public Resource
	{
	public:
		void Set(ComPtr<ID3D11Device> _device) { m_Device = _device; }
		void Release() override;
		bool Load(const std::wstring& _fileName) override;

		Vector2 GetSize() { return m_Size; }

	public:
		std::wstring m_csName;
		ComPtr<ID3D11Device> m_Device;
		// ShaderResourceView
		// 렌더링 파이브라인(픽셀쉐이더)에 전송 데이터
		ComPtr<ID3D11ShaderResourceView> m_ShaderResourceView;
		// 텍스처(이미지) 로드 데이터
		ComPtr<ID3D11Resource>			 m_Texture;
		D3D11_TEXTURE2D_DESC td;
		Vector2 m_Size;
	};


	class TextureMgr : public BaseManager<Texture, TextureMgr>
	{
		friend class Singleton<TextureMgr>;
	private:
		TextureMgr() {}
	};

#define TEXTURE   TextureMgr::Instance()
}
