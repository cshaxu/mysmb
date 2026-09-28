#include "game/dispatcher.h"
#include "game/world/world.h"
#include <string.h>

static unsigned int gravity_calls;
static unsigned int failed;

void mysmb_world_impose_gravity_spr_object(struct mysmb_game *game,
    mysmb_u8 offset, mysmb_u8 force, mysmb_u8 maximum)
{
    ++gravity_calls;
    if (offset != 0U || force != 0x10U || maximum != 1U ||
        game->ram[0x47dU] != 1U || game->ram[8U] != 0xa5U) failed = 1U;
}

int main(void)
{
    static struct mysmb_game game;
    static const unsigned int worlds[] = {0U, 1U, 255U, 256U, 511U,
        512U, 32767U, 32768U, 65280U, 65535U};
    static const unsigned int lengths[] = {0U, 1U, 2U, 15U, 128U, 255U};
    unsigned int a, b, c, phase, collision, area, timer, active;
    unsigned long left, right, center, position, expected;

    for (a=0U; a<10U; ++a) for (b=0U; b<10U; ++b)
    for (c=0U; c<6U; ++c) for (phase=0U; phase<2U; ++phase)
    for (collision=0U; collision<2U; ++collision)
    for (area=0U; area<2U; ++area) for (timer=0U; timer<2U; ++timer) {
        memset(&game, 0, sizeof(game));
        left=worlds[a]; position=worlds[b];
        right=(left+lengths[c]) & 65535UL;
        center=(left+lengths[c]/2U) & 65535UL;
        game.ram[0x46fU]=(mysmb_u8)(left>>8U);
        game.ram[0x475U]=(mysmb_u8)left;
        game.ram[0x47bU]=(mysmb_u8)lengths[c];
        game.ram[0x6dU]=(mysmb_u8)(position>>8U);
        game.ram[0x86U]=(mysmb_u8)position;
        game.ram[0x74eU]=(mysmb_u8)area;
        game.ram[0x747U]=(mysmb_u8)timer;
        game.ram[0x490U]=(mysmb_u8)collision;
        game.ram[9U]=(mysmb_u8)phase;
        game.ram[8U]=0xa5U; game.ram[0x47dU]=0x7fU;
        active=area==0U && timer==0U && left>=256UL &&
            ((position-left)&65535UL)<32768UL &&
            ((right-position)&65535UL)<32768UL;
        expected=position;
        if (active && phase) {
            if (((center-position)&65535UL)>=32768UL)
                expected=(position-1UL)&65535UL;
            else if (collision) expected=(position+1UL)&65535UL;
        }
        gravity_calls=0U; failed=0U;
        mysmb_game_process_whirlpools(&game);
        if (failed || gravity_calls!=active || game.ram[8U]!=0xa5U ||
            game.ram[0x47dU]!=(area ? 0x7fU : active) ||
            game.ram[0x86U]!=(mysmb_u8)expected ||
            game.ram[0x6dU]!=(mysmb_u8)(expected>>8U)) return 1;
    }
    /* Overlapping entries: highest slot wins, exactly one gravity call. */
    memset(&game,0,sizeof(game));
    game.ram[0x46fU]=1U; game.ram[0x475U]=0x80U; game.ram[0x47bU]=0x40U;
    game.ram[0x46bU]=1U; game.ram[0x471U]=0x70U; game.ram[0x477U]=0x20U;
    game.ram[0x6dU]=1U; game.ram[0x86U]=0x90U; game.ram[9U]=1U;
    game.ram[0x490U]=1U; game.ram[8U]=0xa5U;
    gravity_calls=0U; failed=0U;
    mysmb_game_process_whirlpools(&game);
    return failed || gravity_calls!=1U || game.ram[0x86U]!=0x91U;
}
