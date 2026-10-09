#include "platform/dos16/ram_compositor.h"

struct ram_compositor_sprites {
    mysmb_io_u8 MYSMB_IO_FAR *screen;
};

static int overlay_sprite(void *context,mysmb_io_u8 index,mysmb_io_u8 x,
    mysmb_io_u8 y,const mysmb_io_u8 MYSMB_IO_FAR *slots)
{
    struct ram_compositor_sprites *sprites=(struct ram_compositor_sprites *)context;
    mysmb_io_u16 px,py;
    (void)index;
    if(!sprites || !sprites->screen || !slots)return 0;
    for(py=0U;py<8U && (mysmb_io_u16)y+py<MYSMB_PPU_FRAME_HEIGHT;++py)
        for(px=0U;px<8U && (mysmb_io_u16)x+px<MYSMB_PPU_FRAME_WIDTH;++px)
            if(slots[py*8U+px]!=255U)
                sprites->screen[((mysmb_io_u16)y+py)*MYSMB_PPU_FRAME_WIDTH+
                    (mysmb_io_u16)x+px]=slots[py*8U+px];
    return 1;
}

int mysmb_dos16_ram_composite(const struct mysmb_ppu_frame_view *view,
    mysmb_io_u8 MYSMB_IO_FAR *screen,mysmb_io_u16 capacity)
{
    struct ram_compositor_sprites sprites;
    static mysmb_io_u8 MYSMB_IO_FAR sprite_slots[64];
    if(!view || !screen || capacity<MYSMB_IO_VIDEO_PIXELS)return 0;
    /* This obtains the PPU-selected background, including the fixed HUD
     * split, scroll, mask and current palette slots. */
    if(!mysmb_ppu_frame_background_rows(view,screen,capacity,0U,
        MYSMB_PPU_FRAME_HEIGHT))return 0;
    sprites.screen=screen;
    /* sprite_tiles supplies descending OAM order and marks transparent,
     * masked and behind-background pixels as 0xff. */
    return mysmb_ppu_frame_sprite_tiles(view,sprite_slots,sizeof(sprite_slots),
        overlay_sprite,&sprites);
}
