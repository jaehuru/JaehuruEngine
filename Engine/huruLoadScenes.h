#pragma once

#include "..//Engine_SOURCE/huruSceneManager.h"

#include "huruTitleScene.h"
#include "huruPlayScene.h"
#include "huruGameOverScene.h"

namespace huru
{
	void LoadScenes()
	{
		SceneManager::CreateScene<TitleScene>(L"TitleScene");
		SceneManager::CreateScene<PlayScene>(L"PlayScene");
		SceneManager::CreateScene<GameOverScene>(L"GameOverScene");
		//SceneManager::CreateScene<GameClearScene>(L"GameClearScene");


		SceneManager::LoadScene(L"PlayScene");
	}
}