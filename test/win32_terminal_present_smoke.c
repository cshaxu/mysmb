#include <windows.h>
#include <wchar.h>
#include <stdlib.h>
#include "io/video.h"
#include "io/color.h"
static WCHAR encoded[MYSMB_IO_TEXT_CELLS*48U+1024U];
static WCHAR staging[MYSMB_IO_TEXT_CELLS*48U+1024U];
static unsigned int columns,rows,used,writes;
static int input_valid=1;
static BOOL WINAPI read_info(HANDLE output,PCONSOLE_SCREEN_BUFFER_INFO info)
{
    (void)output;ZeroMemory(info,sizeof(*info));
    info->srWindow.Right=(SHORT)(columns-1U);info->srWindow.Bottom=(SHORT)(rows-1U);
    return TRUE;
}
static BOOL WINAPI read_mode(HANDLE input,LPDWORD mode)
{
    (void)input;*mode=0U;return input_valid;
}
static BOOL WINAPI write_output(HANDLE output,const void *bytes,DWORD count,
    LPDWORD written,void *reserved)
{
    (void)output;(void)reserved;
    if(count>=sizeof(encoded)/sizeof(encoded[0]))return FALSE;
    CopyMemory(encoded,bytes,count*sizeof(WCHAR));encoded[count]=0;
    used=(unsigned int)count;*written=count;++writes;return TRUE;
}
#define GetConsoleScreenBufferInfo read_info
#define GetConsoleMode read_mode
#define WriteConsoleW write_output
#include "../src/platform/win32/text_console.c"
static struct mysmb_io_text_frame frame;
static struct mysmb_win32_text_console device;
/* Independently parse emitted cursor/RGB commands and verify every visible
 * source cell. Cropped cells must never occur in the terminal stream. */
static int check_stream(unsigned int width,unsigned int height)
{
    unsigned int at=0U,x=0U,y=0U,count=0U,cursors=0U,n,value[10],v;
    unsigned long foreground=0UL,background=0UL,fg,bg;
    WCHAR command;
    while(at<used) {
        if(encoded[at]==27) {
            if(++at>=used || encoded[at++]!='[')return 1;
            if(encoded[at]=='?') {
                while(at<used && encoded[at]!='l')++at;
                if(at==used)return 2;
                ++at;continue;
            }
            n=0U;
            do {
                if(n>=10U)return 3;
                v=0U;
                while(at<used && encoded[at]>='0' && encoded[at]<='9')
                    v=v*10U+(unsigned int)(encoded[at++]-'0');
                value[n++]=v;
                if(at>=used)return 4;
                command=encoded[at++];
            }while(command==';');
            if(command=='H') {
                if(n!=2U || value[1]!=1U || value[0]!=cursors+1U)return 5;
                y=value[0]-1U;x=0U;++cursors;
            }else if(command=='m') {
                if(n!=10U || value[0]!=38U || value[1]!=2U || value[5]!=48U || value[6]!=2U)return 6;
                foreground=(value[2]<<16U)|(value[3]<<8U)|value[4];
                background=(value[7]<<16U)|(value[8]<<8U)|value[9];
            }else return 7;
        }else {
            if(x>=width || y>=height)return 8;
            fg=mysmb_io_color_text_rgb(frame.cells[y*80U+x].foreground);
            bg=mysmb_io_color_text_rgb(frame.cells[y*80U+x].background);
            if(foreground!=fg || background!=bg || encoded[at]!=frame.cells[y*80U+x].character)return 9;
            ++at;++x;++count;
        }
    }
    return count==width*height && cursors==height?0:10;
}
int main(void)
{
    unsigned int i,cases;
    static const unsigned int sizes[3][2]={{40U,15U},{80U,50U},{120U,60U}};
    device.opened=device.terminal=1U;device.terminal_output=staging;
    for(i=0U;i<4000U;++i) {
        frame.cells[i].character=(unsigned char)('A'+i%26U);
        frame.cells[i].foreground=(unsigned char)(i%16U);
        frame.cells[i].background=(unsigned char)((i/16U)%16U);
    }
    for(cases=0U;cases<3U;++cases) {
        columns=sizes[cases][0];rows=sizes[cases][1];writes=0U;
        if(!mysmb_win32_text_console_present(&device,&frame) || writes!=1U)return 11;
        if(check_stream(columns>80U?80U:columns,rows>50U?50U:rows))return 12;
    }
    input_valid=0;writes=0U;
    if(mysmb_win32_text_console_present(&device,&frame) || writes)return 13;
    return 0;
}
