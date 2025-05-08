#pragma once

#include "huruGameObject.h"

namespace huru
{
	class Bullet : public GameObject
	{
	public:
		Bullet(float x, float y);

		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		bool IsDead()
		{
			return GetPositionY() < -20.f;
		}

	private:
		float mSpeed = 300.f;
	};
}
