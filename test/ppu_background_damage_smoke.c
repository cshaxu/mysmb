#include "ppu/frame.h"
#include <stdio.h>
#include <string.h>

static struct mysmb_ppu_state state;
static struct mysmb_ppu_frame_workspace workspace;
static unsigned char chr[8192],decoded[8192];
static unsigned char first[MYSMB_PPU_BACKGROUND_BYTES];
static unsigned char second[MYSMB_PPU_BACKGROUND_SECOND_BYTES];

#define CHECK(value) do { if (!(value)) { printf("line%d\n",__LINE__); return 1; } } while(0)

static unsigned short marked(const struct mysmb_ppu_background_damage *damage)
{
    unsigned short i,count=0U;
    for(i=0U;i<1920U;++i)
        if((damage->tiles[i>>3U]&(unsigned char)(1U<<(i&7U)))!=0U)++count;
    return count;
}
static int marked_tile(const struct mysmb_ppu_background_damage *damage,
    unsigned short table,unsigned short row,unsigned short column)
{
    unsigned short tile=(unsigned short)(table*960U+row*32U+column);
    return (damage->tiles[tile>>3U]&(unsigned char)(1U<<(tile&7U)))!=0U;
}
static int prepared(struct mysmb_ppu_background_damage *damage)
{
    struct mysmb_ppu_frame_view view;
    mysmb_ppu_frame_begin(&state,&workspace,&view);
    if(!mysmb_ppu_frame_background_damage(&view,damage))return 0;
    mysmb_ppu_frame_end(&view);
    return 1;
}
int main(void)
{
    struct mysmb_ppu_background_damage damage;
    unsigned short i,row,column;
    memset(&state,0,sizeof(state));
    for(i=0U;i<8192U;++i)chr[i]=(unsigned char)(i*17U+3U);
    for(i=0U;i<2048U;++i)state.name_table[i/1024U][i%1024U]=(unsigned char)(i*7U+1U);
    state.chr_data=chr;state.chr_data_size=8192U;state.visible_ppu_mask=8U;
    mysmb_ppu_frame_workspace_bind(&workspace,decoded);
    mysmb_ppu_frame_background_byte_bind(&workspace,first,sizeof(first),second,sizeof(second));
    CHECK(prepared(&damage));
    CHECK(damage.full==1U && damage.count==1920U && marked(&damage)==1920U);
    for(i=0U;i<MYSMB_PPU_BACKGROUND_DAMAGE_BYTES;++i)CHECK(damage.tiles[i]==255U);
    CHECK(prepared(&damage));
    CHECK(damage.full==0U && damage.count==0U && marked(&damage)==0U);
    state.name_table[0][5U]^=1U;
    CHECK(prepared(&damage));
    CHECK(damage.full==0U && damage.count==1U && marked(&damage)==1U && marked_tile(&damage,0U,0U,5U));
    state.name_table[1][960U+8U]^=3U;
    CHECK(prepared(&damage));
    CHECK(damage.full==0U && damage.count==16U && marked(&damage)==16U);
    for(row=4U;row<8U;++row)for(column=0U;column<4U;++column)
        CHECK(marked_tile(&damage,1U,row,column));
    state.palette[0]^=63U;
    CHECK(prepared(&damage));
    CHECK(damage.full==0U && damage.count==0U && marked(&damage)==0U);
    /* The retained surface is black while the PPU background is disabled.
     * Re-enabling it must redraw every cached tile even when nametables did
     * not change. */
    state.visible_ppu_mask^=8U;
    CHECK(prepared(&damage));
    CHECK(damage.full==1U && damage.count==1920U && marked(&damage)==1920U);
    state.visible_ppu_mask^=8U;
    CHECK(prepared(&damage));
    CHECK(damage.full==1U && damage.count==1920U && marked(&damage)==1920U);
    state.visible_ppu_control_0^=16U;
    CHECK(prepared(&damage));
    CHECK(damage.full==1U && damage.count==1920U && marked(&damage)==1920U);
    memset(&damage,0xa5,sizeof(damage));
    CHECK(!mysmb_ppu_frame_background_damage(0,&damage));
    for(i=0U;i<sizeof(damage);++i)CHECK(((unsigned char *)&damage)[i]==0xa5U);
    puts("initial1920 unchanged0 tile1 attribute16 palette0 mask1920 full1920 readonly=1");
    return 0;
}
