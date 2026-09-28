#include "game/enemy/x_counter.h"
#include "game/world/world.h"

/* ROM $CB45 XMoveCntr_GreenPTroopa supplies A=$13 before falling through
 * XMoveCntr_Platform ($CB47). Primary=$A0, secondary=$58. */
void mysmb_enemy_x_counter_green(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_enemy_x_counter_platform(game, slot, 0x13U);
}

/* ROM $CB47-$CB65, including NoIncXM, IncPXM and DecSeXM. */
void mysmb_enemy_x_counter_platform(struct mysmb_game *game, mysmb_u8 slot,
                                    mysmb_u8 maximum)
{
    game->ram[1U] = maximum;
    if ((game->ram[9U] & 3U) != 0U) return;
    if ((game->ram[0x00a0U + slot] & 1U) == 0U) {
        if (game->ram[0x0058U + slot] == game->ram[1U])
            ++game->ram[0x00a0U + slot];
        else
            ++game->ram[0x0058U + slot];
    }
    else {
        if (game->ram[0x0058U + slot] == 0U)
            ++game->ram[0x00a0U + slot];
        else
            --game->ram[0x0058U + slot];
    }
}

/* ROM $CB66-$CB86 MoveWithXMCntrs / XMRight. Save the original counter
 * across the child, then store its returned A before restoring the counter. */
void mysmb_enemy_move_with_x_counters(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 secondary, direction;
    secondary = game->ram[0x0058U + slot];
    direction = 1U;
    if ((game->ram[0x00a0U + slot] & 2U) == 0U) {
        game->ram[0x0058U + slot] = (mysmb_u8)(0U - secondary);
        direction = 2U;
    }
    game->ram[0x0046U + slot] = direction;
    game->ram[0U] = mysmb_world_move_enemy_horizontally(game, slot);
    game->ram[0x0058U + slot] = secondary;
}
