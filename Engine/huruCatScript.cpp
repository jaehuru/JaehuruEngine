#include "huruCatScript.h"
#include "huruInput.h"
#include "huruTransform.h"
#include "huruTime.h"
#include "huruGameObject.h"
#include "huruAnimator.h"

namespace huru
{
	CatScript::CatScript() :
		mState(CatScript::eState::SitDown),
		mAnimator(nullptr),
		mTime(0.f)
	{

	}

	CatScript::~CatScript()
	{

	}

	void CatScript::Initialize()
	{

	}

	void CatScript::Update()
	{
		if (mAnimator == nullptr)
			mAnimator = GetOwner()->GetComponent<Animator>();

		switch (mState)
		{
		case huru::CatScript::eState::SitDown:
			sitDown();
			break;
		case huru::CatScript::eState::Walk:
			move();
			break;
		case huru::CatScript::eState::Sleep:

			break;
		case huru::CatScript::eState::LayDown:

			break;
		case huru::CatScript::eState::Attack:

			break;
		default:
			break;
		}
	}

	void CatScript::LateUpdate()
	{

	}

	void CatScript::Render(HDC hdc)
	{

	}
	void CatScript::sitDown()
	{
		mTime += Time::DeltaTime();
		if (mTime > 3.f)
		{
			mState = CatScript::eState::Walk;
			int direction = (rand() % 4);
			mDirection = static_cast<eDirection>(direction);
			playWalkAnimationByDirection(mDirection);
			mTime = 0.f;
		}
	}

	void CatScript::move()
	{
		mTime += Time::DeltaTime();
		if (mTime > 2.f)
		{
			int isLayDown = rand() % 2;
			if (isLayDown)
			{
				mState = eState::LayDown;
				mAnimator->PlayAnimation(L"LayDown", false);
			}
			else
			{
				mState = eState::SitDown;
				mAnimator->PlayAnimation(L"SitDown", false);
			}
		}
		Transform* tr = GetOwner()->GetComponent<Transform>();
		translate(tr);
	}

	void CatScript::layDown()
	{

	}

	void CatScript::playWalkAnimationByDirection(eDirection dir)
	{
		switch (dir)
		{
		case huru::CatScript::eDirection::Left:
			mAnimator->PlayAnimation(L"LeftWalk", true);
			break;
		case huru::CatScript::eDirection::Right:
			mAnimator->PlayAnimation(L"RightWalk", true);
			break;
		case huru::CatScript::eDirection::Down:
			mAnimator->PlayAnimation(L"DownWalk", true);
			break;
		case huru::CatScript::eDirection::Up:
			mAnimator->PlayAnimation(L"UpWalk", true);
			break;
		default:
			assert(false);
			break;
		}
	}
	void CatScript::translate(Transform* tr)
	{
		Vector2 pos = tr->GetPosition();
		switch (mDirection)
		{
		case huru::CatScript::eDirection::Left:
			pos.x -= 100.f * Time::DeltaTime();
			break;
		case huru::CatScript::eDirection::Right:
			pos.x += 100.f * Time::DeltaTime();
			break;
		case huru::CatScript::eDirection::Down:
			pos.y += 100.f * Time::DeltaTime();
			break;
		case huru::CatScript::eDirection::Up:
			pos.y -= 100.f * Time::DeltaTime();
			break;
		default:
			assert(false);
			break;
		}
		tr->SetPosition(pos);
	}
}