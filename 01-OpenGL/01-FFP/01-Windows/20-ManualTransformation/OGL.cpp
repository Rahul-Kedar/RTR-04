// Header Files
#include <windows.h>
#include <stdio.h>  // For File IO
#include <stdlib.h> // For exit()
#include "OGL.h"

// OpenGL header files
#include <GL/gl.h>
#include <GL/glu.h>

#define _USE_MATH_DEFINES 1
#include <math.h> // For PI & trignometric functions

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

float angleCube = 0.0f;

GLfloat identityMatrix[16];
GLfloat translationMatrix[16];
GLfloat scaleMatrix[16];
GLfloat rotationMatrix_X[16];
GLfloat rotationMatrix_Y[16];
GLfloat rotationMatrix_Z[16];


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
    pfd.cDepthBits = 32;   // Can be 24 as well

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

    // Depth related changes
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    // Initialization of matrix arrays
    // Identity Matrix
    identityMatrix[0] = 1.0f;
    identityMatrix[1] = 0.0f;
    identityMatrix[2] = 0.0f;
    identityMatrix[3] = 0.0f;
    identityMatrix[4] = 0.0f;
    identityMatrix[5] = 1.0f;
    identityMatrix[6] = 0.0f;
    identityMatrix[7] = 0.0f;
    identityMatrix[8] = 0.0f;
    identityMatrix[9] = 0.0f;
    identityMatrix[10] = 1.0f;
    identityMatrix[11] = 0.0f;
    identityMatrix[12] = 0.0f;
    identityMatrix[13] = 0.0f;
    identityMatrix[14] = 0.0f;
    identityMatrix[15] = 1.0f;

    // Translation Matrix
    translationMatrix[0] = 1.0f;
    translationMatrix[1] = 0.0f;
    translationMatrix[2] = 0.0f;
    translationMatrix[3] = 0.0f;
    translationMatrix[4] = 0.0f;
    translationMatrix[5] = 1.0f;
    translationMatrix[6] = 0.0f;
    translationMatrix[7] = 0.0f;
    translationMatrix[8] = 0.0f;
    translationMatrix[9] = 0.0f;
    translationMatrix[10] = 1.0f;
    translationMatrix[11] = 0.0f;
    translationMatrix[12] = 0.0f;
    translationMatrix[13] = 0.0f;
    translationMatrix[14] = -4.0f;
    translationMatrix[15] = 1.0f;

    // Scale Matrix
    scaleMatrix[0] = 0.75f;
    scaleMatrix[1] = 0.0f;
    scaleMatrix[2] = 0.0f;
    scaleMatrix[3] = 0.0f;
    scaleMatrix[4] = 0.0f;
    scaleMatrix[5] = 0.75f;
    scaleMatrix[6] = 0.0f;
    scaleMatrix[7] = 0.0f;
    scaleMatrix[8] = 0.0f;
    scaleMatrix[9] = 0.0f;
    scaleMatrix[10] = 0.75f;
    scaleMatrix[11] = 0.0f;
    scaleMatrix[12] = 0.0f;
    scaleMatrix[13] = 0.0f;
    scaleMatrix[14] = 0.0f;
    scaleMatrix[15] = 1.0f;


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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();

    glLoadMatrixf(identityMatrix);

    //glTranslatef(0.0f, 0.0f, -6.0f);
    glMultMatrixf(translationMatrix);

    //glScalef(0.75f, 0.75f, 0.75f);
    glMultMatrixf(scaleMatrix);

    //glRotatef(angleCube, 1.0f, 1.0f, 1.0f); //Rolling
    //float angle = angleCube * M_PI / 180.0f;
    static float angle = 0.0f;
    angle = angle + 0.001f;
    // X Rotation Matrix
    rotationMatrix_X[0] = 1.0f;
    rotationMatrix_X[1] = 0.0f;
    rotationMatrix_X[2] = 0.0f;
    rotationMatrix_X[3] = 0.0f;
    rotationMatrix_X[4] = 0.0f;
    rotationMatrix_X[5] = cos(angle);
    rotationMatrix_X[6] = sin(angle);
    rotationMatrix_X[7] = 0.0f;
    rotationMatrix_X[8] = 0.0f;
    rotationMatrix_X[9] = -sin(angle);
    rotationMatrix_X[10] = cos(angle);
    rotationMatrix_X[11] = 0.0f;
    rotationMatrix_X[12] = 0.0f;
    rotationMatrix_X[13] = 0.0f;
    rotationMatrix_X[14] = 0.0f;
    rotationMatrix_X[15] = 1.0f;

    // Y Rotation Matrix
    rotationMatrix_Y[0] = cos(angle);
    rotationMatrix_Y[1] = 0.0f;
    rotationMatrix_Y[2] = -sin(angle);
    rotationMatrix_Y[3] = 0.0f;
    rotationMatrix_Y[4] = 0.0f;
    rotationMatrix_Y[5] = 1.0f;
    rotationMatrix_Y[6] = 0.0f;
    rotationMatrix_Y[7] = 0.0f;
    rotationMatrix_Y[8] = sin(angle);
    rotationMatrix_Y[9] = 0.0f;
    rotationMatrix_Y[10] = cos(angle);
    rotationMatrix_Y[11] = 0.0f;
    rotationMatrix_Y[12] = 0.0f;
    rotationMatrix_Y[13] = 0.0f;
    rotationMatrix_Y[14] = 0.0f;
    rotationMatrix_Y[15] = 1.0f;

    // Z Rotation Matrix
    rotationMatrix_Z[0] = cos(angle);
    rotationMatrix_Z[1] = sin(angle);
    rotationMatrix_Z[2] = 0.0f;
    rotationMatrix_Z[3] = 0.0f;
    rotationMatrix_Z[4] = -sin(angle);
    rotationMatrix_Z[5] = cos(angle);
    rotationMatrix_Z[6] = 0.0f;
    rotationMatrix_Z[7] = 0.0f;
    rotationMatrix_Z[8] = 0.0f;
    rotationMatrix_Z[9] = 0.0f;
    rotationMatrix_Z[10] = 1.0f;
    rotationMatrix_Z[11] = 0.0f;
    rotationMatrix_Z[12] = 0.0f;
    rotationMatrix_Z[13] = 0.0f;
    rotationMatrix_Z[14] = 0.0f;
    rotationMatrix_Z[15] = 1.0f;

    glMultMatrixf(rotationMatrix_X);
    glMultMatrixf(rotationMatrix_Y);
    glMultMatrixf(rotationMatrix_Z);

    glBegin(GL_QUADS);
    // Front Face
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);

    // Right Face
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);

    // Back Face
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);

    // Left Face
    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);

    // Top Face
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);

    // Bottom Face
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);

    glEnd();

    SwapBuffers(ghdc);
}

void update(void)
{
    // code
    angleCube = angleCube + 0.3f;
    if (angleCube >= 360.0f)
        angleCube = angleCube - 360.0f;
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
