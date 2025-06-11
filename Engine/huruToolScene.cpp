#include "huruToolScene.h"
#include "huruObject.h"
#include "huruTile.h"
#include "huruTilemapRenderer.h"
#include "huruResources.h"
#include "huruTexture.h"
#include "huruCamera.h"
#include "huruRenderer.h"
#include "huruInput.h"
#include "huruCameraScript.h"

namespace huru
{
	ToolScene::ToolScene() :
		mTexture(nullptr)
	{
		mTexture = Resources::Find<graphics::Texture>(L"SpringFloor");
	}

	ToolScene::~ToolScene()
	{

	}

	void ToolScene::Initialize()
	{
		GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::Particle, Vector2(344.0f, 442.0f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		renderer::mainCamera = cameraComp;
		camera->AddComponent<CameraScript>();

		/*Tile* tile = object::Instantiate<Tile>(eLayerType::Tile);
		TileMapRenderer* tmr = tile->AddComponent<TileMapRenderer>();
		tmr->SetTexture(Resources::Find<graphics::Texture>(L"SpringFloor"));*/

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
			pos = renderer::mainCamera->CalcuateTilePosition(pos);

			if (pos.x >= 0.0f && pos.y >= 0.0f)
			{
				int idxX = pos.x / TileMapRenderer::TileSize.x;
				int idxY = pos.y / TileMapRenderer::TileSize.y;

				Tile* tile = object::Instantiate<Tile>(eLayerType::Tile);
				TileMapRenderer* tmr = tile->AddComponent<TileMapRenderer>();
				tmr->SetTexture(mTexture);
				tmr->SetIndex(TileMapRenderer::SelectedIndex);

				tile->SetIndexPosition(idxX, idxY);
				mTiles.push_back(tile);
			}
			else
			{
				//
			}
		}

		if (Input::GetKeyDown(eKeyCode::S))
		{
			Save();
		}

		if (Input::GetKeyDown(eKeyCode::L))
		{
			Load();
		}
	}

	void ToolScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		for (size_t i = 0; i < 50; i++)
		{
			Vector2 pos = renderer::mainCamera->CalculatePosition
			(
				Vector2(TileMapRenderer::TileSize.x * i, 0.0f)
			);

			MoveToEx(hdc, pos.x, 0, NULL);
			LineTo(hdc, pos.x, 1000);
		}

		for (size_t i = 0; i < 50; i++)
		{
			Vector2 pos = renderer::mainCamera->CalculatePosition
			(
				Vector2(0.0f, TileMapRenderer::TileSize.y * i)
			);

			MoveToEx(hdc, 0, pos.y, NULL);
			LineTo(hdc, 1000, pos.y);
		}
	}

	void ToolScene::OnEnter()
	{

	}

	void ToolScene::OnExit()
	{

	}

	void ToolScene::Save()
	{
		// open a file name
		OPENFILENAME ofn = {};

		wchar_t szFilePath[256] = {};

		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = szFilePath;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = 256;
		ofn.lpstrFilter = L"Tile\0*.tile\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (false == GetSaveFileName(&ofn))
			return;

		FILE* pFile = nullptr;
		_wfopen_s(&pFile, szFilePath, L"wb");

		for (Tile* tile : mTiles)
		{
			TileMapRenderer* tmr = tile->GetComponent<TileMapRenderer>();
			Transform* tr = tile->GetComponent<Transform>();

			Vector2 sourceIndex = tmr->GetIndex();
			Vector2 position = tr->GetPosition();

			int x = sourceIndex.x;
			fwrite(&x, sizeof(int), 1, pFile);
			int y = sourceIndex.y;
			fwrite(&y, sizeof(int), 1, pFile);

			x = position.x;
			fwrite(&x, sizeof(int), 1, pFile);
			y = position.y;
			fwrite(&y, sizeof(int), 1, pFile);
		}

		fclose(pFile);
	}

	void ToolScene::Load()
	{
		OPENFILENAME ofn = {};

		wchar_t szFilePath[256] = {};

		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = szFilePath;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = 256;
		ofn.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (false == GetOpenFileName(&ofn))
			return;

		FILE* pFile = nullptr;
		_wfopen_s(&pFile, szFilePath, L"rb");

		if (!pFile)
			return;

		// 기존 타일 초기화
		for (Tile* tile : mTiles)
			delete tile; // 메모리 해제 필요하다면 (메모리 관리 정책에 맞게)
		mTiles.clear();

		while (true)
		{
			int idxX = 0;
			int idxY = 0;

			int posX = 0;
			int posY = 0;

			if (fread(&idxX, sizeof(int), 1, pFile) != 1)
				break;
			if (fread(&idxY, sizeof(int), 1, pFile) != 1)
				break;
			if (fread(&posX, sizeof(int), 1, pFile) != 1)
				break;
			if (fread(&posY, sizeof(int), 1, pFile) != 1)
				break;

			Tile* tile =
				object::Instantiate<Tile>(eLayerType::Tile, Vector2(posX, posY));
			TileMapRenderer* tmr = tile->AddComponent<TileMapRenderer>();
			tmr->SetTexture(mTexture);
			tmr->SetIndex(Vector2(idxX, idxY));

			mTiles.push_back(tile);
		}
		fclose(pFile);
	}

	void ToolScene::LoadMapFile(const std::wstring& filePath)
	{
		FILE* pFile = nullptr;
		_wfopen_s(&pFile, filePath.c_str(), L"rb");

		if (!pFile)
		{
			MessageBox(nullptr, L"Failed to open map file!", L"Error", MB_OK | MB_ICONERROR);
			return;
		}

		for (Tile* tile : mTiles)
			delete tile;
		mTiles.clear();

		while (true)
		{
			int idxX = 0, idxY = 0;
			int posX = 0, posY = 0;

			if (fread(&idxX, sizeof(int), 1, pFile) != 1) break;
			if (fread(&idxY, sizeof(int), 1, pFile) != 1) break;
			if (fread(&posX, sizeof(int), 1, pFile) != 1) break;
			if (fread(&posY, sizeof(int), 1, pFile) != 1) break;

			Tile* tile = object::Instantiate<Tile>(eLayerType::Tile, Vector2(posX, posY));
			TileMapRenderer* tmr = tile->AddComponent<TileMapRenderer>();
			tmr->SetTexture(mTexture);
			tmr->SetIndex(Vector2(idxX, idxY));

			mTiles.push_back(tile);
		}

		fclose(pFile);
	}
}

LRESULT CALLBACK WndTileProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		POINT mousePos = { };
		GetCursorPos(&mousePos);
		ScreenToClient(hWnd, &mousePos);

		Vector2 mousePosition;
		mousePosition.x = mousePos.x;
		mousePosition.y = mousePos.y;

		int idxX = mousePosition.x / huru::TileMapRenderer::OriginTileSize.x;
		int idxY = mousePosition.y / huru::TileMapRenderer::OriginTileSize.y;

		huru::TileMapRenderer::SelectedIndex = Vector2(idxX, idxY);
	}

	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		huru::graphics::Texture* texture
			= huru::Resources::Find<huru::graphics::Texture>(L"SpringFloor");

		TransparentBlt(hdc
			, 0, 0
			, texture->GetWidth()
			, texture->GetHeight()
			, texture->GetHdc()
			, 0, 0
			, texture->GetWidth()
			, texture->GetHeight()
			, RGB(255, 0, 255));

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
