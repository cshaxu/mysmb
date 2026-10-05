"""Profile native presentation on a private desktop;all generated files stay in build.

Pass --legacy-wait and --source for a retained original root to compare with the
current deadline wait. This measures host CPU/API cadence,not physical scanout.
"""
import argparse,ctypes as c,hashlib,importlib.util,json,platform,shlex,subprocess,sys
from pathlib import Path
sys.dont_write_bytecode=True

HARNESS = r'''
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "platform/win32/frame_wait.h"
static HWND owned_focus;
static unsigned int probe_ticks,frames,counts[8];
static LARGE_INTEGER frequency,last_present;
static double samples[8][2000],intervals[2000];
static HWND probe_foreground(void){return owned_focus;}
static void probe_end(unsigned int stage,LARGE_INTEGER begin)
{
    LARGE_INTEGER end;
    QueryPerformanceCounter(&end);
    if(counts[stage]<2000U)samples[stage][counts[stage]++]=
        (double)(end.QuadPart-begin.QuadPart)*1000.0/frequency.QuadPart;
}
static void probe_presented(void)
{
    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);
    if(frames<2000U && frames)intervals[frames-1U]=
        (double)(now.QuadPart-last_present.QuadPart)*1000.0/frequency.QuadPart;
    last_present=now;++frames;
}
#define GetForegroundWindow probe_foreground
#define WinMain mysmb_unused_product_entry
#include "root_probe.c"
#undef WinMain
static int compare(const void *a,const void *b)
{double x=*(const double*)a,y=*(const double*)b;return x>y?1:x<y?-1:0;}
static void report(FILE *file,const char *name,double *values,unsigned int n)
{
    unsigned int i,long_frames=0;
    if(!n)return;
    for(i=0;i<n;++i)if(values[i]>25.0)++long_frames;
    qsort(values,n,sizeof(double),compare);
    fprintf(file,"%s n=%u median=%.4f p95=%.4f p99=%.4f max=%.4f over25ms=%u\n",
        name,n,values[n/2],values[(n-1)*95/100],values[(n-1)*99/100],values[n-1],long_frames);
}
int main(int argc,char **argv)
{
    static const char *names[]={"game","compositor","text-build-present","rgb-conversion","paint","audio","messages","wait"};
    WNDCLASS wc;
    HWND window;
    HDESK desktop;
    MSG message;
    LARGE_INTEGER begin,start,now;
    unsigned int i;
    unsigned int painted=0U;
    FILE *file;
    struct mysmb_win32_frame_wait pacing;
    char name[80];
    if(argc!=4)return 1;
    FreeConsole();
    sprintf(name,"mysmb-pacing-%lu",GetCurrentProcessId());
    desktop=GetThreadDesktop(GetCurrentThreadId());
    if(!desktop || !SetThreadDesktop(desktop))return 2;
    QueryPerformanceFrequency(&frequency);g_frequency=frequency;
    ZeroMemory(&wc,sizeof(wc));wc.lpfnWndProc=mysmb_win32_window_proc;
    wc.hInstance=GetModuleHandle(NULL);wc.lpszClassName=name;
    if(!RegisterClass(&wc))return 3;
    window=CreateWindow(name,"owned pacing probe",WS_OVERLAPPEDWINDOW,
        0,0,528,519,NULL,NULL,wc.hInstance,NULL);
    if(!window)return 4;
    owned_focus=window;
    ZeroMemory(&g_bitmap_info,sizeof(g_bitmap_info));
    g_bitmap_info.bmiHeader.biSize=sizeof(g_bitmap_info.bmiHeader);
    g_bitmap_info.bmiHeader.biWidth=256;g_bitmap_info.bmiHeader.biHeight=-240;
    g_bitmap_info.bmiHeader.biPlanes=1;g_bitmap_info.bmiHeader.biBitCount=32;
    mysmb_io_control_initialize(&g_control);mysmb_win32_power_on();
    mysmb_win32_focus_pause_initialize(&g_focus_pause);
    mysmb_win32_focus_pause_gained(&g_focus_pause);
    ShowWindow(window,SW_SHOW);UpdateWindow(window);
    if(atoi(argv[1])) {
        mysmb_win32_switch_presenter(window,0);
        if(!g_text_mode)return 5;
        owned_focus=g_console.window;
        ShowWindow(g_console.window,SW_SHOW);
    }
    if(atoi(argv[2])) {
        if(!mysmb_win32_audio_open(&g_audio_output))return 6;
    }
    g_title_paused=2;frames=probe_ticks=0;
#ifdef PROBE_FIXED
    mysmb_win32_frame_wait_open(&pacing);
#endif
    ZeroMemory(counts,sizeof(counts));
    QueryPerformanceCounter(&g_last_tick);start=g_last_tick;
    do {
        QueryPerformanceCounter(&begin);
        while(PeekMessage(&message,NULL,0,0,PM_REMOVE)) {
            TranslateMessage(&message);DispatchMessage(&message);
        }
        probe_end(6,begin);
        mysmb_win32_keyboard_event(&g_keyboard,VK_RETURN,0,(unsigned char)(probe_ticks==100));
        mysmb_win32_step(window);
        if(!g_text_mode && painted!=frames) {
            mysmb_win32_paint(window);painted=frames;
        }
        QueryPerformanceCounter(&begin);
#ifdef PROBE_FIXED
        mysmb_win32_frame_wait_until(&pacing,g_last_tick.QuadPart+frequency.QuadPart/60,
            frequency.QuadPart);
#else
        Sleep(1);
#endif
        probe_end(7,begin);
        QueryPerformanceCounter(&now);
    }while(now.QuadPart-start.QuadPart<frequency.QuadPart*8);
    file=fopen(argv[3],"w");if(!file)return 7;
    fprintf(file,"mode=%s audio=%d ticks=%u frames=%u elapsed=%.4f\n",
        atoi(argv[1])?"text":"graphics",atoi(argv[2]),probe_ticks,frames,
        (double)(now.QuadPart-start.QuadPart)/frequency.QuadPart);
    report(file,"interval",intervals,frames>1?frames-1:0);
    for(i=0;i<8;++i)report(file,names[i],samples[i],counts[i]);
    fclose(file);
#ifdef PROBE_FIXED
    mysmb_win32_frame_wait_close(&pacing);
#endif
    DestroyWindow(window);return 0;
}

'''

