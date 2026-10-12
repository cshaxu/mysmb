#include "platform/win32/text_console_presentation.h"
#include "io/color.h"
#include "io/text_glyph.h"
#include <string.h>

static void mysmb_win32_console_palette(struct mysmb_win32_text_console *console,
    const unsigned long *colors,unsigned char source_colors)
{
    console->colors_valid=1U;
    CopyMemory(console->colors,colors,sizeof(console->colors));
    mysmb_io_color_text_attributes(colors,source_colors,console->fallback_colors);
}

static void mysmb_win32_console_canonical_palette(unsigned long *colors)
{
    unsigned short i;
    for(i=0U;i<16U;++i)
        colors[i]=mysmb_io_color_text_rgb((mysmb_io_u8)i);
}

void mysmb_win32_console_initialize_indexed(struct mysmb_win32_text_console *console)
{
    unsigned long colors[16];
    mysmb_win32_console_canonical_palette(colors);
    mysmb_win32_console_palette(console,colors,0U);
}

static int mysmb_win32_console_write_failure(struct mysmb_win32_text_console *console)
{
    DWORD error=GetLastError();
    if(error==ERROR_INVALID_HANDLE || error==ERROR_ACCESS_DENIED)
        return MYSMB_WIN32_CONSOLE_LOST;
    if(error==ERROR_INVALID_PARAMETER || error==ERROR_NOT_READY)
        return MYSMB_WIN32_CONSOLE_DEFER;
    if(++console->output_failures>=120U)return MYSMB_WIN32_CONSOLE_LOST;
    return MYSMB_WIN32_CONSOLE_DEFER;
}

static int mysmb_win32_terminal_present(struct mysmb_win32_text_console *console,
    const struct mysmb_io_text_frame *frame)
{
    CONSOLE_SCREEN_BUFFER_INFO info;
    WCHAR *out=console->terminal_output,sequence[96];
    DWORD written;
    unsigned int width,height,x,y,count=0U,length;
    int foreground=-1,background=-1;
    unsigned long fg,bg;
    WCHAR glyph;
    const struct mysmb_io_text_cell *cell;
    if(!out || !GetConsoleScreenBufferInfo(console->output,&info))return MYSMB_WIN32_CONSOLE_DEFER;
    width=(unsigned int)(info.srWindow.Right-info.srWindow.Left+1);
    height=(unsigned int)(info.srWindow.Bottom-info.srWindow.Top+1);
    if(width>80U)width=80U;
    if(height>MYSMB_IO_TEXT_FRAME_ROWS(frame))height=MYSMB_IO_TEXT_FRAME_ROWS(frame);
    if(!width || !height)return MYSMB_WIN32_CONSOLE_DEFER;
    lstrcpyW(out,L"\x1b[0m\x1b[?25l");count=10U;
    for(y=0U;y<height;++y) {
        length=(unsigned int)wsprintfW(sequence,L"\x1b[%u;1H",y+1U);
        CopyMemory(out+count,sequence,length*sizeof(WCHAR));count+=length;
        for(x=0U;x<width;++x) {
            cell=&frame->cells[y*80U+x];
            if(foreground!=(int)(cell->foreground&15U) ||
                background!=(int)(cell->background&15U)) {
                foreground=cell->foreground&15U;background=cell->background&15U;
                fg=frame->source_colors==1U?frame->colors[foreground]:mysmb_io_color_text_rgb((mysmb_io_u8)foreground);
                bg=frame->source_colors==1U?frame->colors[background]:mysmb_io_color_text_rgb((mysmb_io_u8)background);
                length=(unsigned int)wsprintfW(sequence,
                    L"\x1b[38;2;%u;%u;%u;48;2;%u;%u;%um",
                    (unsigned int)((fg>>16U)&255U),(unsigned int)((fg>>8U)&255U),
                    (unsigned int)(fg&255U),(unsigned int)((bg>>16U)&255U),
                    (unsigned int)((bg>>8U)&255U),(unsigned int)(bg&255U));
                CopyMemory(out+count,sequence,length*sizeof(WCHAR));count+=length;
            }
            glyph=(WCHAR)mysmb_io_text_glyph_unicode(cell->character);
            if(!glyph)return MYSMB_WIN32_CONSOLE_LOST;
            out[count++]=glyph;
        }
    }
    if(!WriteConsoleW(console->output,out,count,&written,NULL))
        return mysmb_win32_console_write_failure(console);
    console->output_failures=0U;
    return written==count?MYSMB_WIN32_CONSOLE_READY:MYSMB_WIN32_CONSOLE_DEFER;
}

int mysmb_win32_console_present_frame(struct mysmb_win32_text_console *console,
    const struct mysmb_io_text_frame *frame)
{
    unsigned short i;
    unsigned long canonical_colors[16];
    COORD size,origin;
    SMALL_RECT view;
    if(console->vt_output)return mysmb_win32_terminal_present(console,frame);
    if(frame->source_colors==1U && (!console->colors_valid ||
        memcmp(console->colors,frame->colors,sizeof(console->colors))!=0)) {
        mysmb_win32_console_palette(console,frame->colors,1U);
    } else if(frame->source_colors!=1U) {
        mysmb_win32_console_canonical_palette(canonical_colors);
        if(!console->colors_valid ||
            memcmp(console->colors,canonical_colors,sizeof(canonical_colors))!=0)
            mysmb_win32_console_palette(console,canonical_colors,0U);
    }
    for(i=0U;i<MYSMB_IO_TEXT_FRAME_CELLS(frame);++i) {
        console->cells[i].Char.UnicodeChar=(WCHAR)mysmb_io_text_glyph_unicode(frame->cells[i].character);
        if(console->cells[i].Char.UnicodeChar==0U)return MYSMB_WIN32_CONSOLE_LOST;
        console->cells[i].Attributes=(WORD)(console->fallback_colors[
            frame->cells[i].foreground&15U]|(console->fallback_colors[
            frame->cells[i].background&15U]<<4U));
    }
    size.X=80;size.Y=(SHORT)console->rows;origin.X=origin.Y=0;
    view.Left=view.Top=0;view.Right=79;view.Bottom=(SHORT)(console->rows-1U);
    if(!WriteConsoleOutputW(console->output,console->cells,size,origin,&view))
        return mysmb_win32_console_write_failure(console);
    console->output_failures=0U;
    if(view.Left==0 && view.Top==0 && view.Right==79 && view.Bottom==(SHORT)(console->rows-1U))
        return MYSMB_WIN32_CONSOLE_READY;
    return MYSMB_WIN32_CONSOLE_DEFER;
}
