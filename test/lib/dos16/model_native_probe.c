#include <dos.h>
#include <stdio.h>
#include "dos16/text_cells.h"
#include "kvm/color.h"
int main(void)
{
 unsigned short segment,i;unsigned long far *colors;struct mygames_kvm_text_cell far *cells;
 unsigned short far *target;struct mygames_kvm_text_frame frame;FILE *f;
 if(_dos_allocmem(64,&segment))return 1;
 colors=(unsigned long far *)((unsigned long)segment<<16);cells=(struct mygames_kvm_text_cell far *)(colors+16);target=(unsigned short far *)(cells+16);
 for(i=0;i<16;++i){colors[i]=mygames_kvm_color_text_rgb((unsigned char)i);cells[i].character=(unsigned char)(i+32);cells[i].foreground=(unsigned char)i;cells[i].background=(unsigned char)(15-i);}
 frame.cells=cells;frame.columns=16;frame.rows=1;frame.stride=16;frame.capacity=16;frame.colors=colors;frame.source_colors=1;
 mygames_dos16_text_cells(&frame,target);
 for(i=0;i<16;++i)if(target[i]!=(unsigned short)((15-i)*4096U+i*256U+i+32U))return 2;
 _dos_freemem(segment);f=fopen("model.ok","w");if(!f)return 3;fprintf(f,"nearPointer=%u farPointer=%u cells=16 paletteOutsideDgroup=1\n",sizeof(void *),sizeof(void far *));fclose(f);return 0;
}
