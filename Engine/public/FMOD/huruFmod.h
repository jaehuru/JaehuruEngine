#pragma once

#include "Common/CommonInclude.h"

#include "../../../External\FMOD\\inc\\fmod_studio.hpp"
#include "../../../External\\FMOD\\inc\fmod.hpp"
#include "../../../External\\FMOD\\inc\fmod_common.h"
#include "../../../External\\FMOD\\inc\fmod_codec.h"

namespace huru
{
	using namespace math;
	class Fmod
	{
	public:
		static void Initialize();
		static bool CreateSound(const std::string& path, FMOD::Sound** sound);
		static void SoundPlay(FMOD::Sound* sound, FMOD::Channel** channel);
		static void Set2DListenerAttributes(const Vector2* pos);
		static void Release();

	private:
		static FMOD::Studio::System* mSystem;
		static FMOD::System* mCoreSystem;
	};
}

