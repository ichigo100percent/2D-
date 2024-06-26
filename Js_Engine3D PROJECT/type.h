#pragma once

using Color	  = DirectX::XMFLOAT4;
using Vector2 = DirectX::SimpleMath::Vector2;
using Vector3 = DirectX::SimpleMath::Vector3;
using Vector4 = DirectX::SimpleMath::Vector4;
using Matrix  = DirectX::SimpleMath::Matrix;
using DXRect =  DirectX::SimpleMath::Rectangle;
using Quaternion = DirectX::SimpleMath::Quaternion;

enum class eLayerType
{
	None,
	BackGround,
	Tile,
	Npc,
	Player,
	Monster,
	Item,
	Floor,
	Particle,
	DeadLine,
	//
	Max = 16,
};