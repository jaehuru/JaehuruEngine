#include "Component/Camera/huruCamera.h"
#include "GameObject/huruGameObject.h"
#include "Component/Transform/huruTransform.h"
#include "HighLevelInterface/huruApplication.h"

extern Application application;

namespace huru
{
	Camera::Camera() :
		Component(eComponentType::Camera),
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