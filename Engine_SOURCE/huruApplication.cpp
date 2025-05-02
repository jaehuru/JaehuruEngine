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
		// �ʱ�ȭ �ڵ�
		mHwnd = hwnd;
		mHdc = GetDC(hwnd); // ������ �ڵ�κ��� DC�� ������
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
		// ��ó�� ������Ʈ �ڵ�
	}

	void Application::Render()
	{
		// ������ �ڵ�
		HBRUSH blueBrush = CreateSolidBrush(RGB(0, 0, 255));      // �Ķ��� �귯�� ����
		HBRUSH oldBrush = (HBRUSH)SelectObject(mHdc, blueBrush);     // SelectObject�Լ��� ������ ����ϴ� �귯���� ��ȯ

		HPEN redPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		HPEN oldPen = (HPEN)SelectObject(mHdc, redPen);
		SelectObject(mHdc, oldPen);

		Rectangle(mHdc, 100 + mX, 10 + mY, 200 + mX, 100 + mY);

		SelectObject(mHdc, oldBrush);
		DeleteObject(blueBrush);
		DeleteObject(redPen);
	}
}