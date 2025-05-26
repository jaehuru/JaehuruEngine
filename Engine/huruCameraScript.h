#pragma once

#include "..\\Engine_SOURCE\\huruScript.h"
#include "..\\Engine_SOURCE\\huruTransform.h"

namespace huru
{
	class CameraScript : public Script
	{
	public:
		CameraScript();
		~CameraScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

	private:

	};
}

