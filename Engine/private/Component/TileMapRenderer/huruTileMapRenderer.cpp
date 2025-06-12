#include "Component/TileMapRenderer/huruTileMapRenderer.h"
#include "GameObject/huruGameObject.h"
#include "Component/Transform/huruTransform.h"
#include "Resource/huruTexture.h"
#include "Renderer/huruRenderer.h"

namespace huru
{
	Vector2 TileMapRenderer::TileSize = Vector2::One;
	Vector2 TileMapRenderer::OriginTileSize = Vector2::One;
	Vector2 TileMapRenderer::SelectedIndex = Vector2::One;

	TileMapRenderer::TileMapRenderer() :
		Component(eComponentType::TileMapRenderer),
		mTexture(nullptr),
		mTileSize(16.f, 16.f),
		mSize(3.f, 3.f),
		mIndex(0, 0)
	{
		TileSize = mTileSize * mSize;
		OriginTileSize = mTileSize;
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
		Vector2 pos = tr->GetPosition();
		Vector2 scale = tr->GetScale();
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
					mTileSize.x * mSize.x * scale.x,
					mTileSize.y * mSize.y * scale.y,
					mTexture->GetHdc(),
					mIndex.x * mTileSize.x,
					mIndex.y * mTileSize.y,
					mTileSize.x,
					mTileSize.y,
					func);
			}
			else
			{
				TransparentBlt(
					hdc,
					pos.x,
					pos.y,
					mTileSize.x * mSize.x * scale.x,
					mTileSize.y * mSize.y * scale.y,
					mTexture->GetHdc(),
					mIndex.x * mTileSize.x,
					mIndex.y * mTileSize.y,
					mTileSize.x,
					mTileSize.y,
					RGB(255, 0, 255));
			}
		}
	}
}