#pragma once

#include "Component/huruComponent.h"
#include "Resource/huruTexture.h"

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
		math::Vector2 GetIndex() { return mIndex; }
		void SetIndex(math::Vector2 index) { mIndex = index; }

		void SetSize(const math::Vector2& size)
		{
			mSize = size;
		}
		void SetScale(const math::Vector2& scale)
		{
			mScale = scale;
		}

		void UpdateTileSize();

	public:
		static math::Vector2 TileSize;
		static math::Vector2 OriginTileSize;
		static math::Vector2 SelectedIndex;

	private:
		graphics::Texture* mTexture;

		math::Vector2 mSize;
		math::Vector2 mScale;
		math::Vector2 mIndex;
	};
}