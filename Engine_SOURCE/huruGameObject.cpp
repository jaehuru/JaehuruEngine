#include "huruGameObject.h"
#include "huruInput.h"
#include "huruTime.h"
#include "Bullet.h"

namespace huru
{
	std::vector<GameObject*> gGameObjects;

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
		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			float bulletX = mX + 150.f;
			float bulletY = mY + 10;

			gGameObjects.push_back(new Bullet(bulletX, bulletY));
		}
	}

	void GameObject::LateUpdate()
	{
		for (int i = 0; i < gGameObjects.size(); )
		{
			Bullet* bullet = dynamic_cast<Bullet*>(gGameObjects[i]);
			if (bullet && bullet->IsDead())
			{
				delete bullet;
				gGameObjects.erase(gGameObjects.begin() + i);
			}
			else
			{
				++i;
			}
		}
	}

	void GameObject::Render(HDC hdc)
	{
		// ·»´õ¸µ ÄÚµå
		HBRUSH blueBrush = CreateSolidBrush(RGB(0, 0, 255));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, blueBrush);

		HPEN redPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		HPEN oldPen = (HPEN)SelectObject(hdc, redPen);
		SelectObject(hdc, oldPen);

		Rectangle(hdc, 100 + (int)mX, 10 + (int)mY, 200 + (int)mX, 100 + (int)mY);

		SelectObject(hdc, oldBrush);
		DeleteObject(blueBrush);
		DeleteObject(redPen);

		for (GameObject* obj : gGameObjects)
		{
			obj->Render(hdc);
		}
	}
}