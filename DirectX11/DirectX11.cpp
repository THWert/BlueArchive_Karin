#include "framework.h"
float R = 0.0174532f;

//c++
//WINAPI

//핸들 -> 관리 감독
//H 접두어         리소스 핸들 (자원 관리자)
//HFONT,HBITMAP....
//HWND 접두어      Windows 핸들(창 관리자)
HINSTANCE           g_hInst;    //프로그램 자체의 관리자         // 기본 창 클래스 이름입니다.
HWND                g_hwnd;     //창 관리자                     // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
//**윈도우 프로시저** (프로시저) -> 호출 당하는 함수

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
//창사이즈 재조정   바탕화면 좌표
void SetWindowSize(int x, int y, int width, int height);

//메인 진입 함수
//윈도우를 만들고 화면에 출력
int APIENTRY wWinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPWSTR    lpCmdLine,
    int       nCmdShow)
{
    //윈도우 클래스
    WNDCLASS wc;

    //NULL값으로 시작주소부터 크기까지 초기화
    ZeroMemory(&wc, sizeof(WNDCLASS));

    //참조하지 않은 인자에 대해 경고를 표시하지 않는다
    UNREFERENCED_PARAMETER(lpCmdLine);
    //| & ^ 비트연산자
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    //프로시져 넘기기 L(함수 포인터 변수) = R(함수 포인터)
    wc.lpfnWndProc = (WNDPROC)WndProc;
    wc.hInstance = hInstance;
    //아이콘(프로그램 왼쪽위)
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    //윈도우창 활성화시에 마우스커서 모양
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    //ShowCursor(false);

    //윈도우창 바탕색
    wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(LTGRAY_BRUSH));
    wc.lpszClassName = L"DX11"; 
    wc.lpszMenuName = nullptr;

    //	운영체제의 레지스터에 이 프로그램을 등록한다
    if (!RegisterClass(&wc))
        return FALSE; //등록이 안됬다면 프로그램 종료

     //생성된 인스턴스값 저장
    g_hInst = hInstance;

    //	메인 윈도우 생성
    g_hwnd = CreateWindow(
        L"DX11",
        L"DX11",
        WS_OVERLAPPEDWINDOW,
        0,			//창의 시작 x좌표
        0,			//창의 시작 y좌표
        800,		//창의 너비
        600,		//창의 높이
        nullptr,
        nullptr,
        hInstance,	//등록될 인스턴스
        nullptr
    );
    //핸들이 제대로 값을 가지지 못했다면 프로그램 종료
    if (!g_hwnd)
        return FALSE;

    //화면 작업 사이즈 영역 계산
    SetWindowSize(0, 0, 800, 600);

    //	생성한 프로그램을 디스플레이의 최상위로 올린다
    //화면에 표시
    ShowWindow(g_hwnd, nCmdShow);

    //	메인 윈도우 갱신
    UpdateWindow(g_hwnd);

    MSG msg;
    ZeroMemory(&msg, sizeof(MSG));

    //**메시지 루프**
    // 기본 메시지 루프입니다:
    //런타임동안 반복시킬 반복문
    while (true)
    {
        //GetMessage 발생한 메세지를 줄때까지 계속 기다려서 받는애
        //Peek 발생할 때만 집어서 가져오는애
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            //메세지를 집어오지 않을 때
        }
    }
    //프로그램 종료 준비

     //생성된 윈도우 삭제
    DestroyWindow(g_hwnd);
    //등록된 프로그램 해제
    UnregisterClass(L"DX11", hInstance);

    return (int)msg.wParam;
}

//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.

