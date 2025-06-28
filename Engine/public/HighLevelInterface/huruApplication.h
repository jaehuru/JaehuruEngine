#pragma once

#include "Common/CommonInclude.h"
#include "GameObject/huruGameObject.h"
#include "GraphicDevice/huruGraphicDevice_DX11.h"

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

		HWND	GetHwnd() const		{ return mHwnd; }
		HDC		GetHdc() const		{ return mHdc; }
		UINT	GetWidth() const	{ return mWidth; }
		UINT	GetHeight() const	{ return mHeight; }

	private:
		void	clearRenderTarget();
		void	copyRenderTarget(HDC source, HDC dest);
		void	adjustWindowRect(HWND hwnd, UINT width, UINT height);
		void	createBuffer(UINT width, UINT height);
		void	initializeEtc();

	private:
		unique_ptr<GraphicDevice_DX11>	mGraphicDevice;

		HWND			mHwnd;
		HDC				mHdc;

		HDC				mBackHdc;
		HBITMAP			mBackBitmap;

		UINT			mWidth;
		UINT			mHeight;
	};
}
