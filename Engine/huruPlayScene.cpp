#include "huruPlayScene.h"
#include "huruGameObject.h"
#include "huruPlayer.h"
#include "huruTransform.h"
#include "huruSpriteRenderer.h"
#include "huruInput.h"
#include "huruSceneManager.h"
#include "huruGameOverScene.h"
#include "huruObject.h"
#include "huruTexture.h"
#include "huruResources.h"
#include "huruPlayerScript.h"
#include "huruCamera.h"
#include "huruRenderer.h"
#include "huruAnimator.h"
#include "huruCat.h"
#include "huruCatScript.h"

huru::PlayScene::PlayScene()
{

}

huru::PlayScene::~PlayScene()
{

}

void huru::PlayScene::Initialize()
{
	// main camera
	GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::None, Vector2(344.f, 442.f));
	Camera* cameraComp = camera->AddComponent<Camera>();
	renderer::mainCamera = cameraComp;

	// Player
	mPlayer = object::Instantiate<Player>
		(enums::eLayerType::Player);
	PlayerScript* plScript = mPlayer->AddComponent<PlayerScript>();

	

	graphics::Texture* playerTex = 
		Resources::Find<graphics::Texture>(L"Player");

	Animator* playerAnimator = mPlayer->AddComponent<Animator>();

	playerAnimator->CreateAnimation(L"Idle", playerTex,
		Vector2(2000.0f, 250.0f), Vector2(250.0f, 250.0f), Vector2::Zero, 1, 0.1f);
	playerAnimator->CreateAnimation(L"FrontGiveWater", playerTex
		, Vector2(0.0f, 2000.0f), Vector2(250.0f, 250.0f), Vector2::Zero, 12, 0.1f);
	playerAnimator->PlayAnimation(L"Idle", false);

	playerAnimator->GetCompleteEvent(L"FrontGiveWater") = std::bind(&PlayerScript::AttackEffect, plScript);

	mPlayer->GetComponent<Transform>()->SetPosition(Vector2(100.0f, 100.0f));
	mPlayer->GetComponent<Transform>()->SetScale(Vector2(0.5f, 0.5f));

	// Cat
	Cat* cat = object::Instantiate<Cat> (enums::eLayerType::Animal);
	cat->AddComponent<CatScript>();
	cameraComp->SetTarget(cat);

	graphics::Texture* catTex =
		Resources::Find<graphics::Texture>(L"Cat");

	Animator* catAnimator = cat->AddComponent<Animator>();

	catAnimator->CreateAnimation(L"DownWalk", catTex,
		Vector2(0.f, 0.f), Vector2(32.f, 32.f), Vector2::Zero, 4, 0.2f);
	catAnimator->CreateAnimation(L"RightWalk", catTex,
		Vector2(0.f, 32.f), Vector2(32.f, 32.f), Vector2::Zero, 4, 0.2f);
	catAnimator->CreateAnimation(L"UpWalk", catTex,
		Vector2(0.f, 64.f), Vector2(32.f, 32.f), Vector2::Zero, 4, 0.2f);
	catAnimator->CreateAnimation(L"LeftWalk", catTex,
		Vector2(0.f, 96.f), Vector2(32.f, 32.f), Vector2::Zero, 4, 0.2f);
	catAnimator->CreateAnimation(L"SitDown", catTex,
		Vector2(0.f, 128.f), Vector2(32.f, 32.f), Vector2::Zero, 4, 0.2f);
	catAnimator->CreateAnimation(L"Grooming", catTex,
		Vector2(0.f, 160.f), Vector2(32.f, 32.f), Vector2::Zero, 4, 0.2f);
	catAnimator->CreateAnimation(L"LayDown", catTex,
		Vector2(0.f, 192.f), Vector2(32.f, 32.f), Vector2::Zero, 4, 0.2f);

	catAnimator->PlayAnimation(L"SitDown", false);
	cat->GetComponent<Transform>()->SetPosition(Vector2(200.f, 200.f));
	cat->GetComponent<Transform>()->SetScale(Vector2(2.f, 2.f));
	cat->GetComponent<Transform>()->SetRotation(0.f);
	
	// 게임 오브젝트 생성후에 레이어와 게임오브젝트들의 init함수를 호출
	Scene::Initialize();
}
 
void huru::PlayScene::Update()
{
	Scene::Update();
}

void huru::PlayScene::LateUpdate()
{
	Scene::LateUpdate();

	if (Input::GetKeyDown(eKeyCode::N))
	{
		SceneManager::LoadScene(L"GameOverScene");
	}
}

void huru::PlayScene::Render(HDC hdc)
{
	Scene::Render(hdc);
}

void huru::PlayScene::OnEnter()
{

}

void huru::PlayScene::OnExit()
{
	Transform* tr = mPlayer->GetComponent<Transform>();
	tr->SetPosition(Vector2(0, 0));
}