float x = 400;
float y = 300;
float scaleX = 1.0f;
float scaleY = 1.0f;
float seta = 0.0f;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    //어떤 메세지가 발생되었는가를 통해 처리할 조건문
    switch (message)
    {
        //그리라는 메세지가 들어온경우
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        //hdc-> 도화지
        HDC hdc = BeginPaint(hWnd, &ps);

        //내부 원 4등분

        {//우측 하단
            MoveToEx(hdc, x + 100 * cosf(5 * R + seta) * scaleX,
                y + 100 * sinf(5 * R + seta) * scaleY, NULL);

            for (int i = 5; i <= 85; i++)
            {
                LineTo(hdc, x + 100 * cosf(i * R + seta) * scaleX,
                    y + 100 * sinf(i * R + seta) * scaleY);
            }
        }

        {//좌측 하단
            MoveToEx(hdc, x + 100 * cosf(95 * R + seta) * scaleX,
                y + 100 * sinf(95 * R + seta) * scaleY, NULL);

            for (int i = 95; i <= 175; i++)
            {
                LineTo(hdc, x + 100 * cosf(i * R + seta) * scaleX,
                    y + 100 * sinf(i * R + seta) * scaleY);
            }
        }

        {//좌측 상단
            MoveToEx(hdc, x + 100 * cosf(185 * R + seta) * scaleX,
                y + 100 * sinf(185 * R + seta) * scaleY, NULL);

            for (int i = 185; i <= 265; i++)
            {
                LineTo(hdc, x + 100 * cosf(i * R + seta) * scaleX,
                    y + 100 * sinf(i * R + seta) * scaleY);
            }
        }

        {//우측 상단
            MoveToEx(hdc, x + 100 * cosf(275 * R + seta) * scaleX,
                y + 100 * sinf(275 * R + seta) * scaleY, NULL);

            for (int i = 275; i <= 355; i++)
            {
                LineTo(hdc, x + 100 * cosf(i * R + seta) * scaleX,
                    y + 100 * sinf(i * R + seta) * scaleY);
            }
        }

        //내측 사각형 연결 준비

        {//우측
            MoveToEx(hdc, x + 100 * cosf(355 * R + seta) * scaleX,
                y + 100 * sinf(355 * R + seta) * scaleY, NULL);
            LineTo(hdc, x + 83 * cosf(355 * R + seta) * scaleX,
                y + 100 * sinf(355 * R + seta) * scaleY);

            MoveToEx(hdc, x + 100 * cosf(5 * R + seta) * scaleX,
                y + 100 * sinf(5 * R + seta) * scaleY, NULL);
            LineTo(hdc, x + 83 * cosf(5 * R + seta) * scaleX,
                y + 100 * sinf(5 * R + seta) * scaleY);
        }

        {//하단
            MoveToEx(hdc, x + 100 * cosf(85 * R + seta) * scaleX,
                y + 83 * sinf(85 * R + seta) * scaleY, NULL);
            LineTo(hdc, x + 100 * cosf(85 * R + seta) * scaleX,
                y + 100 * sinf(85 * R + seta) * scaleY);

            MoveToEx(hdc, x + 100 * cosf(95 * R + seta) * scaleX,
                y + 83 * sinf(95 * R + seta) * scaleY, NULL);
            LineTo(hdc, x + 100 * cosf(95 * R + seta) * scaleX,
                y + 100 * sinf(95 * R + seta) * scaleY);
        }

        {//좌측
            MoveToEx(hdc, x + 100 * cosf(185 * R + seta) * scaleX,
                y + 100 * sinf(185 * R + seta) * scaleY, NULL);
            LineTo(hdc, x + 83 * cosf(185 * R + seta) * scaleX,
                y + 100 * sinf(185 * R + seta) * scaleY);

            MoveToEx(hdc, x + 100 * cosf(175 * R + seta) * scaleX,
                y + 100 * sinf(175 * R + seta) * scaleY, NULL);
            LineTo(hdc, x + 83 * cosf(175 * R + seta) * scaleX,
                y + 100 * sinf(175 * R + seta) * scaleY);
        }

        {//상단
            MoveToEx(hdc, x + 100 * cosf(265 * R + seta) * scaleX,
                y + 83 * sinf(265 * R + seta) * scaleY, NULL);
            LineTo(hdc, x + 100 * cosf(265 * R + seta) * scaleX,
                y + 100 * sinf(265 * R + seta) * scaleY);

            MoveToEx(hdc, x + 100 * cosf(275 * R + seta) * scaleX,
                y + 83 * sinf(275 * R + seta) * scaleY, NULL);
            LineTo(hdc, x + 100 * cosf(275 * R + seta) * scaleX,
                y + 100 * sinf(275 * R + seta) * scaleY);
        }

        //사각형 연결선

        {//우측
            MoveToEx(hdc, x + 83 * cosf(355 * R + seta) * scaleX,
                y + 100 * sinf(355 * R + seta) * scaleY, NULL);
            LineTo(hdc, x + 83 * cosf(5 * R + seta) * scaleX,
                y + 100 * sinf(5 * R + seta) * scaleY);
        }

        {//하단
            MoveToEx(hdc, x + 100 * cosf(85 * R + seta) * scaleX,
                y + 83 * sinf(85 * R + seta) * scaleY, NULL);
            LineTo(hdc, x + 100 * cosf(95 * R + seta) * scaleX,
                y + 83 * sinf(95 * R + seta) * scaleY);
        }

        {//좌측
            MoveToEx(hdc, x + 83 * cosf(185 * R + seta) * scaleX,
                y + 100 * sinf(185 * R + seta) * scaleY, NULL);
            LineTo(hdc, x + 83 * cosf(175 * R + seta) * scaleX,
                y + 100 * sinf(175 * R + seta) * scaleY);
        }

        {//상단
            MoveToEx(hdc, x + 100 * cosf(265 * R + seta) * scaleX,
                y + 83 * sinf(265 * R + seta) * scaleY, NULL);
            LineTo(hdc, x + 100 * cosf(275 * R + seta) * scaleX,
                y + 83 * sinf(275 * R + seta) * scaleY);
        }

        //내부 외측 4등분

        {//우측 하단
            MoveToEx(hdc, x + 120 * cosf(4 * R + seta) * scaleX,
                y + 120 * sinf(4 * R + seta) * scaleY, NULL);

            for (int i = 4; i <= 86; i++)
            {
                LineTo(hdc, x + 120 * cosf(i * R + seta) * scaleX,
                    y + 120 * sinf(i * R + seta) * scaleY);
            }
        }

        {//좌측 하단
            MoveToEx(hdc, x + 120 * cosf(94 * R + seta) * scaleX,
                y + 120 * sinf(94 * R + seta) * scaleY, NULL);

            for (int i = 94; i <= 176; i++)
            {
                LineTo(hdc, x + 120 * cosf(i * R + seta) * scaleX,
                    y + 120 * sinf(i * R + seta) * scaleY);
            }
        }

        {//좌측 상단
            MoveToEx(hdc, x + 120 * cosf(184 * R + seta) * scaleX,
                y + 120 * sinf(184 * R + seta) * scaleY, NULL);

            for (int i = 184; i <= 266; i++)
            {
                LineTo(hdc, x + 120 * cosf(i * R + seta) * scaleX,
                    y + 120 * sinf(i * R + seta) * scaleY);
            }
        }

        {//우측 상단
            MoveToEx(hdc, x + 120 * cosf(274 * R + seta) * scaleX,
                y + 120 * sinf(274 * R + seta) * scaleY, NULL);

            for (int i = 274; i <= 356; i++)
            {
                LineTo(hdc, x + 120 * cosf(i * R + seta) * scaleX,
                    y + 120 * sinf(i * R + seta) * scaleY);
            }
        }

        //뻗어나가기

        {//우측
            MoveToEx(hdc, x + 120 * cosf(355 * R + seta) * scaleX,
                y + 100 * sinf(355 * R + seta) * scaleY, NULL);
            LineTo(hdc, x + 250 * cosf(355 * R + seta) * scaleX,
                y + 100 * sinf(355 * R + seta) * scaleY);

            MoveToEx(hdc, x + 120 * cosf(5 * R + seta) * scaleX,
                y + 100 * sinf(5 * R + seta) * scaleY, NULL);
            LineTo(hdc, x + 250 * cosf(5 * R + seta) * scaleX,
                y + 100 * sinf(5 * R + seta) * scaleY);
        }

        {//하단
            MoveToEx(hdc, x + 120 * cosf(85 * R + seta) * scaleX,
                y + 120 * sinf(85 * R + seta) * scaleY, NULL);
            LineTo(hdc, x + 120 * cosf(85 * R + seta) * scaleX,
                y + 250 * sinf(85 * R + seta) * scaleY);

            MoveToEx(hdc, x + 120 * cosf(95 * R + seta) * scaleX,
                y + 120 * sinf(95 * R + seta) * scaleY, NULL);
            LineTo(hdc, x + 120 * cosf(95 * R + seta) * scaleX,
                y + 250 * sinf(95 * R + seta) * scaleY);
        }

        {//좌측
            MoveToEx(hdc, x + 120 * cosf(185 * R + seta) * scaleX,
                y + 120 * sinf(185 * R + seta) * scaleY, NULL);
            LineTo(hdc, x + 250 * cosf(185 * R + seta) * scaleX,
                y + 120 * sinf(185 * R + seta) * scaleY);

            MoveToEx(hdc, x + 120 * cosf(175 * R + seta) * scaleX,
                y + 120 * sinf(175 * R + seta) * scaleY, NULL);
            LineTo(hdc, x + 250 * cosf(175 * R + seta) * scaleX,
                y + 120 * sinf(175 * R + seta) * scaleY);
        }

        {//상단
            MoveToEx(hdc, x + 120 * cosf(265 * R + seta) * scaleX,
                y + 120 * sinf(265 * R + seta) * scaleY, NULL);
            LineTo(hdc, x + 120 * cosf(265 * R + seta) * scaleX,
                y + 250 * sinf(265 * R + seta) * scaleY);

            MoveToEx(hdc, x + 120 * cosf(275 * R + seta) * scaleX,
                y + 120 * sinf(275 * R + seta) * scaleY, NULL);
            LineTo(hdc, x + 120 * cosf(275 * R + seta) * scaleX,
                y + 250 * sinf(275 * R + seta) * scaleY);
        }

        //뻗은 곳 연결

        {//우측
            MoveToEx(hdc, x + 250 * cosf(355 * R + seta) * scaleX,
                y + 100 * sinf(355 * R + seta) * scaleY, NULL);
            LineTo(hdc, x + 250 * cosf(5 * R + seta) * scaleX,
                y + 100 * sinf(5 * R + seta) * scaleY);
        }

        {//하단
            MoveToEx(hdc, x + 100 * cosf(84 * R + seta) * scaleX,
                y + 250 * sinf(85 * R + seta) * scaleY, NULL);
            LineTo(hdc, x + 100 * cosf(96 * R + seta) * scaleX,
                y + 250 * sinf(95 * R + seta) * scaleY);
        }

        {//좌측
            MoveToEx(hdc, x + 250 * cosf(185 * R + seta) * scaleX,
                y + 123 * sinf(185 * R + seta) * scaleY, NULL);
            LineTo(hdc, x + 250 * cosf(175 * R + seta) * scaleX,
                y + 123 * sinf(175 * R + seta) * scaleY);
        }

        {//상단
            MoveToEx(hdc, x + 100 * cosf(264 * R + seta) * scaleX,
                y + 250 * sinf(265 * R + seta) * scaleY, NULL);
            LineTo(hdc, x + 100 * cosf(276 * R + seta) * scaleX,
                y + 250 * sinf(275 * R + seta) * scaleY);
        }

        //외측 내부 원

        {//우측 하단
            MoveToEx(hdc, x + 160 * cosf(3 * R + seta) * scaleX,
                y + 160 * sinf(3 * R + seta) * scaleY, NULL);

            for (int i = 3; i <= 86; i++)
            {
                LineTo(hdc, x + 160 * cosf(i * R + seta) * scaleX,
                    y + 160 * sinf(i * R + seta) * scaleY);
            }
        }

        {//좌측 하단
            MoveToEx(hdc, x + 160 * cosf(94 * R + seta) * scaleX,
                y + 160 * sinf(94 * R + seta) * scaleY, NULL);

            for (int i = 94; i <= 176; i++)
            {
                LineTo(hdc, x + 160 * cosf(i * R + seta) * scaleX,
                    y + 160 * sinf(i * R + seta) * scaleY);
            }
        }

        {//좌측 상단
            MoveToEx(hdc, x + 160 * cosf(184 * R + seta) * scaleX,
                y + 160 * sinf(184 * R + seta) * scaleY, NULL);

            for (int i = 184; i <= 266; i++)
            {
                LineTo(hdc, x + 160 * cosf(i * R + seta) * scaleX,
                    y + 160 * sinf(i * R + seta) * scaleY);
            }
        }

        {//우측 상단
            MoveToEx(hdc, x + 160 * cosf(274 * R + seta) * scaleX,
                y + 160 * sinf(274 * R + seta) * scaleY, NULL);

            for (int i = 274; i <= 357; i++)
            {
                LineTo(hdc, x + 160 * cosf(i * R + seta) * scaleX,
                    y + 160 * sinf(i * R + seta) * scaleY);
            }
        }

        //외측 외부 원

        {//우측 하단
            MoveToEx(hdc, x + 220 * cosf(3 * R + seta) * scaleX,
                y + 220 * sinf(3 * R + seta) * scaleY, NULL);

            for (float i = 3.0f; i <= 67.5f; i++)
            {
                LineTo(hdc, x + 220 * cosf(i * R + seta) * scaleX,
                    y + 220 * sinf(i * R + seta) * scaleY);
            }
        }

        {//좌측 하단
            MoveToEx(hdc, x + 220 * cosf(120 * R + seta) * scaleX,
                y + 220 * sinf(120 * R + seta) * scaleY, NULL);

            for (int i = 120; i <= 177; i++)
            {
                LineTo(hdc, x + 220 * cosf(i * R + seta) * scaleX,
                    y + 220 * sinf(i * R + seta) * scaleY);
            }
        }

        {//좌측 상단
            MoveToEx(hdc, x + 220 * cosf(183 * R + seta) * scaleX,
                y + 220 * sinf(183 * R + seta) * scaleY, NULL);

            for (float i = 184.0f; i <= 247.5f; i++)
            {
                LineTo(hdc, x + 220 * cosf(i * R + seta) * scaleX,
                    y + 220 * sinf(i * R + seta) * scaleY);
            }
        }

        {//우측 상단
            MoveToEx(hdc, x + 220 * cosf(300 * R + seta) * scaleX,
                y + 220 * sinf(300 * R + seta) * scaleY, NULL);

            for (int i = 300; i <= 358; i++)
            {
                LineTo(hdc, x + 220 * cosf(i * R + seta) * scaleX,
                    y + 220 * sinf(i * R + seta) * scaleY);
            }
        }

        //추가 원

        {//우측 상단
            MoveToEx(hdc, x + 180 * cosf(274 * R + seta) * scaleX,
                y + 180 * sinf(274 * R + seta) * scaleY, NULL);

            for (int i = 274; i <= 357; i++)
            {
                LineTo(hdc, x + 180 * cosf(i * R + seta) * scaleX,
                    y + 180 * sinf(i * R + seta) * scaleY);
            }
        }

        {//좌측 하단
            MoveToEx(hdc, x + 180 * cosf(94 * R + seta) * scaleX,
                y + 180 * sinf(94 * R + seta) * scaleY, NULL);

            for (int i = 94; i <= 160; i++)
            {
                LineTo(hdc, x + 180 * cosf(i * R + seta) * scaleX,
                    y + 180 * sinf(i * R + seta) * scaleY);
            }
        }

        //메우기

        {//우측 하단
            MoveToEx(hdc, x + 180 * cosf(67.5f * R + seta) * scaleX,
                y + 180 * sinf(67.5f * R + seta) * scaleY, NULL);

            for (float i = 67.5f; i <= 87.0f; i++)
            {
                LineTo(hdc, x + 180 * cosf(i * R + seta) * scaleX,
                    y + 180 * sinf(i * R + seta) * scaleY);
            }

            MoveToEx(hdc, x + 180 * cosf(67.5f * R + seta) * scaleX,
                y + 180 * sinf(67.5f * R + seta) * scaleY, NULL);
            LineTo(hdc, x + 220 * cosf(67.5f * R + seta) * scaleX,
                y + 220 * sinf(67.5f * R + seta) * scaleY);
        }

        {//좌측 상단
            MoveToEx(hdc, x + 180 * cosf(247.5f * R + seta) * scaleX,
                y + 180 * sinf(247.5f * R + seta) * scaleY, NULL);

            for (float i = 247.5f; i <= 267.0f; i++)
            {
                LineTo(hdc, x + 180 * cosf(i * R + seta) * scaleX,
                    y + 180 * sinf(i * R + seta) * scaleY);
            }

            MoveToEx(hdc, x + 180 * cosf(247.5f * R + seta) * scaleX,
                y + 180 * sinf(247.5f * R + seta) * scaleY, NULL);
            LineTo(hdc, x + 220 * cosf(247.5f * R + seta) * scaleX,
                y + 220 * sinf(247.5f * R + seta) * scaleY);
        }

        //깎기

        {//우측 상단
            MoveToEx(hdc, x + 200 * cosf(300 * R + seta) * scaleX,
                y + 200 * sinf(300 * R + seta) * scaleY, NULL);

            for (int i = 300; i <= 358; i++)
            {
                LineTo(hdc, x + 200 * cosf(i * R + seta) * scaleX,
                    y + 200 * sinf(i * R + seta) * scaleY);
            }

            MoveToEx(hdc, x + 200 * cosf(300 * R + seta) * scaleX,
                y + 200 * sinf(300 * R + seta) * scaleY, NULL);
            LineTo(hdc, x + 220 * cosf(300 * R + seta) * scaleX,
                y + 220 * sinf(300 * R + seta) * scaleY);
        }

        {//좌측 하단
            MoveToEx(hdc, x + 200 * cosf(120 * R + seta) * scaleX,
                y + 200 * sinf(120 * R + seta) * scaleY, NULL);

            for (int i = 120; i <= 160; i++)
            {
                LineTo(hdc, x + 200 * cosf(i * R + seta) * scaleX,
                    y + 200 * sinf(i * R + seta) * scaleY);
            }

            MoveToEx(hdc, x + 200 * cosf(120 * R + seta) * scaleX,
                y + 200 * sinf(120 * R + seta) * scaleY, NULL);
            LineTo(hdc, x + 220 * cosf(120 * R + seta) * scaleX,
                y + 220 * sinf(120 * R + seta) * scaleY);

            MoveToEx(hdc, x + 180 * cosf(160 * R + seta) * scaleX,
                y + 180 * sinf(160 * R + seta) * scaleY, NULL);
            LineTo(hdc, x + 200 * cosf(160 * R + seta) * scaleX,
                y + 200 * sinf(160 * R + seta) * scaleY);
        }
  
        EndPaint(hWnd, &ps);
        break;
    }
    //파괴하거나 닫으라는 메세지가 들어온경우
    case WM_DESTROY: case WM_CLOSE:
    {
        //프로그램 종료 호출 함수
        PostQuitMessage(0);
        break;
    }
    case WM_KEYDOWN:
    {
        //키가 눌렸을 때 wm_paint 를 발생 시켜라
        InvalidateRect(hWnd, NULL, true);

        if (wParam == VK_UP)
        {
            y -= 3;
        }
        if (wParam == VK_DOWN)
        {
            y += 3;
        }
        if (wParam == VK_LEFT)
        {
            x -= 3;
        }
        if (wParam == VK_RIGHT)
        {
            x += 3;
        }
        if (wParam == '1')
        {
            scaleX += 0.1f;
        }
        if (wParam == '2')
        {
            scaleX-= 0.1f;
        }
        if (wParam == '3')
        {
            scaleY+= 0.1f;
        }
        if (wParam == '4')
        {
            scaleY-= 0.1f;
        }
        if (wParam == '5')
        {
            seta += 0.1f;
        }
        if (wParam == '6')
        {
            seta -= 0.1f;
        }

    }
    }

    return (DefWindowProc(hWnd, message, wParam, lParam));
}

void SetWindowSize(int x, int y, int width, int height)
{
    //화면크기에 맞는 렉트
    RECT rc;
    rc.left = 0;
    rc.top = 0;
    rc.right = width;
    rc.bottom = height;

    //실제 윈도우 크기 조정
    AdjustWindowRect(&rc, WS_CAPTION | WS_SYSMENU, false);
    //위 RECT 정보로 윈도우 사이즈 세팅
    SetWindowPos(g_hwnd, NULL, x, y, (rc.right - rc.left), (rc.bottom - rc.top),
        SWP_NOZORDER | SWP_NOMOVE);
}