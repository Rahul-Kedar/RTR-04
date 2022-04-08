// Header Files
#include <windows.h>
#include <stdio.h>  // For File IO
#include <stdlib.h> // For exit()
#include "window.h"

#define WIN_WIDTH   800
#define WIN_HEIGHT  600

// Global Function Declarations 
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Global Variables
HWND ghwnd;
BOOL gbFullscreen = FALSE;
BOOL gbActiveWindow = FALSE;

FILE* gpFile = NULL;


// Entry Point Function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
    // function declarations
    int initialize(void);
    void display(void);
    void update(void);
    void uninitialize(void);

    // Variable Declarations
    WNDCLASSEX wndclass;
    HWND hwnd;
    MSG msg;
    TCHAR szAppName[] = TEXT("MyWindow");
    BOOL bDone = FALSE;
    int iRetVal = 0;

    // Code
    if (fopen_s(&gpFile, "Log.txt", "w") != 0)
    {
        MessageBox(NULL, TEXT("Creation of log file failed. Exiting..."), TEXT("File I/O Error"), MB_OK);
        exit(0);
    }
    else
    {
        fprintf(gpFile, "Log file successfully created.\n");
    }

    // Initialization of wndclass structure
    wndclass.cbSize = sizeof(WNDCLASSEX);
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.lpfnWndProc = WndProc;
    wndclass.hInstance = hInstance;
    wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MY_ICON));
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.lpszClassName = szAppName;
    wndclass.lpszMenuName = NULL;
    wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MY_ICON));

    // Register wndclass
    RegisterClassEx(&wndclass);

    int MonitorWidth = GetSystemMetrics(SM_CXSCREEN);
    int MonitorHeight = GetSystemMetrics(SM_CYSCREEN);

    // Create Window
    hwnd = CreateWindow(szAppName,
                        TEXT("Rahul Ajinath Kedar"),
                        WS_OVERLAPPEDWINDOW,
                        (MonitorWidth - WIN_WIDTH) / 2,
                        (MonitorHeight - WIN_HEIGHT) / 2,
                        WIN_WIDTH,
                        WIN_HEIGHT,
                        NULL,
                        NULL,
                        hInstance,
                        NULL);

    ghwnd = hwnd;

    // initialize
    iRetVal = initialize();

    // Show Window
    ShowWindow(hwnd, iCmdShow);

    // foregrounding & focusing the window
    SetForegroundWindow(hwnd);
    SetFocus(hwnd);

    // Game loop
    while (bDone == FALSE)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                bDone = TRUE;
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            if (gbActiveWindow == TRUE)
            {
                // render the scene.
                display();
                
                // update scene.
                update();
            }
        }
    }

    uninitialize();

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    // Function Declaration
    void ToggleFullscreen(void);
    void resize(int, int);

    // Code
    switch(iMsg)
    {
    case WM_SETFOCUS:
        gbActiveWindow = TRUE;
        break;

    case WM_KILLFOCUS:
        gbActiveWindow = FALSE;
        break;

    case WM_ERASEBKGND:
        break;      // As this is retained mode graphics there is WM_PAINT to paint.

    case WM_CHAR:
        switch (wParam)
        {
        case 'F':
        case 'f':
            ToggleFullscreen();
            break;

        default:
            break;
        }
        break;

    case WM_KEYDOWN:
        switch (wParam)
        {
        case 27:
            DestroyWindow(hwnd);
            break;

        default:
            break;
        }
        break;

    case WM_SIZE:
        resize(LOWORD(lParam), HIWORD(lParam));
        break;

    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        break;
    }

    return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

void ToggleFullscreen(void)
{
    //Variable Declarations
    static DWORD dwStyle;
    static WINDOWPLACEMENT wp;
    MONITORINFO mi;


    //code
    wp.length = sizeof(WINDOWPLACEMENT);

    if (gbFullscreen == FALSE)
    {
        dwStyle = GetWindowLong(ghwnd, GWL_STYLE);

        if (dwStyle & WS_OVERLAPPEDWINDOW)
        {
            mi.cbSize = sizeof(MONITORINFO);
            if (GetWindowPlacement(ghwnd, &wp) && GetMonitorInfo(MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY), &mi))
            {
                SetWindowLong(ghwnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
                SetWindowPos(ghwnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right - mi.rcMonitor.left, mi.rcMonitor.bottom - mi.rcMonitor.top, SWP_NOZORDER | SWP_FRAMECHANGED);
            }
            ShowCursor(FALSE);
            gbFullscreen = TRUE;
        }
    }
    else
    {
        SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
        SetWindowPlacement(ghwnd, &wp);
        SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);

        ShowCursor(TRUE);
        gbFullscreen = FALSE;
    }
}

int initialize(void)
{
    // function declarations
    // variable declarations
    // code

    return 0;
}

void resize(int width, int height)
{
    // code
    if (height == 0)
        height = 1;     // To avoid divided by 0 in future code.
}

void display(void)
{
    // code
}

void update(void)
{
    // code
}

void uninitialize(void)
{
    // function declarations
    void ToggleFullscreen(void);

    // code
    if (gbFullscreen)
    {
        ToggleFullscreen();
    }

    if (ghwnd)
    {
        DestroyWindow(ghwnd);
        ghwnd = NULL;
    }

    if (gpFile)
    {
        fprintf(gpFile, "Log file successfully closed.\n");
        fclose(gpFile);
        gpFile = NULL;
    }
}
