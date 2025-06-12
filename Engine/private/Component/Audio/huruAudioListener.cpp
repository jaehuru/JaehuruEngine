#include "Component/Audio/huruAudioListener.h"
#include "Component/Transform/huruTransform.h"
#include "GameObject/huruGameObject.h"
#include "FMOD/huruFmod.h"

namespace huru
{
	AudioListener::AudioListener()
		: Component(enums::eComponentType::AudioListener)
	{
	}

	AudioListener::~AudioListener()
	{
	}

	void AudioListener::Initialize()
	{
	}

	void AudioListener::Update()
	{
	}

	void AudioListener::LateUpdate()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();

		Fmod::Set2DListenerAttributes(&pos);
	}

	void AudioListener::Render(HDC hdc)
	{
	}
}