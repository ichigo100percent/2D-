#pragma once
#include "Js_DxObject.h"

namespace Js
{
	class Actor : public DxObject
	{
	public:
		Actor(ComPtr<ID3D11Device> _device, ComPtr<ID3D11DeviceContext> _context, const std::wstring& _name = {});

		virtual void Update() override;
		virtual void Render() override;

		virtual Actor& Move(float _dx, float _dy, float _dz);
		virtual Actor& Move(Vector3 _direction);
		virtual void CreateGeometry(const RECT& _rect) override;
		virtual void CreateObject(const RECT& _rt, const std::wstring& _texName);


		virtual void SetPos(Vector3& _pos);
		virtual void SetPos(float& _dx, float& _dy);
		virtual void SetWorld(const Matrix& _mat);
		virtual void SetCenterMove(const Vector3& _pos);
		virtual void SetScale(const Vector3& _scale);
		virtual void SetRotate(float& _rotate);
		virtual void SetTranslate(const Vector3& _pos);

		virtual Actor& Transform(Matrix& _m);
		virtual Actor& Transform();

		Vector3	GetPosition() { return m_LocalPosition; }
		RECT GetRect() { return m_Rt; }

	protected:
		Vector3 m_LocalPosition = { 0.f, 0.f, 0.f };
		Vector3 m_LocalRotation = { 0.f, 0.f, 0.f };
		Vector3 m_LocalScale    = { 1.f, 1.f, 1.f };
		Vector3 m_Offset = { 0,0,0 };
		RECT						m_Rt = {};

	protected:
		Matrix		 m_MatWorld;        // c * s * r * t
		Matrix	     m_MatCenter;
		Matrix	     m_MatScale;
		Matrix	     m_MatRotate;
		Matrix	     m_MatTranslate;
	};
}
