#include "huruPlayScene.h"
#include "huruGameObject.h"
#include "huruPlayer.h"
#include "huruTransform.h"
#include "huruSpriteRenderer.h"

huru::PlayScene::PlayScene()
{

}

huru::PlayScene::~PlayScene()
{

}

void huru::PlayScene::Initalize()
{
	{
		Player* pl = new Player();
		Transform* tr
			= pl->AddComponent<Transform>();
		tr->SetPos(800, 450);

		tr->SetName(L"TR");

		SpriteRenderer* sr
			= pl->AddComponent<SpriteRenderer>();
		sr->SetName(L"SR");

		AddGameObject(pl);
	}

	{
		Player* pl = new Player();
		Transform* tr
			= pl->AddComponent<Transform>();
		tr->SetPos(300, 450);

		tr->SetName(L"TR");

		SpriteRenderer* sr
			= pl->AddComponent<SpriteRenderer>();
		sr->SetName(L"SR");

		AddGameObject(pl);
	}

	{
		Player* pl = new Player();
		Transform* tr
			= pl->AddComponent<Transform>();
		tr->SetPos(100, 650);

		tr->SetName(L"TR");

		SpriteRenderer* sr
			= pl->AddComponent<SpriteRenderer>();
		sr->SetName(L"SR");

		AddGameObject(pl);
	}

}

void huru::PlayScene::Update()
{
	Scene::Update();
}

void huru::PlayScene::LateUpdate()
{
	Scene::LateUpdate();
}

void huru::PlayScene::Render(HDC hdc)
{
	Scene::Render(hdc);
}
