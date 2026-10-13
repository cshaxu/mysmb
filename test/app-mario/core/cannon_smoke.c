#include "core/dispatcher.h"
#include "core/objects.h"
#include "core/oam/oam.h"
#include "core/enemy/movement.h"
#include "core/world/world.h"
#include <string.h>

static unsigned int calls[32], count, failed, killed;
static mysmb_u8 offscreen;
static void record(struct mysmb_game *game, mysmb_u8 slot, unsigned int id)
{
    if (game->ram[8U] != slot || count >= 32U) { failed=1U; return; }
    calls[count++]=id*10U+slot;
}
void mysmb_objects_erase_enemy(struct mysmb_game *game, mysmb_u8 slot)
{ record(game,slot,9U); ++killed; game->ram[0xfU+slot]=0U; }
void mysmb_objects_check_enemy_offscreen_bounds(struct mysmb_game *game, mysmb_u8 slot)
{ record(game,slot,1U); }
void mysmb_oam_get_enemy_offscreen_bits(struct mysmb_game *game, mysmb_u8 slot)
{ if(game->ram[8U]!=slot) failed=1U; calls[count++]=20U+slot; game->ram[0x3d1U]=offscreen; }
void mysmb_oam_relative_enemy_position(struct mysmb_game *game, mysmb_u8 slot)
{ record(game,slot,3U); }
void mysmb_objects_update_enemy_bounding_box(struct mysmb_game *game, mysmb_u8 slot)
{ record(game,slot,4U); }
mysmb_u8 mysmb_objects_check_normal_enemy_collision(struct mysmb_game *game,
    mysmb_u8 slot, mysmb_u8 preserve)
{ record(game,slot,5U); if(preserve!=1U) failed=1U; return 0U; }
mysmb_u8 mysmb_objects_draw_normal_enemy_graphics(struct mysmb_game *game, mysmb_u8 slot)
{ record(game,slot,6U); return 1U; }
void mysmb_enemy_move_downward(struct mysmb_game *game,mysmb_u8 slot,
    mysmb_u8 amount,mysmb_u8 maximum)
{ record(game,slot,7U); if(amount!=0x3dU||maximum!=3U) failed=1U; }
mysmb_u8 mysmb_world_move_enemy_horizontally(struct mysmb_game *game,mysmb_u8 slot)
{ record(game,slot,8U); return 0U; }

int main(void)
{
    static struct mysmb_game game;
    unsigned int i, mode, random, speed, page, x, expected_kill;
    unsigned int expected[8]={10U,20U,80U,20U,30U,40U,50U,60U};
    unsigned long enemy, player, difference, sum;
    /* The three slots share a selected cannon: spawn slot 2, then two
     * timer decrements. Spawned objects are not handled on that frame. */
    memset(&game,0,sizeof(game)); game.ram[0x74eU]=1U;
    game.ram[0x46bU]=2U;game.ram[0x471U]=0xf0U;game.ram[0x477U]=4U;
    mysmb_game_process_cannons(&game);
    if(count||game.ram[0x47dU]!=12U||game.ram[0x11U]!=1U||
       game.ram[0x18U]!=0x33U||game.ram[0x89U]!=0xf0U||
       game.ram[0xd1U]!=0xfcU||game.ram[0x49cU]!=9U||game.ram[8U]!=0U) return 1;
    /* Mask choice and no-spawn paths; occupied slots do not use random data. */
    for(mode=0U;mode<2U;++mode) for(random=0U;random<256U;++random) {
        memset(&game,0,sizeof(game));count=0U;
        game.ram[0x74eU]=1U;game.ram[0x6ccU]=(mysmb_u8)mode;
        game.ram[0xfU]=1U;game.ram[0x10U]=1U;game.ram[0x7aaU]=(mysmb_u8)random;
        for(i=0U;i<6U;++i) {game.ram[0x46bU+i]=1U;game.ram[0x47dU+i]=5U;}
        mysmb_game_process_cannons(&game);
        for(i=0U;i<6U;++i) if(game.ram[0x47dU+i]!=
            (i==(random%(mode ? 8U:16U)) ? 4U:5U)) return 2;
        if(count) return 3;
    }
    /* Carry-dependent close-distance rejection across page boundaries.
     * Compare modular 16-bit positions independently of the C byte chain. */
    for(page=0U;page<4U;++page) for(x=0U;x<256U;++x) {
        memset(&game,0,sizeof(game));count=0U;killed=0U;
        game.ram[0xfU]=1U;game.ram[0x6eU]=(mysmb_u8)page;
        game.ram[0x87U]=(mysmb_u8)x;game.ram[0x6dU]=1U;game.ram[0x86U]=0xf0U;
        enemy=page*256UL+x;player=496UL;difference=(enemy-player)&65535UL;
        speed=difference>=32768UL ? 0x18U:0xe8U;
        sum=((difference&255UL)+40UL+(enemy>=player ? 1UL:0UL))&255UL;
        expected_kill=sum<80UL;
        mysmb_game_handle_cannon_bullet(&game,0U);
        if(killed!=expected_kill||game.ram[0x58U]!=speed) return 4;
        if(!expected_kill && (count!=6U||game.ram[0x78aU]!=10U||
           game.ram[0x1eU]!=1U||game.ram[0xfeU]!=8U)) return 5;
    }
    /* Active cannon: bounds, offscreen, move, offscreen, relative, box,
     * player collision, graphics. Defeat adds gravity before horizontal. */
    for(mode=0U;mode<3U;++mode) {
        memset(&game,0,sizeof(game));count=0U;game.ram[0x74eU]=1U;
        game.ram[0xfU]=1U;game.ram[0x16U]=0x33U;
        game.ram[0x1eU]=mode==1U ? 0x20U:1U;
        game.ram[0x747U]=mode==2U ? 0xffU:0U;
        mysmb_game_process_cannons(&game);
        if(mode==0U) { if(count!=8U) return 6; for(i=0U;i<8U;++i) if(calls[i]!=expected[i]) return 7; }
        if(mode==1U && (count!=9U||calls[2]!=70U||calls[3]!=80U)) return 8;
        if(mode==2U && (count!=7U||calls[2]!=20U)) return 9;
    }
    return failed ? 10:0;
}
