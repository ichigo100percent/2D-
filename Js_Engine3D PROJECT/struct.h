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
	Matrix matWorld = Matrix::Identity;
};


struct CameraData
{
	Matrix matView = Matrix::Identity;
	Matrix matProjection = Matrix::Identity;
};

struct AnimationData
{
	Vector2 spriteOffset;
	Vector2 spriteSize;
	Vector2 textureSize;
	float   useAnimation;
	float   padding;
};

struct MyRect
{
	float   left;
	float   top;
	float   right;
	float   bottom;
};