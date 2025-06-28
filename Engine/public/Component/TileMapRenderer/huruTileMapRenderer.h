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

		void SetTexture(Texture* texture) { mTexture = texture; }
		Vector2 GetIndex() { return mIndex; }
		void SetIndex(Vector2 index) { mIndex = index; }
		void SetSize(const Vector2& size) { mSize = size; }
		void SetScale(const Vector2& scale) { mScale = scale; }


	public:
		static Vector2 SelectedIndex;

	private:
		Texture* mTexture;

		Vector2 mSize;
		Vector2 mScale;
		Vector2 mIndex;
	};
}