def instrument(source):
    s=source
    s=s.replace('static void mysmb_win32_build_frame(void)\n{','static void mysmb_win32_build_frame(void)\n{\n    LARGE_INTEGER probe_begin;\n    QueryPerformanceCounter(&probe_begin);')
    s=s.replace('        return;\n    }\n    mysmb_ppu_frame_build', '        probe_end(2,probe_begin);\n        probe_presented();\n        return;\n    }\n    mysmb_ppu_frame_build')
    s=s.replace('    mysmb_win32_draw_gameplay(&video);','    probe_end(1,probe_begin);\n    QueryPerformanceCounter(&probe_begin);\n    mysmb_win32_draw_gameplay(&video);\n    probe_end(3,probe_begin);\n    probe_presented();')
    s=s.replace('    PAINTSTRUCT paint;', '    LARGE_INTEGER probe_begin;\n    PAINTSTRUCT paint;')
    s=s.replace('    dc = BeginPaint', '    QueryPerformanceCounter(&probe_begin);\n    dc = BeginPaint')
    s=s.replace('    EndPaint(window, &paint);', '    EndPaint(window, &paint);\n    probe_end(4,probe_begin);')
    s=s.replace('    unsigned int steps;', '    LARGE_INTEGER probe_begin;\n    unsigned int steps;')
    s=s.replace('        mysmb_game_tick(&g_game, &input, &g_frame);','        QueryPerformanceCounter(&probe_begin);\n        mysmb_game_tick(&g_game, &input, &g_frame);\n        probe_end(0,probe_begin);\n        ++probe_ticks;')
    s=s.replace('        mysmb_win32_audio_submit(&g_audio_output, &g_audio_frame);','        QueryPerformanceCounter(&probe_begin);\n        mysmb_win32_audio_submit(&g_audio_output, &g_audio_frame);\n        probe_end(5,probe_begin);')
    return s

