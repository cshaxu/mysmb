#include <windows.h>
#include <string.h>
#include <stdio.h>
#include "platform/win32/text_console.h"
static int fail_view;
static BOOL probe_view(HANDLE output,BOOL absolute,const SMALL_RECT *view)
{
    if(fail_view) {fail_view=0;SetLastError(ERROR_INVALID_PARAMETER);return FALSE;}
    return SetConsoleWindowInfo(output,absolute,view);
}
#define SetConsoleWindowInfo probe_view
#include "../src/platform/win32/text_console.c"
#undef SetConsoleWindowInfo
static struct mysmb_win32_text_console device;
static struct mysmb_io_text_frame frame;
static CHAR_INFO rendered[4000];
/* Neutral fixture capture only;no ROM/game pixels enter this test. */
static int capture_window(HWND window,const char *diagnostic)
{
    RECT rect;
    typedef HANDLE (WINAPI *set_dpi_context)(HANDLE);
    set_dpi_context set_context;
    HANDLE old_context=NULL;
    HDC screen,memory;
    HBITMAP bitmap;
    HGDIOBJ previous;
    BITMAPINFO info;
    BITMAPFILEHEADER header;
    unsigned char *pixels;
    unsigned long bytes;
    FILE *file;
    char path[1024];
    int ok=0;
    if(strlen(diagnostic)>1000U)return 0;
    /* PrintWindow draws physical pixels;avoid a DPI-virtualized capture crop. */
    set_context=(set_dpi_context)GetProcAddress(GetModuleHandleA("user32.dll"),"SetThreadDpiAwarenessContext");
    if(set_context)old_context=set_context((HANDLE)(LONG_PTR)-4);
    if(!GetWindowRect(window,&rect) || rect.right<=rect.left || rect.bottom<=rect.top) {
        if(old_context)set_context(old_context);return 0;
    }
    ZeroMemory(&info,sizeof(info));info.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
    info.bmiHeader.biWidth=rect.right-rect.left;info.bmiHeader.biHeight=rect.bottom-rect.top;
    info.bmiHeader.biPlanes=1;info.bmiHeader.biBitCount=32;info.bmiHeader.biCompression=BI_RGB;
    bytes=(unsigned long)info.bmiHeader.biWidth*(unsigned long)info.bmiHeader.biHeight*4UL;
    if(bytes>16000000UL){if(old_context)set_context(old_context);return 0;}
    pixels=(unsigned char *)HeapAlloc(GetProcessHeap(),0,bytes);
    if(!pixels){if(old_context)set_context(old_context);return 0;}
    screen=GetDC(window);memory=CreateCompatibleDC(screen);
    bitmap=CreateCompatibleBitmap(screen,info.bmiHeader.biWidth,info.bmiHeader.biHeight);
    previous=SelectObject(memory,bitmap);
    if(PrintWindow(window,memory,0U) &&
        GetDIBits(memory,bitmap,0,(UINT)info.bmiHeader.biHeight,pixels,&info,DIB_RGB_COLORS)) {
        ZeroMemory(&header,sizeof(header));header.bfType=0x4d42U;
        header.bfOffBits=sizeof(header)+sizeof(BITMAPINFOHEADER);header.bfSize=header.bfOffBits+bytes;
        sprintf(path,"%s.bmp",diagnostic);file=fopen(path,"wb");
        if(file){ok=fwrite(&header,1,sizeof(header),file)==sizeof(header) &&
            fwrite(&info.bmiHeader,1,sizeof(BITMAPINFOHEADER),file)==sizeof(BITMAPINFOHEADER) &&
            fwrite(pixels,1,bytes,file)==bytes;fclose(file);}
    }
    SelectObject(memory,previous);DeleteObject(bitmap);DeleteDC(memory);
    ReleaseDC(window,screen);HeapFree(GetProcessHeap(),0,pixels);
    if(old_context)set_context(old_context);return ok;
}
static unsigned int checked_cells;
static int check_frame(void)
{
    COORD size={80,50},origin={0,0};
    SMALL_RECT view={0,0,79,49};
    CONSOLE_SCREEN_BUFFER_INFO info;
    unsigned int i,x,y,width,height;
    if(!GetConsoleScreenBufferInfo(device.output,&info))return 0;
    width=(unsigned int)(info.srWindow.Right-info.srWindow.Left+1);
    height=(unsigned int)(info.srWindow.Bottom-info.srWindow.Top+1);
    if(width>80U)width=80U;if(height>50U)height=50U;
    if(!width || !height)return 0;
    view.Right=(SHORT)(width-1U);view.Bottom=(SHORT)(height-1U);
    if(!ReadConsoleOutputW(device.output,rendered,size,origin,&view))return 0;
    if(view.Left!=0 || view.Top!=0 || view.Right!=(SHORT)(width-1U) || view.Bottom!=(SHORT)(height-1U))return 0;
    for(y=0;y<height;++y)for(x=0;x<width;++x) {
        WCHAR expected;
        i=y*80U+x;expected=(WCHAR)frame.cells[i].character;
        if(expected==0xdaU)expected=0x250cU;
        if(expected==0xbfU)expected=0x2510U;
        if(expected==0xc0U)expected=0x2514U;
        if(expected==0xd9U)expected=0x2518U;
        if(rendered[i].Char.UnicodeChar!=expected)return 0;
    }
    checked_cells=width*height;
    return 1;
}
int main(int argc,char **argv)
{
    HANDLE input,output;
    CONSOLE_SCREEN_BUFFER_INFO original,current;
    CONSOLE_FONT_INFOEX font,after_font;
    CONSOLE_CURSOR_INFO cursor,after_cursor;
    WCHAR title[256],after_title[256];
    CHAR_INFO sentinel[4],after[4];
    DWORD mode,after_mode;
    COORD origin={0,0},size={4,1};
    SMALL_RECT view={0,0,3,0};
    HWND owner;
    unsigned int cycle,i,attempt;
    if(argc<2)return 14;
    if(argc==3) {
        unsigned int wait;
        if(!PostMessage(GetConsoleWindow(),WM_SYSCOMMAND,SC_MAXIMIZE,0))return 15;
        for(wait=0;wait<80 && !IsZoomed(GetConsoleWindow());++wait)Sleep(25U);
        if(wait==80)return 16;
    }
    input=CreateFileA("CONIN$",GENERIC_READ|GENERIC_WRITE,
        FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,0,NULL);
    output=CreateFileA("CONOUT$",GENERIC_READ|GENERIC_WRITE,
        FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,0,NULL);
    if(input==INVALID_HANDLE_VALUE || output==INVALID_HANDLE_VALUE)return 1;
    SetConsoleTitleW(L"MySMB shell preservation sentinel");
    for(i=0;i<4;i++) {sentinel[i].Char.UnicodeChar=(WCHAR)(L'A'+i);sentinel[i].Attributes=0x4eU;}
    /* A freshly allocated host asynchronously applies its initial geometry. */
    Sleep(150U);
    if(!WriteConsoleOutputW(output,sentinel,size,origin,&view) ||
        !GetConsoleScreenBufferInfo(output,&original) || !GetConsoleMode(input,&mode))return 2;
    ZeroMemory(&font,sizeof(font));ZeroMemory(&after_font,sizeof(after_font));
    font.cbSize=sizeof(font);after_font.cbSize=sizeof(after_font);
    if(!GetCurrentConsoleFontEx(output,FALSE,&font) ||
        !GetConsoleCursorInfo(output,&cursor))return 3;
    GetConsoleTitleW(title,256);
    owner=CreateWindowA("STATIC","owned lifecycle probe",0,0,0,0,0,NULL,NULL,GetModuleHandle(NULL),NULL);
    if(!owner)return 4;
    for(i=0;i<4000;i++) {
        frame.cells[i].character=(unsigned char)('!'+i%90U);frame.cells[i].foreground=(unsigned char)(i%16U);frame.cells[i].background=1;
    }
    frame.cells[0].character=0xdaU;frame.cells[79].character=0xbfU;
    frame.cells[3920].character=0xc0U;frame.cells[3999].character=0xd9U;
    for(cycle=0;cycle<4;cycle++) {
        fail_view=cycle==3;
        {
            /* An optional geometry failure keeps valid input/output usable. */
            if(!mysmb_win32_text_console_open(&device,owner) || !device.borrowed ||
                device.window!=GetConsoleWindow() || !mysmb_win32_text_console_present(&device,&frame))return 6;
            if(!check_frame() || (device.geometry_usable && checked_cells!=4000U))return 21;
            {
                FILE *log=fopen(argv[1],"a");
                if(log){fprintf(log,"cycle%u glyphs=%u exact geometry=%u\n",cycle,checked_cells,device.geometry_usable);fclose(log);}
            }
            if(cycle==0 && device.window_usable) {
                unsigned int phase,wait;
                for(phase=0;phase<2;++phase) {
                    if(!PostMessage(device.window,WM_SYSCOMMAND,
                        phase==0?SC_MAXIMIZE:SC_RESTORE,0))return 17;
                    for(wait=0;wait<80;++wait) {
                        if((IsZoomed(device.window)!=0)==(phase==0))break;
                        Sleep(25U);
                    }
                    if(wait==80)return 18;
                    for(wait=0;wait<20;++wait) {
                        if(mysmb_win32_text_console_present(&device,&frame)==MYSMB_WIN32_CONSOLE_LOST)return 19;
                        Sleep(20U);
                    }
                    if(!check_frame())return 22;
                }
                if(!capture_window(device.window,argv[1]))return 23;
                {
                    CONSOLE_SCREEN_BUFFER_INFO fitted;
                    FILE *log;
                    if(!GetConsoleScreenBufferInfo(device.output,&fitted))return 20;
                    log=fopen(argv[1],"a");
                    if(log) {
                        fprintf(log,"caption-maximize-Restore passed;view=%dx%d font=%dx%d\n",
                            fitted.srWindow.Right-fitted.srWindow.Left+1,
                            fitted.srWindow.Bottom-fitted.srWindow.Top+1,
                            device.effective_font.dwFontSize.X,device.effective_font.dwFontSize.Y);
                        fclose(log);
                    }
                }
            }
            mysmb_win32_text_console_close(&device);
        }
        /* Closing a borrowed device detaches only this process. */
        if(!AttachConsole(ATTACH_PARENT_PROCESS))return 7;
        CloseHandle(input);CloseHandle(output);
        input=CreateFileA("CONIN$",GENERIC_READ|GENERIC_WRITE,3,NULL,OPEN_EXISTING,0,NULL);
        output=CreateFileA("CONOUT$",GENERIC_READ|GENERIC_WRITE,3,NULL,OPEN_EXISTING,0,NULL);
        view.Left=view.Top=0;view.Right=3;view.Bottom=0;
        if(!ReadConsoleOutputW(output,after,size,origin,&view) ||
            memcmp(sentinel,after,sizeof(after)))return 8;
        if(!GetConsoleMode(input,&after_mode) || mode!=after_mode ||
            !GetConsoleScreenBufferInfo(output,&current))return 9;
        /* SetWindowPlacement delivers host geometry asynchronously. */
        for(attempt=0;attempt<40;++attempt) {
            if(!memcmp(&original.srWindow,&current.srWindow,sizeof(SMALL_RECT)))break;
            Sleep(25U);if(!GetConsoleScreenBufferInfo(output,&current))return 9;
        }
        if(memcmp(&original.dwSize,&current.dwSize,sizeof(COORD)) ||
            memcmp(&original.dwCursorPosition,&current.dwCursorPosition,sizeof(COORD)) ||
            original.wAttributes!=current.wAttributes ||
            memcmp(&original.srWindow,&current.srWindow,sizeof(SMALL_RECT))) {
            FILE *log=fopen(argv[1],"w");
            if(log) {
                fprintf(log,"cycle%u size%d,%d->%d,%d cursor%d,%d->%d,%d attr%u->%u view%d,%d,%d,%d->%d,%d,%d,%d\n",
                    cycle,original.dwSize.X,original.dwSize.Y,current.dwSize.X,current.dwSize.Y,
                    original.dwCursorPosition.X,original.dwCursorPosition.Y,current.dwCursorPosition.X,current.dwCursorPosition.Y,
                    original.wAttributes,current.wAttributes,original.srWindow.Left,original.srWindow.Top,
                    original.srWindow.Right,original.srWindow.Bottom,current.srWindow.Left,current.srWindow.Top,
                    current.srWindow.Right,current.srWindow.Bottom);fclose(log);
            }
            return 10;
        }
        GetConsoleTitleW(after_title,256);
        if(wcscmp(title,after_title))return 11;
        if(!GetCurrentConsoleFontEx(output,FALSE,&after_font) ||
            memcmp(&font,&after_font,sizeof(font)))return 12;
        if(!GetConsoleCursorInfo(output,&after_cursor) ||
            cursor.dwSize!=after_cursor.dwSize || cursor.bVisible!=after_cursor.bVisible)return 13;
    }
    DestroyWindow(owner);CloseHandle(input);CloseHandle(output);
    return 0;
}
