#include "JPlayScene.h"
#include "APlayer.h"
#include "JCameraScript.h"
#include "JPlayerScript.h"
//Engine
#include "Graphics/RGraphicDevice_DX11.h"
#include "Object/JObject.h"
#include "Component/SpriteRenderer/JSpriteRenderer.h"
#include "Resource/RResources.h"
#include "Resource/RMaterial.h"
#include "Resource/RTexture.h"
#include "Component/Camera/JCamera.h"
#include "Renderer/RRenderer.h"


JPlayScene::JPlayScene()
{

}

JPlayScene::~JPlayScene()
{

}

void JPlayScene::Initialize()
{
	JScene::Initialize();

	// main camera
	AActor* camera = Instantiate<AActor>(ELayerType::None, FVector3(0.0f, 0.0f, -10.0f));
	JCamera* cameraComp = camera->AddComponent<JCamera>();
	cameraComp->SetProjectionType(JCamera::EProjectionType::Perspective);
	cameraComp->SetSize(200.0f);

	JCameraScript* cameraScript = camera->AddComponent<JCameraScript>();
	renderer::mainCamera = cameraComp;

	// player
	for (size_t i = 0; i < 1; i++)
	{
		AActor* player = Instantiate<APlayer>(ELayerType::Player);
		JSpriteRenderer* sr = player->AddComponent<JSpriteRenderer>();
		sr->SetSprite(RResources::Find<RTexture>(L"Player"));

		player->AddComponent<JPlayerScript>();

		if (renderer::selectedActor == nullptr)
			renderer::selectedActor = player;
	}
}

void JPlayScene::Update()
{
	JScene::Update();
}

void JPlayScene::LateUpdate()
{
	JScene::LateUpdate();
}

void JPlayScene::Render()
{
	JScene::Render();
}

void JPlayScene::OnEnter()
{
	JScene::OnEnter();
}

void JPlayScene::OnExit()
{
	JScene::OnExit();
}