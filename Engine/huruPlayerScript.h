#pragma once

#include "..\\Engine_SOURCE\\huruScript.h"

namespace huru
{
	class PlayerScript : public Script
	{
	public:
		PlayerScript();
		~PlayerScript();

		void		Initialize() override;
		void		Update() override;
		void		LateUpdate() override;
		void		Render(HDC hdc) override;

	private:

	};
}

