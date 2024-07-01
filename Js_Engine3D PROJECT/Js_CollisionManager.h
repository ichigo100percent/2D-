#pragma once
#include "Js_Scene.h"
#include "Js_Collider.h"

namespace Js
{
	using namespace enums;

	union CollisionID
	{
		struct
		{
			UINT32 left;
			UINT32 right;
		};

		UINT64 id;
	};

	class CollisionManager
	{
	public:
		static void Init();
		static void Update();
		static void LateUpdate();
		static void Clear();

		static void CollisionLayerCheck(LayerType _left, LayerType _right, bool enable);
		static void LayerCollision(std::shared_ptr<Scene> _scene, LayerType _left, LayerType _right);
		static void ColliderCollision(std::shared_ptr<Collider> _left, std::shared_ptr<Collider> _right);
		static bool Intersect(std::shared_ptr<Collider> _left, std::shared_ptr<Collider> _right);

	private:
		static std::bitset<(UINT)LayerType::Max> m_CollisionLayerMatrix[(UINT)LayerType::Max];
		static std::unordered_map<UINT64, bool> m_CollisionMap;
	};
}