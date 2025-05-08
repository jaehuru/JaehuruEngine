#pragma once

#include "..//Engine_SOURCE/huruScene.h"

namespace huru
{
	class PlayScene : public Scene
	{
	public:
		PlayScene();
		~PlayScene();

		void	Initalize() override;
		void	Update() override;
		void	LateUpdate() override;
		void	Render(HDC hdc) override;
	private:
	};
}

