#include "game/enemy/actor_slots.h"
#include "game/enemy/distance.h"
#include "game/enemy/movement.h"
#include "game/objects.h"

/* ROM $C9CE HammerThrowTmrData, $CA10 HammerBroJumpLData and
 * $C9D8-$CA76 ProcHammerBro through SetShim. Original fallthroughs share
 * the normal/defeated movement owners rather than copying their bodies. */
void mysmb_objects_step_hammer_bros_slot(struct mysmb_game *game, mysmb_u8 slot)
{
    static const mysmb_u8 throw_timers[2] = {0x30U, 0x1cU};
    static const mysmb_u8 jump_lengths[2] = {0x20U, 0x37U};
    mysmb_u8 speed, index, direction;

    if ((game->ram[0x001eU + slot] & 0x20U) != 0U) {
        mysmb_enemy_move_defeated(game, slot);
        return;
    }
    if (game->ram[0x003cU + slot] != 0U) {
        game->ram[0x003cU + slot]--;
        if ((game->ram[0x03d1U] & 0x0cU) == 0U) {
            if (game->ram[0x03a2U + slot] == 0U) {
                game->ram[0x03a2U + slot] = throw_timers[game->ram[0x06ccU]];
                if (mysmb_objects_spawn_hammer(game) != 0U) {
                    game->ram[0x001eU + slot] |= 8U;
                    goto move;
                }
            }
            game->ram[0x03a2U + slot]--;
        }
    }
    else if ((game->ram[0x001eU + slot] & 7U) != 1U) {
        game->ram[0U] = 0U;
        speed = 0xfaU;
        if ((game->ram[0x00cfU + slot] & 0x80U) == 0U) {
            speed = 0xfdU;
            ++game->ram[0U];
            if (game->ram[0x00cfU + slot] >= 0x70U) {
                --game->ram[0U];
                if ((game->ram[0x07a8U + slot] & 1U) == 0U) speed = 0xfaU;
            }
        }
        game->ram[0x00a0U + slot] = speed;
        game->ram[0x001eU + slot] |= 1U;
        index = (mysmb_u8)(game->ram[0U] & game->ram[0x07a9U + slot]);
        if (game->ram[0x06ccU] == 0U) index = 0U;
        game->ram[0x078aU + slot] = jump_lengths[index];
        game->ram[0x003cU + slot] = (mysmb_u8)(game->ram[0x07a8U + slot] | 0xc0U);
    }
move:
    game->ram[0x0058U + slot] = (game->ram[9U] & 0x40U) != 0U ? 0xfcU : 4U;
    direction = 1U;
    if ((mysmb_enemy_player_difference(game, slot) & 0x80U) == 0U) {
        ++direction;
        if (game->ram[0x0796U + slot] == 0U) game->ram[0x0058U + slot] = 0xf8U;
    }
    game->ram[0x0046U + slot] = direction;
    mysmb_enemy_move_normal(game, slot);
}
