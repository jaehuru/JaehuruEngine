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

		mPlayer1.SetColor(RGB(0, 0, 255));  // 파란색
		mPlayer2.SetColor(RGB(255, 0, 0));  // 빨간색
		mPlayer3.SetColor(RGB(0, 255, 0));  // 초록색

		mPlayer1.SetShape(ShapeType::Rectangle); // 사각형
		mPlayer2.SetShape(ShapeType::Circle);    // 원형
		mPlayer3.SetShape(ShapeType::Rhombus);   // 마름모형

		mPlayer1.SetKeySet(DirectionKeySet::Arrow); // 방향키로 조작
		mPlayer2.SetKeySet(DirectionKeySet::WASD);  // WASD로 조작
		mPlayer3.SetKeySet(DirectionKeySet::Auto);  // 자동으로 움직임

		mPlayer1.SetPosition(0, 0);
		mPlayer2.SetPosition(300, 0); // 겹치지 않게 위치 다르게
		mPlayer3.SetPosition(400, 400); // 세 번째 객체 (규칙적으로 움직이게 설정)
		mPlayer3.SetAutoMove(true);    // 자동으로 움직이도록 설정
	}

	void Application::Run()
	{
		Update();
		LateUpdate();
		Render();
	}

	void Application::Update()
	{
		mPlayer1.Update();
		mPlayer2.Update();
		mPlayer3.Update(); // 세 번째 객체 업데이트 (규칙적으로 움직임)
	}

	void Application::LateUpdate()
	{
		// 후처리 업데이트 코드
	}

	void Application::Render()
	{
		mPlayer1.Render(mHdc); // 게임 오브젝트 렌더링
		mPlayer2.Render(mHdc); // 게임 오브젝트 렌더링
		mPlayer3.Render(mHdc); // 세 번째 객체 렌더링 (규칙적으로 움직이는 객체)
	}
}