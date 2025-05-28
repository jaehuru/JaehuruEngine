#include "huruAudioClip.h"

namespace huru
{
	AudioClip::AudioClip() :
		Resource(enums::eResourceType::AudioClip),
		mSound(nullptr),
		mChannel(nullptr)
	{

	}

	AudioClip::~AudioClip()
	{

	}

	HRESULT AudioClip::Load(const std::wstring& path)
	{
		std::string cPath(path.begin(), path.end());
		if (!Fmod::CreateSound(cPath, &mSound))
			return S_FALSE;

		return E_NOTIMPL;
	}
}