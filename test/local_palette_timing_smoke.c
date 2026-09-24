#include "game/game.h"
#include "game/area.h"
#include "smb1_local_rom.h"

int main(void)
{
    struct mysmb_game game;
    struct mysmb_input input;
    struct mysmb_frame frame;
    mysmb_u8 day_palette[0x20U];
    mysmb_u8 night_palette[0x20U];
    mysmb_u8 index;
    mysmb_u8 differs;
    mysmb_u8 count;
    mysmb_u8 saw_player_palette_handoff;

    mysmb_game_initialize(&game);
    mysmb_game_bind_area_source(&game, mysmb_local_prg, MYSMB_LOCAL_PRG_SIZE);
    input.buttons = MYSMB_BUTTON_START;
    mysmb_game_tick(&game, &input, &frame);
    input.buttons = 0U;
    saw_player_palette_handoff = 0U;
    for (count = 0U; count < 200U && game.ram[0x0772U] != 3U; ++count) {
        mysmb_game_tick(&game, &input, &frame);
        if (game.ram[0x0770U] == 1U && game.ram[0x073cU] == 11U &&
            game.ram[0x0300U] == 7U && game.ram[0x0301U] == 0x3fU &&
            game.ram[0x0302U] == 0x10U && game.ram[0x0304U] == 0x22U)
            saw_player_palette_handoff = 1U;
    }
    if (game.ram[0x0772U] != 3U) return 1;
    if (saw_player_palette_handoff == 0U) return 1;
    /* Static address-table streams and the player palette finish their NMI
     * transfers after ScreenRoutines hands off to SecondaryGameSetup. */
    for (count = 0U; count < 4U; ++count)
        mysmb_game_tick(&game, &input, &frame);
    if (game.palette[0U] != mysmb_local_prg[0x05d0U] ||
        game.palette[31U] != mysmb_local_prg[0x0ceaU]) return 1;

    if (mysmb_area_apply_special_palette(&game, 8U) == 0U) return 1;
    if (game.palette[4U] != mysmb_local_prg[0x0d4fU]) return 1;
    if (game.palette[0x15U] != mysmb_local_prg[0x0d50U]) return 1;
    if (game.palette[0x16U] != mysmb_local_prg[0x0d51U]) return 1;
    if (game.palette[0x17U] != mysmb_local_prg[0x0d52U]) return 1;
    if (mysmb_area_apply_special_palette(&game, 12U) != 0U) return 1;

    /* Address control is consumed at the next NMI boundary.  Exercise that
     * boundary in a fresh state so the active game parser cannot queue an
     * unrelated address control during the same gameplay frame. */
    mysmb_game_initialize(&game);
    mysmb_game_bind_area_source(&game, mysmb_local_prg, MYSMB_LOCAL_PRG_SIZE);
    input.buttons = 0U;
    game.palette[4U] = 0U;
    game.ram[0x0773U] = 8U;
    mysmb_game_tick(&game, &input, &frame);
    if (game.palette[4U] != mysmb_local_prg[0x0d4fU] ||
        game.palette[0x15U] != mysmb_local_prg[0x0d50U] ||
        game.palette[0x16U] != mysmb_local_prg[0x0d51U] ||
        game.palette[0x17U] != mysmb_local_prg[0x0d52U] ||
        game.ram[0x0773U] != 0U) return 1;
    if (mysmb_area_apply_special_palette(&game, 9U) == 0U) return 1;
    for (index = 0U; index < 0x20U; ++index)
        day_palette[index] = game.palette[index];
    if (mysmb_area_apply_special_palette(&game, 10U) == 0U) return 1;
    differs = 0U;
    for (index = 0U; index < 0x20U; ++index) {
        night_palette[index] = game.palette[index];
        if (night_palette[index] != day_palette[index]) differs = 1U;
    }
    if (differs == 0U || mysmb_area_apply_special_palette(&game, 11U) == 0U)
        return 1;
    differs = 0U;
    for (index = 0U; index < 0x20U; ++index) {
        if (game.palette[index] != night_palette[index]) differs = 1U;
    }
    return differs != 0U ? 0 : 1;
}
