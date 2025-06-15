#include "Component/SpriteRenderer/huruSpriteRenderer.h"
#include "GameObject/huruGameObject.h"
#include "Component/Transform/huruTransform.h"
#include "Resource/huruTexture.h"
#include "Renderer/huruRenderer.h"

namespace huru
{
	SpriteRenderer::SpriteRenderer() :
		Component(eComponentType::SpriteRenderer),
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
		Vector2 scale = tr->GetScale();
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
			// �ȼ��� ����ȭ ��ų��
			Gdiplus::ImageAttributes imgAtt = {};

			// ����ȭ ��ų �ȼ��� �� ����
			imgAtt.SetColorKey(Gdiplus::Color(230, 230, 230),
								Gdiplus::Color(255, 255, 255));

			// �̹��� ũ�� ���
			float width = mTexture->GetWidth() * mSize.x * scale.x;
			float height = mTexture->GetHeight() * mSize.y * scale.y;

			// �߽� ��ǥ ���
			float cx = pos.x;
			float cy = pos.y;

			Gdiplus::Graphics graphics(hdc);

			// �߽� �������� �̵� -> ȸ�� -> �ٽ� �߽� ����
			graphics.TranslateTransform(cx, cy);
			graphics.RotateTransform(rot);
			graphics.TranslateTransform(-width / 2.f, -height / 2.f);

			// �߽� �������� DrawImage
			graphics.DrawImage(
				mTexture->GetImage(),
				Gdiplus::Rect(
					0,
					0,
					(int)width,
					(int)height),
				0, 0,
				mTexture->GetWidth(),
				mTexture->GetHeight(),
				Gdiplus::UnitPixel,
				nullptr);
		}
	}
}