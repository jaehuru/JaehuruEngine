#pragma once

#include "Component/huruComponent.h"
#include "Resource/huruAnimation.h"


namespace huru
{
	class Animator : public Component
	{
	public:
		struct Event
		{
			void operator=(std::function<void()> func)
			{
				mEvent = std::move(func);
			}

			void operator()()
			{
				if (mEvent)
					mEvent();
			}

			std::function<void()> mEvent;
		};

		struct Events
		{
			Event startEvent;
			Event completeEvent;
			Event endEvent;
		};

		Animator();
		~Animator();

		void	Initialize() override;
		void	Update() override;
		void	LateUpdate() override;
		void	Render(HDC hdc) override;

		void	CreateAnimation(const std::wstring& name,
								graphics::Texture* spriteSheet,
								math::Vector2 leftTop,
								math::Vector2 size,
								math::Vector2 offset,
								UINT spriteLength,
								float duration);
		void	CreateAnimationByFolder(const std::wstring& name,
										const std::wstring& path,
										math::Vector2 offset,
										float duration);
		Animation* FindAnimation(const std::wstring& name);
		void PlayAnimation(const std::wstring& name, bool loop);

		Events* FindEvents(const std::wstring& name);
		std::function<void()>& GetStartEvent(const std::wstring& name);
		std::function<void()>& GetCompleteEvent(const std::wstring& name);
		std::function<void()>& GetEndEvent(const std::wstring& name);

		bool IsComplete() { return mActiveAnimation->IsComplete(); }

	private:
		std::map<std::wstring, Animation*> mAnimations;
		Animation* mActiveAnimation;
		bool mbLoop;

		//Event
		std::map<std::wstring, Events*> mEvents;
	};
}

