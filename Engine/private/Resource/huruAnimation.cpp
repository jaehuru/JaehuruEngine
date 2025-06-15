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
		mFrames{ },
		mIndex(-1),
		mTime(0.f),
		mbComplete(false),
        mbUseSheet(true)
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
		if (mbComplete)
			return;

		mTime += Time::DeltaTime();

		if (!mbUseSheet)
		{
			if (mFrames[mIndex].duration < mTime)
			{
				mTime = 0.f;
				if (mIndex < (int)mFrames.size() - 1)
					mIndex++;
				else
					mbComplete = true;
			}
		}
		else
		{
			if (mFrames[mIndex].duration < mTime)
			{
				mTime = 0.f;
				if (mIndex < (int)mFrames.size() - 1)
					mIndex++;
				else
					mbComplete = true;
			}
		}
	}

	void Animation::Render(HDC hdc)
	{
		if (mbUseSheet)
			RenderFromSheet(hdc);
		else
			RenderFromFrames(hdc);
	}

	void Animation::CreateAnimation(const wstring& name,
									graphics::Texture* spriteSheet,
									Vector2 leftTop, Vector2 size,
									Vector2 offset, UINT spriteLength,
									float duration)
	{
        mbUseSheet = true;
		mTexture = spriteSheet;
		for (size_t i = 0; i < spriteLength; i++)
		{
			Sprite sprite = { };
			sprite.leftTop.x = leftTop.x + size.x * i;
			sprite.leftTop.y = leftTop.y;
			sprite.size = size;
			sprite.offset = offset;
			sprite.duration = duration;

			mFrames.push_back(sprite);
		}
	}

	void Animation::CreateAnimation(const wstring& name, 
									const vector<graphics::Texture*>& frames,
									Vector2 offset,
									float duration)
	{
		mbUseSheet = false;
		mTextures = frames;
		mFrames.clear();

		for (size_t i = 0; i < frames.size(); i++)
		{
			Sprite sprite;
			sprite.offset = offset;
			sprite.duration = duration;
			mFrames.push_back(sprite);
		}

		mIndex = 0;
		mTime = 0.f;
		mbComplete = false;
	}

	void Animation::Reset()
	{
		mTime = 0;
		mIndex = 0.f;
		mbComplete = false;
	}

    Texture* Animation::GetTextureAtCurrentFrame() const
    {
        if (mbUseSheet)
            return mTexture;

        if (mIndex < mTextures.size())
            return mTextures[mIndex];

        return nullptr;
    }

	void Animation::RenderFromFrames(HDC hdc)
	{
		if (mTextures.empty() || mIndex < 0 || mIndex >= (int)mTextures.size())
			return;

		graphics::Texture* texture = mTextures[mIndex];
		if (!texture) return;

		GameObject* gameObj = mAnimator->GetOwner();
		Transform* tr = gameObj->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		float rot = tr->GetRotation();
		Vector2 scale = tr->GetScale();

		if (renderer::mainCamera)
			pos = renderer::mainCamera->CalculatePosition(pos);

		Sprite& sprite = mFrames[mIndex];
		Gdiplus::Image* img = texture->GetImage();

		Gdiplus::Graphics graphics(hdc);
		graphics.TranslateTransform(pos.x, pos.y);
		graphics.RotateTransform(rot);
		graphics.TranslateTransform(-pos.x, -pos.y);

		graphics.DrawImage(
			img,
			Gdiplus::Rect(
				pos.x - (img->GetWidth() / 2) + sprite.offset.x,
				pos.y - (img->GetHeight() / 2) + sprite.offset.y,
				img->GetWidth() * scale.x,
				img->GetHeight() * scale.y),
			0, 0,
			img->GetWidth(),
			img->GetHeight(),
			Gdiplus::UnitPixel,
			nullptr);
	}

	void Animation::RenderFromSheet(HDC hdc)
	{
		if (!mTexture) return;

		GameObject* gameObj = mAnimator->GetOwner();
		Transform* tr = gameObj->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		float rot = tr->GetRotation();
		Vector2 scale = tr->GetScale();

		if (renderer::mainCamera)
			pos = renderer::mainCamera->CalculatePosition(pos);

		Sprite& sprite = mFrames[mIndex];
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
			graphics.TranslateTransform(pos.x, pos.y);
			graphics.RotateTransform(rot);
			graphics.TranslateTransform(-pos.x, -pos.y);

			graphics.DrawImage(
				mTexture->GetImage(),
				Gdiplus::Rect(
					pos.x - (sprite.size.x / 2.f),
					pos.y - (sprite.size.y / 2.f),
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
}