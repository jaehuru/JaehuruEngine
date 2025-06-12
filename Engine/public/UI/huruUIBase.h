#pragma once

#include "Common/huruEntity.h"

namespace huru
{
	class UIBase : public Entity
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

		UIBase(enums::eUIType type);
		virtual ~UIBase();

		/// <summary>
		/// ui가 로드 되었을 초기화 해주는 함수
		/// </summary>
		void Initialize();
		/// <summary>
		/// ui가 활성화되면 호출되는 함수
		/// </summary>
		void Active();
		/// <summary>
		/// ui가 비활성화되면 호출되는 함수
		/// </summary>
		void InActive();
		void Update();
		void LateUpdate();
		void Render(HDC hdc);
		/// <summary>
		/// UI가 사라질 호출되는 함수
		/// </summary>
		void UIClear();

		virtual void OnInit();
		virtual void OnActive();
		virtual void OnInActive();
		virtual void OnUpdate();
		virtual void OnLateUpdate();
		virtual void OnRender(HDC hdc);
		virtual void OnClear();

		enums::eUIType GetType() { return mType; }
		void SetType(enums::eUIType type) { mType = type; }
		void SetFullScreen(bool enable) { mbFullScreen = enable; }
		bool IsFullScreen() { return mbFullScreen; }
		math::Vector2 GetPos() { return mPosition; }
		void SetPos(math::Vector2 position) { mPosition = position; }
		math::Vector2 GetSize() { return mSize; }
		void SetSize(math::Vector2 size) { mSize = size; }

	protected:
		math::Vector2 mPosition;
		math::Vector2 mSize;
		bool mbMouseOn;

	private:
		enums::eUIType mType;
		bool mbFullScreen;
		bool mbEnabled;
		UIBase* mParent;
	};
}

