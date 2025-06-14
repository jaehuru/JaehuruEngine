#include "Layer/huruLayer.h"

namespace huru
{
	Layer::Layer() :
		mGameObjects{}
	{

	}

	Layer::~Layer()
	{
		for (GameObject* obj : mGameObjects)
		{
			if (obj == nullptr)
				continue;

			delete obj;
			obj = nullptr;
		}
	}

	void Layer::Initialize()
	{
		for (GameObject* obj : mGameObjects)
		{
			if (obj == nullptr)
				continue;

			obj->Initialize();
		}
	}

	void Layer::Update()
	{
		for (GameObject* obj : mGameObjects)
		{
			if (obj == nullptr)
				continue;

			GameObject::eState state = obj->GetState();
			if (state == GameObject::eState::Paused ||
				state == GameObject::eState::Dead)
				continue;

			obj->Update();
		}
	}

	void Layer::LateUpdate()
	{
		for (GameObject* obj : mGameObjects)
		{
			if (obj == nullptr)
				continue;

			GameObject::eState state = obj->GetState();
			if (state == GameObject::eState::Paused ||
				state == GameObject::eState::Dead)
				continue;

			obj->LateUpdate();
		}
	}

	void Layer::Render(HDC hdc)
	{
		for (GameObject* obj : mGameObjects)
		{
			if (obj == nullptr)
				continue;

			GameObject::eState state = obj->GetState();
			if (state == GameObject::eState::Paused ||
				state == GameObject::eState::Dead)
				continue;

			obj->Render(hdc);
		}
	}

	void Layer::Destroy()
	{
		vector<GameObject*> deleteObjects = {};
		findDeadGameObjects(deleteObjects);
		eraseDeadGameObject();
		deleteGameObjects(deleteObjects);
	}

	void Layer::AddGameObject(GameObject* gameObj)
	{
		if (gameObj == nullptr)
			return;

		mGameObjects.push_back(gameObj);
	}

	void Layer::EraseGameObject(GameObject* eraseGameObj)
	{
		erase_if(mGameObjects,
			[=](GameObject* gameObj)
			{
				return gameObj == eraseGameObj;
			});
	}

	void Layer::findDeadGameObjects(OUT vector<GameObject*>& gameObjs)
	{
		for (GameObject* gameObj : mGameObjects)
		{
			GameObject::eState active = gameObj->GetState();
			if (active == GameObject::eState::Dead)
				gameObjs.push_back(gameObj);
		}
	}

	void Layer::deleteGameObjects(vector<GameObject*> deleteObjs)
	{
		for (GameObject* obj : deleteObjs)
		{
			delete obj;
			obj = nullptr;
		}
	}

	void Layer::eraseDeadGameObject()
	{
		erase_if(mGameObjects,
			[](GameObject* gameObj)
			{
				return (gameObj)->IsDead();
			});
	}
}