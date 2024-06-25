#pragma once
#include "Js_TextureMgr.h"

namespace Js
{
	struct myRECT
	{
		float    left;
		float    top;
		float    right;
		float    bottom;
	};

	struct SpriteData
	{
		UINT    Index = 0;
		UINT    Length = 0;
		float	PlayTimer = 0.0f;
		float	AnimationTimer = 0.0f;
		float	ChangeTime = 0.0f;
	};

	class Sprite
	{
	public:
		void   Update();

		void   SetTexture(std::shared_ptr<Texture> _texure) { m_Texure = _texure; }
		void   SetAnim(float _animationTimer);
		ComPtr<ID3D11ShaderResourceView> GetSRV();
		ComPtr<ID3D11ShaderResourceView> GetSRV(UINT _index);

		void  Load(std::wstring* _pathList, UINT _size);
		// file, 시작위치, 넓이, 몇번,
		void  Load(std::wstring _path, Vector2 _offset, Vector2 _size, UINT _length, bool _isLoop = false);

	public:
		std::vector<VertexData>  m_List;		 // 프레임 화면 정보
		std::shared_ptr<Texture> m_Texure;
		SpriteData m_SpriteData = {};
		std::vector<ComPtr<ID3D11ShaderResourceView>> m_SRVList;
		std::vector<RECT> m_rtList;
		std::vector<myRECT> m_uvList;
	};
}
