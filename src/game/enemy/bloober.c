#include "game/enemy/actor_slots.h"
#include "game/enemy/distance.h"
#include "game/enemy/movement.h"

/* ROM $CBDF-$CC35 ProcSwimmingB. ChkNearPlayer inherits the carry from
 * the actor's direction path; AND/LDA and the float-state branch retain it. */
static void swim(struct mysmb_game *game, mysmb_u8 slot, mysmb_u8 carry)
{
    mysmb_u8 counter, force, near_y;
    counter = game->ram[0x00a0U + slot];
    if ((counter & 2U) != 0U) {
        if (game->ram[0x0796U + slot] == 0U) {
            near_y = (mysmb_u8)(game->ram[0x00cfU + slot] + 0x10U + carry);
            if (near_y >= game->ram[0x00ceU]) {
                game->ram[0x00a0U + slot] = 0U;
                return;
            }
        }
        if ((game->ram[9U] & 1U) == 0U) ++game->ram[0x00cfU + slot];
        return;
    }
    if ((game->ram[9U] & 7U) != 0U) return;
    force = game->ram[0x0434U + slot];
    if ((counter & 1U) == 0U) {
        force = (mysmb_u8)(force + 1U);
        game->ram[0x0434U + slot] = force;
        game->ram[0x0058U + slot] = force;
        if (force == 2U) ++game->ram[0x00a0U + slot];
    }
    else {
        force = (mysmb_u8)(force - 1U);
        game->ram[0x0434U + slot] = force;
        game->ram[0x0058U + slot] = force;
        if (force == 0U) {
            ++game->ram[0x00a0U + slot];
            game->ram[0x0796U + slot] = 2U;
        }
    }
}

/* ROM $CB87 BlooberBitmasks; $CB89-$CBDE MoveBloober and defeated tail.
 * The original movement JumpEngine ASL of ID 7 supplies entry carry zero. */
void mysmb_objects_step_bloobers_slot(struct mysmb_game *game, mysmb_u8 slot)
{
    static const mysmb_u8 masks[2] = {0x3fU, 3U};
    mysmb_u8 carry, direction, difference, y, x, speed, borrow;
    if ((game->ram[0x001eU + slot] & 0x20U) != 0U) {
        mysmb_enemy_move_slow_vertically(game, slot);
        return;
    }
    carry = 0U;
    if ((game->ram[0x07a8U + slot] & masks[game->ram[0x06ccU]]) == 0U) {
        if ((slot & 1U) != 0U) {
            carry = 1U;
            direction = game->ram[0x0045U];
        }
        else {
            /* PlayerEnemyDiff's final SBC carry uses the page operands
             * and the low-byte borrow, independently of its sign result. */
            borrow = game->ram[0x0087U + slot] < game->ram[0x0086U] ? 1U : 0U;
            carry = (unsigned int)game->ram[0x006eU + slot] >=
                (unsigned int)game->ram[0x006dU] + borrow ? 1U : 0U;
            difference = mysmb_enemy_player_difference(game, slot);
            direction = (difference & 0x80U) != 0U ? 1U : 2U;
        }
        game->ram[0x0046U + slot] = direction;
    }
    swim(game, slot, carry);
    y = (mysmb_u8)(game->ram[0x00cfU + slot] - game->ram[0x0434U + slot]);
    if (y >= 0x20U) game->ram[0x00cfU + slot] = y;
    x = game->ram[0x0087U + slot];
    speed = game->ram[0x0058U + slot];
    if (game->ram[0x0046U + slot] == 1U) {
        game->ram[0x0087U + slot] = (mysmb_u8)(x + speed);
        if ((unsigned int)x + speed > 255U) ++game->ram[0x006eU + slot];
    }
    else {
        game->ram[0x0087U + slot] = (mysmb_u8)(x - speed);
        if (x < speed) --game->ram[0x006eU + slot];
    }
}
