#include <windows.h>
#include <stdio.h>
#include "platform/win32/text_console.h"
static int lost,query_fail,partial,font_effect,font_calls,write_error,minimized,zoomed,window_calls;
static DWORD clock_value;
static CONSOLE_SCREEN_BUFFER_INFO buffer;
static CONSOLE_FONT_INFOEX effective;
static BOOL mode_probe(HANDLE h,LPDWORD mode)
{if(lost && h==(HANDLE)2)return FALSE;*mode=7;return TRUE;}
static BOOL buffer_probe(HANDLE h,PCONSOLE_SCREEN_BUFFER_INFO out)
{(void)h;if(query_fail)return FALSE;*out=buffer;return TRUE;}
static BOOL font_set(HANDLE h,BOOL maximum,PCONSOLE_FONT_INFOEX font)
{(void)h;(void)maximum;++font_calls,write_error,minimized,zoomed,window_calls;if(font_effect)effective=*font;return TRUE;}
static BOOL font_get(HANDLE h,BOOL maximum,PCONSOLE_FONT_INFOEX font)
{(void)h;(void)maximum;*font=effective;return TRUE;}
static COORD largest(HANDLE h)
{COORD size={80,50};(void)h;return size;}
static DWORD probe_clock(void){return clock_value;}
static BOOL vt_write(HANDLE h,const VOID *data,DWORD count,LPDWORD written,LPVOID reserved)
{(void)h;(void)data;(void)reserved;if(write_error){SetLastError((DWORD)write_error);return FALSE;}*written=partial?count-1:count;return TRUE;}
static BOOL cell_write(HANDLE h,const CHAR_INFO *cells,COORD size,COORD origin,PSMALL_RECT view)
{(void)h;(void)cells;(void)size;(void)origin;if(write_error){SetLastError((DWORD)write_error);return FALSE;}if(partial)view->Bottom=20;return TRUE;}
static BOOL iconic(HWND window){(void)window;return minimized;}
static BOOL zoom(HWND window){(void)window;return zoomed;}
static BOOL probe_client(HWND window,LPRECT rect)
{(void)window;rect->left=rect->top=0;rect->right=640;rect->bottom=400;return TRUE;}
static BOOL set_view(HANDLE output,BOOL absolute,const SMALL_RECT *view)
{(void)output;(void)absolute;(void)view;++window_calls;SetLastError(ERROR_INVALID_PARAMETER);return FALSE;}
static BOOL set_size(HANDLE output,COORD size)
{(void)output;(void)size;return FALSE;}
#define IsIconic iconic
#define IsZoomed zoom
#define GetClientRect probe_client
#define SetConsoleWindowInfo set_view
#define SetConsoleScreenBufferSize set_size
#define GetConsoleMode mode_probe
#define GetConsoleScreenBufferInfo buffer_probe
#define SetCurrentConsoleFontEx font_set
#define GetCurrentConsoleFontEx font_get
#define GetLargestConsoleWindowSize largest
#define GetTickCount probe_clock
#define WriteConsoleW vt_write
#define WriteConsoleOutputW cell_write
#include "../src/platform/win32/text_console.c"
static struct mysmb_win32_text_console device;
static struct mysmb_io_text_frame scene;
static WCHAR out[193024];
#define CHECK(x) do {if(!(x)){printf("failed line %d\n",__LINE__);return 1;}}while(0)
int main(void)
{
 unsigned i,backend;
 device.opened=1;device.input=(HANDLE)1;device.output=(HANDLE)2;
 device.terminal_output=out;buffer.dwSize.X=80;buffer.dwSize.Y=50;
 buffer.srWindow.Right=79;buffer.srWindow.Bottom=49;
 effective.cbSize=sizeof(effective);effective.dwFontSize.X=9;effective.dwFontSize.Y=18;
 for(i=0;i<4000;++i){scene.cells[i].character='X';scene.cells[i].foreground=15;}
 /* No-effect host still receives the same request;readback is not visual proof. */
 mysmb_win32_console_fit(&device,1);CHECK(font_calls==1);
 CHECK(device.effective_font.dwFontSize.Y==18);
 font_effect=1;mysmb_win32_console_fit(&device,1);
 CHECK(device.effective_font.dwFontSize.X==8 && device.effective_font.dwFontSize.Y==8);
 for(backend=0;backend<2;++backend) {
  device.vt_output=(unsigned char)backend;
  CHECK(mysmb_win32_text_console_present(&device,&scene)==MYSMB_WIN32_CONSOLE_READY);
  partial=1;
  for(i=0;i<200;++i)CHECK(mysmb_win32_text_console_present(&device,&scene)==MYSMB_WIN32_CONSOLE_DEFER);
  partial=0;write_error=ERROR_INVALID_PARAMETER;
  for(i=0;i<200;++i)CHECK(mysmb_win32_text_console_present(&device,&scene)==MYSMB_WIN32_CONSOLE_DEFER);
  write_error=ERROR_ACCESS_DENIED;CHECK(mysmb_win32_text_console_present(&device,&scene)==MYSMB_WIN32_CONSOLE_LOST);
  write_error=0;query_fail=1;CHECK(mysmb_win32_text_console_present(&device,&scene)==MYSMB_WIN32_CONSOLE_DEFER);
  query_fail=0;lost=1;CHECK(mysmb_win32_text_console_present(&device,&scene)==MYSMB_WIN32_CONSOLE_LOST);
  lost=0;buffer.srWindow.Bottom=29;clock_value=100;
  CHECK(mysmb_win32_text_console_present(&device,&scene)==MYSMB_WIN32_CONSOLE_READY);
  i=(unsigned)font_calls,write_error,minimized,zoomed,window_calls;clock_value=200;
  CHECK(mysmb_win32_text_console_present(&device,&scene)==MYSMB_WIN32_CONSOLE_READY);
  CHECK(font_calls==(int)i);clock_value=300;
  CHECK(mysmb_win32_text_console_present(&device,&scene)==MYSMB_WIN32_CONSOLE_READY);
  CHECK(font_calls==(int)i+1);
  buffer.srWindow.Bottom=49;clock_value=500;
 }
 /* Equivalent visible-window capabilities use the same fit/write policy.
  * Optional failed view changes through maximize/Restore never lose a device. */
 device.window_usable=1;zoomed=1;buffer.srWindow.Bottom=69;clock_value=1000;
 CHECK(mysmb_win32_text_console_present(&device,&scene)==MYSMB_WIN32_CONSOLE_READY);
 clock_value=1200;CHECK(mysmb_win32_text_console_present(&device,&scene)==MYSMB_WIN32_CONSOLE_READY);
 CHECK(window_calls==0);zoomed=0;buffer.srWindow.Bottom=49;clock_value=1400;
 CHECK(mysmb_win32_text_console_present(&device,&scene)==MYSMB_WIN32_CONSOLE_READY);
 clock_value=1600;CHECK(mysmb_win32_text_console_present(&device,&scene)==MYSMB_WIN32_CONSOLE_READY);
 CHECK(window_calls>0);minimized=1;
 CHECK(mysmb_win32_text_console_present(&device,&scene)==MYSMB_WIN32_CONSOLE_DEFER);
 minimized=0;write_error=ERROR_GEN_FAILURE;
 for(i=0;i<119;++i)CHECK(mysmb_win32_text_console_present(&device,&scene)==MYSMB_WIN32_CONSOLE_DEFER);
 CHECK(mysmb_win32_text_console_present(&device,&scene)==MYSMB_WIN32_CONSOLE_LOST);
 write_error=0;CHECK(mysmb_win32_text_console_present(&device,&scene)==MYSMB_WIN32_CONSOLE_READY);
 puts("console capabilities: font/no-effect,settled resize,partial/defer and real handle loss passed");return 0;
}
