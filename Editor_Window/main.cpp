// Editor_Window.cpp : 애플리케이션에 대한 진입점을 정의
//

#include "framework.h"
#include "Editor_Window.h"

#include "..\\Engine_SOURCE\\huruApplication.h"
#include "..\\Engine_SOURCE\\huruResources.h"
#include "..\\Engine_SOURCE\\huruTexture.h"
#include "..\\Engine_SOURCE\\huruSceneManager.h"

#include "..\\Engine\\huruLoadScenes.h"
#include "..\\Engine\\huruLoadResources.h"
#include "..\\Engine\\huruToolScene.h"


huru::Application application;

ULONG_PTR gpToken;
Gdiplus::GdiplusStartupInput gpsi;

#define MAX_LOADSTRING 100

// 전역 변수
HINSTANCE hInst;                                // 현재 인스턴스
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름

// 이 코드 모듈에 포함된 함수의 선언을 전달
ATOM                MyRegisterClass(HINSTANCE hInstance, 
                                    const wchar_t* name, WNDPROC proc);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,         // 프로그램의 인스턴스 핸들
                     _In_opt_ HINSTANCE hPrevInstance,  // 이전 인스턴스 핸들
                     _In_ LPWSTR    lpCmdLine,          // 명령행으로 입력된 프로그램 인수
                     _In_ int       nCmdShow)           // 프로그램이 실행될 형태
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Memory Leak Check
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(255);
    
    // TODO:
    // 전역 문자열을 초기화
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_EDITORWINDOW, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance, szWindowClass, WndProc);
    MyRegisterClass(hInstance, L"TILEWINDOW", WndTileProc);

    // 애플리케이션 초기화를 수행
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_EDITORWINDOW));

    MSG msg;

    // 픽 메시지 : 메시지큐에서 메세지 유무에 상관없이 함수를 호출
    // 매프레임마다 메세지를 확인할수 있는 PeekMessage를 사용
    while (true)
    {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
			    TranslateMessage(&msg);
			    DispatchMessage(&msg);
            }
		}
        else
        {
			// 메시지가 없을 때 수행할 작업
			// 예를 들어, 애니메이션 업데이트, 게임 로직 처리 등
			application.Run();
        }
    }

    Gdiplus::GdiplusShutdown(gpToken);
    application.Release();

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance, const wchar_t* name, WNDPROC proc)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;  
    wcex.lpfnWndProc    = proc;                 
    wcex.cbClsExtra     = 0;    
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_EDITORWINDOW));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_EDITORWINDOW);
    wcex.lpszClassName  = name;            
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   const UINT width = 672;
   const UINT height = 846;
   HWND hWnd = CreateWindowW(
       szWindowClass,
       L"Client",
       WS_OVERLAPPEDWINDOW,
       CW_USEDEFAULT, CW_USEDEFAULT,       // 윈도우 위치 (x, y)
       width, height,                           // 윈도우 너비와 높이
       nullptr, nullptr,
       hInstance,
       nullptr);

   application.Initialize(hWnd, width, height); // 애플리케이션 초기화

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   Gdiplus::GdiplusStartup(&gpToken, &gpsi, NULL);

   //Load Scene
   huru::LoadResources();
   huru::LoadScenes();

   int a = 0;
   srand(unsigned int(&a));

   huru::Scene* activeScene = huru::SceneManager::GetActiveScene();
   std::wstring name = activeScene->GetName();
   if (name == L"ToolScene")
   {
       HWND ToolhWnd = CreateWindowW(
           L"TILEWINDOW",
           L"TileWindow",
           WS_OVERLAPPEDWINDOW,
           CW_USEDEFAULT, CW_USEDEFAULT,       // 윈도우 위치 (x, y)
           width, height,                      // 윈도우 너비와 높이
           nullptr, nullptr,
           hInstance,
           nullptr);

       //Tile 윈도우 크기 조정 -- TOOL
       huru::graphics::Texture* texture = huru::Resources::Find<huru::graphics::Texture>(L"SpringFloor");

       RECT rect =
       {
           0, 0, texture->GetWidth(), texture->GetHeight()
       };
       AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

       UINT toolWidth = rect.right - rect.left;
       UINT toolHeight = rect.bottom - rect.top;

       SetWindowPos(ToolhWnd, nullptr, width, 0, toolWidth, toolHeight, 0);
       ShowWindow(ToolhWnd, true);
       UpdateWindow(ToolhWnd);
   }

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

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

//LRESULT CALLBACK WndTileProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    switch (message)
//    {
//    case WM_COMMAND:
//    {
//        int wmId = LOWORD(wParam);
//        // 메뉴 선택을 구문 분석합니다:
//        switch (wmId)
//        {
//        case IDM_ABOUT:
//            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
//            break;
//        case IDM_EXIT:
//            DestroyWindow(hWnd);
//            break;
//        default:
//            return DefWindowProc(hWnd, message, wParam, lParam);
//        }
//    }
//    break;
//
//    case WM_PAINT:
//    {
//        PAINTSTRUCT ps;
//        HDC hdc = BeginPaint(hWnd, &ps);
//
//        huru::graphics::Texture* texture = huru::Resources::Find<huru::graphics::Texture>(L"SpringFloor");
//
//        TransparentBlt(
//            hdc,
//            0,
//            0,
//            texture->GetWidth(),
//            texture->GetHeight(),
//            texture->GetHdc(),
//            0,
//            0,
//            texture->GetWidth(),
//            texture->GetHeight(),
//            RGB(255, 0, 255));
//
//        EndPaint(hWnd, &ps);
//    }
//    break;
//    case WM_DESTROY:
//        PostQuitMessage(0); 
//        break;
//    default:
//        return DefWindowProc(hWnd, message, wParam, lParam);
//    }
//    return 0;
//}


// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
