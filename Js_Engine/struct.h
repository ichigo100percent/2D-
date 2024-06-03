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