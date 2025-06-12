#pragma once

#include "FMOD/huruFmod.h"
#include "Resource/huruResource.h"

namespace huru
{
	class AudioClip : public Resource
	{
	public:
		AudioClip();
		virtual ~AudioClip();

		virtual HRESULT Load(const std::wstring& path) override;

		void			Play();
		void			Stop();
		void			Set2DAttributes(const math::Vector2 pos);
		void			SetLoop(bool loop) { mbLoop = loop; }

	private:
		FMOD::Sound*		mSound;
		FMOD::Channel*		mChannel;
		float				mMinDistance;
		float				mMaxDistance;
		bool				mbLoop;
	};
}

