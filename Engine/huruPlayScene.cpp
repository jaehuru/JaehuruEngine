#include "huruPlayScene.h"
#include "huruGameObject.h"
#include "huruUIManager.h"
#include "huruTransform.h"
#include "huruSpriteRenderer.h"
#include "huruInput.h"
#include "huruSceneManager.h"
#include "huruGameOverScene.h"
#include "huruObject.h"
#include "huruTexture.h"
#include "huruResources.h"
#include "huruCamera.h"
#include "huruRenderer.h"
#include "huruAnimator.h"
#include "huruBoxCollider2D.h"
#include "huruCircleCollider2D.h"
#include "huruCollisionManager.h"
#include "huruTile.h"
#include "huruTilemapRenderer.h"
#include "huruRigidbody.h"
#include "huruAudioClip.h"
#include "huruAudioListener.h"
#include "huruAudioSource.h"
#include "huruToolScene.h"

huru::PlayScene::PlayScene()
{

}

huru::PlayScene::~PlayScene()
{

}

void huru::PlayScene::Initialize()
{
	ToolScene toolSceneInstance;
	toolSceneInstance.LoadMapFile(L"..\\Resources\\test");

	//Camera
	GameObject* camera = Instantiate<GameObject>(eLayerType::Particle, Vector2(344.0f, 442.0f));
	Camera* cameraComp = camera->AddComponent<Camera>();
	renderer::mainCamera = cameraComp;



	// Player
	

	// Sound
	//AudioClip* ac = Resources::Load<AudioClip>(L"BGSound", L"..\\Resources\\Sound\\...");


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
