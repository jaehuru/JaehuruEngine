#include "huruApplication.h"
#include "huruInput.h"
#include "huruTime.h"

namespace huru
{

	Application::Application() : 
		mHwnd(nullptr),
		mHdc(nullptr)
	{

	}

	Application::~Application()
	{
		
	}

	void Application::Initalize(HWND hwnd)
	{
		mHwnd = hwnd;
		mHdc = GetDC(hwnd);
		mPlayer.SetPosition(0, 0);

		Input::Initialize();
		Time::Initialize();
	}

	void Application::Run()
	{
		Update();
		LateUpdate();
		Render();
	}

	void Application::Update()
	{
		Input::Update();
		Time::Update();

		mPlayer.Update();
	}

	void Application::LateUpdate()
	{
		// 후처리 업데이트 코드
	}

	void Application::Render()
	{
		Rectangle(mHdc, 0, 0, 1600, 900);

		Time::Render(mHdc);
		mPlayer.Render(mHdc);
	}
}