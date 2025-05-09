#pragma once

#include "huruEntity.h"
#include "huruGameObject.h"

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

		void AddGameObject(GameObject* gameObj);

	private:
		//eLayerType mType;
		std::vector<GameObject*> mGameObjects;
	};
}

