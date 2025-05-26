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

	void CollisionManager::Clear()
	{
		mCollisionMap.clear();
		mCollisionLayerMatrix->reset();
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
		const std::vector<GameObject*>& lefts = SceneManager::GetGameObjects(left);
		const std::vector<GameObject*>& rights = SceneManager::GetGameObjects(right);

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
		// �� �浹ü ��ȣ�� ������ ID�� Ȯ���ؼ� CollisionID���� ����
		CollisionID cID = {};
		cID.left = left->GetID();
		cID.right = right->GetID();

		// �ش� id�� �浹ü ������ �˻�
		// ���� �浹ü ������ ���ٸ� �浹������ ����
		auto iter = mCollisionMap.find(cID.ID);
		if (iter == mCollisionMap.end())
		{
			mCollisionMap.insert(std::make_pair(cID.ID, false));
			iter = mCollisionMap.find(cID.ID);
		}

		// �浹 üũ
		if (Intersect(left, right))
		{
			// ���� �浹
			if (iter->second == false)
			{
				left->OnCollisionEnter(right);
				right->OnCollisionEnter(left);
				iter->second = true;
			}
			// �̹� �浹 ��
			else
			{
				left->OnCollisionStay(right);
				right->OnCollisionStay(left);
			}
		}
		else
		{
			// �浹 �� �������
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

		eColliderType leftType = left->GetColliderType();
		eColliderType rightType = right->GetColliderType();

		// AABB(Axis-Aligned Bounding Box) rect - rect
		if (leftType == eColliderType::Rect2D
			&& rightType == eColliderType::Rect2D)
		{
			if (fabs(leftPos.x - rightPos.x) < fabs(leftSize.x / 2.0f + rightSize.x / 2.0f)
				&& fabs(leftPos.y - rightPos.y) < fabs(leftSize.y / 2.0f + rightSize.y / 2.0f))
			{
				return true;
			}
		}

		//circle -circle
		if (leftType == eColliderType::Circle2D
			&& rightType == eColliderType::Circle2D)
		{
			Vector2 leftCirclePos = leftPos + (leftSize / 2.0f);
			Vector2 rightCirclePos = rightPos + (rightSize / 2.0f);
			float distance = (leftCirclePos - rightCirclePos).length();
			if (distance <= (leftSize.x / 2.0f + rightSize.x / 2.0f))
			{
				return true;
			}
		}

		// circle - rect
		if ((leftType == eColliderType::Circle2D && rightType == eColliderType::Rect2D)
			|| (leftType == eColliderType::Rect2D && rightType == eColliderType::Circle2D))
		{
			// Circle�� ���ʿ� ������ ����
			Collider* circle = (leftType == eColliderType::Circle2D) ? left : right;
			Collider* rect = (leftType == eColliderType::Rect2D) ? left : right;

			Vector2 circlePos = circle->GetOwner()->GetComponent<Transform>()->GetPosition() + circle->GetOffset();
			Vector2 circleSize = circle->GetSize() * 100.0f;
			Vector2 circleCenter = circlePos + (circleSize / 2.0f);
			float circleRadius = circleSize.x / 2.0f;

			Vector2 rectPos = rect->GetOwner()->GetComponent<Transform>()->GetPosition() + rect->GetOffset();
			Vector2 rectSize = rect->GetSize() * 100.0f;
			Vector2 rectHalf = rectSize / 2.0f;
			Vector2 rectCenter = rectPos + rectHalf;

			// �簢�� ���ο��� ���� ����� �� ���
			Vector2 closestPoint;
			closestPoint.x = max(rectCenter.x - rectHalf.x, min(circleCenter.x, rectCenter.x + rectHalf.x));
			closestPoint.y = max(rectCenter.y - rectHalf.y, min(circleCenter.y, rectCenter.y + rectHalf.y));


			// �Ÿ� ��
			float distance = (circleCenter - closestPoint).length();
			if (distance <= circleRadius)
			{
				return true;
			}
		}

		return false;
	}
}
