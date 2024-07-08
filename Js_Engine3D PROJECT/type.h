#pragma once

using Color	  = DirectX::XMFLOAT4;
using Vector2 = DirectX::SimpleMath::Vector2;
using Vector3 = DirectX::SimpleMath::Vector3;
using Vector4 = DirectX::SimpleMath::Vector4;
using Matrix  = DirectX::SimpleMath::Matrix;
using DXRect =  DirectX::SimpleMath::Rectangle;
using Quaternion = DirectX::SimpleMath::Quaternion;

static std::wstring to_mw(const std::string& _src)
{
	USES_CONVERSION;
	return std::wstring(A2W(_src.c_str()));
};

static std::string to_wm(const std::wstring& _src)
{
	USES_CONVERSION;
	return std::string(W2A(_src.c_str()));
};


namespace Js::enums
{
	enum class LayerType
	{
		None,
		Player,
		Floor,
		Tower,
		Wall,
		ItemWall,
		WallEnd, // º® ³¡
		MunshRoom,
		Flower,
		Fireball,
		Monster,
		Flag,
		EndPoint,
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
	End,
};
