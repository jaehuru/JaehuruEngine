#include "huruApplication.h"

namespace huru
{

	Application::Application() : 
		mHwnd(nullptr),
		mHdc(nullptr),
		mSpeed(0.f),
		mX(0.f),
		mY(0.f)
	{

	}

	Application::~Application()
	{
		
	}

	void Application::Initalize(HWND hwnd)
	{
		// 초기화 코드
		mHwnd = hwnd;
		mHdc = GetDC(hwnd); // 윈도우 핸들로부터 DC를 가져옴
	}

	void Application::Run()
	{
		Update();
		LateUpdate();
		Render();
	}

	void Application::Update()
	{
		mSpeed = 0.01f;

		if (GetAsyncKeyState(VK_UP) & 0x8000)
			mY -= mSpeed;
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
			mY += mSpeed;
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
			mX -= mSpeed;
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
			mX += mSpeed;
	}

	void Application::LateUpdate()
	{
		// 후처리 업데이트 코드
	}

	void Application::Render()
	{
		// 렌더링 코드
		HBRUSH blueBrush = CreateSolidBrush(RGB(0, 0, 255));      // 파랑색 브러시 생성
		HBRUSH oldBrush = (HBRUSH)SelectObject(mHdc, blueBrush);     // SelectObject함수는 이전에 사용하던 브러쉬를 반환

		HPEN redPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		HPEN oldPen = (HPEN)SelectObject(mHdc, redPen);
		SelectObject(mHdc, oldPen);

		Rectangle(mHdc, 100 + mX, 10 + mY, 200 + mX, 100 + mY);

		SelectObject(mHdc, oldBrush);
		DeleteObject(blueBrush);
		DeleteObject(redPen);
	}
}