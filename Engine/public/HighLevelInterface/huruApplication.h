#pragma once

#include "Common/CommonInclude.h"
#include "GameObject/huruGameObject.h"

namespace huru
{
	class Application
	{
	public:
		Application();
		~Application();
		

		void	Initialize(HWND hwnd, UINT width, UINT height);
		void	Run();

		void	Update();
		void	LateUpdate();
		void	Render();
		void	Destroy();
		void	Release();

		HWND	GetHwnd()	{ return mHwnd; }
		HDC		GetHDC()	{ return mHdc; }
		UINT	GetWidth()	{ return mWidth; }
		UINT	GetHeight()	{ return mHeight; }

	private:
		void	clearRenderTarget();
		void	copyRenderTarget(HDC source, HDC dest);
		void	adjustWindowRect(HWND hwnd, UINT width, UINT height);
		void	createBuffer(UINT width, UINT height);
		void	initializeEtc();

	private:
		HWND			mHwnd;
		HDC				mHdc;

		HDC				mBackHdc;
		HBITMAP			mBackBitmap;

		UINT			mWidth;
		UINT			mHeight;

		//std::vector<Scene*> mScenes;
		//std::vector<GameObject*>	mGameObjects;
	};
}
