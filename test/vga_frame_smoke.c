#include "game/ppu_frame.h"
#include "platform/vga/vga_frame.h"
static mysmb_u8 p0[MYSMB_VGA_PAGE_SIZE],p1[MYSMB_VGA_PAGE_SIZE],p2[MYSMB_VGA_PAGE_SIZE],p3[MYSMB_VGA_PAGE_SIZE];
int main(void) { struct mysmb_ppu_frame ppu; struct mysmb_vga_frame vga; mysmb_u16 i; for(i=0U;i<MYSMB_SCREEN_WIDTH*MYSMB_SCREEN_HEIGHT;++i) ppu.pixels[i]=0x21U; ppu.pixels[0U]=0x16U; mysmb_vga_frame_initialize(&vga,p0,p1,p2,p3); mysmb_vga_frame_build(&ppu,&vga); if(vga.pages[0][0U]!=4U || vga.pages[0][2U]!=1U) return 1; return 0; }