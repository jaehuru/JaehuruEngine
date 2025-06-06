#pragma once

#include "..\\Engine_SOURCE\\huruScript.h"
#include "..\\Engine_SOURCE\\huruTransform.h"

namespace huru
{
	class FloorScript : public Script
	{
	public:
		FloorScript();
		~FloorScript();

		void		Initialize() override;
		void		Update() override;
		void		LateUpdate() override;
		void		Render(HDC hdc) override;

		void		OnCollisionEnter(Collider* other) override;
		void		OnCollisionStay(Collider* other) override;
		void		OnCollisionExit(Collider* other) override;

	private:

	};
}
