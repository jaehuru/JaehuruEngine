#include "huruRigidbody.h"
#include "huruTime.h"
#include "huruGameObject.h"
#include "huruTransform.h"

namespace huru
{
	Rigidbody::Rigidbody() :
		Component(eComponentType::Rigidbody),
		mMass(1.f),
		mFriction(100.f),
		mForce(Vector2::Zero),
		mAccelation(Vector2::Zero),
		mVelocity(Vector2::Zero),
		mGravity(Vector2::Zero)
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

		if (!(mVelocity == Vector2::Zero))
		{
			// �ӵ� �ݴ�������� ������ �ۿ�
			Vector2 friction = -mVelocity;
			friction = friction.normalize() * mFriction * mMass * Time::DeltaTime();

			// ���������� ���� �ӵ� ���ҷ��� ���� �ӵ����� ū ���
			if (mVelocity.length() <= friction.length())
			{
				mVelocity = Vector2::Zero;
			}
			else
			{
				mVelocity += friction;
			}
		}

		Transform* transform = GetOwner()->GetComponent<Transform>();
		Vector2 pos = transform->GetPosition();
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