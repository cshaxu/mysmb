#include "ppu/frame.h"
#include <stdio.h>
#include <string.h>

static mysmb_io_u8 background[MYSMB_PPU_BACKGROUND_BYTES];
static mysmb_io_u8 second[MYSMB_PPU_BACKGROUND_SECOND_BYTES];
static mysmb_io_u8 chr[8192];
static mysmb_io_u8 tiles[2][30][32][64];
static mysmb_io_u8 overlay_slots[64];
static mysmb_io_u8 expected[61440],actual[61440];
static unsigned short calls,last_sprite;
static int apply(void *context,mysmb_io_u8 sprite,mysmb_io_u8 x,mysmb_io_u8 y,
    const mysmb_io_u8 MYSMB_IO_FAR *slots)
{
    mysmb_io_u16 px,py;
    (void)context;
    if(calls && sprite>=last_sprite)return 0;
    last_sprite=sprite;++calls;
    for(py=0U;py<8U && y+py<240U;++py)for(px=0U;px<8U && x+px<256U;++px)
        if(slots[py*8U+px]!=255U)actual[(y+py)*256U+x+px]=slots[py*8U+px];
    return 1;
}
static mysmb_io_u8 background_slot(const struct mysmb_ppu_state *s,mysmb_io_u16 x,mysmb_io_u16 y)
{
    mysmb_io_u16 sx,sy;
    mysmb_io_u8 table;
    if(s->visible_sprite0_split && y<32U){sx=x;sy=y;table=0U;}
    else {sx=(mysmb_io_u16)(x+s->visible_scroll_x);sy=(mysmb_io_u16)(y+s->visible_scroll_y);table=s->visible_ppu_name_table;}
    if(sx>=256U)table^=1U;if(sy>=240U)sy-=240U;if(sy>=240U)sy-=240U;
    return tiles[table&1U][sy>>3U][(sx&255U)>>3U][(sy&7U)*8U+(sx&7U)];
}
int main(void)
{
    struct mysmb_ppu_state s;
    struct mysmb_ppu_frame_workspace w;
    struct mysmb_ppu_frame_view v;
    mysmb_io_u16 i,t,r,c,x,y;
    memset(&s,0,sizeof(s));
    for(i=0U;i<8192U;++i)chr[i]=(mysmb_io_u8)(i*13U+i/3U);
    for(i=0U;i<2048U;++i)s.name_table[i/1024U][i&1023U]=(mysmb_io_u8)(i*7U);
    s.chr_data=chr;s.chr_data_size=sizeof(chr);s.visible_ppu_mask=30U;
    s.visible_ppu_name_table=1U;s.visible_scroll_x=19U;s.visible_scroll_y=23U;s.visible_sprite0_split=1U;
    memset(s.visible_oam,0xefU,sizeof(s.visible_oam));
    s.visible_oam[0]=80U;s.visible_oam[1]=9U;s.visible_oam[2]=0U;s.visible_oam[3]=70U;
    s.visible_oam[4]=80U;s.visible_oam[5]=11U;s.visible_oam[6]=0x20U;s.visible_oam[7]=72U;
    s.visible_oam[8]=5U;s.visible_oam[9]=13U;s.visible_oam[10]=1U;s.visible_oam[11]=5U;
    mysmb_ppu_frame_workspace_bind(&w,0);
    mysmb_ppu_frame_background_byte_bind(&w,background,sizeof(background),second,sizeof(second));
    mysmb_ppu_frame_begin(&s,&w,&v);
    for(t=0U;t<2U;++t)for(r=0U;r<30U;++r)for(c=0U;c<32U;++c)
        if(!mysmb_ppu_frame_background_tile_slots(&v,(mysmb_io_u8)t,(mysmb_io_u8)r,
            (mysmb_io_u8)c,tiles[t][r][c],64U))return 1;
    for(y=0U;y<240U;++y)for(x=0U;x<256U;++x)actual[y*256U+x]=background_slot(&s,x,y);
    if(!mysmb_ppu_frame_slot_rows(&v,expected,sizeof(expected),0U,240U))return 2;
    calls=0U;last_sprite=64U;
    if(!mysmb_ppu_frame_sprite_tiles(&v,overlay_slots,sizeof(overlay_slots),apply,0))return 3;
    if(memcmp(actual,expected,sizeof(actual))!=0)return 4;
    printf("sprites=%u order=%u exact=1\n",calls,last_sprite);
    return 0;
}
