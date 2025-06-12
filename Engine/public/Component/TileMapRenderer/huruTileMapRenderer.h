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

		void SetTexture(graphics::Texture* texture) 
		{
			mTexture = texture; 
		}
		void SetSize(Vector2 size) { mSize = size; }

		Vector2 GetIndex() { return mIndex; }
		void SetIndex(Vector2 index) { mIndex = index; }

	public:
		static Vector2 TileSize;
		static Vector2 OriginTileSize;
		static Vector2 SelectedIndex;

	private:
		graphics::Texture* mTexture;

		Vector2 mTileSize;
		Vector2 mSize;
		Vector2 mIndex;
	};
}