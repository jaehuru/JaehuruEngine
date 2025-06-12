#include "Component/SpriteRenderer/huruSpriteRenderer.h"
#include "GameObject/huruGameObject.h"
#include "Component/Transform/huruTransform.h"
#include "Resource/huruTexture.h"
#include "Renderer/huruRenderer.h"

namespace huru
{
	SpriteRenderer::SpriteRenderer() :
		Component(enums::eComponentType::SpriteRenderer),
		mTexture(nullptr),
		mSize(math::Vector2::One)

	{

	}

	SpriteRenderer::~SpriteRenderer()
	{

	}

	void SpriteRenderer::Initialize()
	{

	}

	void SpriteRenderer::Update()
	{

	}

	void SpriteRenderer::LateUpdate()
	{

	}

	void SpriteRenderer::Render(HDC hdc)
	{
		if (mTexture == nullptr)
			assert(false);

		Transform* tr = GetOwner()->GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();
		math::Vector2 scale = tr->GetScale();
		float rot = tr->GetRotation();

		pos = renderer::mainCamera-> CalculatePosition(pos);

		if (mTexture->GetTextureType() == graphics::Texture::eTextureType::Bmp)
		{
			if (mTexture->IsAlpha())
			{
				BLENDFUNCTION func = { };
				func.BlendOp = AC_SRC_OVER;
				func.BlendFlags = 0;
				func.AlphaFormat = AC_SRC_ALPHA;
				func.SourceConstantAlpha = 255; // 0(Transparent) ~ 255(Opaque)

				AlphaBlend(
					hdc,
					pos.x,
					pos.y,
					mTexture->GetWidth() * mSize.x * scale.x,
					mTexture->GetHeight() * mSize.y * scale.y,
					mTexture->GetHdc(),
					0,
					0,
					mTexture->GetWidth(),
					mTexture->GetHeight(),
					func);
			}
			else
			{
				TransparentBlt(
					hdc,
					pos.x,
					pos.y,
					mTexture->GetWidth() * mSize.x * scale.x,
					mTexture->GetHeight() * mSize.y * scale.y,
					mTexture->GetHdc(),
					0,
					0,
					mTexture->GetWidth(),
					mTexture->GetHeight(),
					RGB(255, 0, 255));
			}
		}
		else if (mTexture->GetTextureType() == graphics::Texture::eTextureType::Png)
		{
			// 픽셀을 투명화 시킬때
			Gdiplus::ImageAttributes imgAtt = {};

			// 투명화 시킬 픽셀의 색 범위
			imgAtt.SetColorKey(Gdiplus::Color(230, 230, 230),
				Gdiplus::Color(255, 255, 255));

			Gdiplus::Graphics graphics(hdc);

			graphics.TranslateTransform(pos.x, pos.y);
			graphics.RotateTransform(rot);
			graphics.TranslateTransform(-pos.x, -pos.y);

			graphics.DrawImage(
				mTexture->GetImage(),
				Gdiplus::Rect
				(
					(int)pos.x,
					(int)pos.y,
					mTexture->GetWidth() * mSize.x * scale.x,
					mTexture->GetHeight() * mSize.y * scale.y
				),
				0, 0,
				mTexture->GetWidth(),
				mTexture->GetHeight(),
				Gdiplus::UnitPixel,
				nullptr);
		}
	}
}