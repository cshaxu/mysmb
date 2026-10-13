#include <string.h>
#include <stdio.h>
#include "win32/window.h"
#include "win32/text_console.h"
static struct mygames_win32_input keys;
static struct mygames_win32_window_input mouse;
static struct mygames_win32_window_geometry geometry;
static struct mygames_kvm_input_event seen[32];
static unsigned short seen_count;
static struct mygames_win32_text_console console;
static DWORD pixels[16];
static void receive(void *context,HWND window,const struct mygames_kvm_input_event *event)
{(void)context;(void)window;if(seen_count<32)seen[seen_count++]=*event;}
static LRESULT CALLBACK procedure(HWND window,UINT message,WPARAM word,LPARAM detail)
{
    LRESULT result;
    if(mygames_win32_window_event(window,message,word,detail,&mouse,&keys,&geometry,
        receive,0,&result))return result;
    if(message==WM_PAINT){mygames_win32_window_paint(window,pixels,4,4,16);return 0;}
    return DefWindowProc(window,message,word,detail);
}
static int poll(unsigned char kind,struct mygames_kvm_input_event *out)
{
    unsigned int budget=64;
    while(budget-- && mygames_win32_text_console_event(&console,&keys,out))
        if(out->kind==kind)return 1;
    return 0;
}
static int inject(INPUT_RECORD *record)
{DWORD written;return WriteConsoleInputW(console.input,record,1,&written) && written==1;}
int main(int argc,char **argv)
{
    HWND window;
    INPUT_RECORD record;
    struct mygames_kvm_input_event event;
    CONSOLE_SCREEN_BUFFER_INFO info;
    DWORD mode;
    HDC dc;
    BITMAPINFO bitmap;
    HBITMAP surface;
    HGDIOBJ old_surface;
    DWORD *rendered;
    RECT target;
    COORD size;
    SMALL_RECT view;
    struct mygames_kvm_text_cell cells[2000];
    struct mygames_kvm_text_frame frame;
    unsigned short i;
    (void)argv;if(argc==1)FreeConsole();
    else ShowWindow(GetConsoleWindow(),SW_SHOWNOACTIVATE);
    for(i=0;i<16;++i)pixels[i]=0x12ab34UL;
    if(mygames_win32_window_create(GetModuleHandle(NULL),"Invalid", "",procedure,0))return 20;
    mygames_win32_window_geometry_initialize(&geometry,0,8,2,16);
    if(mygames_win32_window_create(GetModuleHandle(NULL),"Invalid", "",procedure,&geometry))return 21;
    mygames_win32_window_geometry_initialize(&geometry,8,8,2,16);
    window=mygames_win32_window_create(GetModuleHandle(NULL),"NeutralHostFixture",
        "Neutral host",procedure,&geometry);
    if(!window)return 1;
    ShowWindow(window,SW_SHOW);UpdateWindow(window);seen_count=0;
    memset(&bitmap,0,sizeof(bitmap));bitmap.bmiHeader.biSize=sizeof(bitmap.bmiHeader);
    bitmap.bmiHeader.biWidth=8;bitmap.bmiHeader.biHeight=-8;
    bitmap.bmiHeader.biPlanes=1;bitmap.bmiHeader.biBitCount=32;
    dc=CreateCompatibleDC(NULL);surface=CreateDIBSection(dc,&bitmap,DIB_RGB_COLORS,(void **)&rendered,NULL,0);
    if(!dc || !surface)return 22;
    old_surface=SelectObject(dc,surface);SetRect(&target,0,0,8,8);
    if(!mygames_win32_pixels_present(dc,&target,pixels,4,4,16))return 23;
    GdiFlush();if((rendered[27]&0xffffffUL)!=0x12ab34UL)return 24;
    if(mygames_win32_pixels_present(dc,&target,pixels,0,4,16) ||
        mygames_win32_pixels_present(dc,&target,pixels,4,4,15))return 25;
    SelectObject(dc,old_surface);DeleteObject(surface);DeleteDC(dc);
    SendMessage(window,WM_LBUTTONDOWN,MK_LBUTTON,MAKELPARAM((WORD)-2,3));
    SendMessage(window,WM_MOUSEMOVE,MK_LBUTTON,MAKELPARAM((WORD)-9,(WORD)-7));
    SendMessage(window,WM_RBUTTONDOWN,MK_LBUTTON|MK_RBUTTON,MAKELPARAM(2,3));
    SendMessage(window,WM_LBUTTONUP,MK_RBUTTON,MAKELPARAM(2,3));
    if(seen_count!=4 || seen[0].x!=-2 || seen[1].y!=-7 ||
        seen[2].buttons!=3 || seen[3].buttons!=2 || GetCapture()!=window)return 2;
    SendMessage(window,WM_CAPTURECHANGED,0,0);
    if(seen_count!=5 || seen[4].kind!=MYGAMES_KVM_INPUT_CANCEL || GetCapture()==window)return 3;
    seen_count=0;SendMessage(window,WM_COMMAND,123,0);
    SendMessage(window,WM_KEYDOWN,VK_F2,0);SendMessage(window,WM_KEYDOWN,VK_F2,0x40000000L);
    SendMessage(window,WM_KEYUP,VK_F2,0);
    if(seen_count!=4 || seen[0].physical_code!=123 ||
        seen[1].physical_code!=MYGAMES_KVM_KEY_F2 || !seen[2].repeat || seen[3].down)return 4;
    seen_count=0;SendMessage(window,WM_KILLFOCUS,0,0);
    if(seen_count!=2 || seen[0].kind!=MYGAMES_KVM_INPUT_FOCUS || seen[0].down ||
        seen[1].kind!=MYGAMES_KVM_INPUT_CANCEL)return 5;
    if(mygames_win32_window_paint(window,0,4,4,16) ||
        mygames_win32_window_paint(window,pixels,4,4,15))return 6;
    if(!mygames_win32_text_console_open_profile(&console,window,25,"Neutral cells"))return 7;
    if(!GetConsoleMode(console.input,&mode) || !(mode&ENABLE_MOUSE_INPUT) ||
        (mode&ENABLE_QUICK_EDIT_MODE))return 8;
    memset(cells,0,sizeof(cells));for(i=0;i<2000;++i){cells[i].character='A';cells[i].foreground=15;}
    frame.cells=cells;frame.rows=25;frame.columns=frame.stride=80;frame.capacity=2000;
    frame.source_colors=0;frame.colors=0;
    if(mygames_win32_text_console_present(&console,&frame)!=MYGAMES_WIN32_CONSOLE_READY)return 9;
    console.vt_output=0;console.colors_valid=0;
    if(mygames_win32_text_console_present(&console,&frame)!=MYGAMES_WIN32_CONSOLE_READY)return 10;
    if(!GetConsoleScreenBufferInfo(console.output,&info))return 18;
    size.X=info.dwSize.X>100?info.dwSize.X:100;
    size.Y=info.dwSize.Y>50?info.dwSize.Y:50;view.Left=5;view.Top=3;view.Right=84;view.Bottom=27;
    if(console.window_usable) {
        if(!SetConsoleScreenBufferSize(console.output,size))return 111;
        if(!SetConsoleWindowInfo(console.output,TRUE,&view))return 112;
        if(!GetConsoleScreenBufferInfo(console.output,&info))return 113;
    } else if(argc>1)return 114; /* Classic route must actually be classic. */
    FlushConsoleInputBuffer(console.input);
    memset(&record,0,sizeof(record));record.EventType=MOUSE_EVENT;
    record.Event.MouseEvent.dwMousePosition.X=(short)(info.srWindow.Left-1);
    record.Event.MouseEvent.dwMousePosition.Y=(short)(info.srWindow.Top+2);
    record.Event.MouseEvent.dwButtonState=FROM_LEFT_1ST_BUTTON_PRESSED|RIGHTMOST_BUTTON_PRESSED;
    record.Event.MouseEvent.dwControlKeyState=SHIFT_PRESSED;
    if(!inject(&record) || !poll(MYGAMES_KVM_INPUT_MOUSE_BUTTON,&event) ||
        event.x!=-1 || event.y!=2 || event.buttons!=1 || event.modifiers!=MYGAMES_KVM_MOD_SHIFT)return 12;
    if(!poll(MYGAMES_KVM_INPUT_MOUSE_BUTTON,&event) || event.buttons!=3 ||
        event.physical_code!=MYGAMES_KVM_MOUSE_RIGHT)return 13;
    record.Event.MouseEvent.dwEventFlags=MOUSE_MOVED;
    record.Event.MouseEvent.dwMousePosition.X=(short)(info.srWindow.Left+15);
    if(!inject(&record) || !poll(MYGAMES_KVM_INPUT_MOUSE_MOVE,&event) || event.x!=15)return 14;
    memset(&record,0,sizeof(record));record.EventType=FOCUS_EVENT;
    if(!inject(&record) || !poll(MYGAMES_KVM_INPUT_FOCUS,&event) || event.down ||
        !poll(MYGAMES_KVM_INPUT_CANCEL,&event) || event.buttons || console.pointer.buttons)return 15;
    memset(&record,0,sizeof(record));record.EventType=KEY_EVENT;
    record.Event.KeyEvent.bKeyDown=TRUE;record.Event.KeyEvent.uChar.UnicodeChar=L'2';
    if(!inject(&record) || !poll(MYGAMES_KVM_INPUT_KEY,&event) ||
        event.physical_code!=MYGAMES_KVM_KEY_2 || !console.focused)return 16;
    if(!mygames_win32_text_console_suspend(&console) ||
        !poll(MYGAMES_KVM_INPUT_CANCEL,&event) || !mygames_win32_text_console_resume(&console))return 17;
    mygames_win32_text_console_close(&console);DestroyWindow(window);
    if(argc>1){FILE *receipt=fopen("neutral-classic.ok","w");if(!receipt)return 19;fputs("pass",receipt);fclose(receipt);}
    return 0;
}

