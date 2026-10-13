#include "core/enemy/frenzy.h"
#include "core/enemy/distance.h"
#include "core/enemy/movement.h"
#include "core/world/world.h"

/* ROM $CF6C-$CFDC PlayerLakituDiff through ExMoveLak. The caller owns
 * adjustment bytes $01-$03; Spiny intentionally supplies a different set. */
mysmb_u8 mysmb_enemy_player_lakitu_difference(struct mysmb_game *game,
                                            mysmb_u8 slot)
{
    mysmb_u8 direction, index, page, value, pixels;
    direction = 0U;
    page = mysmb_enemy_player_difference(game, slot);
    if ((page & 0x80U) != 0U) {
        direction = 1U;
        game->ram[0U] = (mysmb_u8)(0U - game->ram[0U]);
    }
    if (game->ram[0U] >= 0x3cU) {
        game->ram[0U] = 0x3cU;
        if (game->ram[0x0016U + slot] == 17U &&
            direction != game->ram[0x00a0U + slot]) {
            if (game->ram[0x00a0U + slot] != 0U) {
                --game->ram[0x0058U + slot];
                if (game->ram[0x0058U + slot] != 0U)
                    return game->ram[0x0058U + slot];
            }
            game->ram[0x00a0U + slot] = direction;
        }
    }
    game->ram[0U] = (mysmb_u8)((game->ram[0U] & 0x3cU) >> 2U);
    index = 0U;
    if (game->ram[0x0057U] != 0U && game->ram[0x0775U] != 0U) {
        index = 1U;
        if (game->ram[0x0057U] >= 0x19U && game->ram[0x0775U] >= 2U)
            index = 2U;
        if (game->ram[0x0016U + slot] != 18U &&
            game->ram[0x00a0U + slot] == 0U) index = 0U;
    }
    value = game->ram[1U + index];
    pixels = game->ram[0U];
    do {
        --value;
        --pixels;
    } while ((pixels & 0x80U) == 0U);
    return value;
}

/* ROM $CF25 LakituDiffAdj and $CF28-$CF6B MoveLakitu. */
void mysmb_enemy_step_lakitus_slot(struct mysmb_game *game, mysmb_u8 slot)
{
    static const mysmb_u8 adjustment[3] = {0x15U, 0x30U, 0x40U};
    mysmb_u8 speed, index;
    if ((game->ram[0x001eU + slot] & 0x20U) != 0U) {
        mysmb_enemy_move_d_vertically(game, slot);
        return;
    }
    if (game->ram[0x001eU + slot] != 0U) {
        game->ram[0x00a0U + slot] = 0U;
        game->ram[0x06cbU] = 0U;
        speed = 0x10U;
    }
    else {
        game->ram[0x06cbU] = 18U;
        index = 3U;
        do {
            --index;
            game->ram[1U + index] = adjustment[index];
        } while (index != 0U);
        speed = mysmb_enemy_player_lakitu_difference(game, slot);
    }
    game->ram[0x0058U + slot] = speed;
    game->ram[0x0046U + slot] = 1U;
    if ((game->ram[0x00a0U + slot] & 1U) == 0U) {
        game->ram[0x0058U + slot] = (mysmb_u8)(0U - speed);
        game->ram[0x0046U + slot] = 2U;
    }
    (void)mysmb_world_move_enemy_horizontally(game, slot);
}
