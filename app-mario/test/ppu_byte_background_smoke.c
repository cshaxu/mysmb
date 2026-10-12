#include "ppu/frame.h"
#include <stdio.h>
#include <string.h>
static struct mysmb_ppu_state state,before;
static struct mysmb_ppu_frame reference,packed,bytes,raw_packed;
static struct mysmb_ppu_frame_workspace pw,bw,rw;
static unsigned char chr[8192],decode[8192],decode2[8192];
static unsigned char first[MYSMB_PPU_BACKGROUND_BYTES+2];
static unsigned char second[MYSMB_PPU_BACKGROUND_SECOND_BYTES+2];
static unsigned char packed_store[MYSMB_PPU_BACKGROUND_BYTES];
static unsigned char raw_store[MYSMB_PPU_BACKGROUND_BYTES];
static unsigned char rows[4096],palette[32];
static unsigned long seed=1UL;
static unsigned long copied=0UL;
static unsigned char random_byte(void)
{seed=(seed*1664525UL+1013904223UL)&0xffffffffUL;return (unsigned char)(seed>>24U);}
#define CHECK(c) do {if(!(c)){printf("line%d\n",__LINE__);return 1;}}while(0)
static int copy_slots(const mysmb_io_u8 *first,const mysmb_io_u8 *second,
    mysmb_io_u8 *destination,mysmb_io_u16 first_count,mysmb_io_u16 second_count,
    mysmb_io_u16 count)
{
    mysmb_io_u16 row;
    if(!first || !destination || !count || count>16U || first_count+second_count!=256U ||
        (second_count && !second))return 0;
    for(row=0U;row<count;++row) {
        memcpy(destination+row*256U,first+row*256U,first_count);
        if(second_count)memcpy(destination+row*256U+first_count,
            second+row*256U,second_count);
    }
    copied+=(unsigned long)count*256UL;
    return 1;
}
static int reject_slots(const mysmb_io_u8 *first,const mysmb_io_u8 *second,
    mysmb_io_u8 *destination,mysmb_io_u16 first_count,mysmb_io_u16 second_count,
    mysmb_io_u16 count)
{
    (void)first;(void)second;(void)destination;(void)first_count;
    (void)second_count;(void)count;
    return 0;
}
int main(void)
{
    unsigned short n,i,t,y,x,count;
    struct mysmb_ppu_frame_view view;
    for(i=0U;i<8192U;++i)chr[i]=random_byte();
    memset(first,0xa5,sizeof(first));memset(second,0xa5,sizeof(second));
    mysmb_ppu_frame_workspace_bind(&pw,decode);
    mysmb_ppu_frame_workspace_bind(&bw,decode2);
    mysmb_ppu_frame_background_bind(&pw,packed_store,sizeof(packed_store));
    mysmb_ppu_frame_workspace_bind(&rw,0);
    mysmb_ppu_frame_background_bind(&rw,raw_store,sizeof(raw_store));
    mysmb_ppu_frame_background_byte_bind(&bw,first+1,MYSMB_PPU_BACKGROUND_BYTES,
        second+1,MYSMB_PPU_BACKGROUND_SECOND_BYTES);
    CHECK(bw.bg_second==second+1);
    mysmb_ppu_frame_slot_rows_bind(&bw,copy_slots);
    memset(&state,0,sizeof(state));
    for(n=0U;n<512U;++n){
        state.chr_data=n%17U?chr:0;
        state.chr_data_size=n%19U?8192U:(unsigned short)(n*31U%8192U);
        if(n%5U==0U)for(t=0U;t<2U;++t)for(i=0U;i<1024U;++i)state.name_table[t][i]=random_byte();
        else state.name_table[n&1U][n%1024U]^=1U;
        for(i=0U;i<32U;++i)state.palette[i]=(unsigned char)(random_byte()&63U);
        for(i=0U;i<256U;++i)state.visible_oam[i]=random_byte();
        state.visible_scroll_x=(unsigned char)n;state.visible_scroll_y=(unsigned char)(n*37U);
        state.visible_ppu_name_table=(unsigned char)(n&3U);
        state.visible_ppu_control_0=(unsigned char)((n/4U)%4U*8U);
        state.visible_ppu_mask=(unsigned char)(n&31U);
        state.visible_sprite0_split=(unsigned char)((n/32U)&1U);
        before=state;
        mysmb_ppu_frame_build(&state,&reference);
        mysmb_ppu_frame_build_cached(&state,&packed,&pw);
        mysmb_ppu_frame_build_cached(&state,&bytes,&bw);
        mysmb_ppu_frame_build_cached(&state,&raw_packed,&rw);
        CHECK(!memcmp(reference.pixels,packed.pixels,sizeof(reference.pixels)));
        CHECK(!memcmp(reference.pixels,bytes.pixels,sizeof(reference.pixels)));
        CHECK(!memcmp(reference.pixels,raw_packed.pixels,sizeof(reference.pixels)));
        mysmb_ppu_frame_palette(&state,palette);
        mysmb_ppu_frame_begin(&state,&bw,&view);
        for(y=0U;y<240U;y+=16U){
            count=16U;
            CHECK(mysmb_ppu_frame_slot_rows(&view,rows,sizeof(rows),y,count));
            for(x=0U;x<count*256U;++x)CHECK(rows[x]<32U &&
                palette[rows[x]]==reference.pixels[y*256U+x]);
        }
        mysmb_ppu_frame_end(&view);
        CHECK(!memcmp(&state,&before,sizeof(state)));
        CHECK(first[0]==0xa5 && first[sizeof(first)-1]==0xa5);
        CHECK(second[0]==0xa5 && second[sizeof(second)-1]==0xa5);
    }
    CHECK(copied!=0UL);
    mysmb_ppu_frame_slot_rows_bind(&bw,reject_slots);
    mysmb_ppu_frame_build_cached(&state,&bytes,&bw);
    CHECK(!memcmp(reference.pixels,bytes.pixels,sizeof(reference.pixels)));
    /* Low-memory/invalid secondary must use the intact packed implementation. */
    mysmb_ppu_frame_background_byte_bind(&bw,first+1,MYSMB_PPU_BACKGROUND_BYTES,0,0);
    CHECK(!bw.bg_second);
    mysmb_ppu_frame_build_cached(&state,&bytes,&bw);
    CHECK(!memcmp(reference.pixels,bytes.pixels,sizeof(reference.pixels)));
    mysmb_ppu_frame_background_byte_bind(&bw,first+1,MYSMB_PPU_BACKGROUND_BYTES,second+1,61439U);
    CHECK(!bw.bg_second);
    mysmb_ppu_frame_background_byte_bind(&bw,first+1,63487U,second+1,61440U);
    CHECK(!bw.bg && !bw.bg_second);
    mysmb_ppu_frame_build_cached(&state,&bytes,&bw);
    CHECK(!memcmp(reference.pixels,bytes.pixels,sizeof(reference.pixels)));
    puts("states512 canonical-packed-byte=equal slots=equal guards=1 fallback=1 slot-copy=1 readonly=1");
    return 0;
}
