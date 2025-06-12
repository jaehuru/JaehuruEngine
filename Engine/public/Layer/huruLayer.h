#pragma once

#include "Common/huruEntity.h"
#include "GameObject/huruGameObject.h"

namespace huru
{
	class Layer : public Entity
	{
	public:
		Layer();
		~Layer();

		virtual void	Initialize();
		virtual void	Update();
		virtual void	LateUpdate();
		virtual void	Render(HDC hdc);
		virtual void	Destroy();

		void AddGameObject(GameObject* gameObj);
		void EraseGameObject(GameObject* eraseGameObj);
		const std::vector<GameObject*>GetGameObjects() { return mGameObjects; }

	private:
		void findDeadGameObjects(OUT std::vector<GameObject*>& gameObjs);
		void deleteGameObjects(std::vector<GameObject*> gameObjs);
		void eraseDeadGameObject();

	private:
		//eLayerType mType;
		std::vector<GameObject*> mGameObjects;
	};

	typedef std::vector<GameObject*>::iterator GameObjectIter;
}

