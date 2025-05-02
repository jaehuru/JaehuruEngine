#pragma once

#include "CommonInclude.h"

namespace huru
{
	class Application
	{
	public:
		Application();
		~Application();
		

		void	Initalize(HWND hwnd);
		void	Run();

		void	Update();
		void	LateUpdate();
		void	Render();

	private:
		HWND	mHwnd;
		HDC		mHdc;

		float	mSpeed;
		float	mX;
		float	mY;
	};
}
