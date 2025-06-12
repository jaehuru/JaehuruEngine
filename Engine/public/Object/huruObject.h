#pragma once

#include "Component/huruComponent.h"
#include "Layer/huruLayer.h"
#include "GameObject/huruGameObject.h"
#include "Scene/huruSceneManager.h"
#include "Scene/huruScene.h"
#include "Component/Transform/huruTransform.h"

namespace huru::object
{
	template<typename T>
	static T* Instantiate(enums::eLayerType type)
	{
		T* gameObj = new T();
		gameObj->SetLayerType(type);
		Scene* activeScene = SceneManager::GetActiveScene();
		Layer* layer = activeScene->GetLayer(type);
		layer->AddGameObject(gameObj);

		return gameObj;
	}

	template<typename T>
	static T* Instantiate(enums::eLayerType type, math::Vector2 position)
	{
		T* gameObj = new T();
		gameObj->SetLayerType(type);
		Scene* activeScene = SceneManager::GetActiveScene();
		Layer* layer = activeScene->GetLayer(type);
		layer->AddGameObject(gameObj);

		Transform* tr = gameObj->GetComponent<Transform>();
		tr->SetPosition(position);

		return gameObj;
	}

	static void DonDestroyOnLoad(GameObject* gameObject)
	{
		Scene* activeScene = SceneManager::GetActiveScene();
		// ��������� ���� ������Ʈ�� ����
		activeScene->EraseGameObject(gameObject);

		// �ش� ���� ������Ʈ�� -> DonDestroy������ ����
		Scene* dontDestroyOnLoad = 
			SceneManager::GetDontDestroyOnLoad();
		dontDestroyOnLoad->
			AddGameObject(gameObject, gameObject->GetLayerType());
	}
}