#include "Component/Rigidbody/huruRigidbody.h"
#include "Component/Transform/huruTransform.h"
#include "Helpers/huruTime.h"
#include "GameObject/huruGameObject.h"

namespace huru
{
	Rigidbody::Rigidbody() :
		Component(enums::eComponentType::Rigidbody),
		mbGround(false),
		mMass(1.f),
		mFriction(10.f),
		mForce(math::Vector2::Zero),
		mAccelation(math::Vector2::Zero),
		mVelocity(math::Vector2::Zero),
		mLimitedVelocity(math::Vector2(200.f, 1000.f)),
		mGravity(math::Vector2(0.f, 800.f))
	{

	}

	Rigidbody::~Rigidbody()
	{

	}

	void Rigidbody::Initialize()
	{
		
	}

	void Rigidbody::Update()
	{
		// F = ma
		// a = F/m
		mAccelation = mForce / mMass;

		mVelocity += mAccelation * Time::DeltaTime();

		if (mbGround) // ��
		{
			math::Vector2 gravity = mGravity;
			gravity.normalize();

			float dot = math::Vector2::Dot(mVelocity, gravity);
			mVelocity -= gravity * dot;
		}
		else // ����
		{
			mVelocity += mGravity * Time::DeltaTime();
		}

		// �ִ� �ӵ� ����
		math::Vector2 gravity = mGravity;
		gravity.normalize();
		float dot = math::Vector2::Dot(mVelocity, gravity);
		gravity = gravity * dot;

		math::Vector2 sideVelocity = mVelocity - gravity;
		if (mLimitedVelocity.y < gravity.length())
		{
			gravity.normalize();
			gravity *= mLimitedVelocity.y;
		}
		
		if (mLimitedVelocity.x < sideVelocity.length())
		{
			sideVelocity.normalize();
			sideVelocity *= mLimitedVelocity.x;
		}

		mVelocity = gravity + sideVelocity;



		if (!(mVelocity == math::Vector2::Zero))
		{
			// �ӵ� �ݴ�������� ������ �ۿ�
			math::Vector2 friction = -mVelocity;
			friction = friction.normalize() * mFriction * mMass * Time::DeltaTime();

			// ���������� ���� �ӵ� ���ҷ��� ���� �ӵ����� ū ���
			if (mVelocity.length() <= friction.length())
			{
				mVelocity = math::Vector2::Zero;
			}
			else
			{
				mVelocity += friction;
			}
		}

		Transform* transform = GetOwner()->GetComponent<Transform>();
		math::Vector2 pos = transform->GetPosition();
		pos = pos + mVelocity * Time::DeltaTime();
		transform->SetPosition(pos);

		mForce.clear();
	}

	void Rigidbody::LateUpdate()
	{

	}

	void Rigidbody::Render(HDC hdc)
	{

	}
}