// VektoriaApp.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//


#include "stdafx.h"
#include <windows.h>
#include <windowsx.h>
#include <WinUser.h>
#include "resource.h"
#include "Game.h"
#include "Vektoria\Timer.h"
#include "Vektoria\Splash.h"
#include "Mmsystem.h"

#pragma comment(lib, "winmm.lib")


//--------------------------------------------------------------------------------------
// Global variables
//--------------------------------------------------------------------------------------
TCHAR szClassName[] = _T("VektoriaWindowClass");
static bool g_bFullscreen = false;
//--------------------------------------------------------------------------------------
// Forward declarations 
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
static void ChangeDisplay(HWND);


CGame * g_pgame;


//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = NULL;   /* This is the handle for our window */
	MSG msg;
	WNDCLASSEX wcex;    /* Data structure for the windowclass */
	BOOL bQuit = FALSE;

	/* The window structure */
	wcex.hInstance = hInstance;
	wcex.lpszClassName = szClassName;
	wcex.lpfnWndProc = WndProc;  /* This function is called by windows */
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;    /* Catch double-clicks */
	wcex.cbSize = sizeof(WNDCLASSEX);
	/* Use vektoria icon and default mouse-pointer */
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.lpszMenuName = NULL;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);  /* Use Windows's default colour as the background of the window */


	/* Register the window class, and if it fails quit the program */
	if (!RegisterClassEx(&wcex))  {
		MessageBox(NULL, _T("Call to RegisterClassEx failed!"), _T("VektoriaV9App"), NULL);
		return 1;
	}

	/* The class is registered, let's create the program*/
	hWnd = CreateWindowEx(
		0,                      /* Extended possibilites for variation */
		szClassName,            /* Classname */
		_T("VektoriaApp"),	/* Title Text */
		WS_OVERLAPPEDWINDOW,    /* default window */
		CW_USEDEFAULT,          /* Windows decides the position */
		CW_USEDEFAULT,          /* where the window ends up on the screen */
		1920,                   /* The programs width */
		1080,                   /* and height in pixels */
		HWND_DESKTOP,           /* The window is a child-window to desktop */
		NULL,                   /* No menu */
		hInstance,              /* Program Instance handler */
		NULL                    /* No Window Creation data */
		);

	if (!hWnd) {
		MessageBox(NULL, _T("Call to CreateWindow failed!"), _T("VektoriaV9App"), NULL);
		return 1;
	}

	CSplash splash;
	splash.Init(hWnd, hInstance);
	splash.Show();


	// display the window on the screen
	ShowWindow(hWnd, nCmdShow);

	// Game Init
	g_pgame = new CGame();
	RECT rect;
	GetClientRect(hWnd, &rect);
	g_pgame->Init(hWnd, &splash);

	CTimer timer;
	timer.SwitchFrameRateCalculationOn();
	double dStartTime = timer.GetElapsedTime();
	double dLastTime = dStartTime;

	float fTimeDelta;
	float fTime;
	float fTimeLastShow = 0.0F;
	bool bFirstTick = true;
	while (!bQuit)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				bQuit = TRUE;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			//FrameRate
			timer.Tick(fTime, fTimeDelta);

			if (fTime - fTimeLastShow >= 0.2F) // TB: SetWindowTextA stürzt ab, wenn zu schnell hintereinander aufgerufen wird (Microsoft-Fehler) => daher die Zeitbegrenzung
			{
				char ac[300];
				sprintf_s(ac,300, "VektoriaApp        FR-Average: %.3f; FR-Long Average: %.3f; FR Min: %.3f; FR Max: %.3f", timer.m_fFrameRateAverage, timer.m_fFrameRateAverageLong, timer.m_fFrameRateMin, timer.m_fFrameRateMax);
				SetWindowTextA(hWnd, ac);
				fTimeLastShow = fTime;
			}

			// Game Tick
			g_pgame->Tick(fTime, fTimeDelta);
			if (bFirstTick)
			{
				splash.Hide();
				bFirstTick = false;
			}

		}
	}
	g_pgame->Fini();
	delete g_pgame;

	/* The program return-value is 0 - The value that PostQuitMessage() gave */
	return ERROR_SUCCESS;
}



/*  This function is called by the Windows function DispatchMessage()  */
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)                  /* handle the messages */
	{
	case WM_SIZE:
		g_pgame->WindowReSize(LOWORD(wParam), HIWORD(lParam));
		return 0;

	case WM_KEYDOWN:
		if (wParam == VK_F11)
		{
			g_bFullscreen = !g_bFullscreen;
			ChangeDisplay(hwnd);
		}
		//if (wParam != VK_ESCAPE) break;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);           /* send a WM_QUIT to the message queue */
		break;

	default:                        /* for messages that we don't deal with */
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}


static void ChangeDisplay(HWND hWnd)
{
	DWORD dwExStyle;
	DWORD dwStyle;

	if (g_bFullscreen)
	{
		// Automatisch die Größe des primären Monitors ermitteln
		int iWidth = GetSystemMetrics(SM_CXSCREEN);
		int iHeight = GetSystemMetrics(SM_CYSCREEN);

		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));

		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (DWORD)iWidth;
		dmScreenSettings.dmPelsHeight = (DWORD)iHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		dwExStyle = WS_EX_APPWINDOW;
		dwStyle = WS_POPUP;
		SetWindowLongPtr(hWnd, GWL_EXSTYLE, dwExStyle);
		SetWindowLongPtr(hWnd, GWL_STYLE, dwStyle);
		SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, iWidth, iHeight, SWP_SHOWWINDOW);
		SetForegroundWindow(hWnd);
		SetFocus(hWnd);
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle = WS_OVERLAPPEDWINDOW;
		SetWindowLongPtr(hWnd, GWL_EXSTYLE, dwExStyle);
		SetWindowLongPtr(hWnd, GWL_STYLE, dwStyle);
		SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 1920, 1080, SWP_SHOWWINDOW); //TODO: alte width und height werte merken und dann wieder setzen
		SetForegroundWindow(hWnd);
		SetFocus(hWnd);
		ChangeDisplaySettings(NULL, 0);
	}


	return;
}