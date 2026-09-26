#include "game/game.h"
#include "game/objects.h"
/* PlayerCtrlRoutine has already run before source object collisions.  These
 * direct object tests therefore provide the control-0 primary box that the
 * ROM left in $04ac-$04af (relative X + 2/+14, Y + 8/+32). */
static void source_player_box(struct mysmb_game *game)
{
    mysmb_u8 x;

    x = (mysmb_u8)(game->ram[0x0086U] - game->ram[0x071cU]);
    game->ram[0x04acU] = (mysmb_u8)(x + 2U);
    game->ram[0x04adU] = (mysmb_u8)(game->ram[0x00ceU] + 8U);
    game->ram[0x04aeU] = (mysmb_u8)(x + 14U);
    game->ram[0x04afU] = (mysmb_u8)(game->ram[0x00ceU] + 32U);
}

int main(void)
{
    struct mysmb_game game;

    mysmb_game_initialize(&game);
    game.frame_number = 0UL;
    game.ram[0x000eU] = 8U;
    game.ram[0x006dU] = 0U;
    game.ram[0x0086U] = 0x40U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x60U;
    game.ram[0x03d0U] = 0U;
    game.ram[0x0499U] = 0U;
    game.ram[0x071aU] = 0U;
    game.ram[0x071cU] = 0U;
    game.ram[0x0756U] = 1U;
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 12U;
    game.ram[0x006eU] = 0U;
    game.ram[0x0087U] = 0x40U;
    game.ram[0x00b6U] = 1U;
    game.ram[0x00cfU] = 0x70U;
    game.ram[0x049aU] = 9U;
    source_player_box(&game);
    mysmb_objects_check_hazard_enemy_collision(&game);
    if (game.ram[0x0756U] != 0U || game.ram[0x079eU] != 8U ||
        game.ram[0x000eU] != 10U || game.ram[0x001dU] != 1U ||
        game.ram[0x0747U] != 0xffU || game.ram[0x0491U] != 1U) return 1;
    mysmb_game_initialize(&game);
    game.frame_number = 0UL;
    game.ram[0x000eU] = 8U;
    game.ram[0x006dU] = 0U;
    game.ram[0x0086U] = 0x40U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x60U;
    game.ram[0x03d0U] = 0U;
    game.ram[0x0499U] = 0U;
    game.ram[0x071aU] = 0U;
    game.ram[0x071cU] = 0U;
    game.ram[0x0756U] = 1U;
    game.ram[0x079eU] = 0U;
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 12U;
    game.ram[0x006eU] = 1U;
    game.ram[0x0087U] = 0x40U;
    game.ram[0x00b6U] = 1U;
    game.ram[0x00cfU] = 0x70U;
    game.ram[0x049aU] = 9U;
    source_player_box(&game);
    mysmb_objects_check_hazard_enemy_collision(&game);
    if (game.ram[0x0756U] != 1U || game.ram[0x079eU] != 0U || game.ram[0x0491U] != 0U) return 1;
    mysmb_game_initialize(&game);
    game.frame_number = 0UL;
    game.ram[0x000eU] = 8U;
    game.ram[0x006dU] = 0U;
    game.ram[0x0086U] = 0x40U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x60U;
    game.ram[0x03d0U] = 0U;
    game.ram[0x0499U] = 0U;
    game.ram[0x071aU] = 0U;
    game.ram[0x071cU] = 0U;
    game.ram[0x0756U] = 1U;
    game.ram[0x079eU] = 0U;
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 18U;
    game.ram[0x006eU] = 0U;
    game.ram[0x0087U] = 0x40U;
    game.ram[0x00b6U] = 1U;
    game.ram[0x00cfU] = 0x70U;
    game.ram[0x049aU] = 9U;
    source_player_box(&game);
    mysmb_objects_check_hazard_enemy_collision(&game);
    if (game.ram[0x0756U] != 0U || game.ram[0x079eU] != 8U ||
        game.ram[0x000eU] != 10U || game.ram[0x0491U] != 1U) return 1;
    game.ram[0x0756U] = 1U;
    game.ram[0x079eU] = 0U;
    game.ram[0x000eU] = 8U;
    game.ram[0x0747U] = 0U;
    game.ram[0x0491U] = 0U;
    game.ram[0x0016U] = 10U;
    source_player_box(&game);
    mysmb_objects_check_hazard_enemy_collision(&game);
    if (game.ram[0x0756U] != 0U || game.ram[0x079eU] != 8U ||
        game.ram[0x000eU] != 10U || game.ram[0x0491U] != 1U) return 1;
    return 0;
}
