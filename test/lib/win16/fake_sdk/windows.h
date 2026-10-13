#ifndef TEST_WIN16_WINDOWS_H
#define TEST_WIN16_WINDOWS_H
#define FAR
#define LoadLibrary test_win16_LoadLibrary
#define FreeLibrary test_win16_FreeLibrary
#define GetProcAddress test_win16_GetProcAddress
#define GlobalAlloc test_win16_GlobalAlloc
#define GlobalLock test_win16_GlobalLock
#define GlobalUnlock test_win16_GlobalUnlock
#define GlobalFree test_win16_GlobalFree
#define WINAPI
typedef unsigned short UINT;
typedef unsigned short HINSTANCE;
typedef void *HGLOBAL;
typedef unsigned long DWORD;
typedef char *LPSTR;
typedef int (*FARPROC)(void);
#define GMEM_MOVEABLE 2
#define GMEM_SHARE 8192
#define GetModuleFileName test_win16_GetModuleFileName
UINT GetModuleFileName(HINSTANCE instance,char *path,UINT capacity);
#define GetTickCount test_win16_GetTickCount
DWORD GetTickCount(void);
HINSTANCE LoadLibrary(const char *name);
void FreeLibrary(HINSTANCE library);
FARPROC GetProcAddress(HINSTANCE library,const char *name);
HGLOBAL GlobalAlloc(UINT flags,DWORD size);
void *GlobalLock(HGLOBAL memory);
int GlobalUnlock(HGLOBAL memory);
HGLOBAL GlobalFree(HGLOBAL memory);
#endif
