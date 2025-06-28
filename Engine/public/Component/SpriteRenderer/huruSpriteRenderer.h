#pragma once

#include "Component/huruComponent.h"
#include "Resource/huruTexture.h"

namespace huru
{
	class SpriteRenderer : public Component
	{
	public:
		SpriteRenderer();
		~SpriteRenderer();

		void	Initialize()	override;
		void	Update()		override;
		void	LateUpdate()	override;
		void	Render()		override;

		void	SetTexture(Texture* texture)	{ mTexture = texture; }
		void	SetSize(Vector2 size)			{ mSize = size; }

	private:
		Texture*		mTexture;
		Vector2			mSize;

	};
}