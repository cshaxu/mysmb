#include "game/presentation/text/actor_scene.h"
#include "game/frame_root.h"
#include "io/color.h"
#include <stdio.h>
#include <string.h>

static struct mysmb_text_actor_workspace actor_workspace;
static struct mysmb_game game,before;
static struct mysmb_io_text_frame frame,original;
static unsigned char prg[0x8000U];
static unsigned char opaque[500];
#define CHECK(c) do {if(!(c)){fprintf(stderr,"scene check %d\n",__LINE__);return 1;}}while(0)

static void sprite(unsigned short index,unsigned char x,unsigned char y)
{
    game.ram[0x0200U+index*4U]=y;
    game.ram[0x0201U+index*4U]=1U;
    game.ram[0x0202U+index*4U]=0U;
    game.ram[0x0203U+index*4U]=x;
}

int main(void)
{
    struct mysmb_text_actor_receipt receipt;
    unsigned short i;
    memset(&game,0,sizeof(game));
    for(i=0U;i<64U;++i)game.ram[0x0200U+i*4U]=0xf8U;
    game.visible_ppu_mask=0x1eU;game.palette[0x12U]=0x16U;
    mysmb_text_observer_enable(&game,1U);
    CHECK(mysmb_text_elements_build(0,0U,9U,&frame));
    sprite(8U,80U,95U);sprite(9U,88U,95U);
    sprite(10U,80U,103U);sprite(11U,88U,103U);
    mysmb_text_observer_record(&game,MYSMB_TEXT_OBSERVE_POWERUP,
        0U,5U,0U,1U,32U,4U,0U);
    mysmb_game_submit_oam(&game);
    before=game;
    CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
    CHECK(receipt.drawn==1U && receipt.unsupported==0U);
    CHECK(receipt.unowned_sprites==0U);
    CHECK(memcmp(&game,&before,sizeof(game))==0);
    CHECK(frame.cells[20U*80U+26U].character=='/');
    CHECK(frame.cells[20U*80U+26U].background==mysmb_io_color_text16(0x16U));
    CHECK(frame.cells[0U].background==9U);
    original=frame;
    game.ram[0x0201U+32U]=2U;
    CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
    CHECK(memcmp(&frame,&original,sizeof(frame))==0);
    mysmb_game_submit_oam(&game);
    CHECK(mysmb_text_elements_build(0,0U,9U,&frame));
    CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
    CHECK(frame.cells[20U*80U+26U].character==' ');
    /* Losing a source column clips it rather than shifting the object. */
    game.visible_oam[32U+9U]=2U;
    CHECK(mysmb_text_elements_build(0,0U,9U,&frame));
    CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
    CHECK(frame.cells[20U*80U+29U].character=='\\');
    CHECK(frame.cells[20U*80U+31U].character==' ');

    /* Unknown types remain explicit and do not paint a fabricated object. */
    mysmb_text_observer_record(&game,MYSMB_TEXT_OBSERVE_ENEMY,
        45U,0U,0U,1U,32U,4U,0U);
    mysmb_game_submit_oam(&game);
    CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
    CHECK(receipt.unsupported==1U);
    /* Already-selected player graphics are interpreted via immutable table. */
    game.area_prg=prg;game.area_prg_size=sizeof(prg);
    prg[0x6e11U]=24U;
    mysmb_text_observer_record(&game,MYSMB_TEXT_OBSERVE_PLAYER,
        0U,0U,24U,1U,32U,4U,1U);
    mysmb_game_submit_oam(&game);
    CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
    CHECK(receipt.drawn==1U && receipt.unsupported==0U);
    game.visible_ppu_mask=0U;original=frame;
    CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
    CHECK(receipt.drawn==0U && memcmp(&frame,&original,sizeof(frame))==0);
    /* A shared selected offset cannot classify the original death branch. */
    game.visible_ppu_mask=0x1eU;
    mysmb_text_observer_record(&game,MYSMB_TEXT_OBSERVE_PLAYER,
        MYSMB_TEXT_PLAYER_DEATH_FLAG,0U,24U,1U,32U,4U,1U);
    mysmb_game_submit_oam(&game);
    CHECK(mysmb_text_elements_build(0,0U,9U,&frame));
    CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
    CHECK(frame.cells[21U*80U+27U].character=='_');
    /* Independent chunks and interleaved original entry priority. */
    mysmb_text_observer_enable(&game,1U);
    for(i=0U;i<64U;++i)game.ram[0x0200U+i*4U]=0xf8U;
    game.palette[0x16U]=0x1aU;
    sprite(8U,80U,95U);sprite(9U,120U,95U);sprite(10U,120U,95U);
    mysmb_text_observer_record(&game,MYSMB_TEXT_OBSERVE_CHUNKS,
        0U,0U,0U,1U,32U,3U,0U);
    game.ram[0x0202U+9U*4U]=1U;
    mysmb_text_observer_record(&game,MYSMB_TEXT_OBSERVE_CHUNKS,
        0U,1U,0U,1U,36U,1U,0U);
    sprite(11U,80U,95U);
    mysmb_text_observer_record(&game,MYSMB_TEXT_OBSERVE_CHUNKS,
        0U,2U,0U,1U,44U,1U,0U);
    mysmb_game_submit_oam(&game);
    CHECK(mysmb_text_elements_build(0,0U,9U,&frame));
    CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
    CHECK(frame.cells[20U*80U+25U].character=='#');
    CHECK(frame.cells[20U*80U+37U].character=='#');
    CHECK(frame.cells[20U*80U+37U].background==mysmb_io_color_text16(0x1aU));
    /* The winning behind-background entry also suppresses later sprites. */
    game.ram[0x0202U+8U*4U]=0x20U;
    mysmb_text_observer_record(&game,MYSMB_TEXT_OBSERVE_CHUNKS,
        0U,0U,0U,1U,32U,1U,0U);
    mysmb_game_submit_oam(&game);
    memset(opaque,0,sizeof(opaque));i=20U*80U+25U;
    CHECK(game.text_observer.visible.owners[10U]==0U);
    opaque[i/8U]=(unsigned char)(1U<<(i%8U));
    CHECK(mysmb_text_elements_build(0,0U,9U,&frame));
    frame.cells[i].character=' ';frame.cells[i].background=5U;
    before=game;
    CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,opaque,&frame,&receipt));
    CHECK(frame.cells[i].character==' ' && frame.cells[i].background==5U);
    CHECK(memcmp(&before,&game,sizeof(game))==0);
    /* Two separated platform rows and every leaf of a vine remain visible. */
    mysmb_text_observer_enable(&game,1U);
    for(i=0U;i<64U;++i)game.ram[0x0200U+i*4U]=0xf8U;
    for(i=0U;i<6U;++i)sprite((unsigned short)(8U+i),
        (unsigned char)(80U+(i%3U)*8U),(unsigned char)(79U+(i/3U)*128U));
    mysmb_text_observer_record(&game,MYSMB_TEXT_OBSERVE_PLATFORM,
        0U,0U,0U,1U,32U,6U,0U);
    mysmb_game_submit_oam(&game);
    CHECK(mysmb_text_elements_build(0,0U,9U,&frame));
    CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
    CHECK(frame.cells[17U*80U+25U].character=='[');
    CHECK(frame.cells[43U*80U+30U].character=='=');
    CHECK(frame.cells[43U*80U+31U].character==']');
    for(i=26U;i<31U;++i)CHECK(frame.cells[17U*80U+i].character=='=');
    mysmb_text_observer_enable(&game,1U);
    for(i=0U;i<6U;++i) {
        sprite((unsigned short)(8U+i),80U,(unsigned char)(79U+i*8U));
        game.ram[0x0201U+(8U+i)*4U]=i==0U?0xe0U:0xe1U;
    }
    mysmb_text_observer_record(&game,MYSMB_TEXT_OBSERVE_VINE,
        0U,0U,0U,1U,32U,6U,0U);
    mysmb_game_submit_oam(&game);
    CHECK(mysmb_text_elements_build(0,0U,9U,&frame));
    CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
    CHECK(frame.cells[17U*80U+25U].character=='^');
    CHECK(frame.cells[25U*80U+25U].character=='|');
    /* Flag score is a separate subcomponent, not the flag's anchor. */
    sprite(8U,80U,95U);sprite(9U,88U,95U);sprite(10U,88U,103U);
    sprite(11U,100U,47U);sprite(12U,108U,47U);
    mysmb_text_observer_enable(&game,1U);
    mysmb_text_observer_record(&game,MYSMB_TEXT_OBSERVE_FLAG,
        0U,0U,0U,1U,32U,5U,0U);
    mysmb_game_submit_oam(&game);
    CHECK(mysmb_text_elements_build(0,0U,9U,&frame));
    CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
    CHECK(frame.cells[10U*80U+31U].character=='5');
    CHECK(frame.cells[20U*80U+25U].character=='|');
    /* Moving throw keeps base legs; a full throw replaces those legs. */
    mysmb_text_observer_enable(&game,1U);
    for(i=0U;i<8U;++i)sprite((unsigned short)(8U+i),
        (unsigned char)(80U+(i%2U)*8U),(unsigned char)(79U+(i/2U)*8U));
    prg[0x6e0bU]=32U;
    mysmb_text_observer_record(&game,MYSMB_TEXT_OBSERVE_PLAYER,
        MYSMB_TEXT_PLAYER_THROW_FLAG|MYSMB_TEXT_PLAYER_MIXED_FLAG,
        48U,56U,1U,32U,8U,0U);
    mysmb_game_submit_oam(&game);
    CHECK(mysmb_text_elements_build(0,0U,9U,&frame));
    CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
    CHECK(frame.cells[22U*80U+26U].character==' ');
    mysmb_text_observer_record(&game,MYSMB_TEXT_OBSERVE_PLAYER,
        MYSMB_TEXT_PLAYER_THROW_FLAG,48U,56U,1U,32U,8U,0U);
    mysmb_game_submit_oam(&game);
    CHECK(mysmb_text_elements_build(0,0U,9U,&frame));
    CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
    CHECK(frame.cells[22U*80U+26U].character=='_');
    /* Only the source-replaced swim side gets the kick silhouette. */
    prg[0x6e08U]=8U;
    mysmb_text_observer_record(&game,MYSMB_TEXT_OBSERVE_PLAYER,
        MYSMB_TEXT_PLAYER_KICK_FLAG,8U,8U,1U,32U,8U,0U);
    mysmb_game_submit_oam(&game);
    CHECK(mysmb_text_elements_build(0,0U,9U,&frame));
    CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
    CHECK(frame.cells[22U*80U+25U].character=='~');
    CHECK(frame.cells[22U*80U+29U].character==' ');
    mysmb_text_observer_record(&game,MYSMB_TEXT_OBSERVE_PLAYER,
        MYSMB_TEXT_PLAYER_KICK_FLAG,8U,8U,2U,32U,8U,0U);
    mysmb_game_submit_oam(&game);
    CHECK(mysmb_text_elements_build(0,0U,9U,&frame));
    CHECK(mysmb_text_actor_scene_draw(&game,&actor_workspace,0,&frame,&receipt));
    CHECK(frame.cells[22U*80U+25U].character==' ');
    CHECK(frame.cells[22U*80U+29U].character=='~');
    puts("observed actor scene: whole templates/fill/latch/clipping/unknown/read-only passed");
    return 0;
}
