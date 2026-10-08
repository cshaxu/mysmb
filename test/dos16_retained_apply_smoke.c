#include "platform/dos16/retained_background.h"
#include "ppu/frame.h"
#include <stdio.h>
#include <string.h>

static mysmb_io_u8 background[MYSMB_PPU_BACKGROUND_BYTES];
static mysmb_io_u8 second[MYSMB_PPU_BACKGROUND_SECOND_BYTES];
static mysmb_io_u8 chr[8192];
static mysmb_io_u8 projected[2][30][32][64];
static unsigned short writes;
static unsigned short plane_writes[4];
static int store(void *context,mysmb_io_u8 table,mysmb_io_u8 row,
    mysmb_io_u8 column,const mysmb_io_u8 MYSMB_IO_FAR *slots)
{
    (void)context;
    if(table>=2U || row>=30U || column>=32U)return 0;
    memcpy(projected[table][row][column],slots,64U);++writes;return 1;
}
static int store_plane(void *context,mysmb_io_u8 plane,mysmb_io_u8 table,
    mysmb_io_u8 row,mysmb_io_u8 column,const mysmb_io_u8 MYSMB_IO_FAR *slots)
{
    (void)context;
    if(plane>=4U || table>=2U || row>=30U || column>=32U)return 0;
    memcpy(projected[table][row][column],slots,64U);++plane_writes[plane];return 1;
}
static void state(struct mysmb_ppu_state *s)
{
    mysmb_io_u16 i;
    memset(s,0,sizeof(*s));s->chr_data=chr;s->chr_data_size=sizeof(chr);
    for(i=0U;i<2048U;++i)s->name_table[i/1024U][i&1023U]=(mysmb_io_u8)(i*11U);
    for(i=0U;i<8192U;++i)chr[i]=(mysmb_io_u8)(i*3U+i/5U);
}
int main(void)
{
    struct mysmb_ppu_state s;
    struct mysmb_ppu_frame_workspace w;
    struct mysmb_ppu_frame_view v;
    mysmb_io_u8 tile[64];
    state(&s);mysmb_ppu_frame_workspace_bind(&w,0);
    mysmb_ppu_frame_background_byte_bind(&w,background,sizeof(background),second,sizeof(second));
    mysmb_ppu_frame_begin(&s,&w,&v);writes=0U;
    if(!mysmb_dos16_retained_background_apply(&v,store,0) || writes!=1920U)return 1;
    if(!mysmb_ppu_frame_background_tile_slots(&v,1U,29U,31U,tile,sizeof(tile)) ||
        memcmp(tile,projected[1][29][31],64U)!=0)return 2;
    mysmb_ppu_frame_end(&v);mysmb_ppu_frame_begin(&s,&w,&v);writes=0U;
    if(!mysmb_dos16_retained_background_apply(&v,store,0) || writes!=0U)return 3;
    mysmb_ppu_frame_end(&v);s.name_table[1][9U*32U+6U]^=1U;
    mysmb_ppu_frame_begin(&s,&w,&v);writes=0U;
    if(!mysmb_dos16_retained_background_apply(&v,store,0) || writes!=1U)return 4;
    if(!mysmb_ppu_frame_background_tile_slots(&v,1U,9U,6U,tile,sizeof(tile)) ||
        memcmp(tile,projected[1][9][6],64U)!=0)return 5;
    mysmb_ppu_frame_end(&v);mysmb_ppu_frame_begin(&s,&w,&v);
    memset(plane_writes,0,sizeof(plane_writes));
    if(!mysmb_dos16_retained_background_apply_planes(&v,store_plane,0) ||
        plane_writes[0] || plane_writes[1] || plane_writes[2] || plane_writes[3])return 6;
    mysmb_ppu_frame_end(&v);s.name_table[0][3U*32U+2U]^=1U;
    mysmb_ppu_frame_begin(&s,&w,&v);memset(plane_writes,0,sizeof(plane_writes));
    if(!mysmb_dos16_retained_background_apply_planes(&v,store_plane,0) ||
        plane_writes[0]!=1U || plane_writes[1]!=1U || plane_writes[2]!=1U ||
        plane_writes[3]!=1U)return 7;
    printf("initial=1920 unchanged=0 tile=1\n");
    return 0;
}
