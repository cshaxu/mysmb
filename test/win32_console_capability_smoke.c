#include <stdio.h>
#include <string.h>
#include "platform/win32/text_console.h"
static int lost,query_fail,partial,font_effect,font_calls,write_error,minimized,zoomed,window_calls,geometry_effect,fail_buffer_once;
static DWORD clock_value,palette_sets,cell_writes;
static CONSOLE_SCREEN_BUFFER_INFO buffer;
static CONSOLE_SCREEN_BUFFER_INFOEX palette;
static CONSOLE_FONT_INFOEX effective;
static CHAR_INFO written_cells[MYSMB_IO_TEXT_CELLS];
static WCHAR vt_prefix[512],vt_output[MYSMB_IO_TEXT_CELLS*48U+1024U];
static BOOL mode_probe(HANDLE h,LPDWORD mode)
{if(lost && h==(HANDLE)2)return FALSE;*mode=ENABLE_VIRTUAL_TERMINAL_PROCESSING;return TRUE;}
static BOOL buffer_probe(HANDLE h,PCONSOLE_SCREEN_BUFFER_INFO out)
{(void)h;if(query_fail)return FALSE;*out=buffer;return TRUE;}
static BOOL palette_probe(HANDLE h,PCONSOLE_SCREEN_BUFFER_INFOEX out)
{(void)h;*out=palette;out->cbSize=sizeof(*out);out->dwSize=buffer.dwSize;
 out->srWindow=buffer.srWindow;return TRUE;}
