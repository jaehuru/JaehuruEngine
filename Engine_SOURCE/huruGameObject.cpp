#include "huruGameObject.h"

namespace huru
{
	GameObject::GameObject(DirectionKeySet keySet, ShapeType shape) :
		mX(0.f),
		mY(0.f),
		mSpeed(0.01f),
		mKeySet(keySet),
		mColor(RGB(0, 0, 255)),
		mShape(shape)
	{

	}
	GameObject::~GameObject()
	{

	}

	void GameObject::Update()
	{
		switch (mKeySet)
		{
		case DirectionKeySet::Arrow:
			if (GetAsyncKeyState(VK_UP) & 0x8000)    mY -= mSpeed;
			if (GetAsyncKeyState(VK_DOWN) & 0x8000)  mY += mSpeed;
			if (GetAsyncKeyState(VK_LEFT) & 0x8000)  mX -= mSpeed;
			if (GetAsyncKeyState(VK_RIGHT) & 0x8000) mX += mSpeed;
			break;

		case DirectionKeySet::WASD:
			if (GetAsyncKeyState('W') & 0x8000) mY -= mSpeed;
			if (GetAsyncKeyState('S') & 0x8000) mY += mSpeed;
			if (GetAsyncKeyState('A') & 0x8000) mX -= mSpeed;
			if (GetAsyncKeyState('D') & 0x8000) mX += mSpeed;
			break;
		case DirectionKeySet::Auto:
			if (mIsAutoMove)
			{
				mX += mSpeed;

				if (mX >= 500)
					mSpeed = -mSpeed;
				else if (mX <= 0)
					mSpeed = -mSpeed;
			}
			break;
		}
	}

	void GameObject::LateUpdate()
	{

	}

	void GameObject::Render(HDC hdc)
	{
		// 색상에 맞는 브러시 생성
		HBRUSH brush = CreateSolidBrush(mColor);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);

		// 객체의 형태에 맞는 그리기
		switch (mShape)
		{
		case ShapeType::Rectangle:
			Rectangle(hdc, (int)(100 + mX), (int)(10 + mY), (int)(200 + mX), (int)(100 + mY));
			break;
		case ShapeType::Circle:
			Ellipse(hdc, (int)(100 + mX), (int)(10 + mY), (int)(200 + mX), (int)(100 + mY));
			break;
		case ShapeType::Rhombus:
			POINT points[4] = {
			{(int)(150 + mX), (int)(10 + mY)},
			{(int)(200 + mX), (int)(55 + mY)},   
			{(int)(150 + mX), (int)(100 + mY)}, 
			{(int)(100 + mX), (int)(55 + mY)}    
			};
			Polygon(hdc, points, 4);
			break;
		}

		// 이전 상태로 복원
		SelectObject(hdc, oldBrush);
		DeleteObject(brush);

	}
}