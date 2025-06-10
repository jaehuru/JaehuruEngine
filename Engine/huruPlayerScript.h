#pragma once

#include "..\\Engine_SOURCE\\huruScript.h"
#include "..\\Engine_SOURCE\\huruTexture.h"

namespace huru
{
	class Collider;
	class Animator;

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

		void OnCollisionEnter(Collider* other) override;
		void OnCollisionStay(Collider* other) override;
		void OnCollisionExit(Collider* other) override;

		void SetPixelMapTexture(graphics::Texture* texture) 
		{
			mPixelMap = texture;
		}

	private:
		void		idle();
		void		move();
		void		giveWater();

	private:
		eState mState;
		Animator* mAnimator;
		graphics::Texture* mPixelMap;

	};
}

