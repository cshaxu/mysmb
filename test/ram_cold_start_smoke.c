#include "game/game.h"

int main(void)
{
    struct mysmb_game game;

    mysmb_game_initialize(&game);
    /* InitializeMemory starts at page seven and deliberately skips page-one
     * bytes $60-$ff; the owner-local cold RAM supplies zero there. */
    if (game.ram[0x0160U] != 0U || game.ram[0x01ffU] != 0U) return 1;
    /* The OAM offscreen pass still owns its Y coordinates after cold boot. */
    if (game.ram[0x0200U] != 0xf8U || game.ram[0x02fcU] != 0xf8U) return 2;
    return 0;
}