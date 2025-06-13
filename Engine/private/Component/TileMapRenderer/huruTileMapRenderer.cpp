#include "Component/TileMapRenderer/huruTileMapRenderer.h"
#include "GameObject/huruGameObject.h"
#include "Component/Transform/huruTransform.h"
#include "Resource/huruTexture.h"
#include "Renderer/huruRenderer.h"

namespace huru
{
	math::Vector2 TileMapRenderer::SelectedIndex = math::Vector2::One;

	TileMapRenderer::TileMapRenderer() :
		Component(enums::eComponentType::TileMapRenderer),
		mTexture(nullptr),
		mSize(0.f, 0.f),
		mScale(0.f, 0.f),
		mIndex(0, 0)
	{

	}

	TileMapRenderer::~TileMapRenderer()
	{   

	}

	void TileMapRenderer::Initialize()
	{

	}

	void TileMapRenderer::Update()
	{

	}

	void TileMapRenderer::LateUpdate()
	{

	}

	void TileMapRenderer::Render(HDC hdc)
	{
		if (mTexture == nullptr)
			assert(false);

		Transform* tr = GetOwner()->GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();
		math::Vector2 scale = tr->GetScale();
		float rot = tr->GetRotation();

		pos = renderer::mainCamera->CalculatePosition(pos);

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
					mSize.x * mScale.x * scale.x,
					mSize.y * mScale.y * scale.y,
					mTexture->GetHdc(),
					mIndex.x * mSize.x,
					mIndex.y * mSize.y,
					mSize.x,
					mSize.y,
					func);
			}
			else
			{
				TransparentBlt(
					hdc,
					pos.x,
					pos.y,
					mSize.x * mScale.x * scale.x,
					mSize.y * mScale.y * scale.y,
					mTexture->GetHdc(),
					mIndex.x * mSize.x,
					mIndex.y * mSize.y,
					mSize.x,
					mSize.y,
					RGB(255, 0, 255));
			}
		}
	}
}