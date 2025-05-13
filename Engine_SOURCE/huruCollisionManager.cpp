#include "huruCollisionManager.h"
#include "huruScene.h"
#include "huruSceneManager.h"
#include "huruGameObject.h"
#include "huruCollider.h"
#include "huruTransform.h"

namespace huru
{
	std::bitset<(UINT)eLayerType::Max>CollisionManager::mCollisionLayerMatrix[(UINT)eLayerType::Max] = { };
	std::unordered_map<UINT64, bool> CollisionManager::mCollisionMap = { };

	CollisionManager::CollisionManager()
	{

	}

	CollisionManager::~CollisionManager()
	{

	}

	void CollisionManager::Initialize()
	{
		
	}

	void CollisionManager::Update()
	{
		Scene* scene = SceneManager::GetActiveScene();
		for (UINT row = 0; row < (UINT)eLayerType::Max; row++)
		{
			for (UINT col = 0; col < (UINT)eLayerType::Max; col++)
			{
				if (mCollisionLayerMatrix[row][col] == true)
				{
					LayerCollsion(scene, (eLayerType)row, (eLayerType)col);
				}
			}
		}
	}

	void CollisionManager::LateUpdate()
	{

	}

	void CollisionManager::Render(HDC hdc)
	{

	}

	void CollisionManager::CollisionLayerCheck(eLayerType left, 
												eLayerType right,
												bool enable)
	{
		int row = 0;
		int col = 0;

		if (left <= right)
		{
			row = (UINT)left;
			col = (UINT)right;
		}		  
		else	  
		{		 
			row = (UINT)right;
			col = (UINT)left;
		}

		mCollisionLayerMatrix[row][col] = enable;
	}

	void CollisionManager::LayerCollsion(Scene* scene, eLayerType left, eLayerType right)
	{
		const std::vector<GameObject*>& lefts = 
			scene->GetLayer(left)->GetGameObjects();
		const std::vector<GameObject*>& rights =
			scene->GetLayer(right)->GetGameObjects();

		for (GameObject* left : lefts)
		{
			if (left->IsActive() == false)
				continue;

			Collider* leftCol = left->GetComponent<Collider>();
			if (leftCol == nullptr)
				continue;
			
			for (GameObject* right : rights)
			{
				if (right->IsActive() == false)
					continue;

				Collider* rightCol = right->GetComponent<Collider>();
				if (rightCol == nullptr)
					continue;

				if (left == right)
					continue;

				ColliderCollision(leftCol, rightCol);
			}
		}
	}

	void CollisionManager::ColliderCollision(Collider* left, Collider* right)
	{
		// 두 충돌체 번호를 가져온 ID를 확인해서 CollisionID값을 세팅
		CollisionID cID = {};
		cID.left = left->GetID();
		cID.right = right->GetID();

		// 해당 id로 충돌체 정보를 검색
		// 만약 충돌체 정보가 없다면 충돌정보를 생성
		auto iter = mCollisionMap.find(cID.ID);
		if (iter == mCollisionMap.end())
		{
			mCollisionMap.insert(std::make_pair(cID.ID, false));
			iter = mCollisionMap.find(cID.ID);
		}

		// 충돌 체크
		if (Intersect(left, right))
		{
			// 최초 충돌
			if (iter->second == false)
			{
				left->OnCollisionEnter(right);
				right->OnCollisionEnter(left);
				iter->second = true;
			}
			// 이미 충돌 중
			else
			{
				left->OnCollisionStay(right);
				right->OnCollisionStay(left);
			}
		}
		else
		{
			// 충돌 후 벗어났을때
			if (iter->second == true)
			{
				left->OnCollisionExit(right);
				right->OnCollisionExit(left);
				iter->second = false;
			}
		}
	}

	bool CollisionManager::Intersect(Collider* left, Collider* right)
	{
		Transform* leftTr = left->GetOwner()->GetComponent<Transform>();
		Transform* rightTr = right->GetOwner()->GetComponent<Transform>();

		Vector2 leftPos = leftTr->GetPosition() + left->GetOffset();
		Vector2 rightPos = rightTr->GetPosition() + right->GetOffset();

		Vector2 leftSize = left->GetSize() * 100.0f;
		Vector2 rightSize = right->GetSize() * 100.0f;

		//AABB 충돌 구현
		if (fabs(leftPos.x - rightPos.x) < fabs(leftSize.x / 2.0f + rightSize.x / 2.0f)
			&& fabs(leftPos.y - rightPos.y) < fabs(leftSize.y / 2.0f + rightSize.y / 2.0f))
		{
			return true;
		}

		return false;
	}
}
