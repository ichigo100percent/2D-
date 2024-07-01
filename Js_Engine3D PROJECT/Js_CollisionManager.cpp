#include "Js_CollisionManager.h"
#include "Js_SceneManager.h"
#include "Js_DxObject.h"
#include "Js_Transform.h"

namespace Js
{
	std::bitset<(UINT)LayerType::Max> CollisionManager::m_CollisionLayerMatrix[(UINT)LayerType::Max] = {};
	std::unordered_map<UINT64, bool> CollisionManager::m_CollisionMap = {};

	void CollisionManager::Init()
	{
	}
	void CollisionManager::Update()
	{
		std::shared_ptr<Scene> scene = SceneManager::GetActiveScene();

		for (UINT row = 0; row < (UINT)LayerType::Max; row++)
		{
			for (UINT col = 0; col < (UINT)LayerType::Max; col++)
			{
				if (m_CollisionLayerMatrix[row][col] == true)
				{
					LayerCollision(scene, (LayerType)row, (LayerType)col);
				}
			}
		}
	}
	void CollisionManager::LateUpdate()
	{
	}
	void CollisionManager::Clear()
	{
		m_CollisionMap.clear();
		m_CollisionLayerMatrix->reset();
	}
	void CollisionManager::CollisionLayerCheck(LayerType _left, LayerType _right, bool enable)
	{
		int row = 0;
		int col = 0;
		if (_left <= _right)
		{
			row = (UINT)_left;
			col = (UINT)_right;
		}
		else
		{
			row = (UINT)_right;
			col = (UINT)_left;
		}
		m_CollisionLayerMatrix[row][col] = enable;
	}
	void CollisionManager::LayerCollision(std::shared_ptr<Scene> _scene, LayerType _left, LayerType _right)
	{
		const std::vector<std::shared_ptr<DxObject>>& lefts = SceneManager::GetLayerGameObjects(_left);
		const std::vector<std::shared_ptr<DxObject>>& rights = SceneManager::GetLayerGameObjects(_right);

		for (auto& left : lefts)
		{
			if (left->IsActive() == false)
				continue;
			std::shared_ptr<Collider> leftCol = left->GetComponent<Collider>();
			if (leftCol == nullptr)
				continue;

			for (auto& right : rights)
			{
				if (right->IsActive() == false)
					continue;
				auto rightCol = right->GetComponent<Collider>();
				if (rightCol == nullptr)
					continue;
				if (left == right)
					continue;

				ColliderCollision(leftCol, rightCol);
			}
		}

	}
	void CollisionManager::ColliderCollision(std::shared_ptr<Collider> _left, std::shared_ptr<Collider> _right)
	{
		//두 충돌체 번호로 가져온 ID 확인하여 CollisonID 세팅
		CollisionID id = {};
		id.left = _left->GetID();
		id.right = _right->GetID();

		//이전 충돌 정보를 검색한다
		//만약에 충돌정보가 없는 상태라면
		//충돌정보를 생성해준다
		auto iter = m_CollisionMap.find(id.id);
		if (iter == m_CollisionMap.end())
		{
			m_CollisionMap.insert(std::make_pair(id.id, false));
			iter = m_CollisionMap.find(id.id);
		}

		//충돌체크를 해준다
		if (Intersect(_left, _right))
		{
			//최초 충돌
			if (iter->second == false)
			{
				_left->OnCollisionEnter(_right);
				_right->OnCollisionEnter(_left);
				iter->second = true;
			}
			else //이미 충돌 중
			{
				_left->OnCollisionStay(_right);
				_right->OnCollisionStay(_left);
			}
		}
		else
		{
			//충돌을 하지 않는 상태
			if (iter->second == true)
			{
				_left->OnCollisionExit(_right);
				_right->OnCollisionExit(_left);
				iter->second = false;
			}
		}
	}
	bool CollisionManager::Intersect(std::shared_ptr<Collider> _left, std::shared_ptr<Collider> _right)
	{
		
		std::shared_ptr<Transform> leftTr = _left->GetOwner()->GetTransform();
		std::shared_ptr<Transform> rightTr = _right->GetOwner()->GetTransform();

		auto leftRt = leftTr->GetRect();
		auto rightRt = rightTr->GetRect();

		// 두 사각형이 충돌하는지 확인
		if (leftRt.left   <   rightRt.right &&
			leftRt.right  >   rightRt.left &&
			leftRt.top > rightRt.bottom &&
			leftRt.bottom < rightRt.top)
		{
			return true;
		}
		return false;

	}
}