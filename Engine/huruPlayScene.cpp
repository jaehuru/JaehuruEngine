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

	mPlayer = object::Instantiate<Player>
		(enums::eLayerType::Player);
	mPlayer->AddComponent<PlayerScript>();

	graphics::Texture* pacmanTextuer = 
		Resources::Find<graphics::Texture>(L"Cat");

	// 애니메이션 동작
	Animator* animator = mPlayer->AddComponent<Animator>();
	animator->CreateAnimation(L"CatFrontMove", pacmanTextuer, 
		Vector2(0.f, 0.f), Vector2(32.f, 32.f), Vector2::Zero, 4, 0.2f);
	animator->PlayAnimation(L"CatFrontMove");
	
	GameObject* bg = object::Instantiate<GameObject>
		(enums::eLayerType::Background);
	SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
	bgsr->SetSize(Vector2(3.f, 3.f));

	graphics::Texture* bgTexture = Resources::Find<graphics::Texture>(L"Map");
	bgsr->SetTexture(bgTexture);
	
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
