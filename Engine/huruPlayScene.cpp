#include "huruPlayScene.h"
#include "huruGameObject.h"

huru::PlayScene::PlayScene()
{

}

huru::PlayScene::~PlayScene()
{

}

void huru::PlayScene::Initalize()
{
	GameObject* gameObj = new GameObject();
	AddGameObject(gameObj);
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
