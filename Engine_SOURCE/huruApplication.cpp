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
		// �ʱ�ȭ �ڵ�
		mHwnd = hwnd;
		mHdc = GetDC(hwnd); // ������ �ڵ�κ��� DC�� ������
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
		mPlayer.Update(); // ���� ������Ʈ ������Ʈ
	}

	void Application::LateUpdate()
	{
		// ��ó�� ������Ʈ �ڵ�
	}

	void Application::Render()
	{
		mPlayer.Render(mHdc); // ���� ������Ʈ ������
	}
}