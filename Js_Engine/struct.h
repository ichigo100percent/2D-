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
	Vector2 position;
	Vector4 color;
	Vector2 texture;

	VertexData() = default;
	VertexData(Vector2 _pos, Vector4 _col, Vector2 _tex) : position(_pos), color(_col), texture(_tex) {}
};

struct ConstantBuffer
{
	DirectX::SimpleMath::Matrix worldMatrix;
};

struct TransformData
{
	Vector3 transform;
	float dummy;
};