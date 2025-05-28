#pragma once

#include "huruFmod.h"
#include "huruResource.h"

namespace huru
{
	class AudioClip : public Resource
	{
	public:
		AudioClip();
		~AudioClip() override;

		HRESULT Load(const std::wstring& path) override;

	private:
		FMOD::Sound* mSound;
		FMOD::Channel* mChannel;
	};
}

