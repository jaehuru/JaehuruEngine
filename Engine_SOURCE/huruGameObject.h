#pragma once

#include "CommonInclude.h"

namespace huru
{
	class GameObject
	{
	public:
		GameObject();
		~GameObject();

		void	Update();
		void	LateUpdate();
		void	Render(HDC hdc);

		void	SetPosition(float x, float y)
		{
			mX = x;
			mY = y;
		}

		float	GetPositionX() { return mX; }
		float	GetPositionY() { return mY; }

	private:
		// 게임 오브젝트의 좌표
		float		mSpeed;

		float		mX;
		float		mY;
	};
}

