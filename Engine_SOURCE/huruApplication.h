#pragma once

#include "CommonInclude.h"
#include "huruGameObject.h"

namespace huru
{
	class Application
	{
	public:
		Application();
		~Application();
		

		void	Initalize(HWND hwnd, UINT width, UINT height);
		void	Run();

		void	Update();
		void	LateUpdate();
		void	Render();

	private:
		HWND			mHwnd;
		HDC				mHdc;

		HDC				mBackHdc;
		HBITMAP			mBackBitmap;

		UINT			mWidth;
		UINT			mHeight;

		GameObject		mPlayer;
	};
}
