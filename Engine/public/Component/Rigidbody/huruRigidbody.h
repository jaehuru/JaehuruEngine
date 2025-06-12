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
		float			mMass;				// ����
		float			mFriction;			// ������

		math::Vector2			mForce;				// ��
		math::Vector2			mAccelation;		// ���ӵ�
		math::Vector2			mVelocity;			// �ӵ�
		math::Vector2			mLimitedVelocity;	// �ӵ�
		math::Vector2			mGravity;			// �߷�
	};
}

