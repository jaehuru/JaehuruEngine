// Bullet.cpp
#include "Bullet.h"
#include "huruTime.h"

namespace huru
{
	Bullet::Bullet(float x, float y)
	{
		SetPosition(x, y); // 부모 클래스 GameObject의 mX, mY 설정
	}

	void Bullet::Update()
	{
		float deltaY = mSpeed * Time::DeltaTime();
		float currentY = GetPositionY(); // 현재 Y 값 가져오기
		SetPosition(GetPositionX(), currentY - deltaY);
	}

	void Bullet::Render(HDC hdc)
	{
		HBRUSH brush = CreateSolidBrush(RGB(255, 255, 0));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);

		float x = GetPositionX();
		float y = GetPositionY();
		Ellipse(hdc, (int)x, (int)y, (int)x + 10, (int)y + 10);

		SelectObject(hdc, oldBrush);
		DeleteObject(brush);
	}
}
