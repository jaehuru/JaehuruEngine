#include "Component/Transform/huruTransform.h"

namespace huru
{
	Transform::Transform() :
		Component(enums::eComponentType::Transform),
		mPosition(math::Vector2::Zero),
		mScale(math::Vector2::One),
		mRotation(0.f)
	{

	}

	Transform::~Transform()
	{

	}

	void Transform::Initialize()
	{

	}

	void Transform::Update()
	{

	}

	void Transform::LateUpdate()
	{

	}

	void Transform::Render(HDC hdc)
	{

	}
}