#ifndef MYSMB_TEST_TERRAIN_ENTRY_H
#define MYSMB_TEST_TERRAIN_ENTRY_H
#include "game/player.h"

/* Direct HeadChk/DoFootCheck/DoPlayerSideCheck tests supply GBBAdr's
 * cursor and ChkOnScr's collision mask. Production initializes them once
 * in PlayerBGCollision, before invoking the complete chain. */
static void mysmb_test_terrain_entry(struct mysmb_game *game)
{
    game->ram[0xebU] = game->ram[0x714U] || game->ram[0x754U] ?
        14U : (game->ram[0x704U] ? 7U : 0U);
    game->ram[0x490U] = 0xffU;
}
#endif
