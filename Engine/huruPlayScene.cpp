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
#include "huruBoxCollider2D.h"
#include "huruCircleCollider2D.h"
#include "huruCollisionManager.h"
#include "huruTile.h"
#include "huruTilemapRenderer.h"
#include "huruRigidbody.h"

huru::PlayScene::PlayScene()
{

}

huru::PlayScene::~PlayScene()
{

}

void huru::PlayScene::Initialize()
{
	// main camera
	GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::Particle, Vector2(344.0f, 442.0f));
	Camera* cameraComp = camera->AddComponent<Camera>();
	renderer::mainCamera = cameraComp;

	mPlayer = object::Instantiate<Player>(enums::eLayerType::Player);
	PlayerScript* plScript = mPlayer->AddComponent<PlayerScript>();
	object::DonDestroyOnLoad(mPlayer);

	//BoxCollider2D* collider = mPlayer->AddComponent<BoxCollider2D>();
	CircleCollider2D* collider = mPlayer->AddComponent<CircleCollider2D>();
	collider->SetOffset(Vector2(-50.f, -50.f));


	graphics::Texture* playerTex = Resources::Find<graphics::Texture>(L"Player");
	Animator* playerAnimator = mPlayer->AddComponent<Animator>();
	playerAnimator->CreateAnimation(L"Idle", playerTex
		, Vector2(2000.0f, 250.0f), Vector2(250.0f, 250.0f), Vector2::Zero, 1, 0.1f);
	playerAnimator->CreateAnimation(L"FrontGiveWater", playerTex
		, Vector2(0.0f, 2000.0f), Vector2(250.0f, 250.0f), Vector2::Zero, 12, 0.1f);
	playerAnimator->PlayAnimation(L"Idle", false);

	playerAnimator->GetCompleteEvent(L"FrontGiveWater") = std::bind(&PlayerScript::AttackEffect, plScript);

	//playerAnimator->
	mPlayer->GetComponent<Transform>()->SetPosition(Vector2(400.0f, 250.0f));
	//mPlayer->GetComponent<Transform>()->SetScale(Vector2(2.0f, 2.0f));
	mPlayer->AddComponent<Rigidbody>();


	//CAT
	Cat* cat = object::Instantiate<Cat>(enums::eLayerType::Animal);
	//cat->SetActive(true);
	cat->AddComponent<CatScript>();
	//cameraComp->SetTarget(cat);
	graphics::Texture* catTex = Resources::Find<graphics::Texture>(L"Cat");
	Animator* catAnimator = cat->AddComponent<Animator>();
	BoxCollider2D* catCollider = cat->AddComponent<BoxCollider2D>();
	//CircleCollider2D* catCollider = cat->AddComponent<CircleCollider2D>();
	catCollider->SetOffset(Vector2(-50.f, -50.f));
	//catAnimator->CreateAnimation(L"DownWalk", catTex
	//	, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
	//catAnimator->CreateAnimation(L"RightWalk", catTex
	//	, Vector2(0.0f, 32.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
	//catAnimator->CreateAnimation(L"UpWalk", catTex
	//	, Vector2(0.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
	//catAnimator->CreateAnimation(L"LeftWalk", catTex
	//	, Vector2(0.0f, 96.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
	//catAnimator->CreateAnimation(L"SitDown", catTex
	//	, Vector2(0.0f, 128.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
	//catAnimator->CreateAnimation(L"Grooming", catTex
	//	, Vector2(0.0f, 160.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
	//catAnimator->CreateAnimation(L"LayDown", catTex
	//	, Vector2(0.0f, 192.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);

	//catAnimator->PlayAnimation(L"SitDown", false);
	catAnimator->CreateAnimationByFolder(L"MushroomIdle", L"..\\Resources\\Mushroom", Vector2::Zero, 0.1f);

	catAnimator->PlayAnimation(L"MushroomIdle", true);

	cat->GetComponent<Transform>()->SetPosition(Vector2(200.0f, 200.0f));
	cat->GetComponent<Transform>()->SetScale(Vector2(1.0f, 1.0f));
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
	Scene::OnEnter();

	CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Animal, true);
}

void huru::PlayScene::OnExit()
{
	Scene::OnExit();
}
