#pragma once

#include "Component/huruComponent.h"

namespace huru
{
	class Rigidbody : public Component
	{
	public:
		Rigidbody();
		~Rigidbody();

		void		Initialize()	override;
		void		Update()		override;
		void		LateUpdate()	override;
		void		Render()		override;

		Vector2		GetVelocity() const				{ return mVelocity; }

		void		SetMass(float mass)				{ mMass = mass; }
		void		AddForce(Vector2 force)			{ mForce = force; }
		void		SetGround(bool ground)			{ mbGround = ground; }
		void		SetVelocity(Vector2 velocity)	{ mVelocity = velocity; }

	private:
		bool			mbGround;
		float			mMass;				
		float			mFriction;			
											
		Vector2			mForce;				
		Vector2			mAccelation;		
		Vector2			mVelocity;			
		Vector2			mLimitedVelocity;	
		Vector2			mGravity;			
	};
}

