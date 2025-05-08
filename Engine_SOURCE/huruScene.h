#pragma once

#include "huruEntity.h"
#include "huruGameObject.h"

namespace huru
{
	class Scene : public Entity
	{
	public:
		Scene();
		~Scene();

		virtual void	Initalize();
		virtual void	Update();
		virtual void	LateUpdate();
		virtual void	Render(HDC hdc);

		void AddGameObject(GameObject* gameObj);

	private:
		std::vector<GameObject*> mGameObjects;
	};
}

