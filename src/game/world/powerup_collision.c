#include "game/objects.h"
#include "core/area.h"

/* ROM $D800-$D84C HandlePowerUpCollision through NoPUp. Children preserve
 * their own ownership. Erasure and the default score precede type/status
 * reads; 1UP overwrites only the score control after that common path. */
void mysmb_objects_collect_power_up(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 type;
    mysmb_objects_erase_enemy(game, slot);
    mysmb_objects_setup_floatey_from_relative(game, slot, 6U);
    game->ram[0x00feU] = 0x20U;
    type = game->ram[0x0039U];
    if (type >= 2U) {
        if (type == 3U) {
            game->ram[0x0110U + slot] = 0x0bU;
        }
        else {
            game->ram[0x079fU] = 0x23U;
            game->ram[0x00fbU] = 0x40U;
        }
        return;
    }
    if (game->ram[0x0756U] == 0U) {
        game->ram[0x0756U] = 1U;
        mysmb_objects_set_player_routine(game, 9U, 0U);
    }
    else if (game->ram[0x0756U] == 1U) {
        /* Source reloads X=ObjectOffset before and after GetPlayerColors;
         * neither child consumes incoming X, and SetPRout restores it. */
        game->ram[0x0756U] = 2U;
        (void)mysmb_area_queue_player_palette(game);
        mysmb_objects_set_player_routine(game, 12U, 0U);
    }
}
