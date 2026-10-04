#include "game/presentation/text/actor_scene.h"
#include "game/frame_root.h"
#include "io/color.h"
#include <stdio.h>
#include <string.h>

static struct mysmb_game game,before;
static struct mysmb_io_text_frame frame,original;
static unsigned char prg[0x8000U];
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
    CHECK(mysmb_text_actor_scene_draw(&game,&frame,&receipt));
    CHECK(receipt.drawn==1U && receipt.unsupported==0U);
    CHECK(receipt.unowned_sprites==0U);
    CHECK(memcmp(&game,&before,sizeof(game))==0);
    CHECK(frame.cells[20U*80U+26U].character=='/');
    CHECK(frame.cells[20U*80U+26U].background==mysmb_io_color_text16(0x16U));
    CHECK(frame.cells[0U].background==9U);
    original=frame;
    game.ram[0x0201U+32U]=2U;
    CHECK(mysmb_text_actor_scene_draw(&game,&frame,&receipt));
    CHECK(memcmp(&frame,&original,sizeof(frame))==0);
    mysmb_game_submit_oam(&game);
    CHECK(mysmb_text_elements_build(0,0U,9U,&frame));
    CHECK(mysmb_text_actor_scene_draw(&game,&frame,&receipt));
    CHECK(frame.cells[20U*80U+26U].character==' ');
    /* Losing a source column clips it rather than shifting the object. */
    game.visible_oam[32U+9U]=2U;
    CHECK(mysmb_text_elements_build(0,0U,9U,&frame));
    CHECK(mysmb_text_actor_scene_draw(&game,&frame,&receipt));
    CHECK(frame.cells[20U*80U+29U].character=='\\');
    CHECK(frame.cells[20U*80U+31U].character==' ');

    /* Unknown types remain explicit and do not paint a fabricated object. */
    mysmb_text_observer_record(&game,MYSMB_TEXT_OBSERVE_ENEMY,
        45U,0U,0U,1U,32U,4U,0U);
    mysmb_game_submit_oam(&game);
    CHECK(mysmb_text_actor_scene_draw(&game,&frame,&receipt));
    CHECK(receipt.unsupported==1U);
    /* Already-selected player graphics are interpreted via immutable table. */
    game.area_prg=prg;game.area_prg_size=sizeof(prg);
    prg[0x6e11U]=24U;
    mysmb_text_observer_record(&game,MYSMB_TEXT_OBSERVE_PLAYER,
        0U,0U,24U,1U,32U,4U,1U);
    mysmb_game_submit_oam(&game);
    CHECK(mysmb_text_actor_scene_draw(&game,&frame,&receipt));
    CHECK(receipt.drawn==1U && receipt.unsupported==0U);
    game.visible_ppu_mask=0U;original=frame;
    CHECK(mysmb_text_actor_scene_draw(&game,&frame,&receipt));
    CHECK(receipt.drawn==0U && memcmp(&frame,&original,sizeof(frame))==0);
    /* A shared selected offset cannot classify the original death branch. */
    game.visible_ppu_mask=0x1eU;
    mysmb_text_observer_record(&game,MYSMB_TEXT_OBSERVE_PLAYER,
        MYSMB_TEXT_PLAYER_DEATH_FLAG,0U,24U,1U,32U,4U,1U);
    mysmb_game_submit_oam(&game);
    CHECK(mysmb_text_elements_build(0,0U,9U,&frame));
    CHECK(mysmb_text_actor_scene_draw(&game,&frame,&receipt));
    CHECK(frame.cells[21U*80U+27U].character=='_');
    puts("observed actor scene: whole templates/fill/latch/clipping/unknown/read-only passed");
    return 0;
}
