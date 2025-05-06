#include "huruGameObject.h"
#include "huruInput.h"

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
		if (Input::GetKey(eKeyCode::Up))
			mY -= mSpeed;
		if (Input::GetKey(eKeyCode::Down))
			mY += mSpeed;
		if (Input::GetKey(eKeyCode::A))
			mX -= mSpeed;
		if (Input::GetKey(eKeyCode::D))
			mX += mSpeed;
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

		Rectangle(hdc, 100 + mX, 10 + mY, 200 + mX, 100 + mY);

		SelectObject(hdc, oldBrush);
		DeleteObject(blueBrush);
		DeleteObject(redPen);
	}
}