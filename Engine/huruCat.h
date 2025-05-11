#pragma once

#include "..\\Engine_SOURCE\\huruGameObject.h"

namespace huru
{

	class Cat : public GameObject
	{
	public:
		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

	private:

	};
}