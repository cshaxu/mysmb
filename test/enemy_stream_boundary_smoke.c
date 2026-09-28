#include "game/enemy/stream.h"
#include "game/enemy/init.h"
#include "game/enemy/loop.h"
#include "game/enemy/group.h"
#include <string.h>

static unsigned int initialized, continued, reject;
void mysmb_enemy_stream_handle_group(struct mysmb_game *game,mysmb_u8 id)
{ (void)game;(void)id;continued+=100U; }
void mysmb_enemy_checkpoint_loaded(struct mysmb_game *game,mysmb_u8 slot)
{
    ++initialized;
    if(reject) game->ram[0xfU+slot]=0U;
}
void mysmb_enemy_process_loop_command(struct mysmb_game *game,
    const struct mysmb_area_source *source,mysmb_u8 slot)
{ (void)game;(void)source;(void)slot;++continued; }

int main(void)
{
    static struct mysmb_game game;
    static mysmb_u8 prg[256],expected[2048];
    struct mysmb_area_source source;
    unsigned int page,x,offset,kind,world,right,extended,within;
    source.prg=prg;source.prg_size=256U;
    /* Independent 16-bit boundary model; all right-page/right-X pairs. */
    for(page=0U;page<256U;++page) for(x=0U;x<256U;++x) {
        memset(&game,0,sizeof(game));memset(prg,0xff,sizeof(prg));
        game.ram[0xeaU]=0x80U;game.ram[0x71bU]=(mysmb_u8)page;
        game.ram[0x71dU]=(mysmb_u8)x;
        right=page*256U+x;extended=(right+48U)&65535U;
        extended&=65520U;
        game.ram[0x73aU]=(mysmb_u8)(extended/256U);
        prg[0]=(mysmb_u8)(extended&240U);prg[1]=0x33U;
        memcpy(expected,game.ram,sizeof(expected));
        expected[6U]=(mysmb_u8)(extended/256U);expected[7U]=(mysmb_u8)extended;
        expected[0x6eU]=game.ram[0x73aU];expected[0x87U]=prg[0];
        world=extended;within=world>=right;
        expected[0x739U]=2U;
        if(within) {
            expected[0xb6U]=1U;expected[0x16U]=0x33U;expected[0xfU]=1U;
        }
        initialized=0U;continued=0U;reject=0U;
        (void)mysmb_enemy_stream_process_current(&game,&source,0U);
        if(initialized!=within || continued || memcmp(expected,game.ram,sizeof(expected))) return 1;
    }
    /* INY and cursor wrap, accepted/rejected initialization, and both orders
     * of the row-$0F/page-bit gate. Compare the entire portable RAM image. */
    for(offset=0U;offset<256U;++offset) for(kind=0U;kind<4U;++kind) {
        memset(&game,0,sizeof(game));memset(prg,0xff,sizeof(prg));
        game.ram[0xeaU]=0x80U;game.ram[0x739U]=(mysmb_u8)offset;
        prg[offset]=(mysmb_u8)(kind>=2U?0x0fU:0x10U);
        prg[(offset+1U)&255U]=(mysmb_u8)(kind==2U?3U:(kind==3U?0x86U:0x33U));
        if(kind==3U) game.ram[0x71bU]=1U;
        memcpy(expected,game.ram,sizeof(expected));
        expected[6U]=game.ram[0x71bU];expected[7U]=0x30U;
        reject=kind==1U;initialized=0U;continued=0U;
        if(kind==2U) {
            expected[0x73aU]=3U;expected[0x73bU]=1U;
            expected[0x739U]=(mysmb_u8)(offset+2U);
        } else {
            expected[0x6eU]=(mysmb_u8)(kind==3U?1U:0U);
            expected[0x87U]=(mysmb_u8)(kind==3U?0U:0x10U);
            expected[0xb6U]=1U;expected[0xcfU]=(mysmb_u8)(kind==3U?0xf0U:0U);
            expected[0x16U]=(mysmb_u8)(kind==3U?6U:0x33U);
            expected[0xfU]=(mysmb_u8)(reject?0U:1U);
            if(kind==3U) expected[0x73aU]=1U;
            if(!reject) expected[0x739U]=(mysmb_u8)(offset+2U);
        }
        (void)mysmb_enemy_stream_process_current(&game,&source,0U);
        if(initialized!=(kind==2U?0U:1U) || continued!=(kind==2U?1U:0U) ||
            memcmp(expected,game.ram,sizeof(expected))) return 2;
    }
    /* These parser arms have no such ordinary records in the original
     * enemy streams. Prove their handoff without inventing child behavior. */
    for(kind=0U;kind<2U;++kind) {
        memset(&game,0,sizeof(game));memset(prg,0xff,sizeof(prg));
        game.ram[0xeaU]=0x80U;prg[0]=0x10U;
        prg[1]=(mysmb_u8)(kind?0x3fU:0x2eU);
        offset=kind?0U:5U;
        memcpy(expected,game.ram,sizeof(expected));
        expected[7U]=0x30U;expected[0x87U+offset]=0x10U;
        expected[0xb6U+offset]=1U;expected[0x16U+offset]=prg[1];
        expected[0xfU+offset]=1U;expected[0x739U]=2U;
        initialized=0U;continued=0U;reject=0U;
        (void)mysmb_enemy_stream_process_current(&game,&source,(mysmb_u8)offset);
        if(initialized!=1U || continued || memcmp(expected,game.ram,sizeof(expected))) return 3;
    }
    return 0;
}
