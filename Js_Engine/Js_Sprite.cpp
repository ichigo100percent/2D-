#include "Js_Sprite.h"
#include "Js_Time.h"

namespace Js
{
	void Sprite::Update()
	{
		m_SpriteData.PlayTimer += Time::DeltaTime();
		if (m_SpriteData.PlayTimer > m_SpriteData.ChangeTime)
		{
			m_SpriteData.Index++;
			m_SpriteData.PlayTimer -= m_SpriteData.ChangeTime;
			if (m_SpriteData.Index >= m_SpriteData.Length)
			{
				m_SpriteData.Index = 0;
			}
		}
		if (m_uvList.size() > 0)
		{
			float left = m_uvList[m_SpriteData.Index].left;
			float right = m_uvList[m_SpriteData.Index].right;
			float top = m_uvList[m_SpriteData.Index].top;
			float bottom = m_uvList[m_SpriteData.Index].bottom;

			m_List[0].texture = Vector2(left, bottom);
			m_List[1].texture = Vector2(left, top);
			m_List[2].texture = Vector2(right, bottom);
			m_List[3].texture = Vector2(right, top);
		}
	}
	void Sprite::SetAnim(float _animationTimer)
	{
		m_SpriteData.Index = 0;
		m_SpriteData.AnimationTimer = _animationTimer;
		m_SpriteData.ChangeTime = m_SpriteData.AnimationTimer / static_cast<float>(m_SpriteData.Length);
	}
	ComPtr<ID3D11ShaderResourceView> Sprite::GetSRV()
	{
		if (m_SRVList.size() > m_SpriteData.Index)
		{
			return m_SRVList[m_SpriteData.Index];
		}
		return m_Texure->m_ShaderResourceView;
	}
	ComPtr<ID3D11ShaderResourceView> Sprite::GetSRV(UINT _index)
	{
		return ComPtr<ID3D11ShaderResourceView>();
	}
	void Sprite::Load(std::wstring* _pathList, UINT _size)
	{
	}
	void Sprite::Load(std::wstring _path, Vector2 _offset, Vector2 _size, UINT _length, bool _isLoop)
	{
		m_Texure = TEXTURE.Load(_path);
		m_SpriteData.Length = _length;

		UINT width = m_Texure->GetSize().x;
		UINT height = m_Texure->GetSize().y;

		for (UINT i = 0; i < m_SpriteData.Length; i++)
		{
			RECT rt;
			rt.left = _offset.x + _size.x * i;
			rt.right = rt.left + _size.x;
			rt.top = _offset.y;
			rt.bottom = rt.top + _size.y;
			m_rtList.push_back(rt);
			
			myRECT uvRt;
			uvRt.left = (float)rt.left / (float)width;
			uvRt.right = (float)rt.right / (float)width;
			uvRt.top = (float)rt.top / (float)height;
			uvRt.bottom = (float)rt.bottom / (float)height;
			m_uvList.push_back(uvRt);
		}
		m_List.resize(4);
	}
}