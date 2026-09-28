#include "game/player.h"
#include "game/oam/oam.h"
#include "game/world/world.h"

/* PlayerCtrlRoutine, original source lines 5583-5687 ($b0e9-$b1c6).
 * Each child retains its separate source owner and conformance status. */
void mysmb_player_latch_input(struct mysmb_game *game, mysmb_u8 buttons)
{
    if (game->ram[0x074eU] == 0U &&
        (game->ram[0x00b5U] != 1U || game->ram[0x00ceU] >= 0xd0U))
        buttons = 0U;
    game->ram[0x06fcU] = buttons;
    game->ram[0x000aU] = (mysmb_u8)(buttons & 0xc0U);
    game->ram[0x000cU] = (mysmb_u8)(buttons & 3U);
    game->ram[0x000bU] = (mysmb_u8)(buttons & 0x0cU);
    if ((game->ram[0x000bU] & 4U) != 0U &&
        game->ram[0x001dU] == 0U && game->ram[0x000cU] != 0U) {
        game->ram[0x000cU] = 0U;
        game->ram[0x000bU] = 0U;
    }
}

void mysmb_player_step(struct mysmb_game *game, mysmb_u8 buttons)
{
    mysmb_u8 threshold;
    mysmb_u8 death_route;
    mysmb_u8 high_y;
    if (game->ram[0x000eU] != 0x0bU)
        mysmb_player_latch_input(game, buttons);
    mysmb_player_movement_subs(game);
    game->ram[0x0499U] = game->ram[0x0754U] != 0U ? 1U :
        (game->ram[0x0714U] == 0U ? 0U : 2U);
    if (game->ram[0x0057U] != 0U)
        game->ram[0x0045U] = (game->ram[0x0057U] & 0x80U) != 0U ? 2U : 1U;
    mysmb_player_update_scroll(game);
    mysmb_oam_get_player_offscreen_bits(game);
    mysmb_oam_relative_player_position(game);
    mysmb_world_set_bounding_box(game, 0x04acU, game->ram[0x0499U],
                                game->ram[0x03adU], game->ram[0x03b8U]);
    mysmb_player_background_collision(game);
    if (game->ram[0x00ceU] >= 0x40U && game->ram[0x000eU] != 5U &&
        game->ram[0x000eU] != 7U && game->ram[0x000eU] >= 4U)
        game->ram[0x03c4U] &= 0xdfU;

    /* CMP/BMI tests bit 7 of the wrapped difference, not unsigned order. */
    high_y = game->ram[0x00b5U];
    if (((mysmb_u8)(high_y - 2U) & 0x80U) != 0U) return;
    game->ram[0x0723U] = 1U;
    threshold = 4U;
    death_route = 0U;
    if (game->ram[0x0759U] != 0U || game->ram[0x0743U] == 0U) {
        death_route = 1U;
        if (game->ram[0x000eU] != 0x0bU) {
            if (game->ram[0x0712U] == 0U) {
                game->ram[0x00fcU] = 1U;
                game->ram[0x0712U] = 1U;
            }
            threshold = 6U;
        }
    }
    if (((mysmb_u8)(high_y - threshold) & 0x80U) != 0U) return;
    if (death_route == 0U) {
        game->ram[0x0758U] = 0U;
        mysmb_player_set_entrance(game);
        ++game->ram[0x0752U];
    }
    else if (game->ram[0x07b1U] == 0U)
        game->ram[0x000eU] = 6U;
}
