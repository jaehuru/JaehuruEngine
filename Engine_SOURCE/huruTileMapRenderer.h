#pragma once

#include "huruEntity.h"
#include "huruComponent.h"
#include "huruTexture.h"

namespace huru
{
	class TileMapRenderer : public Component
	{
	public:
		TileMapRenderer();
		~TileMapRenderer();

		void Initialize() override;
		void Update()  override;
		void LateUpdate()  override;
		void Render(HDC hdc)  override;

		void SetTexture(graphics::Texture* texture) { mTexture = texture; }
		void SetSize(Vector2 size) { mSize = size; }
	private:
		graphics::Texture* mTexture;

		Vector2 mTileSize;
		Vector2 mSize;
		Vector2 mIndex;
	};
}