#include "Component/Animator/huruAnimator.h"
#include "Resource/huruResources.h"
#include "Resource/huruAnimation.h"

namespace huru
{
	Animator::Animator() :
		Component(eComponentType::Animator),
		mAnimations{ },
		mActiveAnimation(nullptr),
		mbLoop(false),
		mEvents{ }
	{

	}

	Animator::~Animator()
	{
		for (auto& iter : mAnimations)
		{
			delete iter.second;
			iter.second = nullptr;
		}

		for (auto& iter : mEvents)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}

	void Animator::Initialize()
	{

	}

	void Animator::Update()
	{
		if (mActiveAnimation)
		{
			mActiveAnimation->Update();

			Events* events = FindEvents(mActiveAnimation->GetName());

			if (mActiveAnimation->IsComplete() == true)
			{
				if (events)
					events->completeEvent();

				if (mbLoop == true)
					mActiveAnimation->Reset();
			}
		}
	}

	void Animator::LateUpdate()
	{

	}

	void Animator::Render(HDC hdc)
	{
		if (mActiveAnimation)
			mActiveAnimation->Render(hdc);
	}

	void Animator::CreateAnimation(const wstring& name,
									graphics::Texture* spriteSheet,
									Vector2 leftTop, Vector2 size,
									Vector2 offset, UINT spriteLength,
									float duration)
	{
		Animation* animation = nullptr;
		animation = FindAnimation(name);
		if (animation != nullptr)
			return;

		animation = new Animation();
		animation->SetName(name);
		animation->CreateAnimation(name, spriteSheet, leftTop, size, 
										offset, spriteLength, duration);

		animation->SetAnimator(this);

		Events* events = new Events();
		mEvents.insert(make_pair(name, events));

		mAnimations.insert(make_pair(name, animation));
	}
	
	void Animator::CreateAnimationByFolder(const wstring& name, 
											const wstring& path,
											Vector2 offset,
											float duration)
	{
		Animation* animation = FindAnimation(name);
		if (animation != nullptr) return;

		int fileCount = 0;
		filesystem::path fs(path);
		vector<graphics::Texture*> images;

		for (auto& p : filesystem::directory_iterator(fs))
		{
			wstring ext = p.path().extension().wstring();
			std::transform(ext.begin(), ext.end(), ext.begin(), ::towlower);

			if (ext != L".bmp" && ext != L".png")
				continue; 

			wstring fileName = p.path().filename();
			wstring fullName = p.path();

			graphics::Texture* texture = Resources::Load<graphics::Texture>(fileName, fullName);
			if (texture)
			{
				images.push_back(texture);
				fileCount++;
			}
		}

		if (images.empty())
			return;

		UINT imageWidth = images[0]->GetWidth();
		UINT imageHeight = images[0]->GetHeight();
		UINT sheetWidth = imageWidth * fileCount;
		UINT sheetHeight = imageHeight;

		graphics::Texture* spriteSheet = graphics::Texture::Create(name, sheetWidth, sheetHeight);

		Gdiplus::Graphics graphics(spriteSheet->GetHdc());

		for (size_t i = 0; i < images.size(); ++i)
		{
			filesystem::path filepath = images[i]->GetPath();

			wstring ext = filepath.extension().wstring();
			std::transform(ext.begin(), ext.end(), ext.begin(), ::towlower);

			if (ext == L".png")
			{
				Gdiplus::Image image(filepath.c_str());
				graphics.DrawImage(&image, i * imageWidth, 0, imageWidth, imageHeight);
			}
			else if (ext == L".bmp")
			{
				BLENDFUNCTION bf = {};
				bf.BlendOp = AC_SRC_OVER;
				bf.SourceConstantAlpha = 255;
				bf.AlphaFormat = 0;

				AlphaBlend(
					spriteSheet->GetHdc(),
					i * imageWidth,
					0,
					imageWidth,
					imageHeight,
					images[i]->GetHdc(),
					0,
					0,
					imageWidth,
					imageHeight,
					bf);
			}
		}

		CreateAnimation(name, spriteSheet, Vector2::Zero,
			Vector2(imageWidth, imageHeight),
			offset, fileCount, duration);
	}

	void Animator::AddAnimation(const std::wstring& name, Animation* animation)
	{
		if (animation == nullptr)
			return;

		mAnimations[name] = animation;
	}

	Animation* Animator::FindAnimation(const wstring& name)
	{
		auto iter = mAnimations.find(name);
		if (iter == mAnimations.end())
			return nullptr;

		return iter->second;
	}

	void Animator::PlayAnimation(const wstring& name, bool loop)
	{
		Animation* animation = FindAnimation(name);
		if (animation == nullptr)
			return;
		if (mActiveAnimation)
		{
			Events* currentEvents = FindEvents(mActiveAnimation->GetName());
			if (currentEvents)
				currentEvents->endEvent();
		}

		Events* nextEvents = FindEvents(animation->GetName());
		if (nextEvents)
			nextEvents->startEvent();

		mActiveAnimation = animation;
		mActiveAnimation->Reset();
		mbLoop = loop;
	}

	Animator::Events* Animator::FindEvents(const wstring& name)
	{
		auto iter = mEvents.find(name);
		if (iter == mEvents.end())
			return nullptr;

		return iter->second;
	}

	function<void()>& Animator::GetStartEvent(const wstring& name)
	{
		Events* events = FindEvents(name);
		return events->startEvent.mEvent;
	}

	function<void()>& Animator::GetCompleteEvent(const wstring& name)
	{
		Events* events = FindEvents(name);
		return events->completeEvent.mEvent;
	}

	function<void()>& Animator::GetEndEvent(const wstring& name)
	{
		Events* events = FindEvents(name);
		return events->endEvent.mEvent;
	}
}