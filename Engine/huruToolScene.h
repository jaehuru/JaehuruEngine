#pragma once

#include "..//Engine_SOURCE/huruScene.h"
//#include "huruTile.h"

namespace huru
{
	class Tile;
	
	class ToolScene : public Scene
	{
	public:
		ToolScene();
		~ToolScene();

		void	Initialize() override;
		void	Update() override;
		void	LateUpdate() override;
		void	Render(HDC hdc) override;

		void	OnEnter() override;
		void	OnExit() override;

		void	Save();
		void	Load();

	private:
		std::vector<Tile*> mTiles;
	};
}

LRESULT CALLBACK WndTileProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);