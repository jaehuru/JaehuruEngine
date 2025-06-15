#include "Resource/huruAnimation.h"
#include "Helpers/huruTime.h"
#include "Component/Transform/huruTransform.h"
#include "GameObject/huruGameObject.h"
#include "Component/Animator/huruAnimator.h"
#include "Renderer/huruRenderer.h"
#include "Component/Camera/huruCamera.h"

namespace huru
{

	Animation::Animation() :
		Resource(eResourceType::Animation),
		mAnimator(nullptr),
		mTexture(nullptr),
		mSpriteSheet{ },
		mIndex(-1),
		mTime(0.f),
		mbComplete(false)
	{

	}

	Animation::~Animation()
	{

	}

	HRESULT Animation::Load(const wstring& path)
	{
		return E_NOTIMPL;
	}

	void Animation::Update()
	{
		UpdateSheet();
	}

	void Animation::Render(HDC hdc)
	{
		RenderFromSheet(hdc);
	}

	void Animation::CreateAnimation(const wstring& name,
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

			mSpriteSheet.push_back(sprite);
		}
	}

	void Animation::Reset()
	{
		mTime = 0;
		mIndex = 0.f;
		mbComplete = false;
	}

	void Animation::RenderFromSheet(HDC hdc)
	{
		if (!mTexture) return;

		if (mIndex < 0 || mIndex >= (int)mSpriteSheet.size())
			return; 

		GameObject* gameObj = mAnimator->GetOwner();
		Transform* tr = gameObj->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		float rot = tr->GetRotation();
		Vector2 scale = tr->GetScale();

		if (renderer::mainCamera)
			pos = renderer::mainCamera->CalculatePosition(pos);

		Sprite& sprite = mSpriteSheet[mIndex];
		graphics::Texture::eTextureType type = mTexture->GetTextureType();

		if (type == graphics::Texture::eTextureType::Bmp)
		{
			HDC imgHdc = mTexture->GetHdc();

			if (mTexture->IsAlpha())
			{
				BLENDFUNCTION func = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
				AlphaBlend(
					hdc,
					pos.x - (sprite.size.x / 2.f) + sprite.offset.x,
					pos.y - (sprite.size.y / 2.f) + sprite.offset.y,
					sprite.size.x * scale.x,
					sprite.size.y * scale.y,
					imgHdc,
					sprite.leftTop.x,
					sprite.leftTop.y,
					sprite.size.x,
					sprite.size.y,
					func);
			}
			else
			{
				TransparentBlt(
					hdc,
					pos.x - (sprite.size.x / 2.f) + sprite.offset.x,
					pos.y - (sprite.size.y / 2.f) + sprite.offset.y,
					sprite.size.x * scale.x,
					sprite.size.y * scale.y,
					imgHdc,
					sprite.leftTop.x,
					sprite.leftTop.y,
					sprite.size.x,
					sprite.size.y,
					RGB(255, 0, 255));
			}
		}
		else if (type == graphics::Texture::eTextureType::Png)
		{
			Gdiplus::Graphics graphics(hdc);
			float centerX = pos.x;
			float centerY = pos.y;
			float testRot = 45.0f;
			graphics.TranslateTransform(centerX, centerY);   // 이미지 중심으로 원점 이동
			graphics.RotateTransform(testRot);                    // 회전
			graphics.TranslateTransform(-centerX, -centerY); // 원점 복귀

			graphics.DrawImage(
				mTexture->GetImage(),
				Gdiplus::Rect(
					centerX - (sprite.size.x * scale.x) / 2,
					centerY - (sprite.size.y * scale.y) / 2,
					sprite.size.x * scale.x,
					sprite.size.y * scale.y),
				sprite.leftTop.x,
				sprite.leftTop.y,
				sprite.size.x,
				sprite.size.y,
				Gdiplus::UnitPixel,
				nullptr);
		}
	}

	void Animation::UpdateSheet()
	{
		if (mIndex < 0 || mIndex >= (int)mSpriteSheet.size())
			return;

		if (mSpriteSheet.empty())
			return;

		mTime += Time::DeltaTime();

		if (mSpriteSheet[mIndex].duration < mTime)
		{
			mTime = 0.f;
			if (mIndex < (int)mSpriteSheet.size() - 1)
				mIndex++;
			else
				mbComplete = true;
		}
	}
}