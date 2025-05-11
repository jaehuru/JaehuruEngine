#pragma once

#include "huruComponent.h"
#include "huruLayer.h"
#include "huruGameObject.h"
#include "huruSceneManager.h"
#include "huruScene.h"
#include "huruTransform.h"

namespace huru::object
{
	template<typename T>
	static T* Instantiate(huru::enums::eLayerType type)
	{
		T* gameObj = new T();
		Scene* activeScene = SceneManager::GetActiveScene();
		Layer* layer = activeScene->GetLayer(type);
		layer->AddGameObject(gameObj);

		return gameObj;
	}

	template<typename T>
	static T* Instantiate(huru::enums::eLayerType type, math::Vector2 position)
	{
		T* gameObj = new T();
		Scene* activeScene = SceneManager::GetActiveScene();
		Layer* layer = activeScene->GetLayer(type);
		layer->AddGameObject(gameObj);

		Transform* tr = gameObj->GetComponent<Transform>();
		tr->SetPosition(position);

		return gameObj;
	}

	static void Destroy(GameObject* obj)
	{
		obj->Death();
	}
}