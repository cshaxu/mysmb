#include "game/world/world.h"

int main(void)
{
    struct mysmb_game game;

    /* ROM ImposeGravity: Y=$20, speed=$ff, dummy=$b0 and force=$50 preserve
     * both ADC carries: Y remains $20 and its high byte remains $01. */
    mysmb_game_initialize_memory(&game, 0U);
    game.ram[0x0416U + 7U] = 0xb0U;
    game.ram[0x0433U + 7U] = 0x50U;
    game.ram[0x009fU + 7U] = 0xffU;
    game.ram[0x00ceU + 7U] = 0x20U;
    game.ram[0x00b5U + 7U] = 1U;
    mysmb_world_impose_gravity_spr_object(&game, 7U, 0x50U, 3U);
    if (game.ram[0x0416U + 7U] != 0U || game.ram[0x00ceU + 7U] != 0x20U ||
        game.ram[0x00b5U + 7U] != 1U || game.ram[0x009fU + 7U] != 0xffU) return 1;

    /* ROM MoveObjectHorizontally carries X=$fe plus 4 pixels into page. */
    mysmb_game_initialize_memory(&game, 0U);
    game.ram[0x0057U + 7U] = 0x40U;
    game.ram[0x0400U + 7U] = 0U;
    game.ram[0x0086U + 7U] = 0xfeU;
    game.ram[0x006dU + 7U] = 1U;
    mysmb_world_move_spr_object_horizontally(&game, 7U);
    if (game.ram[0x0086U + 7U] != 2U || game.ram[0x006dU + 7U] != 2U) return 2;

    /* $22 + signed-$01 + carried fractional step produces $22 with an ADC
     * carry.  Page delta $ff plus that carry preserves page $03. */
    mysmb_game_initialize_memory(&game, 0U);
    game.ram[0x0057U + 1U] = 0xffU;
    game.ram[0x0400U + 1U] = 0x10U;
    game.ram[0x0086U + 1U] = 0x22U;
    game.ram[0x006dU + 1U] = 3U;
    mysmb_world_move_enemy_horizontally(&game, 0U);
    if (game.ram[0x0400U + 1U] != 0U || game.ram[0x0086U + 1U] != 0x22U ||
        game.ram[0x006dU + 1U] != 3U) return 3;
    return 0;
}
