#pragma once

#include "Resource/huruResource.h"
#include "Resource/huruTexture.h"

namespace huru
{
	class Animation : public Resource
	{
	public:
		struct Sprite
		{
			math::Vector2 leftTop;
			math::Vector2 size;
			math::Vector2 offset;
			float duration;

			Sprite() :
				leftTop(math::Vector2::Zero),
				size(math::Vector2::Zero),
				offset(math::Vector2::Zero),
				duration(0.f)
			{

			}
		};

		Animation();
		~Animation();

		HRESULT Load(const std::wstring& path) override;

		void Update();
		void Render(HDC hdc);

		void		CreateAnimation(const std::wstring& name,
									graphics::Texture* spriteSheet,
									math::Vector2 leftTop,
									math::Vector2 size,
									math::Vector2 offset,
									UINT spriteLength,
									float duration);

		void Reset();

		bool IsComplete() { return mbComplete; } 
		void SetAnimator(class Animator* animator) { mAnimator = animator; }

	private:
		class Animator*			mAnimator;
		graphics::Texture*		mTexture;

		std::vector<Sprite>		mAnimationSheet;
		int						mIndex;
		float					mTime;
		bool					mbComplete;
	};
}

