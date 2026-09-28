#include "game/dispatcher.h"
#include "game/objects.h"
#include "game/oam/oam.h"
#include "game/enemy/movement.h"
#include "game/world/world.h"

/* ROM $ba33 BulletBillHandler. Child collision/graphics implementations
 * retain their separate fidelity obligations; this owner supplies their
 * original current-slot sequence and does not manufacture bounding boxes. */
void mysmb_game_handle_cannon_bullet(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 low, borrow, high, carry, direction;
    mysmb_u16 subtrahend;

    if (game->ram[0x0747U] == 0U) {
        if (game->ram[0x001eU + slot] == 0U) {
            if ((game->ram[0x03d1U] & 0x0cU) == 0x0cU) {
                mysmb_objects_erase_enemy(game, slot);
                return;
            }
            /* PlayerEnemyDiff leaves its low difference and page SBC carry.
             * LDY/INY/DEY/LDA do not replace that carry before ADC #$28. */
            low = (mysmb_u8)(game->ram[0x0087U + slot] - game->ram[0x0086U]);
            borrow = game->ram[0x0087U + slot] < game->ram[0x0086U] ? 1U : 0U;
            subtrahend = (mysmb_u16)game->ram[0x006dU] + borrow;
            high = (mysmb_u8)(game->ram[0x006eU + slot] - subtrahend);
            carry = game->ram[0x006eU + slot] >= subtrahend ? 1U : 0U;
            direction = (high & 0x80U) != 0U ? 1U : 2U;
            game->ram[0x0046U + slot] = direction;
            /* BulletBillXSpdData at $ba31: right +$18, left -$18. */
            game->ram[0x0058U + slot] = direction == 1U ? 0x18U : 0xe8U;
            if ((mysmb_u8)(low + 0x28U + carry) < 0x50U) {
                mysmb_objects_erase_enemy(game, slot);
                return;
            }
            game->ram[0x001eU + slot] = 1U;
            game->ram[0x078aU + slot] = 0x0aU;
            game->ram[0x00feU] = 8U;
        }
        if ((game->ram[0x001eU + slot] & 0x20U) != 0U)
            mysmb_enemy_move_downward(game, slot, 0x3dU, 3U);
        mysmb_world_move_enemy_horizontally(game, slot);
    }
    game->ram[0x03d1U] = mysmb_objects_get_enemy_offscreen_bits(game, slot);
    mysmb_oam_relative_enemy_position(game, slot);
    mysmb_objects_update_enemy_bounding_box(game, slot);
    (void)mysmb_objects_check_normal_enemy_collision(game, slot, 1U);
    mysmb_objects_draw_bullet_bill(game, slot);
}

/* ROM $b9bc ProcessCannons through ExCannon. CannonBitmasks ($b9ba)
 * selects four random bits normally, three in secondary hard mode. */
void mysmb_game_process_cannons(struct mysmb_game *game)
{
    mysmb_u8 slot, cannon, mask;

    if (game->ram[0x074eU] == 0U) return;
    slot = 3U;
    while (slot != 0U) {
        --slot;
        game->ram[0x0008U] = slot;
        if (game->ram[0x000fU + slot] == 0U) {
            mask = game->ram[0x06ccU] == 0U ? 0x0fU : 7U;
            cannon = (mysmb_u8)(game->ram[0x07a8U + slot] & mask);
            if (cannon < 6U && game->ram[0x046bU + cannon] != 0U) {
                if (game->ram[0x047dU + cannon] != 0U) {
                    /* CMP #6 leaves carry clear: SBC #0 decrements even
                     * when TimerControl blocks the later spawn branch. */
                    --game->ram[0x047dU + cannon];
                }
                else if (game->ram[0x0747U] == 0U) {
                    game->ram[0x047dU + cannon] = 0x0eU;
                    game->ram[0x006eU + slot] = game->ram[0x046bU + cannon];
                    game->ram[0x0087U + slot] = game->ram[0x0471U + cannon];
                    game->ram[0x00cfU + slot] = (mysmb_u8)(game->ram[0x0477U + cannon] - 8U);
                    game->ram[0x00b6U + slot] = 1U;
                    game->ram[0x000fU + slot] = 1U;
                    game->ram[0x001eU + slot] = 0U;
                    game->ram[0x049aU + slot] = 9U;
                    game->ram[0x0016U + slot] = 0x33U;
                    continue;
                }
            }
        }
        if (game->ram[0x0016U + slot] != 0x33U) continue;
        mysmb_objects_check_enemy_offscreen_bounds(game, slot);
        if (game->ram[0x000fU + slot] == 0U) continue;
        game->ram[0x03d1U] = mysmb_objects_get_enemy_offscreen_bits(game, slot);
        mysmb_game_handle_cannon_bullet(game, slot);
    }
}
