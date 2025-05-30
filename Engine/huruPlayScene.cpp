#include "huruPlayScene.h"
#include "huruGameObject.h"
#include "huruPlayer.h"
#include "huruUIManager.h"
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
#include "huruFloor.h"
#include "huruFloorScript.h"

huru::PlayScene::PlayScene()
{

}

huru::PlayScene::~PlayScene()
{

}

void huru::PlayScene::Initialize()
{
	// Camera
	GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::Particle, Vector2(344.0f, 442.0f));
	Camera* cameraComp = camera->AddComponent<Camera>();
	renderer::mainCamera = cameraComp;



	// Player
	mPlayer = object::Instantiate<Player>(enums::eLayerType::Player);
	cameraComp->SetTarget(mPlayer);
	object::DonDestroyOnLoad(mPlayer);
	PlayerScript* plScript = mPlayer->AddComponent<PlayerScript>();

	BoxCollider2D* collider = mPlayer->AddComponent<BoxCollider2D>();

	graphics::Texture* playerTex = Resources::Find<graphics::Texture>(L"Player");

	Animator* playerAnimator = mPlayer->AddComponent<Animator>();
	playerAnimator->CreateAnimation(L"Idle", playerTex
		, Vector2(2000.0f, 250.0f), Vector2(250.0f, 250.0f), Vector2::Zero, 1, 0.1f);
	playerAnimator->CreateAnimation(L"FrontGiveWater", playerTex
		, Vector2(0.0f, 2000.0f), Vector2(250.0f, 250.0f), Vector2::Zero, 12, 0.1f);
	playerAnimator->PlayAnimation(L"Idle", false);
	playerAnimator->GetCompleteEvent(L"FrontGiveWater") = std::bind(&PlayerScript::AttackEffect, plScript);

	mPlayer->GetComponent<Transform>()->SetPosition(Vector2(300.f, 250.0f));
	mPlayer->AddComponent<Rigidbody>();




	// Floor
	Floor* floor = object::Instantiate<Floor>(eLayerType::Floor, Vector2(100.0f, 600.0f));
	floor->SetName(L"Floor");
	BoxCollider2D* floorCol = floor->AddComponent<BoxCollider2D>();
	floorCol->SetSize(Vector2(10.0f, 1.0f));
	floor->AddComponent<FloorScript>();




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

	CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Floor, true);

	UIManager::Push(eUIType::Button);
}

void huru::PlayScene::OnExit()
{
	UIManager::Pop(eUIType::Button);

	Scene::OnExit();
}
