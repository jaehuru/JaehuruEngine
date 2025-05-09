#include "huruPlayScene.h"
#include "huruGameObject.h"
#include "huruPlayer.h"
#include "huruTransform.h"
#include "huruSpriteRenderer.h"
#include "huruInput.h"
#include "huruSceneManager.h"
#include "huruGameOverScene.h"
#include "huruObject.h"

huru::PlayScene::PlayScene()
{

}

huru::PlayScene::~PlayScene()
{

}

void huru::PlayScene::Initialize()
{
	{
		bg = object::Instantiate<Player>
			(enums::eLayerType::Background, Vector2(100.f, 100.f));
		SpriteRenderer* sr = bg->AddComponent<SpriteRenderer>();
		sr->ImageLoad(L"C:\\Users\\USER-PC\\Documents\\CODING\\CPP\\JaehuruEngine\\Resources\\bg2.png");
	}

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
	wchar_t str[50] = L"Play Scene";
	TextOut(hdc, 0, 0, str, 10);
}

void huru::PlayScene::OnEnter()
{

}

void huru::PlayScene::OnExit()
{
	Transform* tr = bg->GetComponent<Transform>();
	tr->SetPosition(Vector2(0, 0));
}
