#include "huruPlayerScript.h"
#include "huruInput.h"
#include "huruTransform.h"
#include "huruTime.h"
#include "huruGameObject.h"

namespace huru
{
	PlayerScript::PlayerScript()
	{

	}

	PlayerScript::~PlayerScript()
	{

	}

	void PlayerScript::Initialize()
	{

	}

	void PlayerScript::Update()
	{
		if (Input::GetKey(eKeyCode::Right))
		{
			Transform* tr = GetOwner()->GetComponent<Transform>();
			Vector2 pos = tr->GetPosition();
			pos.x += 100.f * Time::DeltaTime();
			tr->SetPosition(pos);
		}

		if (Input::GetKey(eKeyCode::Left))
		{
			Transform* tr = GetOwner()->GetComponent<Transform>();
			Vector2 pos = tr->GetPosition();
			pos.x -= 100.f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
	}

	void PlayerScript::LateUpdate()
	{

	}

	void PlayerScript::Render(HDC hdc)
	{

	}
}