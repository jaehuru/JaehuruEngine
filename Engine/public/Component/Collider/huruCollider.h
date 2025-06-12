#pragma once

#include "Component/huruComponent.h"

namespace huru
{
	class Collider : public Component
	{

	public:
		Collider(enums::eColliderType type);
		~Collider();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		math::Vector2 GetOffset() { return mOffset; }
		void SetOffset(math::Vector2 offset) { mOffset = offset; }

		UINT32 GetID() { return mID; }

		math::Vector2 GetSize() { return mSize; }
		void SetSize(math::Vector2 size) { mSize = size; }

		enums::eColliderType GetColliderType() { return mType; }

	private:
		static UINT32 mCollisionID;
		UINT mID;
		math::Vector2 mOffset;
		math::Vector2 mSize;

		enums::eColliderType mType;
	};
}

