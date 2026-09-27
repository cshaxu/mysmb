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

    mysmb_game_initialize(&game);
    prg[0x40U] = 0x0eU;
    prg[0x41U] = 0x25U;
    prg[0x42U] = 0x0dU;
    prg[0x43U] = 0x01U;
    prg[0x44U] = 0x25U;
    prg[0x45U] = 0x02U;
    prg[0x46U] = 0xfdU;
    mysmb_game_bind_area_source(&game, prg, (mysmb_u16)sizeof(prg));
    game.ram[0x00e7U] = 0x40U;
    game.ram[0x00e8U] = 0x80U;
    game.ram[0x0725U] = 1U;
    game.ram[0x0728U] = 1U;
    game.ram[0x0730U] = 0xffU;
    game.ram[0x0731U] = 0xffU;
    game.ram[0x0732U] = 0xffU;

    /* Chk1Row14 reaches RdyDecode while backloading, so an earlier-page
     * attribute object still changes terrain and background scenery. The
     * next current-page object then takes InitRear and terminates preload. */
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x0727U] != 5U || game.ram[0x0742U] != 2U ||
        game.ram[0x0728U] != 0U || game.ram[0x072cU] != 4U) return 1;

    mysmb_game_initialize(&game);
    prg[0x40U] = 0x0dU;
    prg[0x41U] = 0x4bU;
    prg[0x42U] = 0xfdU;
    mysmb_game_bind_area_source(&game, prg, (mysmb_u16)sizeof(prg));
    game.ram[0x00e7U] = 0x40U;
    game.ram[0x00e8U] = 0x80U;
    game.ram[0x0730U] = 0xffU;
    game.ram[0x0731U] = 0xffU;
    game.ram[0x0732U] = 0xffU;
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x0745U] != 1U || game.ram[0x072cU] != 2U) return 1;

    mysmb_game_initialize(&game);
    prg[0x40U] = 0x25U;
    prg[0x41U] = 0x02U;
    prg[0x42U] = 0xfdU;
    mysmb_game_bind_area_source(&game, prg, (mysmb_u16)sizeof(prg));
    game.ram[0x00e7U] = 0x40U;
    game.ram[0x00e8U] = 0x80U;
    game.ram[0x0725U] = 0U;
    game.ram[0x0726U] = 2U;
    game.ram[0x0728U] = 1U;
    game.ram[0x0729U] = 1U;
    game.ram[0x0730U] = 0xffU;
    game.ram[0x0731U] = 0xffU;
    game.ram[0x0732U] = 0xffU;
    game.ram[0x0008U] = 2U;

    /* InitRear clears the preload flags and ObjectOffset, then returns before
     * BackColC can stage or advance the first current-page object. */
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x0728U] != 0U || game.ram[0x0729U] != 0U ||
        game.ram[0x0008U] != 0U || game.ram[0x072cU] != 0U ||
        game.ram[0x06a6U] != 0U) return 1;

    mysmb_game_initialize(&game);
    prg[0x40U] = 0x20U;
    prg[0x41U] = 0x02U;
    prg[0x42U] = 0x0dU;
    prg[0x43U] = 0x01U;
    prg[0x44U] = 0xfdU;
    prg[0x50U] = 0x25U;
    prg[0x51U] = 0x02U;
    mysmb_game_bind_area_source(&game, prg, (mysmb_u16)sizeof(prg));
    game.ram[0x00e7U] = 0x40U;
    game.ram[0x00e8U] = 0x80U;
    game.ram[0x0725U] = 1U;
    game.ram[0x072aU] = 0U;
    game.ram[0x072cU] = 0U;
    game.ram[0x072eU] = 0x10U;
    game.ram[0x0730U] = 0xffU;
    game.ram[0x0731U] = 1U;
    game.ram[0x0732U] = 0xffU;

    /* The slot-two behind-page skip must not make ProcessAreaData repeat
     * after slot zero handles the current page-control entry. The active
     * slot is therefore decremented once from one to zero, not to $ff. */
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x072aU] != 1U || game.ram[0x072cU] != 4U ||
        game.ram[0x0731U] != 0U || game.ram[0x0729U] != 0U) return 1;

    mysmb_game_initialize(&game);
    prg[0x40U] = 0x0eU;
    prg[0x41U] = 0x43U;
    prg[0x42U] = 0xfdU;
    mysmb_game_bind_area_source(&game, prg, (mysmb_u16)sizeof(prg));
    game.ram[0x00e7U] = 0x40U;
    game.ram[0x00e8U] = 0x80U;
    game.ram[0x0730U] = 0xffU;
    game.ram[0x0731U] = 0xffU;
    game.ram[0x0732U] = 0xffU;
    game.ram[0x0744U] = 7U;

    /* Alter2 passes values below four to SetFore without touching the
     * background-color control byte. */
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x0741U] != 3U || game.ram[0x0744U] != 7U) return 1;

    mysmb_game_initialize(&game);
    prg[0x40U] = 0x0eU;
    prg[0x41U] = 0x44U;
    prg[0x42U] = 0xfdU;
    mysmb_game_bind_area_source(&game, prg, (mysmb_u16)sizeof(prg));
    game.ram[0x00e7U] = 0x40U;
    game.ram[0x00e8U] = 0x80U;
    game.ram[0x0730U] = 0xffU;
    game.ram[0x0731U] = 0xffU;
    game.ram[0x0732U] = 0xffU;
    game.ram[0x0741U] = 3U;

    /* Alter2 stores values four through seven as BackgroundColorCtrl, then
     * reaches SetFore with A forced to zero. */
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x0744U] != 4U || game.ram[0x0741U] != 0U) return 1;
    return 0;
}
