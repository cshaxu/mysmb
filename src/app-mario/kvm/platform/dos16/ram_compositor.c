#include "io/video.h"
#include "platform/dos16/ram_compositor.h"

struct ram_compositor_sprites {
    mygames_kvm_u8 MYGAMES_KVM_FAR *screen;
};

static int overlay_sprite(void *context,mygames_kvm_u8 index,mygames_kvm_u8 x,
    mygames_kvm_u8 y,const mygames_kvm_u8 MYGAMES_KVM_FAR *slots)
{
    struct ram_compositor_sprites *sprites=(struct ram_compositor_sprites *)context;
    mygames_kvm_u16 px,py;
    (void)index;
    if(!sprites || !sprites->screen || !slots)return 0;
    for(py=0U;py<8U && (mygames_kvm_u16)y+py<MYSMB_PPU_FRAME_HEIGHT;++py)
        for(px=0U;px<8U && (mygames_kvm_u16)x+px<MYSMB_PPU_FRAME_WIDTH;++px)
            if(slots[py*8U+px]!=255U)
                sprites->screen[((mygames_kvm_u16)y+py)*MYSMB_PPU_FRAME_WIDTH+
                    (mygames_kvm_u16)x+px]=slots[py*8U+px];
    return 1;
}

int mysmb_dos16_ram_composite(const struct mysmb_ppu_frame_view *view,
    mygames_kvm_u8 MYGAMES_KVM_FAR *screen,mygames_kvm_u16 capacity)
{
    struct ram_compositor_sprites sprites;
    static mygames_kvm_u8 MYGAMES_KVM_FAR sprite_slots[64];
    if(!view || !screen || capacity<MYSMB_VIDEO_PIXELS)return 0;
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
