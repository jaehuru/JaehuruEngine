#pragma once

#include "..//Engine_SOURCE/huruScene.h"


namespace huru
{
	class Tile;
	namespace graphics { class Texture; }
	
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

		void	LoadMapFile(const std::wstring& filePath);

	private:
		std::vector<Tile*> mTiles;
		graphics::Texture* mTexture;
	};
}

LRESULT CALLBACK WndTileProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

