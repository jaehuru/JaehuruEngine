#pragma once

#include "Component/huruComponent.h"

namespace huru
{
	class Rigidbody : public Component
	{
	public:
		Rigidbody();
		~Rigidbody();

		void		Initialize() override;
		void		Update() override;
		void		LateUpdate() override;
		void		Render(HDC hdc) override;

		void		SetMass(float mass) { mMass = mass; }
		void		AddForce(math::Vector2 force) { mForce = force; }
		void		SetGround(bool ground) { mbGround = ground; }
		void		SetVelocity(math::Vector2 velocity) { mVelocity = velocity; }
		math::Vector2		GetVelocity() { return mVelocity; }

	private:
		bool			mbGround;
		float			mMass;				// 질량
		float			mFriction;			// 마찰력

		math::Vector2			mForce;				// 힘
		math::Vector2			mAccelation;		// 가속도
		math::Vector2			mVelocity;			// 속도
		math::Vector2			mLimitedVelocity;	// 속도
		math::Vector2			mGravity;			// 중력
	};
}

