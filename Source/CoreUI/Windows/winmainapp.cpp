#include "winmainapp.h"
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

static TCHAR szWindowClass[] = _T("DesktopApp");
static TCHAR szTitle[] = _T("DConsole");

HINSTANCE hInst;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WinMainApp::WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nCmdShow)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
                   _T("Call to RegisterClassEx failed!"),
                   _T("DConsole Stderr"),
                   NULL);

        return 1;
    }
    hInst = hInstance;
    platform_window = CreateWindow(
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        500, 100,
        NULL,
        NULL,
        hInstance,
        NULL);

    if (!platform_window)
    {
        MessageBox(NULL,
                   _T("Call to CreateWindow failed!"),
                   _T("DConsole Stder"),
                   NULL);

        return 1;
    }
    fprintf(stderr, "1:%s \n", __PRETTY_FUNCTION__);
    ShowWindow(platform_window,
               nCmdShow);
    UpdateWindow(platform_window);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        fprintf(stderr, "2:%s \n", __PRETTY_FUNCTION__);
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    fprintf(stderr, "3:%s \n", __PRETTY_FUNCTION__);
    return (int)msg.wParam;
}


LRESULT CALLBACK WndProc(HWND platform_window, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    TCHAR greeting[] = _T("Hello, DConsole!");

    switch (message)
    {
    case WM_PAINT:
        hdc = BeginPaint(platform_window, &ps);
        TextOut(hdc,
                5, 5,
                greeting, _tcslen(greeting));

        EndPaint(platform_window, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(platform_window, message, wParam, lParam);
        break;
    }

    return 0;
}

WinMainApp::WinMainApp()
:DConsoleUI()
{
}
void WinMainApp::StartApp()
{
    WinMain(0, 0, 0, 1);
}