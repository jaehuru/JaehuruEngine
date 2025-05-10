#include "huruSpriteRenderer.h"
#include "huruGameObject.h"
#include "huruTransform.h"
#include "huruTexture.h"

namespace huru
{
	SpriteRenderer::SpriteRenderer() :
		Component(enums::eComponentType::SpriteRenderer),
		mTexture(nullptr),
		mSize(Vector2::One)

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
		Vector2 pos = tr->GetPosition();

		if (mTexture->GetTextureType() == graphics::Texture::eTextureType::Bmp)
		{
			TransparentBlt(hdc, (int)pos.x, (int)pos.y,
				mTexture->GetWidth() * (int)mSize.x,
				mTexture->GetHeight() * (int)mSize.y,
				mTexture->GetHdc(), 0, 0,
				mTexture->GetWidth(), mTexture->GetHeight(),
				RGB(255, 0, 255));
		}
		else if (mTexture->GetTextureType() == graphics::Texture::eTextureType::Png)
		{
			Gdiplus::Graphics graphics(hdc);
			graphics.DrawImage(
				mTexture->GetImage(),
				Gdiplus::Rect(
					(int)pos.x,
					(int)pos.y, 
					mTexture->GetWidth() * (int)mSize.x,
					mTexture->GetHeight() * (int)mSize.y));
		}
	}
}