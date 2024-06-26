#pragma once

class BaseCore
{
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;
};

struct VertexData
{
	Vector3 position;
	Vector4 color;
	Vector2 texture;

	VertexData() = default;
	VertexData(Vector3 _pos, Vector4 _col, Vector2 _tex) : position(_pos), color(_col), texture(_tex) {}
};

struct ConstantBuffer
{
	Matrix mView;
	Matrix mProjection;
	Matrix mWorld;
};

struct TransformData
{
	Vector3 transform;
	float dummy;
};

struct JsRect
{
	float x, y, w, h;
	JsRect() = default;
	JsRect(float _x, float _y, float _w, float _h)
		: x(_x), y(_y), w(_w), h(_h) {}
};