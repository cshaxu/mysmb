#include "core/game.h"
#include "ppu/frame.h"
#include "platform/vga/vga_frame.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
void mysmb_ppu_frame_reference(const struct mysmb_game *,struct mysmb_ppu_frame *);
static struct mysmb_game game;
#define state game.ppu
static struct mysmb_ppu_state before;
static struct mysmb_ppu_frame raw,full;
static unsigned char chr[8192],decode0[8192],decode1[8192],band[4096+32],plane[1280+32];
static unsigned long seed=19UL,compared=0UL,vga_compared=0UL;
static unsigned char random_byte(void){seed=(seed*1664525UL+1013904223UL)&0xffffffffUL;return (unsigned char)(seed>>24);}
static int guards(unsigned char *p,unsigned short n){unsigned short i;for(i=0;i<16;++i)if(p[i]!=0xa5 || p[16U+n+i]!=0xa5)return 0;return 1;}
static int zero_alias_edges(void)
{
    struct mysmb_ppu_frame_workspace workspace;
    unsigned short scroll,mask,i;
    memset(&state,0,sizeof(state));memset(chr,0,sizeof(chr));
    memset(state.name_table[0]+960U,255,64U);
    memset(state.name_table[1]+960U,255,64U);
    memset(state.visible_oam,255,256U);
    state.chr_data=chr;state.chr_data_size=8192U;
    for(i=0U;i<32U;++i)state.palette[i]=(unsigned char)(i+17U);
    state.palette[0]=15U;state.palette[17]=48U;
    state.visible_sprite0_split=1U;
    /* A behind-background sprite spans the fixed/scrolled split;background
     * tile zero remains transparent despite nonzero palette aliases/attrs. */
    chr[16]=0x80U;chr[23]=0x80U;
    state.visible_oam[0]=30U;state.visible_oam[1]=1U;
    state.visible_oam[2]=32U;state.visible_oam[3]=249U;
    mysmb_ppu_frame_workspace_bind(&workspace,decode0);
    for(scroll=0U;scroll<8U;++scroll)for(mask=0U;mask<32U;++mask){
        state.visible_scroll_x=(unsigned char)scroll;state.visible_ppu_mask=(unsigned char)mask;
        mysmb_ppu_frame_reference(&game,&raw);
        mysmb_ppu_frame_build_cached(&state,&full,&workspace);
        if(memcmp(raw.pixels,full.pixels,61440U))return 15;
        memset(band,165,sizeof(band));
        if(!mysmb_ppu_frame_build_rows_cached(&state,band+16,4096U,31U,8U,&workspace) ||
            memcmp(band+16,raw.pixels+31U*256U,2048U) || !guards(band,2048U))return 16;
    }
    return 0;
}
int main(void)
{
    struct mysmb_ppu_frame_workspace w0,w1;
    struct mysmb_io_video_band view;
    unsigned short c,i,first,rows,stop,j,p,y,x,sy,sx,n;
    clock_t started=clock();
    for(c=0;c<512;++c){
        for(i=0;i<sizeof(state);++i)((unsigned char *)&state)[i]=random_byte();
        for(i=0;i<8192;++i)chr[i]=(c%7U==0U)?0U:random_byte();
        state.chr_data=(c%11U==0U)?0:chr;
        state.chr_data_size=c%5U==0U?(unsigned short)(c*17U):8192U;
        state.visible_scroll_x=(unsigned char)c;state.visible_scroll_y=(unsigned char)(c*7U);
        state.visible_sprite0_split=(unsigned char)(c&1U);
        state.visible_ppu_control_0=(unsigned char)((c%4U)*8U);
        state.visible_ppu_mask=(unsigned char)(c&31U);
        for(i=0;i<32;++i)state.palette[i]&=63U;
        /* Exercise sprite overlap, flips, priorities and every strip/screen edge. */
        for(i=0;i<64;++i){state.visible_oam[i*4U]=(unsigned char)(i*4U+c);state.visible_oam[i*4U+2U]=(unsigned char)((i%8U)*32U+(i&3U));}
        before=state;
        mysmb_ppu_frame_workspace_bind(&w0,decode0);mysmb_ppu_frame_workspace_bind(&w1,decode1);
        mysmb_ppu_frame_reference(&game,&raw);mysmb_ppu_frame_build_cached(&state,&full,&w0);
        if(memcmp(raw.pixels,full.pixels,61440U)){printf("raw/cache mismatch %u\n",c);return 1;}
        /* Three source-strip sizes, cached and uncached. */
        for(j=0;j<6;++j){
            n=j%3U==0U?1U:(j%3U==1U?11U:16U);
            for(first=0;first<240;first=(unsigned short)(first+rows)){
                rows=(unsigned short)(240U-first);if(rows>n)rows=n;
                memset(band,0xa5,sizeof(band));
                if(!mysmb_ppu_frame_build_rows_cached(&state,band+16,4096U,first,rows,j<3?&w1:0))return 2;
                if(!guards(band,(unsigned short)(rows*256U)))return 3;
                if(memcmp(band+16,raw.pixels+first*256U,rows*256U)){printf("strip mismatch %u %u %u\n",c,j,first);return 4;}
                compared+=(unsigned long)rows*256UL;
            }
        }
        /* 25 destination bands, each composed once then reused for four planes. */
        for(first=0;first<400;first=(unsigned short)(first+16U)){
            sy=(unsigned short)(first*3U/5U);stop=(unsigned short)((first+15U)*3U/5U);
            rows=(unsigned short)(stop-sy+1U);memset(band,0xa5,sizeof(band));
            if(!mysmb_ppu_frame_build_rows_cached(&state,band+16,4096U,sy,rows,&w1)||!guards(band,(unsigned short)(rows*256U)))return 5;
            view.pixels=band+16;view.first=sy;view.rows=rows;
            for(p=0;p<4;++p){
                memset(plane,0xa5,sizeof(plane));if(!mysmb_vga_frame_build_band(&view,p,first,16,plane+16))return 12;
                if(!guards(plane,1280))return 6;
                for(y=0;y<16;++y)for(x=0;x<80;++x){
                    sx=(unsigned short)((4U*x+p)*4U/5U);
                    i=(unsigned short)(((first+y)*3U/5U-sy)*256U+sx);
                    if((band[16U+i]&63U)!=plane[16U+y*80U+x]){printf("plane mismatch %u %u %u\n",c,first,p);return 7;}
                    ++vga_compared;
                }
            }
        }
        if(memcmp(&state,&before,sizeof(state)))return 8;
        /* Same workspace rebinds to null/short resources without stale colors. */
        state.chr_data=0;state.chr_data_size=0;
        mysmb_ppu_frame_reference(&game,&raw);
        if(!mysmb_ppu_frame_build_rows_cached(&state,band+16,4096U,31,16,&w1)||memcmp(band+16,raw.pixels+31U*256U,4096))return 9;
    }
    memset(band,0xa5,sizeof(band));
    if(mysmb_ppu_frame_build_rows_cached(&state,band+16,4096U,240,1,&w1)||mysmb_ppu_frame_build_rows_cached(&state,band+16,4096U,239,2,&w1)||mysmb_ppu_frame_build_rows_cached(0,band+16,4096U,0,1,&w1)||mysmb_ppu_frame_build_rows_cached(&state,0,4096U,0,1,&w1))return 10;
    if(mysmb_ppu_frame_build_rows_cached(&state,band+16,255U,0,1,&w1))return 13;
    view.pixels=band+16;view.first=1U;view.rows=1U;
    if(mysmb_vga_frame_build_band(&view,0,0,16,band+16))return 14;
    for(i=0;i<sizeof(band);++i)if(band[i]!=0xa5)return 11;
    printf("cases=512 stripBytes=%lu planeBytes=%lu sourceImmutable=1 guards=1 invalidRejected=1 seconds=%.3f\n",compared,vga_compared,(double)(clock()-started)/CLOCKS_PER_SEC);
    return zero_alias_edges();
}
