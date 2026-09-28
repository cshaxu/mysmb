#include "game/objects.h"
#include "game/world/world.h"
#include "game/oam/oam.h"

/* ROM $BE70-$BED3 BlockObjectsCore through UpdSte. State is the original
 * stacked low nibble. Child entries use their declared array offsets;
 * relative/offscreen/draw returns restore X from ObjectOffset. */
void mysmb_objects_step_block(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 state;

    state = game->ram[0x0026U + slot];
    if (state != 0U) {
        state = (mysmb_u8)(state & 0x0fU);
        if (state == 1U) {
            mysmb_world_impose_gravity_block(game, slot);
            slot = game->ram[8U];
            mysmb_oam_relative_block_position(game, slot);
            slot = game->ram[8U];
            mysmb_oam_get_block_offscreen_bits(game, slot);
            slot = game->ram[8U];
            mysmb_objects_draw_bouncing_block(game, slot);
            slot = game->ram[8U];
            if ((game->ram[0x00d7U + slot] & 0x0fU) < 5U) {
                game->ram[0x03ecU + slot] = 1U;
                state = 0U;
            }
        } else {
            mysmb_world_impose_gravity_block(game, slot);
            mysmb_world_move_spr_object_horizontally(game,
                (mysmb_u8)(slot + 9U));
            mysmb_world_impose_gravity_block(game, (mysmb_u8)(slot + 2U));
            mysmb_world_move_spr_object_horizontally(game,
                (mysmb_u8)(slot + 11U));
            slot = game->ram[8U];
            mysmb_oam_relative_block_position(game, slot);
            slot = game->ram[8U];
            mysmb_oam_get_block_offscreen_bits(game, slot);
            slot = game->ram[8U];
            mysmb_objects_draw_brick_chunks(game, slot);
            slot = game->ram[8U];
            /* High-Y zero preserves the saved state; the source comment
             * says kill, but BEQ goes directly to UpdSte without LDA #0. */
            if (game->ram[0x00beU + slot] != 0U) {
                if (game->ram[0x00d9U + slot] > 0xf0U)
                    game->ram[0x00d9U + slot] = 0xf0U;
                if (game->ram[0x00d7U + slot] >= 0xf0U) state = 0U;
            }
        }
    }
    game->ram[0x0026U + slot] = state;
}
