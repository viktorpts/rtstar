// rtstar.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "rtstar.h"
#include "Cluster.h"
#include "visual.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

int drstate = 0;								// Render state
float mzoom = 1;									// Mouse zoom
HDC bmpCanvas = NULL;							// Our canvas
HBITMAP bmpBMP = NULL;							// Bitmap to fill the canvas

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
					 LPTSTR    lpCmdLine,
					 int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_RTSTAR, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_RTSTAR));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= NULL;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_RTSTAR));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_POPUP,
		// Window coordinates; set to fullscreen from launch
		0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
		NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_LBUTTONDOWN:
		if(drstate == 0)
		{
			drstate = 1;
			InvalidateRect(hWnd, NULL, 0);
		}
		break;
	case WM_RBUTTONDOWN:
		if(drstate == 2)
		{
			mzoom *= 1.2;
			drstate = 1;
			InvalidateRect(hWnd, NULL, 0);
		}
		break;
	case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);

			// Obtain the size of the drawing area.
			RECT rc;
			GetClientRect(
				hWnd,
				&rc
			);			

			// Save the original object
			HGDIOBJ original = NULL;
			original = SelectObject(
				ps.hdc,
				GetStockObject(DC_PEN)
			);

			if(drstate == 0)
			{
				bmpCanvas = CreateCompatibleDC(hdc);
				bmpBMP = CreateCompatibleBitmap(hdc,rc.right,rc.bottom);
				// Copy window to off-screen canvas
				//SelectObject(bmpCanvas,bmpBMP);
				//BitBlt(bmpCanvas,0,0,rc.right,rc.bottom,hdc,0,0,SRCCOPY);
			}
			if(drstate == 1)
			{
				// Blank the screen
				FillRect(hdc,&rc,(HBRUSH)GetStockObject(BLACK_BRUSH));


				// Output some text
				HFONT hFont = (HFONT)GetStockObject(ANSI_VAR_FONT);
				SelectObject(ps.hdc,hFont);
				SetTextColor(ps.hdc, RGB(64, 255, 64));
				SetBkColor(ps.hdc, RGB(0,0,0));
				TextOut(ps.hdc,rc.bottom + 32,32,L"Rendering, please wait...",24);

				CGObject *star;
				for (double g=1;g<=STARCOUNT;g++) {
					star = new CGObject(g);
					star->Generate();
					star->SetAnomaly(10*2.3352624e55);
					CCartC coord = star->GetCartesian();

					//RotatePointX(&coord.x,&coord.y,&coord.z,-PI/3);

					RGBTRIPLE color = star->GetColor();
					COLORREF oc;


					int x,y;
					float z;
					x = int( (coord.x / GHALO / 2 + 0.5) * rc.bottom * mzoom ) - int((mzoom-1)*300);
					y = int( (coord.y / GHALO / 2 + 0.5) * rc.bottom * mzoom ) - int((mzoom-1)*300);
					//z = (coord.z / GHALO / 2 + 0.75);
					z = 1;
					if (x >= 0 && x <= rc.right && y >=0 && y <= rc.bottom) {
						oc = GetPixel(hdc, x, y);
						SetPixel(hdc, x, y, AdjustColor(oc,color,0.25*z));

						// Set falloff colors
						oc = GetPixel(hdc, x-1, y);
						if(oc != CLR_INVALID) {
							SetPixel(hdc, x-1, y, AdjustColor(oc,color,0.125*z));
						}

						oc = GetPixel(hdc, x+1, y);
						if(oc != CLR_INVALID) {
							SetPixel(hdc, x+1, y, AdjustColor(oc,color,0.125*z));
						}

						oc = GetPixel(hdc, x, y-1);
						if(oc != CLR_INVALID) {
							SetPixel(hdc, x, y-1, AdjustColor(oc,color,0.125*z));
						}

						oc = GetPixel(hdc, x, y+1);
						if(oc != CLR_INVALID) {
							SetPixel(hdc, x, y+1, AdjustColor(oc,color,0.125*z));
						}
					}
				}

				TextOut(ps.hdc,rc.bottom + 32,60,L"Complete.",9);
				// Clean up text output
				DeleteObject(hFont);

				// Copy results to off-screen canvas for later reference
				SelectObject(bmpCanvas,bmpBMP);
				BitBlt(bmpCanvas,0,0,rc.right,rc.bottom,hdc,0,0,SRCCOPY);
				drstate = 2;
			}
			if (drstate == 2)
			{
				BitBlt(hdc, 0, 0, rc.right, rc.bottom, bmpCanvas, 0, 0, SRCCOPY);
			}


			// Restore the original object
			SelectObject(ps.hdc, original);
			SelectObject(bmpCanvas,NULL);


			EndPaint(hWnd, &ps);
		}
		break;
	case WM_DESTROY:
		// CLEANUP IS ESSENTIAL!!; Delete any galactic data, the star-chart is exceptionally large
		DeleteObject(bmpCanvas);
		DeleteObject(bmpBMP);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}