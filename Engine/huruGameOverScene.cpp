#include "huruGameOverScene.h"
#include "huruGameObject.h"
#include "huruInput.h"
#include "huruSceneManager.h"
#include "huruPlayScene.h"

namespace huru
{
	GameOverScene::GameOverScene()
	{

	}

	GameOverScene::~GameOverScene()
	{

	}

	void GameOverScene::Initialize()
	{
		Scene::Initialize();
	}

	void GameOverScene::Update()
	{
		Scene::Update();
	}

	void GameOverScene::LateUpdate()
	{
		Scene::LateUpdate();

		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(L"PlayScene");
		}
	}

	void GameOverScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		wchar_t str[50] = L"Game Over";
		TextOut(hdc, 0, 0, str, 9);
	}

	void GameOverScene::OnEnter()
	{

	}

	void GameOverScene::OnExit()
	{

	}
}
