#include "huruToolScene.h"
#include "huruObject.h"
#include "huruTile.h"
#include "huruTilemapRenderer.h"
#include "huruResources.h"
#include "huruTexture.h"
#include "huruCamera.h"
#include "huruRenderer.h"
#include "huruInput.h"

namespace huru
{
	ToolScene::ToolScene()
	{
		 
	}

	ToolScene::~ToolScene()
	{

	}

	void ToolScene::Initialize()
	{
		GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::Particle, Vector2(344.0f, 442.0f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		renderer::mainCamera = cameraComp;

		Tile* tile = object::Instantiate<Tile>(eLayerType::Tile);
		TileMapRenderer* tmr = tile->AddComponent<TileMapRenderer>();
		tmr->SetTexture(Resources::Find<graphics::Texture>(L"SpringFloor"));

		Scene::Initialize();
	}

	void ToolScene::Update()
	{
		Scene::Update();
	}

	void ToolScene::LateUpdate()
	{
		Scene::LateUpdate();

		if (Input::GetKeyDown(eKeyCode::LButton))
		{
			Vector2 pos = Input::GetMousePosition();

			int idxX = pos.x / TileMapRenderer::TileSize.x;
			int idxY = pos.y / TileMapRenderer::TileSize.y;	

			Tile* tile = object::Instantiate<Tile>(eLayerType::Tile);
			TileMapRenderer* tmr = tile->AddComponent<TileMapRenderer>();
			tmr->SetTexture(Resources::Find<graphics::Texture>(L"SpringFloor"));

			tile->SetPosition(idxX, idxY);
		}
	}

	void ToolScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		for (size_t i = 0; i < 50; i++)
		{
			MoveToEx(hdc, TileMapRenderer::TileSize.x * i, 0, NULL);
			LineTo(hdc, TileMapRenderer::TileSize.x * i, 1000);
		}

		for (size_t i = 0; i < 50; i++)
		{
			MoveToEx(hdc, 0, TileMapRenderer::TileSize.y * i, NULL);
			LineTo(hdc, 1000, TileMapRenderer::TileSize.y * i);
		}
	}

	void ToolScene::OnEnter()
	{

	}

	void ToolScene::OnExit()
	{

	}

}

LRESULT CALLBACK WndTileProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		//int wmId = LOWORD(wParam);
		//// 메뉴 선택을 구문 분석합니다:
		//switch (wmId)
		//{
		//case IDM_ABOUT:
		//	DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
		//	break;
		//case IDM_EXIT:
		//	DestroyWindow(hWnd);
		//	break;
		//default:
		//	return DefWindowProc(hWnd, message, wParam, lParam);
		//}
	}
	break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		huru::graphics::Texture* texture = huru::Resources::Find<huru::graphics::Texture>(L"SpringFloor");

		TransparentBlt(
			hdc,
			0,
			0,
			texture->GetWidth(),
			texture->GetHeight(),
			texture->GetHdc(),
			0,
			0,
			texture->GetWidth(),
			texture->GetHeight(),
			RGB(255, 0, 255));

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
