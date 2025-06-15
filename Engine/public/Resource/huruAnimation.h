#pragma once

#include "Resource/huruResource.h"
#include "Resource/huruTexture.h"

namespace huru
{
	using namespace graphics;

	class Animation : public Resource
	{
	public:
		struct Sprite
		{
			Vector2		leftTop;
			Vector2		size;
			Vector2		offset;
			float		duration;

			Sprite() :
				leftTop(Vector2::Zero),
				size(Vector2::Zero),
				offset(Vector2::Zero),
				duration(0.f)
			{

			}
		};

		Animation();
		~Animation();

		HRESULT		Load(const wstring& path) override;

		void		Update();
		void		Render(HDC hdc);

		//��Ʈ ��� �ִϸ��̼� ����
		void		CreateAnimation(const wstring& name,
									Texture* spriteSheet,
									Vector2 leftTop,
									Vector2 size,
									Vector2 offset,
									UINT spriteLength,
									float duration);

		// ���ο� ���� PNG ������ ��� �ִϸ��̼� ����
		void		CreateAnimation(const wstring& name,
									const vector<Texture*>& frames,
									Vector2 offset,
									float duration);

		void		Reset();

		bool		IsComplete() { return mbComplete; } 
		void		SetAnimator(class Animator* animator) { mAnimator = animator; }
		bool		IsUsingSheet() const { return mbUseSheet; }

		Texture*	GetTextureAtCurrentFrame() const;

	private:
		void		RenderFromFrames(HDC hdc);
		void		RenderFromSheet(HDC hdc);

		void		UpdateFrame();
		void		UpdateSheet();

	private:
		class Animator*				mAnimator;
		Texture*					mTexture; // ��Ʈ 
		vector<Sprite>				mAnimationSheet; 
		vector<Texture*>			mTextures; // ���� �ؽ�ó

		int							mIndex;
		float						mTime;
		bool						mbComplete;
		bool						mbUseSheet;
		Vector2						mOffset;
		float						mDuration;
	};
}

