#pragma once

#include "Component/huruComponent.h"

namespace huru
{
	class Camera : public Component
	{
	public:
		math::Vector2 CalculatePosition(math::Vector2 pos) { return pos - mDistance; }
		math::Vector2 CalcuateTilePosition(math::Vector2 pos) { return pos + mDistance; };

		Camera();
		~Camera();

		void		Initialize() override;
		void		Update() override;
		void		LateUpdate() override;
		void		Render(HDC hdc) override;

		void SetTarget(GameObject* target) { mTarget = target; }

	private:
		class GameObject* mTarget;

		math::Vector2 mDistance;
		math::Vector2 mResolution;
		math::Vector2 mLookPosition;
	};
}

