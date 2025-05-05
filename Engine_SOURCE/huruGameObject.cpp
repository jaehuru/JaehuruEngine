#include "huruGameObject.h"

namespace huru
{
	GameObject::GameObject() :
		mX(0.f),
		mY(0.f),
		mSpeed(0.01f)
	{

	}
	GameObject::~GameObject()
	{

	}

	void GameObject::Update()
	{
		if (GetAsyncKeyState(VK_UP) & 0x8000)
			mY -= mSpeed;
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
			mY += mSpeed;
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
			mX -= mSpeed;
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
			mX += mSpeed;
	}

	void GameObject::LateUpdate()
	{

	}

	void GameObject::Render(HDC hdc)
	{
		// 렌더링 코드
		HBRUSH blueBrush = CreateSolidBrush(RGB(0, 0, 255));      // 파랑색 브러시 생성
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, blueBrush);     // SelectObject함수는 이전에 사용하던 브러쉬를 반환

		HPEN redPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		HPEN oldPen = (HPEN)SelectObject(hdc, redPen);
		SelectObject(hdc, oldPen);

		Rectangle(hdc, 100 + mX, 10 + mY, 200 + mX, 100 + mY);

		SelectObject(hdc, oldBrush);
		DeleteObject(blueBrush);
		DeleteObject(redPen);
	}
}