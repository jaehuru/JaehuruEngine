#include "huruGameObject.h"
#include "huruInput.h"
#include "huruTime.h"

namespace huru
{
	GameObject::GameObject() :
		mX(0.f),
		mY(0.f)
	{

	}
	GameObject::~GameObject()
	{

	}

	void GameObject::Update()
	{
		const int speed = 100.f;
		if (Input::GetKey(eKeyCode::W))
			mY -= speed * Time::DeltaTime();
		if (Input::GetKey(eKeyCode::S))
			mY += speed * Time::DeltaTime();
		if (Input::GetKey(eKeyCode::A))
			mX -= speed * Time::DeltaTime();
		if (Input::GetKey(eKeyCode::D))
			mX += speed * Time::DeltaTime();
	}

	void GameObject::LateUpdate()
	{

	}

	void GameObject::Render(HDC hdc)
	{
		// ·»´õ¸µ ÄÚµå
		HBRUSH blueBrush = CreateSolidBrush(RGB(0, 0, 255));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, blueBrush);

		HPEN redPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		HPEN oldPen = (HPEN)SelectObject(hdc, redPen);
		SelectObject(hdc, oldPen);

		Ellipse(hdc, 20 + mX, 30 + mY, 100 + mX, 100 + mY);

		SelectObject(hdc, oldBrush);
		DeleteObject(blueBrush);
		DeleteObject(redPen);
	}
}