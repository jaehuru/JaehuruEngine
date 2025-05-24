#pragma once

#include "..//Engine_SOURCE/huruSceneManager.h"

#include "huruTitleScene.h"
#include "huruPlayScene.h"
#include "huruGameOverScene.h"
#include "huruToolScene.h"

namespace huru
{
	void LoadScenes()
	{
		//SceneManager::CreateScene<TitleScene>(L"TitleScene");
		//SceneManager::CreateScene<PlayScene>(L"PlayScene");
		//SceneManager::CreateScene<GameOverScene>(L"GameOverScene");
		SceneManager::CreateScene<ToolScene>(L"ToolScene");
		

		SceneManager::LoadScene(L"ToolScene");
	}
}