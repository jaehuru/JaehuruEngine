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
		// ���� ������Ʈ�� ��ǥ
		float		mSpeed;

		float		mX;
		float		mY;
	};
}

