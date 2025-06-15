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
		mTextures{ },
		mAnimationSheet{ },
		mIndex(-1),
		mTime(0.f),
		mbComplete(false),
        mbUseSheet(true),
		mOffset(Vector2::One),
		mDuration(0.f)
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

		if (mbUseSheet)
			UpdateSheet();
		else
			UpdateFrame();
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

			mAnimationSheet.push_back(sprite);
		}
	}

	void Animation::CreateAnimation(const wstring& name, 
									const vector<graphics::Texture*>& frames,
									Vector2 offset,
									float duration)
	{
		mbUseSheet = false;

		mTextures = frames;  
		mAnimationSheet.clear();  
		mOffset = offset;  
		mDuration = duration;
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

		Gdiplus::Image* img = texture->GetImage();

		// 독립 텍스처는 보통 전체 이미지가 한 프레임이므로 offset을 별도로 멤버로 관리한다고 가정
		Vector2 offset = mOffset; // 멤버 변수로 offset 관리 (없으면 Vector2::Zero로 대체)

		Gdiplus::Graphics graphics(hdc);
		graphics.TranslateTransform(pos.x, pos.y);
		graphics.RotateTransform(rot);
		graphics.TranslateTransform(-pos.x, -pos.y);

		graphics.DrawImage(
			img,
			Gdiplus::Rect(
				pos.x - (img->GetWidth() / 2) + offset.x,
				pos.y - (img->GetHeight() / 2) + offset.y,
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

		if (mIndex < 0 || mIndex >= (int)mAnimationSheet.size()) 
			return; 

		GameObject* gameObj = mAnimator->GetOwner();
		Transform* tr = gameObj->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		float rot = tr->GetRotation();
		Vector2 scale = tr->GetScale();

		if (renderer::mainCamera)
			pos = renderer::mainCamera->CalculatePosition(pos);

		Sprite& sprite = mAnimationSheet[mIndex];
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

	void Animation::UpdateFrame()
	{
		if (mTextures.empty())
			return;

		mTime += Time::DeltaTime();

		if (mTime >= mDuration)
		{
			mTime = 0.f;
			if (mIndex < (int)mTextures.size() - 1)
				mIndex++;
			else
				mbComplete = true;
		}
	}

	void Animation::UpdateSheet()
	{
		if (mIndex < 0 || mIndex >= (int)mAnimationSheet.size())
			return;

		if (mAnimationSheet.empty())
			return;

		mTime += Time::DeltaTime();

		if (mAnimationSheet[mIndex].duration < mTime)
		{
			mTime = 0.f;
			if (mIndex < (int)mAnimationSheet.size() - 1)
				mIndex++;
			else
				mbComplete = true;
		}
	}
}