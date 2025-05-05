#pragma once

#include "CommonInclude.h"

enum class DirectionKeySet
{
	Arrow, // 방향키
	WASD,  // W, A, S, D
	Auto // 자동으로 움직임
};

enum class ShapeType
{
	Rectangle,
	Circle,
	Rhombus
};

namespace huru
{
	class GameObject
	{
	public:
		GameObject(DirectionKeySet keySet = DirectionKeySet::Arrow, ShapeType shape = ShapeType::Rectangle);
		~GameObject();

		void Update();
		void LateUpdate();
		void Render(HDC hdc);

		void SetPosition(float x, float y)
		{
			mX = x;
			mY = y;
		}

		void SetKeySet(DirectionKeySet keySet)
		{
			mKeySet = keySet;
		}

		void SetColor(COLORREF color)
		{
			mColor = color;
		}

		void SetShape(ShapeType shape)
		{
			mShape = shape;
		}

		void SetAutoMove(bool isAutoMove)
		{
			mIsAutoMove = isAutoMove;
		}

	private:
		// 게임 오브젝트의 좌표
		float mSpeed;

		float mX;
		float mY;

		DirectionKeySet mKeySet;
		COLORREF mColor; 
		ShapeType mShape;
		bool mIsAutoMove = false; // 자동으로 움직이는지 여부
	};
}

