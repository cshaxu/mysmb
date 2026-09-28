#include "game/player.h"

/* ROM OnGroundStateSub/GndMove: children may change controller state. */
static void mysmb_player_ground_state(struct mysmb_game *game)
{
    mysmb_player_update_animation_speed(game, game->ram[0x06fcU]);
    if (game->ram[0x000cU] != 0U) game->ram[0x0033U] = game->ram[0x000cU];
    mysmb_player_impose_friction(game);
    game->ram[0x06ffU] = mysmb_player_move_horizontally(game);
}

/* ROM FallingSub/JumpSwimSub through ExitMov1. Falling enters LRAir
 * directly and does not execute the swimming animation/facing branch. */
static void mysmb_player_air_state(struct mysmb_game *game, mysmb_u8 falling)
{
    mysmb_u8 height;
    if (falling != 0U) {
        game->ram[0x0709U] = game->ram[0x070aU];
    }
    else {
        if ((game->ram[0x009fU] & 0x80U) == 0U)
            game->ram[0x0709U] = game->ram[0x070aU];
        else if ((game->ram[0x000aU] & game->ram[0x000dU] & 0x80U) == 0U) {
            height = (mysmb_u8)(game->ram[0x0708U] - game->ram[0x00ceU]);
            if (height >= game->ram[0x0706U])
                game->ram[0x0709U] = game->ram[0x070aU];
        }
        if (game->ram[0x0704U] != 0U) {
            mysmb_player_update_animation_speed(game, game->ram[0x06fcU]);
            if (game->ram[0x00ceU] < 0x14U) game->ram[0x0709U] = 0x18U;
            if (game->ram[0x000cU] != 0U) game->ram[0x0033U] = game->ram[0x000cU];
        }
    }
    if (game->ram[0x000cU] != 0U) mysmb_player_impose_friction(game);
    game->ram[0x06ffU] = mysmb_player_move_horizontally(game);
    if (game->ram[0x000eU] == 0x0bU) game->ram[0x0709U] = 0x28U;
    mysmb_player_move_vertically(game);
}

/* ROM PlayerMovementSubs/SetCrouch/ProcMove/MoveSubs/NoMoveSub.
 * Crouch is preserved for a large airborne player. Physics always runs;
 * freeze and state are then read from its returned state. */
void mysmb_player_movement_subs(struct mysmb_game *game)
{
    if (game->ram[0x0754U] != 0U) game->ram[0x0714U] = 0U;
    else if (game->ram[0x001dU] == 0U)
        game->ram[0x0714U] = (mysmb_u8)(game->ram[0x000bU] & 4U);
    mysmb_player_physics_sub(game);
    if (game->ram[0x070bU] != 0U) return;
    if (game->ram[0x001dU] != 3U) game->ram[0x0789U] = 0x18U;
    switch (game->ram[0x001dU]) {
    case 0U: mysmb_player_ground_state(game); break;
    case 1U: mysmb_player_air_state(game, 0U); break;
    case 2U: mysmb_player_air_state(game, 1U); break;
    case 3U: mysmb_player_climb(game); break;
    }
}
