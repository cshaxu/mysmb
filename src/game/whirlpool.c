#include "core/dispatcher.h"
#include "game/world/world.h"

/* ROM $b7b8 ProcessWhirlpools -> WhPull. The SBC page result is tested
 * by sign, not by an unsigned host-world comparison. Data slots descend. */
void mysmb_game_process_whirlpools(struct mysmb_game *game)
{
    mysmb_u8 slot, left, page, length, right, right_page, difference;
    mysmb_u8 player_x, player_page, center, center_page;
    mysmb_u16 sum;

    if (game->ram[0x074eU] != 0U) return;
    game->ram[0x047dU] = 0U;
    if (game->ram[0x0747U] != 0U) return;
    slot = 5U;
    while (slot != 0U) {
        --slot;
        left = game->ram[0x0471U + slot];
        length = game->ram[0x0477U + slot];
        sum = (mysmb_u16)left + length;
        right = (mysmb_u8)sum;
        game->ram[2U] = right;
        page = game->ram[0x046bU + slot];
        if (page == 0U) continue;
        right_page = (mysmb_u8)(page + (sum > 0xffU ? 1U : 0U));
        game->ram[1U] = right_page;
        player_x = game->ram[0x0086U];
        player_page = game->ram[0x006dU];
        difference = (mysmb_u8)(player_page - page -
            (player_x < left ? 1U : 0U));
        if ((difference & 0x80U) != 0U) continue;
        difference = (mysmb_u8)(right_page - player_page -
            (right < player_x ? 1U : 0U));
        if ((difference & 0x80U) != 0U) continue;

        /* WhirlpoolActivate: the center includes the low-byte carry. */
        game->ram[0U] = (mysmb_u8)(length >> 1U);
        sum = (mysmb_u16)left + game->ram[0U];
        center = (mysmb_u8)sum;
        game->ram[1U] = center;
        center_page = (mysmb_u8)(page + (sum > 0xffU ? 1U : 0U));
        game->ram[0U] = center_page;
        if ((game->ram[0x0009U] & 1U) != 0U) {
            difference = (mysmb_u8)(center_page - player_page -
                (center < player_x ? 1U : 0U));
            if ((difference & 0x80U) != 0U) {
                game->ram[0x0086U] = (mysmb_u8)(player_x - 1U);
                game->ram[0x006dU] = (mysmb_u8)(player_page -
                    (player_x == 0U ? 1U : 0U));
            }
            else if ((game->ram[0x0490U] & 1U) != 0U) {
                game->ram[0x0086U] = (mysmb_u8)(player_x + 1U);
                game->ram[0x006dU] = (mysmb_u8)(player_page +
                    (player_x == 0xffU ? 1U : 0U));
            }
        }
        /* WhPull tail-jumps with A=X=0, force=$10 and maximum speed=1.
         * X is a register argument; ObjectOffset is not written here. */
        game->ram[0U] = 0x10U;
        game->ram[0x047dU] = 1U;
        game->ram[2U] = 1U;
        mysmb_world_impose_gravity(game, 0U, 0U);
        return;
    }
}
