#include "huruApplication.h"

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
		// 초기화 코드
		mHwnd = hwnd;
		mHdc = GetDC(hwnd); // 윈도우 핸들로부터 DC를 가져옴
		mPlayer.SetPosition(0, 0);
	}

	void Application::Run()
	{
		Update();
		LateUpdate();
		Render();
	}

	void Application::Update()
	{
		mPlayer.Update(); // 게임 오브젝트 업데이트
	}

	void Application::LateUpdate()
	{
		// 후처리 업데이트 코드
	}

	void Application::Render()
	{
		mPlayer.Render(mHdc); // 게임 오브젝트 렌더링
	}
}