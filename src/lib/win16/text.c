#include "win16/text.h"
#include "kvm/color.h"
static DWORD color(unsigned long rgb)
{return ((rgb&255UL)<<16)|(rgb&0xff00UL)|((rgb>>16)&255UL);}
int mygames_win16_text_paint(HDC dc,const RECT *rect,
    const struct mygames_kvm_text_frame FAR *frame)
{
    unsigned short x,y,i;
    unsigned long rgb;
    DWORD colors[16];
    int reduced;
    int width,height,cw,ch,result=1;
    HFONT font,previous;
    RECT cell;
    const struct mygames_kvm_text_cell FAR *source;
    char character;
    if(!dc || !rect || !mygames_kvm_text_valid(frame))return 0;
    width=rect->right-rect->left;height=rect->bottom-rect->top;
    if(width<=0 || height<=0)return 0;
    /* Match the indexed DIB path on standard VGA. GDI's direct RGB
     * approximation can turn a light blue sky white and hide white captions.
     * Quantize once per slot, never once per character. */
    reduced=GetDeviceCaps(dc,BITSPIXEL)*GetDeviceCaps(dc,PLANES)<=4;
    for(i=0U;i<16U;++i) {
        rgb=frame->source_colors?frame->colors[i]:
            mygames_kvm_color_text_rgb((unsigned char)i);
        if(reduced && frame->source_colors)
            rgb=mygames_kvm_color_text_rgb(mygames_kvm_color_text_nearest(rgb));
        colors[i]=color(rgb);
    }
    cw=width/frame->columns;ch=height/frame->rows;
    if(cw<1)cw=1;if(ch<1)ch=1;
    font=CreateFont(ch,cw,0,0,400,0,0,0,OEM_CHARSET,0,0,0,FIXED_PITCH,0);
    if(!font)return 0;
    previous=(HFONT)SelectObject(dc,font);
    for(y=0;y<frame->rows;++y)for(x=0;x<frame->columns;++x) {
        source=frame->cells+y*frame->stride+x;
        cell.left=rect->left+(int)((long)x*width/frame->columns);
        cell.right=rect->left+(int)((long)(x+1U)*width/frame->columns);
        cell.top=rect->top+(int)((long)y*height/frame->rows);
        cell.bottom=rect->top+(int)((long)(y+1U)*height/frame->rows);
        SetTextColor(dc,colors[source->foreground&15U]);
        SetBkColor(dc,colors[source->background&15U]);
        character=(char)source->character;
        if(!ExtTextOut(dc,cell.left,cell.top,ETO_OPAQUE|ETO_CLIPPED,&cell,&character,1,0))result=0;
    }
    SelectObject(dc,previous);DeleteObject(font);return result;
}
