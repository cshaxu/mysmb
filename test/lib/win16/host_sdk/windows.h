#ifndef TEST_WIN16_HOST_WINDOWS_H
#define TEST_WIN16_HOST_WINDOWS_H
#include "../fake_sdk/windows.h"
#define PASCAL
#define __export
#define FALSE 0
#define TRUE 1
#define COLOR_WINDOW 5
#define COLORONCOLOR 3
#define DIB_RGB_COLORS 0
#define SRCCOPY 0
#define CS_HREDRAW 1
#define CS_VREDRAW 2
#define IDC_ARROW ((char *)1)
#define WS_OVERLAPPEDWINDOW 0
#define CW_USEDEFAULT 0
#define BITSPIXEL 12
#define PLANES 14
#define SM_CYSCREEN 1
#define SM_CYCAPTION 2
#define SM_CYFRAME 3
#define WM_QUERYNEWPALETTE 1
#define WM_PALETTECHANGED 2
#define WM_KEYDOWN 3
#define WM_KEYUP 4
#define WM_SETFOCUS 5
#define WM_KILLFOCUS 6
#define WM_TIMER 7
#define WM_PAINT 8
#define WM_DESTROY 9
#define WM_QUIT 10
#define WM_CLOSE 11
#define GetMessage test_host_GetMessage
#define DispatchMessage test_host_DispatchMessage
#define SetTimer test_host_SetTimer
#define KillTimer test_host_KillTimer
#define CreateWindow test_host_CreateWindow
#define DestroyWindow test_host_DestroyWindow
#define PostQuitMessage test_host_PostQuitMessage
#define DefWindowProc test_host_DefWindowProc
#define RegisterClass test_host_RegisterClass
#define GetDC test_host_GetDC
#define GetClientRect test_host_GetClientRect
#define SelectPalette test_host_SelectPalette
#define CreatePalette test_host_CreatePalette
#define DeleteObject test_host_DeleteObject
#define LoadCursor test_host_LoadCursor
#define RealizePalette test_host_RealizePalette
#define ReleaseDC test_host_ReleaseDC
#define InvalidateRect test_host_InvalidateRect
#define UpdateWindow test_host_UpdateWindow
#define BeginPaint test_host_BeginPaint
#define EndPaint test_host_EndPaint
#define SetStretchBltMode test_host_SetStretchBltMode
#define StretchDIBits test_host_StretchDIBits
#define GetDeviceCaps test_host_GetDeviceCaps
#define GetSystemMetrics test_host_GetSystemMetrics
#define AdjustWindowRect test_host_AdjustWindowRect
#define ShowWindow test_host_ShowWindow
#define TranslateMessage test_host_TranslateMessage
typedef unsigned short WORD;
#include <stdint.h>
typedef uintptr_t WPARAM;
typedef long LPARAM,LRESULT;
typedef void *HWND;
typedef void *HDC;
typedef void *HPALETTE;
typedef void *HBRUSH;
typedef struct {long left,top,right,bottom;} RECT;
typedef struct {int unused;} PAINTSTRUCT;
typedef struct {DWORD biSize;long biWidth,biHeight;WORD biPlanes,biBitCount;DWORD biCompression,biSizeImage;long biXPelsPerMeter,biYPelsPerMeter;DWORD biClrUsed,biClrImportant;} BITMAPINFOHEADER;
typedef struct {unsigned char rgbBlue,rgbGreen,rgbRed,rgbReserved;} RGBQUAD;
typedef struct {BITMAPINFOHEADER header;RGBQUAD colors[1];} BITMAPINFO;
typedef struct {unsigned char peRed,peGreen,peBlue,peFlags;} PALETTEENTRY;
typedef struct {WORD version,count;PALETTEENTRY entries[1];} LOGPALETTE;
typedef struct {unsigned short style;LRESULT (*lpfnWndProc)(HWND,UINT,WPARAM,LPARAM);HINSTANCE hInstance;void *hCursor;HBRUSH hbrBackground;const char *lpszClassName;} WNDCLASS;
typedef struct {UINT message;WPARAM wParam;LPARAM lParam;} MSG;
int KillTimer(HWND,unsigned short);
int SetTimer(HWND,unsigned short,unsigned short,void *);
int DestroyWindow(HWND);
void PostQuitMessage(int);
void InvalidateRect(HWND,const RECT *,int);
void UpdateWindow(HWND);
HDC GetDC(HWND);
HPALETTE SelectPalette(HDC,HPALETTE,int);
unsigned short RealizePalette(HDC);
void ReleaseDC(HWND,HDC);
HDC BeginPaint(HWND,PAINTSTRUCT *);
void GetClientRect(HWND,RECT *);
void SetStretchBltMode(HDC,int);
void StretchDIBits(HDC,int,int,int,int,int,int,int,int,const void *,const BITMAPINFO *,int,long);
void EndPaint(HWND,PAINTSTRUCT *);
LRESULT DefWindowProc(HWND,UINT,WPARAM,LPARAM);
int GetDeviceCaps(HDC,int);
HPALETTE CreatePalette(const LOGPALETTE *);
int DeleteObject(void *);
void *LoadCursor(HINSTANCE,const char *);
int RegisterClass(const WNDCLASS *);
int GetSystemMetrics(int);
int AdjustWindowRect(RECT *,long,int);
HWND CreateWindow(const char *,const char *,long,int,int,int,int,HWND,void *,HINSTANCE,void *);
void ShowWindow(HWND,int);
int GetMessage(MSG *,HWND,int,int);
void TranslateMessage(const MSG *);
void DispatchMessage(const MSG *);
#endif
