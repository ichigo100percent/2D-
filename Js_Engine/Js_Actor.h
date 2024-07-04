#pragma once
#include "Js_DxObject.h"
#include "Js_Sprite.h"
namespace Js
{	
	//class Sprite {};


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


		void SetSprite(std::shared_ptr<Sprite> _sprite) { m_Sprite = _sprite; }
		virtual void SetPos(Vector3& _pos);
		virtual void SetPos(const float& _dx, const float& _dy);
		void SetTransform(const Matrix& _mat);

		virtual void SetWorld(const Matrix& _mat);
		virtual void SetCenterMove(const Vector3& _pos);
		virtual void SetScale(const Vector3& _scale);
		virtual void SetRotate(float _rotate);
		virtual void SetTranslate(const Vector3& _pos);

		virtual Actor& Transform(Matrix& _m);
		virtual Actor& Transform();

		Vector3	GetPosition() { return m_LocalPosition; }
		RECT GetRect() { return m_Rt; }
		Vector3 GetOffset() { return m_Offset; }
		void SetActive(const bool& _active) { m_Active = _active; }
		bool GetActive() { return m_Active; }
	protected:
		std::shared_ptr<Sprite> m_Sprite;
		Vector3 m_LocalPosition = { 0.f, 0.f, 0.f };
		Vector3 m_LocalRotation = { 0.f, 0.f, 0.f };
		Vector3 m_LocalScale    = { 1.f, 1.f, 1.f };
		Vector3 m_Offset = { 0,0,0 };
		RECT    m_Rt = {};
		bool    m_Active = true;
	protected:
		Matrix		 m_MatWorld;        // c * s * r * t
		Matrix	     m_MatCenter;
		Matrix	     m_MatScale;
		Matrix	     m_MatRotate;
		Matrix	     m_MatTranslate;
	};
}
