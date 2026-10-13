/* Optional Win32 SDL1.2 public-ABI test proxy;never linked into the product.
 * Forward all device calls to the installed runtime. Only SDL_PollEvent is
 * intercepted to supply a finite script and capture the dummy video surface.
 * No guest memory,game code or desktop input is changed. */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Public SDL1.2 Win32 keyboard ABI: byte fields and 32-bit enum values. */
struct probe_key {
    unsigned char type,which,state,pad;
    unsigned char scan,padding[3];
    int symbol,modifiers;
    unsigned short unicode;
};
union probe_event { struct probe_key key; unsigned char bytes[24]; };
_Static_assert(sizeof(struct probe_key)==20 && sizeof(union probe_event)==24,
    "Probe requires the SDL1.2 Win32 event ABI");
#ifdef _WIN64
#error DOSBox0.74-3 uses a 32-bit SDL library
#endif
typedef int (__cdecl *poll_fn)(void *);
typedef void *(__cdecl *surface_fn)(void);
typedef void *(__cdecl *rw_fn)(const char *,const char *);
typedef int (__cdecl *save_fn)(void *,void *,int);
static poll_fn original_poll;
static surface_fn video_surface;
static rw_fn open_file;
static save_fn save_bmp;
static FILE *script,*log_file;
static DWORD beginning;
static unsigned long due;
static int argument,value,pending;
static char action[16],name[64];
static unsigned short mouse_x,mouse_y;

static void next_action(void)
{
    char line[160];
    pending=0;
    if (script && fgets(line,sizeof(line),script)) {
        if (sscanf(line,"%lu %15s %63s %d",&due,action,name,&value)>=3) {
            argument=atoi(name);pending=1;
        }
    }
}

__declspec(dllexport) int __cdecl probe_poll(void *event)
{
    HMODULE real;
    union { FARPROC address; surface_fn surface; rw_fn rw; } entry;
    union probe_event generated;
    int result;
    if (!original_poll) {
        real=LoadLibraryA("SDL_real.dll");
        if (!real) return 0;
        original_poll=(poll_fn)GetProcAddress(real,"SDL_PollEvent");
        entry.address=GetProcAddress(real,"SDL_GetVideoSurface");video_surface=entry.surface;
        entry.address=GetProcAddress(real,"SDL_RWFromFile");open_file=entry.rw;
        save_bmp=(save_fn)GetProcAddress(real,"SDL_SaveBMP_RW");
        if (!original_poll || !video_surface || !open_file || !save_bmp) return 0;
        beginning=GetTickCount();script=fopen("input.script","r");
        log_file=fopen("probe.log","w");next_action();
    }
    result=original_poll(event);
    if (result || !event || !pending || (DWORD)(GetTickCount()-beginning)<due) return result;
    if (!strcmp(action,"capture")) {
        void *surface=video_surface();
        void *output=surface?open_file(name,"wb"):0;
        result=output?save_bmp(surface,output,1):-1;
        if (log_file) fprintf(log_file,"capture %s result=%d ms=%lu\n",name,result,
            (unsigned long)(GetTickCount()-beginning));
        result=0;
    } else {
        memset(&generated,0,sizeof(generated));
        if (!strcmp(action,"key")) {
            generated.key.type=value?2U:3U;generated.key.state=value?1U:0U;
            generated.key.symbol=argument;
            /* SDL Win32 supplies physical scans even for ASCII key events.
             * Preserve the host mapper's normal usescancodes setting. */
            if(argument>=0 && argument<128)
                generated.key.scan=(unsigned char)MapVirtualKeyA(
                    (UINT)(argument>='a' && argument<='z'?
                        argument-'a'+'A':argument),MAPVK_VK_TO_VSC);
            else if(argument>=282 && argument<=293)
                generated.key.scan=(unsigned char)MapVirtualKeyA(VK_F1+argument-282,MAPVK_VK_TO_VSC);
            else if(argument==308 || argument==306 || argument==304)
                generated.key.scan=(unsigned char)MapVirtualKeyA(argument==308?VK_MENU:
                    argument==306?VK_CONTROL:VK_SHIFT,MAPVK_VK_TO_VSC);
        } else if (!strcmp(action,"move")) {
            /* SDL1.2 motion: type,which,state,pad,x,y,xrel,yrel. */
            short relative_x=(short)(argument-mouse_x),relative_y=(short)(value-mouse_y);
            mouse_x=(unsigned short)argument;mouse_y=(unsigned short)value;
            generated.bytes[0]=4U;
            memcpy(generated.bytes+4,&mouse_x,2);memcpy(generated.bytes+6,&mouse_y,2);
            memcpy(generated.bytes+8,&relative_x,2);memcpy(generated.bytes+10,&relative_y,2);
        } else if (!strcmp(action,"button")) {
            /* SDL1.2 button: type,which,button,state,x,y. */
            generated.bytes[0]=(unsigned char)(value?5:6);
            generated.bytes[2]=(unsigned char)argument;generated.bytes[3]=(unsigned char)value;
            memcpy(generated.bytes+4,&mouse_x,2);memcpy(generated.bytes+6,&mouse_y,2);
        } else if (!strcmp(action,"quit")) generated.bytes[0]=12U;
        else { next_action();return 0; }
        memcpy(event,&generated,sizeof(generated));result=1;
        if (log_file) fprintf(log_file,"%s %d %d ms=%lu\n",action,argument,value,
            (unsigned long)(GetTickCount()-beginning));
    }
    if (log_file) fflush(log_file);
    next_action();return result;
}
