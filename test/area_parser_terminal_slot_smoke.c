#include "game/area.h"
#include "game/game.h"

int main(void)
{
    struct mysmb_game game;
    static mysmb_u8 prg[0x100U];

    mysmb_game_initialize(&game);
    prg[0x40U] = 0xfdU;
    prg[0x42U] = 0x25U;
    prg[0x43U] = 0x02U;
    mysmb_game_bind_area_source(&game, prg, (mysmb_u16)sizeof(prg));
    game.ram[0x00e7U] = 0x40U;
    game.ram[0x00e8U] = 0x80U;
    game.ram[0x0725U] = 0U;
    game.ram[0x0726U] = 2U;
    game.ram[0x0732U] = 0U;
    game.ram[0x072fU] = 2U;

    /* DecodeAreaData's $fd return still falls through ChkLength and the
     * remaining ProcADLoop slots. */
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x06a6U] != 0x5fU || game.ram[0x0732U] != 0xffU) return 1;
    return 0;
}
