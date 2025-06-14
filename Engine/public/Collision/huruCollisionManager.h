#pragma once

#include "Common/CommonInclude.h"
#include "Component/Collider/huruBoxCollider2D.h"
#include "Component/Collider/huruCircleCollider2D.h"

namespace huru
{
	class Scene;

	union CollisionID
	{
		struct
		{
			UINT32 left;
			UINT32 right;
		};

		UINT64 ID;
	};

	class CollisionManager
	{
	public:
		CollisionManager();
		~CollisionManager();

		static void				Initialize();
		static void				Update();
		static void				LateUpdate();
		static void				Render(HDC hdc);
		static void				Clear();

		static void				CollisionLayerCheck(enums::eLayerType left,
													enums::eLayerType right,
													bool enable);
		static void				LayerCollsion(Scene* scene, enums::eLayerType left, enums::eLayerType right);
		static void				ColliderCollision(Collider* left, Collider* right);
		static bool				Intersect(Collider* left, Collider* right);

		static math::Vector2	CalculateCollisionDepth(Collider* left, Collider* right);
		static bool				CheckCollisionWithDepth(Collider* left, Collider* right, math::Vector2& outDepth);

		static bool				IntersectRectRect(Collider* left, Collider* right);
		static bool				IntersectCircleCircle(Collider* left, Collider* right);
		static bool				IntersectCircleRect(Collider* circle, Collider* rect);

	private:
		static std::bitset<(UINT)enums::eLayerType::Max>mCollisionLayerMatrix[(UINT)enums::eLayerType::Max];
		static std::unordered_map<UINT64, bool> mCollisionMap;
	};
}

