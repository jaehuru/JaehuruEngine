#pragma once

#include "huruComponent.h"

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
		void		AddForce(Vector2 force) { mForce = force; }
		void		SetGround(bool ground) { mbGround = ground; }
		void		SetVelocity(Vector2 velocity) { mVelocity = velocity; }
		Vector2		GetVelocity() { return mVelocity; }

	private:
		bool			mbGround;
		float			mMass;				// ����
		float			mFriction;			// ������

		Vector2			mForce;				// ��
		Vector2			mAccelation;		// ���ӵ�
		Vector2			mVelocity;			// �ӵ�
		Vector2			mLimitedVelocity;	// �ӵ�
		Vector2			mGravity;			// �߷�
	};
}

