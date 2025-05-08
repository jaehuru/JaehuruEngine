#pragma once

#include "..//Engine_SOURCE/huruSceneManager.h"
#include "huruPlayScene.h"

namespace huru
{
	void LoadScenes()
	{
		SceneManager::CreateScene<PlayScene>(L"PlayScene");
		/*SceneManager::CreateScene<PlayScene>(L"TitleScene");
		SceneManager::CreateScene<PlayScene>(L"GameOverScene");
		SceneManager::CreateScene<PlayScene>(L"GameClearScene");*/


		SceneManager::LoadScene(L"PlayScene");
	}
}