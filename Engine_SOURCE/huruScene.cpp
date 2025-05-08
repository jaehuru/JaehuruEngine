#include "huruScene.h"

namespace huru
{
	Scene::Scene() :
		mGameObjects{}
	{

	}

	Scene::~Scene()
	{

	}
	void Scene::Initalize()
	{

	}

	void Scene::Update()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			gameObj->Update();
		}
	}

	void Scene::LateUpdate()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			gameObj->LateUpdate();
		}
	}

	void Scene::Render(HDC hdc)
	{
		for (GameObject* gameObj : mGameObjects)
		{
			gameObj->Render(hdc);
		}
	}
	void Scene::AddGameObject(GameObject* gameObj)
	{
		mGameObjects.push_back(gameObj);
	}
}