static BOOL palette_write(HANDLE h,PCONSOLE_SCREEN_BUFFER_INFOEX in)
{(void)h;palette=*in;++palette_sets;return TRUE;}
static BOOL font_set(HANDLE h,BOOL maximum,PCONSOLE_FONT_INFOEX font)
{(void)h;(void)maximum;++font_calls;if(font_effect)effective=*font;return TRUE;}
static BOOL font_get(HANDLE h,BOOL maximum,PCONSOLE_FONT_INFOEX font)
{(void)h;(void)maximum;*font=effective;return TRUE;}
static COORD largest(HANDLE h)
{COORD size={80,50};(void)h;return size;}
static DWORD probe_clock(void){return clock_value;}
static BOOL cell_write(HANDLE h,const CHAR_INFO *cells,COORD size,COORD origin,PSMALL_RECT view)
{(void)h;(void)size;(void)origin;if(write_error){SetLastError((DWORD)write_error);return FALSE;}CopyMemory(written_cells,cells,sizeof(written_cells));++cell_writes;if(partial)view->Bottom=20;return TRUE;}
static BOOL vt_write(HANDLE h,const VOID *data,DWORD count,LPDWORD written,LPVOID reserved)
{DWORD n=count<511U?count:511U;(void)h;(void)reserved;if(write_error){SetLastError((DWORD)write_error);return FALSE;}CopyMemory(vt_prefix,data,n*sizeof(WCHAR));vt_prefix[n]=0;*written=count;return TRUE;}
static BOOL iconic(HWND window){(void)window;return minimized;}
static BOOL zoom(HWND window){(void)window;return zoomed;}
static BOOL probe_client(HWND window,LPRECT rect)
{(void)window;rect->left=rect->top=0;rect->right=640;rect->bottom=400;return TRUE;}
static BOOL set_view(HANDLE output,BOOL absolute,const SMALL_RECT *view)
{(void)output;(void)absolute;++window_calls;if(geometry_effect){buffer.srWindow=*view;return TRUE;}SetLastError(ERROR_INVALID_PARAMETER);return FALSE;}
static BOOL set_size(HANDLE output,COORD size)
{(void)output;if(fail_buffer_once && size.X==80 && size.Y==50){--fail_buffer_once;return FALSE;}if(geometry_effect){buffer.dwSize=size;return TRUE;}return FALSE;}
#define IsIconic iconic
#define IsZoomed zoom
#define GetClientRect probe_client
#define SetConsoleWindowInfo set_view
#define SetConsoleScreenBufferSize set_size
#define GetConsoleMode mode_probe
#define GetConsoleScreenBufferInfo buffer_probe
#define GetConsoleScreenBufferInfoEx palette_probe
#define SetConsoleScreenBufferInfoEx palette_write
#define SetCurrentConsoleFontEx font_set
#define GetCurrentConsoleFontEx font_get
#define GetLargestConsoleWindowSize largest
#define GetTickCount probe_clock
#define WriteConsoleW vt_write
#define WriteConsoleOutputW cell_write
#include "../src/platform/win32/text_console.c"
static struct mysmb_win32_text_console device;
static struct mysmb_io_text_frame scene;
#define CHECK(x) do {if(!(x)){printf("failed line %d\n",__LINE__);return 1;}}while(0)
static WORD expected_attribute(const struct mysmb_io_text_frame *frame,unsigned int i)
{
    unsigned char fg=frame->cells[i].foreground&15U,bg=frame->cells[i].background&15U;
    if(frame->source_colors==1U) {
        fg=mysmb_io_color_text_nearest(frame->colors[fg]);
        bg=mysmb_io_color_text_nearest(frame->colors[bg]);
    }
    return (WORD)(fg|((WORD)bg<<4U));
}
static int check_palette(const unsigned long *colors)
{
    unsigned int i;
    for(i=0U;i<16U;++i)
        if(palette.ColorTable[i]!=RGB((colors[i]>>16U)&255UL,
            (colors[i]>>8U)&255UL,colors[i]&255UL))return 0;
    return 1;
}
int main(void)
{
 unsigned i,previous_fonts;
 device.opened=1;device.input=(HANDLE)1;device.output=(HANDLE)2;
 buffer.dwSize.X=80;buffer.dwSize.Y=50;buffer.srWindow.Right=79;buffer.srWindow.Bottom=49;
 effective.cbSize=sizeof(effective);effective.dwFontSize.X=2;effective.dwFontSize.Y=4;
 device.window_usable=0U;CHECK(mysmb_win32_console_indexed_carrier(&device));
 effective.dwFontSize.X=9;effective.dwFontSize.Y=18;
 CHECK(!mysmb_win32_console_indexed_carrier(&device));
 scene.rows=50;scene.source_colors=1;
 for(i=0U;i<4000U;++i) {
  scene.cells[i].character='X';scene.cells[i].foreground=(unsigned char)(i&15U);
  scene.cells[i].background=(unsigned char)((i>>4U)&15U);
 }
 for(i=0U;i<16U;++i)scene.colors[i]=((unsigned long)(i*13U)<<16U)|((unsigned long)(255U-i*11U)<<8U)|(unsigned long)(i*7U);
 /* The mock reports VT mode enabled. Presentation must still use ColorTable
  * plus indexed CHAR_INFO, never a WriteConsoleW escape stream. */
 /* A hidden carrier owns its font. A logical grid request must not install
  * the visible-console font and transiently invalidate its capture region. */
 device.window_usable=0;mysmb_win32_console_fit(&device,1);CHECK(font_calls==0);
 device.window_usable=1;mysmb_win32_console_fit(&device,1);CHECK(font_calls==1);
 CHECK(device.effective_font.dwFontSize.Y==18);
 font_effect=1;mysmb_win32_console_fit(&device,1);
 CHECK(device.effective_font.dwFontSize.X==8 && device.effective_font.dwFontSize.Y==8);
 CHECK(mysmb_win32_text_console_present(&device,&scene)==MYSMB_WIN32_CONSOLE_READY);
 CHECK(palette_sets==0U && cell_writes==1U);
 for(i=0U;i<4000U;++i)CHECK(written_cells[i].Attributes==expected_attribute(&scene,i));
 partial=1;
 for(i=0U;i<200;++i)CHECK(mysmb_win32_text_console_present(&device,&scene)==MYSMB_WIN32_CONSOLE_DEFER);
 partial=0;write_error=ERROR_INVALID_PARAMETER;
 for(i=0U;i<200;++i)CHECK(mysmb_win32_text_console_present(&device,&scene)==MYSMB_WIN32_CONSOLE_DEFER);
 write_error=ERROR_ACCESS_DENIED;CHECK(mysmb_win32_text_console_present(&device,&scene)==MYSMB_WIN32_CONSOLE_LOST);
 write_error=0;query_fail=1;CHECK(mysmb_win32_text_console_present(&device,&scene)==MYSMB_WIN32_CONSOLE_DEFER);
 query_fail=0;lost=1;CHECK(mysmb_win32_text_console_present(&device,&scene)==MYSMB_WIN32_CONSOLE_LOST);
 lost=0;buffer.srWindow.Bottom=29;clock_value=100;
 CHECK(mysmb_win32_text_console_present(&device,&scene)==MYSMB_WIN32_CONSOLE_READY);
 previous_fonts=(unsigned)font_calls;clock_value=200;
 CHECK(mysmb_win32_text_console_present(&device,&scene)==MYSMB_WIN32_CONSOLE_READY);
 CHECK(font_calls==(int)previous_fonts);clock_value=300;
 CHECK(mysmb_win32_text_console_present(&device,&scene)==MYSMB_WIN32_CONSOLE_READY);
 CHECK(font_calls==(int)previous_fonts+1);
 buffer.srWindow.Bottom=49;clock_value=500;
 /* A non-window carrier owns geometry as well as font: it must never see the
  * temporary 1x1 probe rectangle used only by classic visible consoles. */
 {COORD target={80,50};SMALL_RECT view={0,0,79,49};
  device.window_usable=0;geometry_effect=1;window_calls=0;
  CHECK(!mysmb_win32_console_size(&device,target,&view));CHECK(window_calls==0);
  device.window_usable=1;
  CHECK(mysmb_win32_console_size(&device,target,&view));
  buffer.dwSize.X=120;buffer.dwSize.Y=30;buffer.srWindow.Right=119;buffer.srWindow.Bottom=29;fail_buffer_once=2;
  CHECK(!mysmb_win32_console_size(&device,target,&view));
  CHECK(buffer.dwSize.X==120 && buffer.dwSize.Y==30 && buffer.srWindow.Right==119 && buffer.srWindow.Bottom==29);
  fail_buffer_once=1;CHECK(mysmb_win32_console_size(&device,target,&view));
  geometry_effect=0;CHECK(!mysmb_win32_console_size(&device,target,&view));
  buffer.srWindow=view;buffer.dwSize=target;window_calls=0;
 }
 device.window_usable=1;zoomed=1;buffer.srWindow.Bottom=69;clock_value=1000;
 CHECK(mysmb_win32_text_console_present(&device,&scene)==MYSMB_WIN32_CONSOLE_READY);
 clock_value=1200;CHECK(mysmb_win32_text_console_present(&device,&scene)==MYSMB_WIN32_CONSOLE_READY);
 CHECK(window_calls==0);zoomed=0;buffer.srWindow.Bottom=49;clock_value=1400;
 CHECK(mysmb_win32_text_console_present(&device,&scene)==MYSMB_WIN32_CONSOLE_READY);
 clock_value=1600;CHECK(mysmb_win32_text_console_present(&device,&scene)==MYSMB_WIN32_CONSOLE_READY);
 CHECK(window_calls>0);minimized=1;
 CHECK(mysmb_win32_text_console_present(&device,&scene)==MYSMB_WIN32_CONSOLE_DEFER);
 minimized=0;write_error=ERROR_GEN_FAILURE;
 for(i=0U;i<119;++i)CHECK(mysmb_win32_text_console_present(&device,&scene)==MYSMB_WIN32_CONSOLE_DEFER);
 CHECK(mysmb_win32_text_console_present(&device,&scene)==MYSMB_WIN32_CONSOLE_LOST);
 write_error=0;
 scene.rows=25;scene.colors[0]=0x787cecUL;scene.colors[2]=0xeceeeeUL;
 for(i=0U;i<2000U;++i){scene.cells[i].foreground=2;scene.cells[i].background=0;}
 CHECK(mysmb_win32_text_console_present(&device,&scene)==MYSMB_WIN32_CONSOLE_READY);
 CHECK(palette_sets==0U);
 for(i=0U;i<2000U;++i)CHECK(written_cells[i].Attributes==expected_attribute(&scene,i));
 scene.source_colors=0;
 for(i=0U;i<16U;++i)scene.colors[i]=0U;
 for(i=0U;i<2000U;++i) {
  scene.cells[i].foreground=(unsigned char)(i&15U);
  scene.cells[i].background=(unsigned char)((i>>4U)&15U);
 }
 CHECK(mysmb_win32_text_console_present(&device,&scene)==MYSMB_WIN32_CONSOLE_READY);
 for(i=0U;i<16U;++i)scene.colors[i]=mysmb_io_color_text_rgb((mysmb_io_u8)i);
 for(i=0U;i<2000U;++i)
  CHECK(written_cells[i].Attributes==expected_attribute(&scene,i));
 /* A successful output-mode capability selects authored RGB VT output. */
 device.vt_output=1U;device.terminal_output=vt_output;scene.source_colors=1U;
 scene.rows=25U;buffer.srWindow.Bottom=24;scene.colors[0]=0x787cecUL;scene.colors[2]=0xeceeeeUL;
 for(i=0U;i<2000U;++i){scene.cells[i].foreground=2U;scene.cells[i].background=0U;}
 CHECK(mysmb_win32_text_console_present(&device,&scene)==MYSMB_WIN32_CONSOLE_READY);
 CHECK(wcsncmp(vt_prefix,L"\x1b[0m",4U)==0);
 CHECK(wcsstr(vt_prefix,L"38;2;236;238;238;48;2;120;124;236m")!=0);
 puts("console capabilities: VT RGB and standard 16-colour API paths passed");return 0;
}
