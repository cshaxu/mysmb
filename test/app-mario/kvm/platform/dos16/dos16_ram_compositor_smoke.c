#include "io/video.h"
#include "platform/dos16/ram_compositor.h"
#include <stdio.h>
#include <string.h>

static mygames_kvm_u8 background[MYSMB_PPU_BACKGROUND_BYTES];
static mygames_kvm_u8 second[MYSMB_PPU_BACKGROUND_SECOND_BYTES];
static mygames_kvm_u8 chr[8192];
static mygames_kvm_u8 expected[MYSMB_VIDEO_PIXELS],actual[MYSMB_VIDEO_PIXELS];

static int frame(struct mysmb_ppu_state *state,struct mysmb_ppu_frame_workspace *work)
{
    struct mysmb_ppu_frame_view view;
    mysmb_ppu_frame_begin(state,work,&view);
    if(!mysmb_dos16_ram_composite(&view,actual,sizeof(actual)) ||
        !mysmb_ppu_frame_slot_rows(&view,expected,sizeof(expected),0U,240U)) {
        mysmb_ppu_frame_end(&view);return 0;
    }
    mysmb_ppu_frame_end(&view);
    return memcmp(actual,expected,sizeof(actual))==0;
}

int main(void)
{
    struct mysmb_ppu_state state;
    struct mysmb_ppu_frame_workspace work;
    mygames_kvm_u16 i;
    memset(&state,0,sizeof(state));
    for(i=0U;i<8192U;++i)chr[i]=(mygames_kvm_u8)(i*13U+i/3U);
    for(i=0U;i<2048U;++i)state.name_table[i/1024U][i&1023U]=(mygames_kvm_u8)(i*7U);
    state.chr_data=chr;state.chr_data_size=sizeof(chr);state.visible_ppu_mask=30U;
    state.visible_ppu_name_table=1U;state.visible_scroll_x=19U;
    state.visible_scroll_y=23U;state.visible_sprite0_split=1U;
    memset(state.visible_oam,0xefU,sizeof(state.visible_oam));
    state.visible_oam[0]=80U;state.visible_oam[1]=9U;state.visible_oam[3]=70U;
    state.visible_oam[4]=80U;state.visible_oam[5]=11U;state.visible_oam[6]=0x20U;
    state.visible_oam[7]=72U;state.visible_oam[8]=5U;state.visible_oam[9]=13U;
    state.visible_oam[10]=1U;state.visible_oam[11]=5U;
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
    printf("ram compositor frames=4 exact=1 bytes=%u\n",MYSMB_VIDEO_PIXELS);
    return 0;
}
