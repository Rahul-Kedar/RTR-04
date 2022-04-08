// Header Files
#include <windows.h>
#include <stdio.h>  // For File IO
#include <stdlib.h> // For exit()
#include "OGL.h"

// OpenGL header files
#include <GL/gl.h>
#include <GL/glu.h>

#define WIN_WIDTH   800
#define WIN_HEIGHT  600

// OpenGL libraries
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

// Global Function Declarations 
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Global Variables
HWND ghwnd = NULL;
HDC ghdc = NULL;
HGLRC ghrc = NULL;
BOOL gbFullscreen = FALSE;
BOOL gbActiveWindow = FALSE;

FILE* gpFile = NULL;

float angleRectangle = 0.0f;


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
    wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
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
    hwnd = CreateWindowEx(WS_EX_APPWINDOW,
                        szAppName,
                        TEXT("OpenGL Window"),
                        WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
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
    if (iRetVal == -1)
    {
        fprintf(gpFile, "choose pixel format failed\n");
        uninitialize();
    }    
    else if (iRetVal == -2)
    {
        fprintf(gpFile, "set pixel format failed\n");
        uninitialize();
    }
    else if (iRetVal == -3)
    {
        fprintf(gpFile, "create OpenGL context failed\n");
        uninitialize();
    }
    else if (iRetVal == -4)
    {
        fprintf(gpFile, "making OpenGL context as curren context failed\n");
        uninitialize();
    }
    else
    {
        fprintf(gpFile, "initialize successfull\n");
    }

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
        return 0;       // It is immediate mode graphics so there is someone else here to erase background (OpenGL).

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
    void resize(int, int);

    // variable declarations
    PIXELFORMATDESCRIPTOR pfd;
    int iPixelFormatIndex = 0;

    // code
    // intialization of PIXELFORMATDESCRIPTOR
    ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cRedBits = 8;
    pfd.cGreenBits = 8;
    pfd.cBlueBits = 8;
    pfd.cAlphaBits = 8;

    // GetDC
    ghdc = GetDC(ghwnd);

    // choose pixel format
    iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd);

    if (iPixelFormatIndex == 0)
    {
        return -1;
    }

    // set choosen pixel format
    if (SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == FALSE)
    {
        return -2;
    }

    // create OpenGL rendering context
    ghrc = wglCreateContext(ghdc);
    if (ghrc == NULL)
    {
        return -3;
    }

    // make redering context as current context
    if (wglMakeCurrent(ghdc, ghrc) == FALSE)
    {
        return -4;
    }

    // OpenGL code starts here.
    // Clear the screen using black color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Warmup resize call
    resize(WIN_WIDTH, WIN_HEIGHT);

    return 0;
}

void resize(int width, int height)
{
    // code
    if (height == 0)
        height = 1;     // To avoid divided by 0 in future code.

    glViewport(0, 0, (GLsizei)width, (GLsizei)height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f); 
}

void display(void)
{
    // code
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -6.0f);
    glRotatef(angleRectangle, 1.0f, 0.0f, 0.0f); //Rolling

    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glEnd();

    SwapBuffers(ghdc);
}

void update(void)
{
    // code
    angleRectangle = angleRectangle + 0.5f;
    if (angleRectangle >= 360.0f)
        angleRectangle = angleRectangle - 360.0f;
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

    if (wglGetCurrentContext() == ghrc)
    {
        wglMakeCurrent(NULL, NULL);
    }

    if (ghrc)
    {
        wglDeleteContext(ghrc);
        ghrc = NULL;
    }
    
    if (ghdc)
    {
        ReleaseDC(ghwnd, ghdc);
        ghdc = NULL;
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
