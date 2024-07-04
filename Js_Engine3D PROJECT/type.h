#pragma once

using Color	  = DirectX::XMFLOAT4;
using Vector2 = DirectX::SimpleMath::Vector2;
using Vector3 = DirectX::SimpleMath::Vector3;
using Vector4 = DirectX::SimpleMath::Vector4;
using Matrix  = DirectX::SimpleMath::Matrix;
using DXRect =  DirectX::SimpleMath::Rectangle;
using Quaternion = DirectX::SimpleMath::Quaternion;


namespace Js::enums
{
	enum class LayerType
	{
		None,
		Player,
		Floor,
		Tower,
		Wall,
		MunshRoom,
		Flower,
		Monster,
		End,
		Max,
	};
}


enum class ColliderType
{
	Circle2D,
	Rect2D,
	End,
};

enum class State
{
	Idle,
	Jump,
	Move,
	Die,
	End,
};

enum class MarioType
{
	Nomal,
	Super,
	Fire,
};
