#include "huruAnimation.h"
#include "huruTime.h"
#include "huruTransform.h"
#include "huruGameObject.h"
#include "huruAnimator.h"
#include "huruRenderer.h"
#include "huruCamera.h"

namespace huru
{
	Animation::Animation() :
		Resource(enums::eResourceType::Animation),
		mAnimator(nullptr),
		mTexture(nullptr),
		mAnimationSheet{ },
		mIndex(-1),
		mTime(0.f),
		mbComplete(false)
	{

	}

	Animation::~Animation()
	{

	}

	HRESULT Animation::Load(const std::wstring& path)
	{
		return E_NOTIMPL;
	}

	void Animation::Update()
	{
		if (mbComplete)
			return;

		mTime += Time::DeltaTime();

		if (mAnimationSheet[mIndex].duration < mTime)
		{
			mTime = 0.f;
			if (mIndex < mAnimationSheet.size() - 1)
				mIndex++;
			else
				mbComplete = true;
		}
	}

	void Animation::Render(HDC hdc)
	{
		// 조건 : 해당 이미지 알파채널이 있어야함
		if (mTexture == nullptr)
			return;

		GameObject* gameObj = mAnimator->GetOwner();
		Transform* tr = gameObj->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		if (renderer::mainCamera)
			pos = renderer::mainCamera->CalculatePosition(pos);

		BLENDFUNCTION func = { };
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = 125; // 0(Transparent) ~ 255(Opaque)

		Sprite sprite = mAnimationSheet[mIndex];
		HDC imgHdc = mTexture->GetHdc();

		AlphaBlend(	hdc,
					pos.x,
					pos.y,
					sprite.size.x * 5,
					sprite.size.y * 5,
					imgHdc,
					sprite.leftTop.x,
					sprite.leftTop.y,
					sprite.size.x,
					sprite.size.y,
					func);
	}

	void Animation::CreateAnimation(const std::wstring& name,
									graphics::Texture* spriteSheet,
									Vector2 leftTop, Vector2 size,
									Vector2 offset, UINT spriteLength,
									float duration)
	{
		mTexture = spriteSheet;
		for (size_t i = 0; i < spriteLength; i++)
		{
			Sprite sprite = { };
			sprite.leftTop.x = leftTop.x + size.x * i;
			sprite.leftTop.y = leftTop.y;
			sprite.size = size;
			sprite.offset = offset;
			sprite.duration = duration;

			mAnimationSheet.push_back(sprite);
		}
	}

	void Animation::Reset()
	{
		mTime = 0;
		mIndex = 0.f;
		mbComplete = false;
	}
}