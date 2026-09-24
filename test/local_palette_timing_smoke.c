#include "game/game.h"
#include "smb1_local_rom.h"

int main(void)
{
    struct mysmb_game game;
    struct mysmb_input input;
    struct mysmb_frame frame;
    mysmb_u8 count;

    mysmb_game_initialize(&game);
    mysmb_game_bind_area_source(&game, mysmb_local_prg, MYSMB_LOCAL_PRG_SIZE);
    input.buttons = MYSMB_BUTTON_START;
    mysmb_game_tick(&game, &input, &frame);
    input.buttons = 0U;
    for (count = 0U; count < 200U && game.ram[0x0772U] != 3U; ++count)
        mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x0772U] != 3U) return 1;
    /* Static address-table streams and the player palette finish their NMI
     * transfers after ScreenRoutines hands off to SecondaryGameSetup. */
    for (count = 0U; count < 4U; ++count)
        mysmb_game_tick(&game, &input, &frame);
    return game.palette[0U] == mysmb_local_prg[0x05d0U] &&
        game.palette[31U] == mysmb_local_prg[0x0ceaU] ? 0 : 1;
}
