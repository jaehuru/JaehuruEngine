#include "huruCamera.h"
#include "huruGameObject.h"
#include "huruTransform.h"
#include "huruApplication.h"

extern huru::Application application;

namespace huru
{
	Camera::Camera() :
		Component(enums::eComponentType::Camera),
		mDistance(Vector2::Zero),
		mResolution(Vector2::Zero),
		mLookPosition(Vector2::Zero),
		mTarget(nullptr)
	{

	}

	Camera::~Camera()
	{

	}

	void Camera::Initialize()
	{
		mResolution.x = application.GetWidth();
		mResolution.y = application.GetHeight();
	}

	void Camera::Update()
	{
		if (mTarget)
		{
			Transform* tr = mTarget->GetComponent<Transform>();
			mLookPosition = tr->GetPosition();
		}
		else
		{
			Transform* cameraTr = GetOwner()->GetComponent<Transform>();
			mLookPosition = cameraTr->GetPosition();
		}

		mDistance = mLookPosition - (mResolution / 2.f);
	}

	void Camera::LateUpdate()
	{

	}

	void Camera::Render(HDC hdc)
	{

	}
}