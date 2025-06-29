#pragma once

#include "Scene/huruScene.h"

namespace huru
{
	class DontDestroyOnLoad : public Scene
	{
	public:
		DontDestroyOnLoad();
		~DontDestroyOnLoad();

		void	Initialize()	override;
		void	Update()		override;
		void	LateUpdate()	override;
		void	Render()		override;

		void	OnEnter()		override;
		void	OnExit()		override;

	private:

	};
}