def main():
    root=Path(__file__).resolve().parents[1]
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--build-directory',type=Path,required=True)
    parser.add_argument('--output',type=Path,required=True)
    parser.add_argument('--source',type=Path,default=root/'src/platform/win32/main_win32.c')
    parser.add_argument('--legacy-wait',action='store_true')
    parser.add_argument('--audio',choices=['0','1'],default='0')
    args=parser.parse_args()
    output=args.output.resolve();tree=args.build_directory.resolve()
    if not output.is_relative_to(root/'build'):
        raise ValueError('Profiles must remain beneath the repository build directory')
    output.mkdir(parents=True,exist_ok=True)
    original=args.source.read_text();(output/'root_probe.c').write_text(instrument(original))
    (output/'probe.c').write_text(HARNESS)
    cache=(tree/'CMakeCache.txt').read_text().splitlines()
    compiler=next(line.split('=',1)[1] for line in cache
                  if line.startswith(('CMAKE_C_COMPILER:FILEPATH=','CMAKE_C_COMPILER:STRING=')))
    rsp=tree/'CMakeFiles/mysmb_win32_text_switch_smoke.dir'
    objects=[x for x in shlex.split((rsp/'objects1.rsp').read_text())
             if not x.endswith(('test/win32_text_switch_smoke.c.obj',
                                'src/platform/win32/frame_wait.c.obj'))]
    executable=output/'presentation-profile.exe'
    command=[compiler,'-std=c90','-DMYSMB_LOCAL_TITLE=1']
    if not args.legacy_wait:command+=['-DPROBE_FIXED=1']
    command+=shlex.split((rsp/'includes_C.rsp').read_text())
    command+=[str(output/'probe.c'),str(root/'src/platform/win32/frame_wait.c')]+objects
    command+=shlex.split((rsp/'linkLibs.rsp').read_text())+['-o',str(executable)]
    subprocess.run(command,cwd=tree,check=True)
    spec=importlib.util.spec_from_file_location('owned_host',root/'tools/Verify-Win32StartupConsole.py')
    host=importlib.util.module_from_spec(spec);spec.loader.exec_module(host)
    name='mysmb-profile-%d'%host.k.GetCurrentProcessId()
    desktop=host.u.CreateDesktopW(name,None,None,0,0x10000000,None)
    host.require(desktop,'Create private desktop')
    records=[]
    try:
        for mode in (0,1):
            receipt=output/('text.txt' if mode else 'graphics.txt')
            handle=host.start('"%s" %d %s "%s"'%(executable,mode,args.audio,receipt),
                              name,output)
            try:
                if host.k.WaitForSingleObject(handle,20000)!=0:
                    host.k.TerminateProcess(handle,90)
                    raise RuntimeError('Native probe exceeded20second budget')
                code=host.w.DWORD();host.k.GetExitCodeProcess(handle,c.byref(code))
                host.require(code.value==0,'Probe exit%d'%code.value)
                text=receipt.read_text()
                if len(text)>20000:raise ValueError('Profile exceeded receipt budget')
                print(text,flush=True);records.append(text)
            finally:host.k.CloseHandle(handle)
    finally:host.u.CloseDesktop(desktop)
    (output/'binding.json').write_text(json.dumps({
        'sourceSha256':hashlib.sha256(original.encode()).hexdigest(),
        'probeSha256':hashlib.sha256(executable.read_bytes()).hexdigest(),
        'host':platform.platform(),'compiler':compiler,'audio':args.audio,
        'legacyWait':args.legacy_wait,'records':records},indent=2))

if __name__=='__main__':main()
