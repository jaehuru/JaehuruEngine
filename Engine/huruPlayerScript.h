#pragma once

#include "..\\Engine_SOURCE\\huruScript.h"

namespace huru
{
	class PlayerScript : public Script
	{
	public:
		enum class eState
		{
			Idle,
			Walk,
			FrontGiveWater,
			End,
		};

		PlayerScript();
		~PlayerScript();

		void		Initialize() override;
		void		Update() override;
		void		LateUpdate() override;
		void		Render(HDC hdc) override;

		void		AttackEffect();

	private:
		void		idle();
		void		move();
		void		giveWater();

	private:
		eState mState;
		class Animator* mAnimator;

	};
}

