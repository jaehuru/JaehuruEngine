// Editor_Window.cpp : 애플리케이션에 대한 진입점을 정의
//

#include "framework.h"
#include "Editor_Window.h"

#include "..\\Engine_SOURCE\\huruApplication.h"
#include "..\\Engine\\huruLoadScenes.h"
#include "..\\Engine\\huruLoadResources.h"

huru::Application application;

ULONG_PTR gpToken;
Gdiplus::GdiplusStartupInput gpsi;

#define MAX_LOADSTRING 100

// 전역 변수
HINSTANCE hInst;                                // 현재 인스턴스
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름

// 이 코드 모듈에 포함된 함수의 선언을 전달
ATOM                MyRegisterClass(HINSTANCE hInstance);
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

    // TODO:
    // 전역 문자열을 초기화
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_EDITORWINDOW, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

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

    // 기본 메시지 루프
    /*while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }*/

    Gdiplus::GdiplusShutdown(gpToken);

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;  
    wcex.lpfnWndProc    = WndProc;                  // 윈도우 프로시저 함수, 윈도우의 메시지 처리 함수를 지정함
    wcex.cbClsExtra     = 0;    
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_EDITORWINDOW));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_EDITORWINDOW);
    wcex.lpszClassName  = szWindowClass;            
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
       szTitle,
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
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가

            // DC(Device Context)란 출력에 필요한 모든 정보를 가지는 데이터 구조체이며 GDI모듈에 의해 관리됨

			//HBRUSH pinkBrush = CreateSolidBrush(RGB(255, 0, 255));      // 분홍색 브러시 생성
			//HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, pinkBrush);     // SelectObject함수는 이전에 사용하던 브러쉬를 반환

			//Rectangle(hdc, 10, 10, 100, 100);       // 사각형 그리기 예시

			//(HBRUSH)SelectObject(hdc, oldBrush);    
			//DeleteObject(pinkBrush);                    

			//HPEN redPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));   
		    //HPEN oldPen = (HPEN)SelectObject(hdc, redPen);          

			//Ellipse(hdc, 120, 10, 200, 100);        // 타원 그리기 예시

            //(HPEN)SelectObject(hdc, oldPen);
			//DeleteObject(redPen);    

            // 기본으로 자주 사용 되는 GDI오브젝트는 미리 DC안에 만들어져 있음
            // 스톡 오브젝트라고 한다
			//HBRUSH grayBrush = (HBRUSH)GetStockObject(GRAY_BRUSH);
			//oldBrush = (HBRUSH)SelectObject(hdc, grayBrush);

			//Rectangle(hdc, 10, 120, 100, 220);
			//SelectObject(hdc, oldBrush);

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
