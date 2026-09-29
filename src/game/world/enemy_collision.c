#include "game/world/world.h"
#include "game/objects.h"

/* ROM $DA25 SetBitsMask and $DA2C ClearBitsMask. Unmasked source indexing
 * uses the bound PRG; the resource-free fallback covers the seven entries. */
static mysmb_u8 collision_mask(const struct mysmb_game *game,
                              mysmb_u8 slot, mysmb_u8 clear)
{
    mysmb_u16 address;
    mysmb_u8 mask;
    address = (mysmb_u16)((clear != 0U ? 0x5a2cU : 0x5a25U) + slot);
    if (game->area_prg != 0 && address < game->area_prg_size)
        return game->area_prg[address];
    mask = slot < 7U ? (mysmb_u8)(0x80U >> slot) : 0U;
    return clear != 0U ? (mysmb_u8)(mask ^ 0xffU) : mask;
}

/* ROM $DB1C EnemyTurnAround through $DB44 ExTA. */
void mysmb_objects_turn_enemy(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 id;
    id = game->ram[0x0016U + slot];
    if (id == 13U || id == 17U || id == 5U) return;
    if (id != 18U && id != 14U && id >= 7U) return;
    game->ram[0x0058U + slot] = (mysmb_u8)(0U - game->ram[0x0058U + slot]);
    game->ram[0x0046U + slot] ^= 3U;
}

/* ROM $DAB4 ProcEnemyCollisions through $DB1C's turnaround tail.
 * Child calls preserve X, but RAM1 and ObjectOffset are live RAM. */
static void process_pair(struct mysmb_game *game, mysmb_u8 slot,
                         mysmb_u8 second)
{
    mysmb_u8 score;
    if (((game->ram[0x001eU + second] | game->ram[0x001eU + slot]) &
         0x20U) != 0U) return;
    if (game->ram[0x001eU + slot] >= 6U) {
        if (game->ram[0x0016U + slot] == 5U) return;
        if ((game->ram[0x001eU + second] & 0x80U) != 0U) {
            mysmb_objects_setup_floatey_from_relative(game, slot, 6U);
            mysmb_world_shell_or_block_defeat(game, slot);
            second = game->ram[1U];
        }
        mysmb_world_shell_or_block_defeat(game, second);
        slot = game->ram[8U];
        score = (mysmb_u8)(game->ram[0x0125U + slot] + 4U);
        slot = game->ram[1U];
        mysmb_objects_setup_floatey_from_relative(game, slot, score);
        slot = game->ram[8U];
        ++game->ram[0x0125U + slot];
        return;
    }
    if (game->ram[0x001eU + second] >= 6U) {
        if (game->ram[0x0016U + second] == 5U) return;
        mysmb_world_shell_or_block_defeat(game, slot);
        second = game->ram[1U];
        score = (mysmb_u8)(game->ram[0x0125U + second] + 4U);
        slot = game->ram[8U];
        mysmb_objects_setup_floatey_from_relative(game, slot, score);
        slot = game->ram[1U];
        ++game->ram[0x0125U + slot];
        return;
    }
    mysmb_objects_turn_enemy(game, second);
    mysmb_objects_turn_enemy(game, game->ram[8U]);
}

/* ROM $DA33 EnemiesCollision through $DAB1 ExitECRoutine.
 * The caller prepares boxes. Original X addresses the candidate box and Y
 * the current box; the stack preserves that Y across every child call. */
void mysmb_objects_step_enemy_collisions_current(struct mysmb_game *game,
                                                 mysmb_u8 slot)
{
    mysmb_u8 second;
    mysmb_u8 first_box;
    mysmb_u8 candidate_box;
    mysmb_u8 hit;
    mysmb_u8 mask;
    mysmb_u8 id;
    if ((game->ram[9U] & 1U) == 0U || game->ram[0x074eU] == 0U) return;
    id = game->ram[0x0016U + slot];
    if (id >= 0x15U || id == 17U || id == 13U ||
        game->ram[0x03d8U + slot] != 0U) return;
    first_box = mysmb_world_enemy_box_offset(game);
    second = (mysmb_u8)(slot - 1U);
    while ((second & 0x80U) == 0U) {
        game->ram[1U] = second;
        id = game->ram[0x0016U + second];
        if (game->ram[0x000fU + second] != 0U && id < 0x15U &&
            id != 17U && id != 13U && game->ram[0x03d8U + second] == 0U) {
            candidate_box = (mysmb_u8)(second * 4U + 4U);
            hit = mysmb_world_boxes_collide(game,
                (mysmb_u16)(0x04acU + candidate_box),
                (mysmb_u16)(0x04acU + first_box));
            slot = game->ram[8U];
            second = game->ram[1U];
            if (hit == 0U) {
                game->ram[0x0491U + second] &= collision_mask(game, slot, 1U);
            } else if (((game->ram[0x001eU + slot] |
                         game->ram[0x001eU + second]) & 0x80U) != 0U) {
                process_pair(game, slot, second);
            } else {
                mask = collision_mask(game, slot, 0U);
                if ((game->ram[0x0491U + second] & mask) == 0U) {
                    game->ram[0x0491U + second] |= mask;
                    process_pair(game, slot, second);
                }
            }
        }
        second = (mysmb_u8)(game->ram[1U] - 1U);
    }
}
