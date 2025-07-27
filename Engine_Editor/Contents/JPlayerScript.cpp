#include "JPlayerScript.h"
#include "AProjectTile.h"
//Engine
#include "Helpers/Input.h"
#include "Component/SpriteRenderer/JSpriteRenderer.h"
#include "Object/JObject.h"
#include "Resource/RResources.h"
#include "Resource/RTexture.h"


JPlayerScript::JPlayerScript()
{

}

JPlayerScript::~JPlayerScript()
{

}

void JPlayerScript::Initialize()
{

}

void JPlayerScript::Update()
{
	static FVector3 postions = FVector3(-1, 1, 0);

	if (Input::GetKeyDown(EKeyCode::N))
	{
		mProjTile = Instantiate<AProjectTile>(ELayerType::Player, postions);
		JSpriteRenderer* sr = mProjTile->AddComponent<JSpriteRenderer>();
		sr->SetSprite(RResources::Find<RTexture>(L"Player"));
		postions.x += 1.0f;
	}

	if (Input::GetKeyDown(EKeyCode::D))
	{
		if (mProjTile != nullptr)
		{
			Destroy(mProjTile);
			mProjTile = nullptr;
		}
	}
}

void JPlayerScript::LateUpdate()
{

}

void JPlayerScript::Render()
{

}