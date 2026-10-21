#include <windows.h>
#include <stdio.h>
static unsigned ticks,phase,colors;
static HWND game;
static FILE *logfile;
static void record(const char *s,unsigned n) {fprintf(logfile,"%s %u\n",s,n);fflush(logfile);}
static unsigned diversity(HWND window) {
 HDC dc;RECT rect;unsigned x,y,n=0,i;DWORD seen[32],c;
 GetClientRect(window,&rect);dc=GetDC(window);
 for(y=8;y<(unsigned)rect.bottom;y+=16)for(x=8;x<(unsigned)rect.right;x+=16) {
  c=GetPixel(dc,x,y);for(i=0;i<n;i++)if(seen[i]==c)break;
  if(i==n && n<32)seen[n++]=c;
 }
 ReleaseDC(window,dc);return n;
}
long FAR PASCAL CheckProc(HWND window,UINT message,WPARAM w,LPARAM l) {
 if(message==WM_TIMER) {
  ++ticks;
  if(!phase) {
   game=FindWindow("MygamesWin16","MySMB");
   if(game){SetActiveWindow(game);SetFocus(game);UpdateWindow(game);phase=1;ticks=0;record("window",1);record("focus",GetFocus()==game);}
  } else if(phase==1 && ticks>=16) {
   colors=diversity(game);record("graphics_colors",colors);
   PostMessage(game,WM_KEYDOWN,VK_TAB,1L);PostMessage(game,WM_KEYUP,VK_TAB,0xc0000001L);
   phase=2;ticks=0;
  } else if(phase==2 && ticks>=8) {
   record("text_colors",diversity(game));
   PostMessage(game,WM_KEYDOWN,VK_TAB,1L);PostMessage(game,WM_KEYUP,VK_TAB,0xc0000001L);
   phase=3;ticks=0;
  } else if(phase==3 && ticks>=8) {
   record("graphics_return_colors",diversity(game));
   PostMessage(game,WM_KEYDOWN,VK_ESCAPE,1L);phase=4;ticks=0;
  } else if(phase==4 && !IsWindow(game)) {
   record("exit",1);fclose(logfile);KillTimer(window,1);ExitWindows(0L,0);
  }
  if(ticks>50){record("timeout",phase);fclose(logfile);ExitWindows(0L,0);}
  return 0;
 }
 return DefWindowProc(window,message,w,l);
}
int PASCAL WinMain(HINSTANCE instance,HINSTANCE previous,LPSTR command,int show) {
 WNDCLASS wc;HWND window;MSG msg;
 logfile=fopen("C:\\CHECK.LOG","wt");if(!logfile)return 1;
 wc.style=0;wc.lpfnWndProc=CheckProc;wc.cbClsExtra=0;wc.cbWndExtra=0;
 wc.hInstance=instance;wc.hIcon=0;wc.hCursor=0;wc.hbrBackground=0;wc.lpszMenuName=0;wc.lpszClassName="I86Check";
 if(!RegisterClass(&wc))return 2;
 window=CreateWindow("I86Check","Probe",WS_OVERLAPPED,0,0,10,10,0,0,instance,0);
 record("WinExec",WinExec("C:\\MYSMB86W.EXE",SW_SHOW));
 SetTimer(window,1,1000,0);
 while(GetMessage(&msg,0,0,0)){TranslateMessage(&msg);DispatchMessage(&msg);}return 0;
}
