#include "platform/dos16/compact_vga_layout.h"
#include "platform/dos16/retained_background.h"
#include "ppu/frame.h"
#include <stdio.h>
#include <string.h>

/* RAM model of the compact DOS adapter.  It uses the same cache/page capacity
 * and PPU callbacks as the hardware presenter, then compares every visible
 * slot against the canonical PPU output. */
struct compact_sprite_context { mygames_kvm_u8 page,pan; };
static mygames_kvm_u8 cache[240][512],pages[2][240][264],chr[8192];
static mygames_kvm_u8 expected[61440],scratch[8192],sprite_slots[64];
static mygames_kvm_u8 current_page;

static int tile(void *context,mygames_kvm_u8 table,mygames_kvm_u8 row,
    mygames_kvm_u8 column,const mygames_kvm_u8 MYGAMES_KVM_FAR *slots)
{
    mygames_kvm_u16 x,y;
    (void)context;
    if(!slots)return 0;
    for(y=0U;y<8U;++y)for(x=0U;x<8U;++x)
        cache[row*8U+y][table*256U+column*8U+x]=slots[y*8U+x];
    return 1;
}

static int sprite(void *context,mygames_kvm_u8 index,mygames_kvm_u8 x,
    mygames_kvm_u8 y,const mygames_kvm_u8 MYSMB_PPU_FRAME_FAR *slots)
{
    struct compact_sprite_context *draw=(struct compact_sprite_context *)context;
    mygames_kvm_u16 px,py;
    (void)index;
    if(!draw || !slots)return 0;
    for(py=0U;py<8U && y+py<240U;++py)for(px=0U;px<8U && x+px<256U;++px)
        if(slots[py*8U+px]!=255U)
            pages[draw->page][y+py][draw->pan+x+px]=slots[py*8U+px];
    return 1;
}

static int frame(struct mysmb_ppu_state *state,struct mysmb_ppu_frame_workspace *work)
{
    struct mysmb_ppu_frame_view view;
    struct mysmb_ppu_scene_viewport scene;
    struct compact_sprite_context sprites;
    mygames_kvm_u16 x,y,source_x,source_y,aligned_x;
    mygames_kvm_u8 page,pan;
    mysmb_ppu_frame_begin(state,work,&view);
    if(!mysmb_dos16_retained_background_apply(&view,tile,0) ||
        !mysmb_ppu_frame_scene_viewport(&view,&scene))return 0;
    page=(mygames_kvm_u8)(current_page^1U);pan=(mygames_kvm_u8)(scene.output_origin_x&7U);
    aligned_x=(mygames_kvm_u16)scene.scene_page*256U+
        ((mygames_kvm_u16)scene.output_origin_x&0xfff8U);
    for(y=0U;y<240U;++y)for(x=0U;x<264U;++x) {
        source_x=(mygames_kvm_u16)(aligned_x+x);
        if(source_x>=512U)source_x-=512U;
        source_y=(mygames_kvm_u16)scene.output_origin_y+y;
        if(source_y>=240U)source_y-=240U;
        pages[page][y][x]=cache[source_y][source_x];
    }
    if(scene.fixed_top) {
        if(!mysmb_ppu_frame_background_rows(&view,scratch,sizeof(scratch),0U,32U))return 0;
        for(y=0U;y<32U;++y)for(x=0U;x<256U;++x)
            pages[page][y][pan+x]=scratch[y*256U+x];
    }
    sprites.page=page;sprites.pan=pan;
    if(!mysmb_ppu_frame_sprite_tiles(&view,sprite_slots,sizeof(sprite_slots),sprite,&sprites) ||
        !mysmb_ppu_frame_slot_rows(&view,expected,sizeof(expected),0U,240U))return 0;
    for(y=0U;y<240U;++y)for(x=0U;x<256U;++x)
        if(pages[page][y][pan+x]!=expected[y*256U+x])return 0;
    current_page=page;mysmb_ppu_frame_end(&view);return 1;
}

int main(void)
{
    struct mysmb_ppu_state state;
    struct mysmb_ppu_frame_workspace work;
    static mygames_kvm_u8 background[MYSMB_PPU_BACKGROUND_BYTES];
    static mygames_kvm_u8 second[MYSMB_PPU_BACKGROUND_SECOND_BYTES];
    mygames_kvm_u16 i;
    memset(&state,0,sizeof(state));
    for(i=0U;i<8192U;++i)chr[i]=(mygames_kvm_u8)(i*11U+i/7U);
    for(i=0U;i<2048U;++i)state.name_table[i/1024U][i&1023U]=(mygames_kvm_u8)(i*3U);
    state.chr_data=chr;state.chr_data_size=sizeof(chr);state.visible_ppu_mask=30U;
    state.visible_sprite0_split=1U;state.visible_ppu_name_table=1U;
    state.visible_scroll_x=19U;state.visible_scroll_y=23U;
    memset(state.visible_oam,0xefU,sizeof(state.visible_oam));
    state.visible_oam[0]=76U;state.visible_oam[1]=9U;state.visible_oam[3]=64U;
    state.visible_oam[4]=76U;state.visible_oam[5]=11U;state.visible_oam[6]=0x20U;state.visible_oam[7]=68U;
    mysmb_ppu_frame_workspace_bind(&work,0);
    mysmb_ppu_frame_background_byte_bind(&work,background,sizeof(background),second,sizeof(second));
    if(!frame(&state,&work))return 1;
    state.visible_scroll_x=43U;state.visible_scroll_y=37U;state.visible_oam[3]=90U;
    state.name_table[1][9U*32U+4U]^=1U;
    if(!frame(&state,&work))return 2;
    state.visible_sprite0_split=0U;state.visible_oam[0]=239U;state.visible_oam[4]=239U;
    state.visible_ppu_name_table=0U;state.visible_scroll_x=3U;state.visible_scroll_y=0U;
    if(!frame(&state,&work))return 3;
    state.visible_sprite0_split=1U;state.visible_ppu_name_table=1U;
    state.visible_scroll_x=252U;state.visible_scroll_y=239U;state.visible_oam[3]=250U;
    if(!frame(&state,&work))return 4;
    printf("compact overlay frames=4 exact=1 bytes=%u\n",MYSMB_DOS16_COMPACT_TOTAL_BYTES);
    return 0;
}
