#pragma once

#include "huruEntity.h"
#include "huruGameObject.h"
#include "huruLayer.h"

namespace huru
{
	class Scene : public Entity
	{
	public:
		Scene();
		~Scene();

		virtual void	Initialize();
		virtual void	Update();
		virtual void	LateUpdate();
		virtual void	Render(HDC hdc);
		virtual void	Destroy();

		virtual void	OnEnter();
		virtual void	OnExit();

		void			AddGameObject(GameObject* gameObj,
										const enums::eLayerType type);
		void			EraseGameObject(GameObject* gameObj);
		Layer*			GetLayer(const enums::eLayerType type) 
		{
			return mLayers[(UINT)type]; 
		}

	private:
		void			createLayers();
		
	private:
		std::vector<Layer*> mLayers;
	};
}

