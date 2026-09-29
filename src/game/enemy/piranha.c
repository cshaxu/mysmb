#include "game/objects.h"
#include "game/enemy/distance.h"

/* ROM $D3B0-$D40F MovePiranhaPlant through PutinPipe. Dedicated plant
 * speed/move/endpoint arrays alias the original enemy physics storage. */
void mysmb_objects_step_piranha_plants_slot(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 page_difference;
    if (game->ram[0x001eU + slot] != 0U ||
        game->ram[0x078aU + slot] != 0U) goto put_in_pipe;
    if (game->ram[0x00a0U + slot] == 0U) {
        if ((game->ram[0x0058U + slot] & 0x80U) == 0U) {
            page_difference = mysmb_enemy_player_difference(game, slot);
            if ((page_difference & 0x80U) != 0U)
                game->ram[0U] = (mysmb_u8)(0U - game->ram[0U]);
            if (game->ram[0U] < 0x21U) goto put_in_pipe;
        }
        game->ram[0x0058U + slot] = (mysmb_u8)(0U - game->ram[0x0058U + slot]);
        ++game->ram[0x00a0U + slot];
    }
    game->ram[0U] = game->ram[
        ((game->ram[0x0058U + slot] & 0x80U) != 0U ? 0x0417U : 0x0434U) + slot];
    if ((game->ram[9U] & 1U) == 0U || game->ram[0x0747U] != 0U)
        goto put_in_pipe;
    game->ram[0x00cfU + slot] = (mysmb_u8)(game->ram[0x00cfU + slot] +
                                                   game->ram[0x0058U + slot]);
    if (game->ram[0x00cfU + slot] == game->ram[0U]) {
        game->ram[0x00a0U + slot] = 0U;
        game->ram[0x078aU + slot] = 0x40U;
    }
put_in_pipe:
    game->ram[0x03c5U + slot] = 0x20U;
}
