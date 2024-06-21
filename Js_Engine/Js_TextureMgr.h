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

	public:
		std::wstring m_csName;
		ComPtr<ID3D11Device> m_Device;
		// ShaderResourceView
		// ������ ���̺����(�ȼ����̴�)�� ���� ������
		ComPtr<ID3D11ShaderResourceView> m_ShaderResourceView;
		// �ؽ�ó(�̹���) �ε� ������
		ComPtr<ID3D11Resource>			 m_Texture;
	};


	class TextureMgr : public BaseManager<Texture, TextureMgr>
	{
		friend class Singleton<TextureMgr>;
	private:
		TextureMgr() {}
	};

#define TEXTURE   TextureMgr::Instance()
}
