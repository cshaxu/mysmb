#include "core/world/world.h"
#include "core/oam/oam.h"
#include "core/objects.h"
#include "core/enemy/init_targets.h"

/* ROM $D736 BowserIdentities. Bound source bytes also preserve unmasked
 * indexing beyond the eight normal worlds. The fallback only supports the
 * legal table domain in resource-free primitive tests. */
static mysmb_u8 bowser_identity(const struct mysmb_game *game, mysmb_u8 world)
{
    static const mysmb_u8 identities[8] = {6U,0U,2U,18U,17U,7U,5U,45U};
    mysmb_u16 address;
    address = (mysmb_u16)(0x5736U + world);
    if (game->area_prg != 0 && address < game->area_prg_size)
        return game->area_prg[address];
    return world < 8U ? identities[world] : 0U;
}

/* ROM $D7BC EnemySmackScore through $D7C3 ExHCF. */
static void enemy_smack_score(struct mysmb_game *game, mysmb_u8 slot,
                              mysmb_u8 score)
{
    mysmb_objects_setup_floatey_from_relative(game, slot, score);
    game->ram[0x00ffU] = 8U;
}

/* ROM $D795 ShellOrBlockDefeat through GoombaPoints. The stun child
 * preserves X; its A input is the ID or the Piranha's adjusted Y. */
void mysmb_world_shell_or_block_defeat(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 value;
    mysmb_u8 score;
    value = game->ram[0x0016U + slot];
    if (value == 13U) {
        /* CMP #PiranhaPlant supplies carry=1 to ADC #$18. */
        value = (mysmb_u8)(game->ram[0x00cfU + slot] + 0x19U);
        game->ram[0x00cfU + slot] = value;
    }
    mysmb_world_stun_enemy(game, slot, value);
    game->ram[0x001eU + slot] =
        (mysmb_u8)((game->ram[0x001eU + slot] & 0x1fU) | 0x20U);
    value = game->ram[0x0016U + slot];
    score = value == 5U ? 6U : (value == 6U ? 1U : 2U);
    enemy_smack_score(game, slot, score);
}

/* ROM $D73E HandleEnemyFBallCol: relative position, live offset, duplicate
 * Bowser selection, immunity, health and source defeat/score tails. */
void mysmb_world_handle_fireball_enemy_hit(struct mysmb_game *game,
                                           mysmb_u8 slot)
{
    mysmb_u8 id;
    mysmb_u8 world;
    mysmb_oam_relative_enemy_position(game, slot);
    slot = game->ram[0x0001U];
    if ((game->ram[0x000fU + slot] & 0x80U) != 0U) {
        slot = (mysmb_u8)(game->ram[0x000fU + slot] & 0x0fU);
        if (game->ram[0x0016U + slot] != 45U) slot = game->ram[0x0001U];
    }
    id = game->ram[0x0016U + slot];
    if (id == 2U) return;
    if (id == 45U) {
        --game->ram[0x0483U];
        if (game->ram[0x0483U] != 0U) return;
        mysmb_enemy_init_vertical_state(game, slot);
        /* InitVStf preserves X and returns A=0. */
        game->ram[0x0058U + slot] = 0U;
        game->ram[0x06cbU] = 0U;
        game->ram[0x00a0U + slot] = 0xfeU;
        world = game->ram[0x075fU];
        game->ram[0x0016U + slot] = bowser_identity(game, world);
        game->ram[0x001eU + slot] = world < 3U ? 0x23U : 0x20U;
        game->ram[0x00feU] = 0x80U;
        enemy_smack_score(game, game->ram[0x0001U], 9U);
        return;
    }
    if (id == 8U || id == 12U || id >= 0x15U) return;
    mysmb_world_shell_or_block_defeat(game, slot);
}
