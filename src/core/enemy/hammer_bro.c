#include "core/enemy/actor_slots.h"
#include "core/enemy/distance.h"
#include "core/enemy/movement.h"
#include "core/objects.h"

/* ROM $C9CE HammerThrowTmrData, $CA10 HammerBroJumpLData and
 * $C9D8-$CA76 ProcHammerBro through SetShim. Original fallthroughs share
 * the normal/defeated movement owners rather than copying their bodies. */
static void hammer_bro_move(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 direction;
    game->ram[0x0058U + slot] = (game->ram[9U] & 0x40U) != 0U ? 0xfcU : 4U;
    direction = 1U;
    if ((mysmb_enemy_player_difference(game, slot) & 0x80U) == 0U) {
        ++direction;
        if (game->ram[0x0796U + slot] == 0U) game->ram[0x0058U + slot] = 0xf8U;
    }
    game->ram[0x0046U + slot] = direction;
    mysmb_enemy_move_normal(game, slot);
}

void mysmb_enemy_hammer_bro_set_jump(struct mysmb_game *game, mysmb_u8 slot,
                                     mysmb_u8 vertical_speed)
{
    static const mysmb_u8 jump_lengths[2] = {0x20U, 0x37U};
    mysmb_u8 index;

    game->ram[0x00a0U + slot] = vertical_speed;
    game->ram[0x001eU + slot] |= 1U;
    index = (mysmb_u8)(game->ram[0U] & game->ram[0x07a9U + slot]);
    if (game->ram[0x06ccU] == 0U) index = 0U;
    game->ram[0x078aU + slot] = jump_lengths[index];
    game->ram[0x003cU + slot] = (mysmb_u8)(game->ram[0x07a8U + slot] | 0xc0U);
    /* ROM SetHJ falls through MoveHammerBroXDir and MoveNormalEnemy. */
    hammer_bro_move(game, slot);
}

void mysmb_objects_step_hammer_bros_slot(struct mysmb_game *game, mysmb_u8 slot)
{
    static const mysmb_u8 throw_timers[2] = {0x30U, 0x1cU};
    mysmb_u8 speed;

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
        mysmb_enemy_hammer_bro_set_jump(game, slot, speed);
        return;
    }
move:
    hammer_bro_move(game, slot);
}
