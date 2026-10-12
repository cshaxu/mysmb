#include "text/scene.h"
#include "text/layout.h"
#include "text/compact_elements.h"
#include "core/frame_root.h"
#include "io/color.h"
#include <stdio.h>
#include <string.h>
static struct mysmb_game game,before;
static struct mysmb_text_scene_workspace workspace;
static struct mysmb_io_text_frame frame;
static struct mysmb_io_text_cell run_frames[3][2000];
static unsigned char prg[32768];
#define CHECK(c) do {if(!(c)){fprintf(stderr,"compact check %d\n",__LINE__);return 1;}}while(0)
int main(void)
{
    struct mysmb_text_element e;
    unsigned char colors[3]={4U,6U,8U},palette[32];
    unsigned short kind,pose,i,j,n,found,ar,br;
    for(i=0U;i<32U;++i)palette[i]=(unsigned char)((i%4U)==0U?0x22U:(i%4U)==1U?0x16U:(i%4U)==2U?0x27U:0x18U);
    for(i=0U;i<64U;++i)CHECK(mysmb_io_color_text_nearest(mysmb_io_color_rgb((mysmb_io_u8)i))==mysmb_io_color_text16((mysmb_io_u8)i));
    memset(&frame,0xa5,sizeof(frame));
    mysmb_text_frame_initialize(&frame,9U,25U,palette);
    CHECK(frame.rows==25U && frame.source_colors==1U);
    CHECK(frame.colors[mysmb_text_contrast(&frame,0U)]==mysmb_io_color_rgb(0x30U));
    CHECK(frame.cells[2000U].character==0xa5U);
    for(i=0U;i<32U;++i)CHECK(frame.colors[mysmb_text_color(&frame,palette[i])]==mysmb_io_color_rgb(palette[i]));
    n=0U;
    for(kind=0U;kind<46U;++kind)for(pose=0U;pose<(kind<=1U || kind==43U || kind==44U?17U:1U);++pose) {
        memset(&e,0,sizeof(e));e.kind=(unsigned char)kind;e.pose=(unsigned char)pose;e.x=80;e.y=96;
        mysmb_text_frame_initialize(&frame,9U,25U,0);
        CHECK(mysmb_text_compact_draw(&e,colors,&frame,0,0));
        found=0U;
        for(i=0U;i<2000U;++i){CHECK(frame.cells[i].foreground<16U && frame.cells[i].background<16U);if(frame.cells[i].background!=9U || frame.cells[i].character!=' ')++found;}
        CHECK(found>0U);++n;
    }
    memset(&game,0,sizeof(game));memset(prg,0,sizeof(prg));game.area_prg=prg;game.area_prg_size=sizeof(prg);
    memset(game.ppu.name_table,0x24,sizeof(game.ppu.name_table));
    for(i=0U;i<32U;++i)game.ppu.palette[i]=palette[i];
    game.ppu.visible_ppu_mask=0x1eU;
    for(i=0U;i<64U;++i)game.ram[0x200U+i*4U]=0xf8U;
    mysmb_text_observer_enable(&game,1U);
    /* Two adjacent source font lines that project onto the same25-row line. */
    game.ppu.name_table[0U][2U*32U+4U]=10U;
    game.ppu.name_table[0U][3U*32U+4U]=11U;
    before=game;
    CHECK(mysmb_text_scene_build_profile(&game,&workspace,&frame,25U));
    CHECK(memcmp(&game,&before,sizeof(game))==0);
    ar=br=25U;
    for(i=0U;i<2000U;++i){if(frame.cells[i].character=='A')ar=i/80U;if(frame.cells[i].character=='B')br=i/80U;}
    CHECK(ar<25U && br<25U && ar!=br);
    memset(game.ppu.name_table,0x24,sizeof(game.ppu.name_table));
    prg[0x0b0bU]=0U;prg[0x0b0fU]=0x90U;
    prg[0x1000U]=0x90U;prg[0x1001U]=0x91U;prg[0x1002U]=0x92U;prg[0x1003U]=0x93U;
    game.ppu.name_table[0U][12U*32U+12U]=0x90U;
    game.ppu.name_table[0U][13U*32U+12U]=0x91U;
    game.ppu.name_table[0U][12U*32U+13U]=0x92U;
    game.ppu.name_table[0U][13U*32U+13U]=0x93U;
    game.ppu.name_table[0U][0x3dbU]=3U;
    for(j=0U;j<16U;++j) {
        game.ppu.visible_scroll_y=(unsigned char)j;
        CHECK(mysmb_text_scene_build_profile(&game,&workspace,&frame,25U));
        found=0U;for(i=0U;i<2000U;++i)if(frame.cells[i].character=='?')++found;
        CHECK(found==1U);
    }
    game.ppu.visible_scroll_y=0U;
    memset(game.ppu.name_table,0x24,sizeof(game.ppu.name_table));
    for(i=0U;i<8U;++i) {
        j=(unsigned short)(0x220U+i*4U);game.ram[j]=(unsigned char)(95U+(i/2U)*8U);
        game.ram[j+1U]=1U;game.ram[j+2U]=0U;game.ram[j+3U]=(unsigned char)(80U+(i%2U)*8U);
    }
    mysmb_text_observer_record(&game,MYSMB_TEXT_OBSERVE_PLAYER,0U,0U,0U,1U,32U,8U,0U);
    mysmb_game_submit_oam(&game);before=game;
    CHECK(mysmb_text_scene_build_profile(&game,&workspace,&frame,25U));
    CHECK(memcmp(&game,&before,sizeof(game))==0);
    found=0U;for(i=0U;i<2000U;++i)if(frame.cells[i].character=='M')++found;
    CHECK(found==1U);
    /* Source-selected walk offsets must stay three distinct native cell
     * frames,including both player identities/sizes and facing directions. */
    prg[0x6e09U]=16U;prg[0x6e0bU]=32U;
    prg[0x6e11U]=16U;prg[0x6e13U]=32U;
    for(kind=0U;kind<4U;++kind)for(j=0U;j<2U;++j) {
        for(pose=0U;pose<3U;++pose) {
            mysmb_text_observer_enable(&game,0U);mysmb_text_observer_enable(&game,1U);
            mysmb_text_observer_record(&game,MYSMB_TEXT_OBSERVE_PLAYER,(unsigned char)(kind/2U),0U,
                (unsigned char)(32U+pose*8U),(unsigned char)(j==0U?1U:2U),32U,8U,(unsigned char)(kind%2U));
            mysmb_game_submit_oam(&game);before=game;
            CHECK(mysmb_text_scene_build_profile(&game,&workspace,&frame,25U));
            CHECK(memcmp(&game,&before,sizeof(game))==0);
            memcpy(run_frames[pose],frame.cells,sizeof(run_frames[pose]));
        }
        CHECK(memcmp(run_frames[0],run_frames[1],sizeof(run_frames[0]))!=0);
        CHECK(memcmp(run_frames[1],run_frames[2],sizeof(run_frames[0]))!=0);
        CHECK(memcmp(run_frames[0],run_frames[2],sizeof(run_frames[0]))!=0);
    }
    CHECK(mysmb_text_scene_build(&game,&workspace,&frame));
    CHECK(frame.rows==50U && frame.source_colors==0U);
    CHECK(memcmp(&game,&before,sizeof(game))==0);
    printf("compact: %u kind/pose proposals;palette,capacity,caption collision,source immutability and legacy profile pass\n",n);
    return 0;
}
