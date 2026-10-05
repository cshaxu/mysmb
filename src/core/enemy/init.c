#include "core/objects.h"
#include "core/enemy/init.h"
#include "core/enemy/init_targets.h"
#include "core/enemy/frenzy.h"

enum {
    MYSMB_ENEMY_FLAG = 0x000fU,
    MYSMB_ENEMY_ID = 0x0016U,
    MYSMB_ENEMY_STATE = 0x001eU,
    MYSMB_ENEMY_Y_HIGH = 0x00b6U,
    MYSMB_ENEMY_Y = 0x00cfU
};

/* ROM $C282-$C2EF: initializer target provenance for JumpEngine scratch.
 * These addresses are data only; native C implements every runtime path. */
static const mysmb_u16 mysmb_enemy_init_addresses[55] = {
    0xc30eU, 0xc30eU, 0xc30eU, 0xc31eU, 0xc2f0U, 0xc328U, 0xc2f1U, 0xc342U,
    0xc36bU, 0xc2f0U, 0xc375U, 0xc375U, 0xc2f7U, 0xc787U, 0xc7d1U, 0xc34aU,
    0xc33dU, 0xc385U, 0xc7a0U, 0xc2f0U, 0xc7a0U, 0xc7a0U, 0xc7a0U, 0xc7a0U,
    0xc7b8U, 0xc2f0U, 0xc2f0U, 0xc45cU, 0xc45cU, 0xc45cU, 0xc45cU, 0xc459U,
    0xc2f0U, 0xc2f0U, 0xc2f0U, 0xc2f0U, 0xc7dfU, 0xc812U, 0xc83fU, 0xc845U,
    0xc80bU, 0xc803U, 0xc80bU, 0xc84bU, 0xc857U, 0xc549U, 0xbc60U, 0xb91eU,
    0xc2f0U, 0xc2f0U, 0xc2f0U, 0xc2f0U, 0xc2f0U, 0xc307U, 0xc881U
};

/* Legacy convenience entry for supplied row/ID data. The original parser
 * owns position setup and InitEnemyObject separately in stream.c; this
 * helper is not the source InitEnemyObject implementation. */
void mysmb_enemy_initialize_loaded(struct mysmb_game *game, mysmb_u8 slot,
                                   mysmb_u8 row, mysmb_u8 id)
{
    game->ram[MYSMB_ENEMY_Y_HIGH + slot] = 1U;
    game->ram[MYSMB_ENEMY_Y + slot] = (mysmb_u8)(row << 4U);
    game->ram[MYSMB_ENEMY_ID + slot] = id;
    game->ram[MYSMB_ENEMY_FLAG + slot] = 1U;
    game->ram[MYSMB_ENEMY_STATE + slot] = 0U;
    mysmb_enemy_checkpoint_loaded(game, slot);
}
void mysmb_enemy_checkpoint_loaded(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 id;
    mysmb_u16 target;
    id = game->ram[MYSMB_ENEMY_ID + slot];
    /* ROM CheckpointEnemyID, not the stream parser, owns this add.  Group
     * and frenzy producers enter here after supplying their own Y value. */
    if (game->ram[MYSMB_ENEMY_ID + slot] < 0x15U) {
        game->ram[MYSMB_ENEMY_Y + slot] =
            (mysmb_u8)(game->ram[MYSMB_ENEMY_Y + slot] + 8U);
        game->ram[0x03d8U + slot] = 1U;
    }
    /* Preserve the original dispatch scratch before any target executes.
     * Only the declared vector IDs $00-$36 are certified by this binding. */
    if (id < 55U) {
        target = mysmb_enemy_init_addresses[id];
        game->ram[4U] = 0x81U;
        game->ram[5U] = 0xc2U;
        game->ram[6U] = (mysmb_u8)target;
        game->ram[7U] = (mysmb_u8)(target >> 8U);
        if (target == 0xc2f0U) return; /* NoInitCode. */
        if (target == 0xc881U) return; /* EndOfEnemyInitCode. */
    }
    /* InitEnemyRoutines entry $2E is the residual PwrUpJmp tail. */
    if (game->ram[MYSMB_ENEMY_ID + slot] == 0x2eU) {
        mysmb_objects_initialize_power_up(game);
        return;
    }
    if (id == 0x2fU) {
        /* JumpEngine leaves Y = (ID << 1) + 2 after reading target high.
         * Preserve that register input even for this residual table entry. */
        mysmb_objects_start_vine(game, slot, 0x60U);
        return;
    }
    /* Five vector aliases enter the same original frenzy dispatcher. */
    if (id == 0x12U || (id >= 0x14U && id <= 0x17U)) {
        mysmb_enemy_init_frenzy(game, slot);
        return;
    }
    if (game->ram[MYSMB_ENEMY_ID + slot] == 24U) {
        mysmb_enemy_end_frenzy(game, slot);
        return;
    }
    switch (id) {
    case 0U:
    case 1U:
    case 2U:
        mysmb_enemy_init_normal(game, slot);
        return;
    case 3U:
        mysmb_enemy_init_red_koopa(game, slot);
        return;
    case 6U:
        mysmb_enemy_init_goomba(game, slot);
        return;
    case 5U:
        mysmb_enemy_init_hammer_bro(game, slot);
        return;
    case 8U:
        mysmb_enemy_init_bullet_bill(game, slot);
        return;
    case 13U:
        mysmb_enemy_init_piranha_plant(game, slot);
        return;
    case 10U:
    case 11U:
        mysmb_enemy_init_cheep_cheep(game, slot);
        return;
    case 12U:
        mysmb_enemy_init_podoboo(game, slot);
        return;
    case 7U:
        mysmb_enemy_init_bloober(game, slot);
        return;
    case 14U:
        mysmb_enemy_init_jump_green_ptroopa(game, slot);
        return;
    case 15U:
        mysmb_enemy_init_red_ptroopa(game, slot);
        return;
    case 16U:
        mysmb_enemy_init_horizontal_fly_swim(game, slot);
        return;
    case 17U:
        mysmb_enemy_init_lakitu(game, slot);
        return;
    case 36U:
        mysmb_enemy_init_balance_platform(game, slot);
        return;
    case 37U:
        mysmb_enemy_init_vertical_platform(game, slot);
        return;
    case 38U:
        mysmb_enemy_init_large_lift_up(game, slot);
        return;
    case 39U:
        mysmb_enemy_init_large_lift_down(game, slot);
        return;
    case 40U:
    case 42U:
        mysmb_enemy_init_horizontal_platform(game, slot);
        return;
    case 41U:
        mysmb_enemy_init_drop_platform(game, slot);
        return;
    case 43U:
        mysmb_enemy_init_small_lift_up(game, slot);
        return;
    case 44U:
        mysmb_enemy_init_small_lift_down(game, slot);
        return;
    case 27U:
    case 28U:
    case 29U:
    case 30U:
        mysmb_enemy_init_firebar_entry(game, slot, 0U);
        return;
    case 31U:
        mysmb_enemy_init_firebar_entry(game, slot, 1U);
        return;
    case 45U:
        mysmb_enemy_init_bowser(game, slot);
        return;
    case 53U:
        mysmb_enemy_init_retainer(game, slot);
        return;
    default:
        break;
    }
    /* IDs outside the original vector retain the unverified legacy fallback. */
    mysmb_enemy_init_normal(game, slot);
}
