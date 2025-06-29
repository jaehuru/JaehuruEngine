#include "Resource/huruAudioClip.h"

namespace huru
{
	AudioClip::AudioClip() :
		Resource(eResourceType::AudioClip),
		mSound(nullptr),
		mChannel(nullptr), 
		mMinDistance(1.0f), 
		mMaxDistance(1000.0f), 
		mbLoop(false)
	{

	}

	AudioClip::~AudioClip()
	{
		mSound->release();
		mSound = nullptr;
	}

	HRESULT AudioClip::Load(const wstring& path)
	{
		string cPath(path.begin(), path.end());
		if (!Fmod::CreateSound(cPath, &mSound))
			return S_FALSE;

		mSound->set3DMinMaxDistance(mMinDistance, mMaxDistance);

		return S_OK;
	}

	void AudioClip::Play()
	{
		if (mbLoop)
			mSound->setMode(FMOD_LOOP_NORMAL);
		else
			mSound->setMode(FMOD_LOOP_OFF);

		Fmod::SoundPlay(mSound, &mChannel);
	}

	void AudioClip::Stop()
	{
		mChannel->stop();
	}

	void AudioClip::Set3DAttributes(const Vector3 pos)
	{
		FMOD_VECTOR fmodPos(pos.x, pos.y, pos.z);
		FMOD_VECTOR fmodVel(0.0f, 0.0f, 0.0f);

		mChannel->set3DAttributes(&fmodPos, &fmodVel);
	}
}