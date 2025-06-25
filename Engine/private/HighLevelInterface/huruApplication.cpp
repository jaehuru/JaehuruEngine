#include "HighLevelInterface/huruApplication.h"
#include "Helpers/huruInput.h"
#include "Helpers/huruTime.h"
#include "Scene/huruSceneManager.h"
#include "Resource/huruResources.h"
#include "Collision/huruCollisionManager.h"
#include "UI/huruUIManager.h"
#include "FMOD/huruFmod.h"

namespace huru
{

	Application::Application() : 
		mHwnd(nullptr),
		mHdc(nullptr),
		mWidth(0),
		mHeight(0),
		mBackHdc(NULL),
		mBackBitmap(NULL)
	{

	}

	Application::~Application()
	{
		
	}

	void Application::Initialize(HWND hwnd, UINT width, UINT height)
	{
		adjustWindowRect(hwnd, width, height);
		createBuffer(width, height);
		initializeEtc();

		mGraphicDevice = make_unique<graphics::GraphicDevice_DX11>();
		mGraphicDevice->Initialize();

		Fmod::Initialize();
		CollisionManager::Initialize();
		UIManager::Initialize();
		SceneManager::Initialize();
	}

	void Application::Run()
	{
		Update();
		LateUpdate();
		Render();

		Destroy();
	}

	void Application::Update()
	{
		Input::Update();
		Time::Update();
		CollisionManager::Update();
		UIManager::Update();
		SceneManager::Update();
	}

	void Application::LateUpdate()
	{
		// 후처리 업데이트 코드
		CollisionManager::LateUpdate();
		UIManager::LateUpdate();
		SceneManager::LateUpdate();

	}

	void Application::Render()
	{
		mGraphicDevice->Render();

		Time::Render(mBackHdc);
		CollisionManager::Render(mBackHdc);
		SceneManager::Render(mBackHdc);
		UIManager::Render(mBackHdc);

		
	}

	void Application::Destroy()
	{
		SceneManager::Destroy();
	}

	void Application::Release()
	{
		SceneManager::Release();
		UIManager::Release();
		Resources::Release();
	}

	void Application::clearRenderTarget()
	{
		HBRUSH blackBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
		HBRUSH oldBrush = (HBRUSH)SelectObject(mBackHdc, blackBrush);

		::Rectangle(mBackHdc, -1, -1, 1601, 901);

		SelectObject(mBackHdc, oldBrush);
		DeleteObject(blackBrush);
	}

	void Application::copyRenderTarget(HDC source, HDC dest)
	{
		BitBlt(dest, 0, 0, mWidth, mHeight,
			source, 0, 0, SRCCOPY);
	}

	void Application::adjustWindowRect(HWND hwnd, UINT width, UINT height)
	{
		mHwnd = hwnd;
		mHdc = GetDC(hwnd);

		RECT rect = 
		{ 
			0, 0, static_cast<LONG>(width), static_cast<LONG>(height) 
		};
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		mWidth = rect.right - rect.left;
		mHeight = rect.bottom - rect.top;

		SetWindowPos(mHwnd, nullptr, 0, 0, mWidth, mHeight, 0);
		ShowWindow(mHwnd, true);
	}

	void Application::createBuffer(UINT width, UINT height)
	{
		//윈도우 해상도에 맞는 백버퍼(도화지)생성
		mBackBitmap = CreateCompatibleBitmap(mHdc, width, height);

		//백버퍼를 가르킬 DC생성
		mBackHdc = CreateCompatibleDC(mHdc);

		HBITMAP oldBitmap = (HBITMAP)SelectObject(mBackHdc, mBackBitmap);
		DeleteObject(oldBitmap);
	}

	void Application::initializeEtc()
	{
		Input::Initialize();
		Time::Initialize();
	}
}