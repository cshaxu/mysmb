#include "platform/win32/snapshot_replace.h"
#include <windows.h>
#include <stdio.h>
static HWND owned_window;
static HWND test_foreground(void){return owned_window;}
static SHORT test_key(int key){(void)key;return 0;}
/* Controlled host focus/key services exercise the production root without
 * activation, global input or access to the user's desktop. */
#define GetForegroundWindow test_foreground
#define GetAsyncKeyState test_key
#define MYSMB_WIN32_EMBEDDED_TEST 1
#define WinMain mysmb_unused_product_entry
#include "../src/platform/win32/main_win32.c"
#undef WinMain
static struct mysmb_io_snapshot expected,actual;
static unsigned char wire[MYSMB_SNAPSHOT_FILE_BYTES];
int main(int argc,char **argv)
{
    WNDCLASS wc;
    struct mysmb_input input;
    struct mysmb_snapshot_files files;
    FILE *file;
    char path[300];
    unsigned int i;
    LARGE_INTEGER clock_before;
    char title_before[80],title_after[80];
    if(argc!=2)return 1;
    memset(&wc,0,sizeof(wc));wc.lpfnWndProc=mysmb_win32_window_proc;
    wc.hInstance=GetModuleHandle(NULL);wc.lpszClassName="SnapshotBindingTest";
    if(!RegisterClass(&wc))return 2;
    owned_window=CreateWindow(wc.lpszClassName,"test",0,0,0,256,240,
        NULL,NULL,wc.hInstance,NULL);
    if(!owned_window)return 3;
    SendMessage(owned_window,WM_SETFOCUS,0,0);
    mysmb_io_control_initialize(&g_control);mysmb_win32_power_on();
    mysmb_win32_snapshot_initialize();
    /* Production directory discovery must locate this executable,even though
     * CTest's working directory may be elsewhere. Fault tests use an isolated
     * supplied build directory after this assertion. */
    if(!g_snapshot_ready || !strstr(g_snapshot_files.directory,"build"))return 4;
    if(!mysmb_file_storage_initialize(&g_snapshot_files,argv[1],
        mysmb_win32_snapshot_replace,&files) ||
        !mysmb_snapshot_store_initialize(&g_snapshot_store,&files))return 5;
    QueryPerformanceFrequency(&g_frequency);QueryPerformanceCounter(&g_last_tick);
    mysmb_win32_focus_pause_initialize(&g_focus_pause);
    mysmb_win32_focus_pause_gained(&g_focus_pause);
    mysmb_win32_window_proc(owned_window,WM_KEYDOWN,'P',0);
    mysmb_win32_snapshot_request(owned_window);
    memset(&expected,0xa5,sizeof(expected));g_snapshot_store.staging=expected;
    mysmb_win32_window_proc(owned_window,WM_KEYUP,'P',0);
    mysmb_win32_audio_renderer_initialize(&g_audio_output.renderer);
    input.buttons2=0U;
    for(i=0U;i<1200U;++i){
        if(!mysmb_game_startup_step(&g_game,1U))continue;
        input.buttons=i==100U?MYSMB_BUTTON_START:0U;
        mysmb_game_tick(&g_game,&input,&g_frame);
        if(mysmb_game_snapshot_running(&g_game,&g_frame))break;
    }
    if(!mysmb_game_snapshot_running(&g_game,&g_frame) ||
        memcmp(&g_snapshot_store.staging,&expected,sizeof(expected)))return 7;
    /* The single workspace captures the actual paused state only on P. */
    input.buttons=MYSMB_BUTTON_START;
    for(i=0U;i<80U && !mysmb_game_is_paused(&g_game);++i){
        input.buttons=i%2U?0U:MYSMB_BUTTON_START;
        mysmb_game_tick(&g_game,&input,&g_frame);
    }
    if(!mysmb_game_is_paused(&g_game))return 8;
    if(!mysmb_game_snapshot_capture(&g_game,&expected,g_snapshot_fingerprint) ||
        !mysmb_win32_audio_capture(&g_audio_output.renderer,expected.payload+MYSMB_SNAPSHOT_CORE_BYTES))return 6;
    mysmb_win32_window_proc(owned_window,WM_KEYDOWN,'P',0);
    mysmb_win32_snapshot_request(owned_window);
    sprintf(path,"%s/mysmb.sav",argv[1]);file=fopen(path,"rb");
    if(!file)return 9;
    i=(unsigned int)fread(wire,1,sizeof(wire),file);fclose(file);
    if(i!=sizeof(wire) || mysmb_snapshot_decode(wire,sizeof(wire),
        g_snapshot_fingerprint,&actual)!=MYSMB_SNAPSHOT_OK ||
        memcmp(&expected,&actual,sizeof(expected)))return 10;
    /* Load at title without Enter;pending audio flags and clock debt reset. */
    mysmb_win32_window_proc(owned_window,WM_KEYUP,'P',0);
    mysmb_win32_power_on();g_audio_output.next=7U;g_audio_output.queued[0]=1U;
    mysmb_win32_window_proc(owned_window,WM_KEYDOWN,'O',0);
    if(!mysmb_win32_snapshot_request(owned_window) || !mysmb_game_is_paused(&g_game) ||
        !g_game_started || g_audio_output.next || g_audio_output.queued[0])return 11;
    mysmb_game_snapshot_capture(&g_game,&actual,g_snapshot_fingerprint);
    mysmb_win32_audio_capture(&g_audio_output.renderer,actual.payload+MYSMB_SNAPSHOT_CORE_BYTES);
    if(memcmp(&expected,&actual,sizeof(actual)))return 12;
    mysmb_win32_window_proc(owned_window,WM_KEYDOWN,'O',0x40000000L);
    if(g_snapshot_requests)return 13;
    /* A read-only destination preserves prior file/live state/title.
     * Synchronous I/O rebases timing instead of accumulating catch-up debt. */
    if(!SetFileAttributesA(path,FILE_ATTRIBUTE_READONLY))return 15;
    clock_before=g_last_tick;GetWindowTextA(owned_window,title_before,sizeof(title_before));
    mysmb_win32_window_proc(owned_window,WM_KEYDOWN,'P',0);
    if(!mysmb_win32_snapshot_request(owned_window) || g_last_tick.QuadPart<clock_before.QuadPart)return 16;
    clock_before=g_last_tick;
    file=fopen(path,"rb");if(!file)return 17;
    i=(unsigned int)fread(wire,1,sizeof(wire),file);fclose(file);
    if(i!=sizeof(wire) || mysmb_snapshot_decode(wire,sizeof(wire),g_snapshot_fingerprint,&actual) ||
        memcmp(&expected,&actual,sizeof(actual)))return 18;
    if(!SetFileAttributesA(path,FILE_ATTRIBUTE_NORMAL))return 19;
    file=fopen(path,"r+b");if(!file)return 20;
    if(fseek(file,100L,SEEK_SET) || fputc(wire[100]^1U,file)==EOF || fclose(file))return 21;
    mysmb_win32_window_proc(owned_window,WM_KEYUP,'O',0);
    mysmb_win32_window_proc(owned_window,WM_KEYDOWN,'O',0);
    if(mysmb_win32_snapshot_request(owned_window))return 22;
    mysmb_game_snapshot_capture(&g_game,&actual,g_snapshot_fingerprint);
    mysmb_win32_audio_capture(&g_audio_output.renderer,actual.payload+MYSMB_SNAPSHOT_CORE_BYTES);
    GetWindowTextA(owned_window,title_after,sizeof(title_after));
    if(memcmp(&expected,&actual,sizeof(actual)) || strcmp(title_before,title_after) ||
        g_last_tick.QuadPart<clock_before.QuadPart)return 23;
    /* Failed loading may dirty scratch;the next paused P must recapture live. */
    mysmb_win32_window_proc(owned_window,WM_KEYUP,'P',0);
    mysmb_win32_window_proc(owned_window,WM_KEYDOWN,'P',0);
    if(!mysmb_win32_snapshot_request(owned_window))return 27;
    file=fopen(path,"rb");if(!file)return 28;
    i=(unsigned int)fread(wire,1,sizeof(wire),file);fclose(file);
    if(i!=sizeof(wire) || mysmb_snapshot_decode(wire,sizeof(wire),g_snapshot_fingerprint,&actual) ||
        memcmp(&expected,&actual,sizeof(actual)))return 29;
    remove(path);
    mysmb_win32_window_proc(owned_window,WM_KEYUP,'O',0);
    mysmb_win32_window_proc(owned_window,WM_KEYDOWN,'O',0);
    if(mysmb_win32_snapshot_request(owned_window))return 24;
    owned_window=NULL;g_focus_pause.focused=0U;
    mysmb_win32_window_proc(NULL,WM_KEYDOWN,'P',0);
    if(g_snapshot_requests)return 14;
    sprintf(path,"%s/mysmb.log",argv[1]);file=fopen(path,"r");if(!file)return 25;
    i=0U;while(fgets(title_after,sizeof(title_after),file))++i;fclose(file);
    if(i!=3U)return 26;
    remove(path);
    return 0;
}
