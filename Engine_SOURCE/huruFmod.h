#pragma once

#include "CommonInclude.h"

#include "..\\External\FMOD\\inc\\fmod_studio.hpp"
#include "..\\External\\FMOD\\inc\fmod.hpp"
#include "..\\External\\FMOD\\inc\fmod_common.h"
#include "..\\External\\FMOD\\inc\fmod_codec.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\External\\FMOD\\lib\\x64\\fmodL_vc.lib")
#pragma comment(lib, "..\\External\\FMOD\\lib\\x64\\fmodstudioL_vc.lib")
#else
#pragma comment(lib, "..\\External\\FMOD\\lib\\x64\\fmod_vc.lib")
#pragma comment(lib, "..\\External\\FMOD\\lib\\x64\\fmodstudio_vc.lib")
#endif

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

