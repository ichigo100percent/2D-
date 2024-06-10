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
	Vector2 uv;

	VertexData() = default;
	VertexData(Vector3 _pos, Vector2 _tex) : position(_pos), uv(_tex) {}
};

struct TransformData
{
	Vector3 offset;
	float dummy = 0;
};

struct JsRect
{
	float x, y, w, h;
	JsRect() = default;
	JsRect(float _x, float _y, float _w, float _h)
		: x(_x), y(_y), w(_w), h(_h) {}
};