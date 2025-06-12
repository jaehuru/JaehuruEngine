#pragma once

#include "Component/huruComponent.h"

namespace huru
{
	class Transform : public Component
	{
	public:
		Transform();
		~Transform();

		void		Initialize() override;
		void		Update()  override;
		void		LateUpdate()  override;
		void		Render(HDC hdc)  override;

		void SetPosition(math::Vector2 pos) { mPosition.x = pos.x; mPosition.y = pos.y; }
		math::Vector2 GetPosition() { return mPosition; }
		math::Vector2 GetScale() { return mScale; }
		float GetRotation() { return mRotation; }
		void SetRotation(float rotate) { mRotation = rotate; }
		void SetScale(math::Vector2 scale) { mScale = scale; }

	private:
		math::Vector2			mPosition;
		math::Vector2			mScale;
		float			mRotation;
	};
}