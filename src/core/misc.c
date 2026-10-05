#include "core/objects.h"
#include "core/oam/oam.h"
#include "core/world/world.h"

/* ROM $BB96-$BBF7 MiscObjectsCore through MiscLoopBack. Every slot,
 * including empty slots, writes ObjectOffset before its state is read. */
void mysmb_objects_step_misc(struct mysmb_game *game)
{
    mysmb_u8 slot;
    mysmb_u8 state;
    mysmb_u8 retired;
    mysmb_u16 sum;

    slot = 8U;
    do {
        game->ram[8U] = slot;
        state = game->ram[0x002aU + slot];
        if (state != 0U) {
            if ((state & 0x80U) != 0U) {
                mysmb_objects_step_hammer(game, slot);
                /* DrawHammer returns the restored original misc X. */
                slot = game->ram[8U];
            }
            else {
                retired = 0U;
                if (state == 1U) {
                    game->ram[0U] = 0x50U;
                    game->ram[2U] = 6U;
                    game->ram[1U] = 3U;
                    mysmb_world_impose_gravity_spr_object(game,
                        (mysmb_u8)(slot + 0x0dU), 0x50U, 6U);
                    slot = game->ram[8U];
                    if (game->ram[0x00acU + slot] == 5U)
                        game->ram[0x002aU + slot]++;
                }
                else {
                    game->ram[0x002aU + slot]++;
                    sum = (mysmb_u16)game->ram[0x0093U + slot] + game->ram[0x0775U];
                    game->ram[0x0093U + slot] = (mysmb_u8)sum;
                    game->ram[0x007aU + slot] = (mysmb_u8)(
                        game->ram[0x007aU + slot] + (sum > 0xffU ? 1U : 0U));
                    if (game->ram[0x002aU + slot] == 0x30U) {
                        game->ram[0x002aU + slot] = 0U;
                        retired = 1U;
                    }
                }
                if (retired == 0U) {
                    mysmb_oam_relative_misc_position(game, slot);
                    mysmb_oam_get_misc_offscreen_bits(game, slot);
                    mysmb_objects_get_coin_bounding_box(game, slot);
                    mysmb_objects_draw_jump_coin(game, slot);
                    /* The original box and coin graphics restore misc X. */
                    slot = game->ram[8U];
                }
            }
        }
        slot = (mysmb_u8)(slot - 1U);
    } while (slot < 0x80U);
}
