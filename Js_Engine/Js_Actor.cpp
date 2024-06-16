#include "Js_Actor.h"
#include "Js_Input.h"
#include "Js_Time.h"

namespace Js
{
	Actor::Actor(ComPtr<ID3D11Device> _device, ComPtr<ID3D11DeviceContext> _context, const std::wstring& _name)
		: DxObject(_device, _context, _name)
	{
	}
	void Actor::Update()
	{
		m_MatWorld = m_MatCenter * m_MatScale * m_MatRotate * m_MatTranslate;
		Transform(m_MatWorld);
		m_Offset = Vector3::Zero;
	}
	void Actor::Render()
	{
		DxObject::Render();
	}
	Actor& Actor::Move(float _dx, float _dy, float _dz)
	{
		Move(_dx, _dy, _dz);
		return *this;
	}
	Actor& Actor::Move(Vector3 _direction)
	{
		Vector3 offset = _direction * 100 * Time::DeltaTime();
		m_LocalPosition += offset;
		m_Offset += offset;

		SetTranslate(m_LocalPosition);
		m_Rt.left = m_List[1].position.x;
		m_Rt.right = m_List[2].position.x;
		m_Rt.top = m_List[1].position.y;
		m_Rt.bottom = m_List[0].position.y;

		return *this;
	}
	void Actor::CreateGeometry(const RECT& _rect)
	{
		DxObject::CreateGeometry(_rect);
		// 사각형의 센터를 포지션으로
		m_LocalPosition.x = (_rect.left + _rect.right) * 0.5f;
		m_LocalPosition.y = (_rect.bottom + _rect.top) * 0.5f;
		m_LocalPosition.z = 0;

		Vector3 Center = -m_LocalPosition;
		SetCenterMove(Center);
		SetTranslate(m_LocalPosition);
		m_Rt = _rect;
	}
	void Actor::CreateObject(const RECT& _rt, const std::wstring& _texName)
	{
		CreateGeometry(_rt);
		CreateVertexBuffer();
		CreateIndexBuffer();
		CreateVS();
		CreateInputLayout();
		CreatePS();

		CreateRasterizerState();
		CreateSRV(_texName);
	}
	void Actor::SetPos(Vector3& _pos)
	{
		m_LocalPosition = _pos;
		m_MatWorld._41 = m_LocalPosition.x;
		m_MatWorld._42 = m_LocalPosition.y;
		m_MatWorld._43 = m_LocalPosition.z;
	}
	void Actor::SetPos(float& _dx, float& _dy)
	{
		m_LocalPosition.x = _dx;
		m_LocalPosition.y = _dy;
	}
	void Actor::SetTransform(const Matrix& _mat)
	{
		for (int i = 0; i < m_Vertices.size(); ++i)
		{
			m_List[i].position = Vector3::Transform(m_List[i].position, _mat);
		}

		UpdateVertexBuffer();
	}
	void Actor::SetWorld(const Matrix& _m)
	{
		m_MatWorld = _m;
	}
	void Actor::SetCenterMove(const Vector3& _pos)
	{
		m_MatCenter = Matrix::CreateTranslation(_pos);
	}
	void Actor::SetScale(const Vector3& _scale)
	{
		m_MatScale = Matrix::CreateScale(_scale);
	}
	void Actor::SetRotate(float& _rotate)
	{
		// x -> y -> z 순서
		m_MatRotate = Matrix::CreateRotationZ(_rotate);
	}
	void Actor::SetTranslate(const Vector3& _pos)
	{
		m_MatTranslate = Matrix::CreateTranslation(_pos);		
	}
	Actor& Actor::Transform(Matrix& _m)
	{
		for (int i = 0; i < m_Vertices.size(); i++)
		{
			m_List[i].position = Vector3::Transform(m_Vertices[i].position, _m);
		}
		UpdateVertexBuffer();
		return *this;
	}
	Actor& Actor::Transform()
	{
		for (int i = 0; i < m_Vertices.size(); i++)
		{
			m_List[i].position = Vector3::Transform(m_Vertices[i].position, m_MatWorld);
		}
		UpdateVertexBuffer();

		return *this;
	}
}