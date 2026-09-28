#include "game/objects.h"
#include "game/enemy/movement.h"
#include "game/enemy/loop.h"
#include "game/enemy/init_targets.h"
#include "game/enemy/actor_slots.h"
#include "game/area.h"

enum {
    MYSMB_VRAM_BUFFER1 = 0x0300U,
    MYSMB_BOWSER_BODY_CONTROLS = 0x0363U,
    MYSMB_BOWSER_FEET_TIMER = 0x0364U,
    MYSMB_BOWSER_FRONT_SLOT = 0x0368U,
    MYSMB_BRIDGE_COLLAPSE_OFFSET = 0x0369U,
    MYSMB_EVENT_MUSIC = 0x00fcU,
    MYSMB_NOISE_SOUND = 0x00fdU,
    MYSMB_SQUARE2_SOUND = 0x00feU,
    MYSMB_ENEMY_ID = 0x0016U,
    MYSMB_ENEMY_STATE = 0x001eU,
    MYSMB_ENEMY_Y = 0x00cfU
};
/* ROM $D00F MoveD_Bowser: shared by bridge collapse and RunBowser. */
void mysmb_enemy_move_d_bowser(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_enemy_move_slow_vertically(game, slot);
    slot = game->ram[8U];
    mysmb_objects_draw_bowsers_slot(game, slot);
}

/* ROM $CFDD-$D060 BridgeCollapseData / BridgeCollapse. The first victory
 * task appends two two-tile blank rows to VRAM_Buffer1 every fourth call,
 * then lets the following NMI make that metatile removal visible. */
mysmb_u8 mysmb_objects_step_bridge_collapse(struct mysmb_game *game)
{
    static const mysmb_u8 collapse_low[15] = {
        0x1aU, 0x58U, 0x98U, 0x96U, 0x94U, 0x92U, 0x90U, 0x8eU,
        0x8cU, 0x8aU, 0x88U, 0x86U, 0x84U, 0x82U, 0x80U
    };
    mysmb_u8 slot;
    mysmb_u8 offset;
    mysmb_u8 low;
    mysmb_u8 state;
    mysmb_u8 index;

    slot = game->ram[MYSMB_BOWSER_FRONT_SLOT];
    if (game->ram[MYSMB_ENEMY_ID + slot] != 45U) goto set_mode;
    game->ram[8U] = slot;
    state = game->ram[MYSMB_ENEMY_STATE + slot];
    if (state != 0U) {
        if ((state & 0x40U) != 0U && game->ram[MYSMB_ENEMY_Y + slot] < 0xe0U) {
            mysmb_enemy_move_d_bowser(game, slot);
            return 0U;
        }
        goto set_mode;
    }
    game->ram[MYSMB_BOWSER_FEET_TIMER]--;
    if (game->ram[MYSMB_BOWSER_FEET_TIMER] != 0U) goto draw_bowser;
    game->ram[MYSMB_BOWSER_FEET_TIMER] = 4U;
    game->ram[MYSMB_BOWSER_BODY_CONTROLS] ^= 1U;
    game->ram[0x0005U] = 0x22U;
    index = game->ram[MYSMB_BRIDGE_COLLAPSE_OFFSET];
    low = collapse_low[index];
    game->ram[0x0004U] = low;
    offset = game->ram[MYSMB_VRAM_BUFFER1];
    mysmb_area_rem_bridge(game, 12U, (mysmb_u8)(offset + 1U), low, 0x22U);
    slot = game->ram[8U];
    /* RemBridge preserves Y, independent of the current RAM buffer offset. */
    mysmb_area_move_v_offset(game, (mysmb_u8)(offset + 1U));
    game->ram[MYSMB_SQUARE2_SOUND] = 8U;
    game->ram[MYSMB_NOISE_SOUND] = 1U;
    game->ram[MYSMB_BRIDGE_COLLAPSE_OFFSET]++;
    if (game->ram[MYSMB_BRIDGE_COLLAPSE_OFFSET] == 15U) {
        mysmb_enemy_init_vertical_state(game, slot);
        game->ram[MYSMB_ENEMY_STATE + slot] = 0x40U;
        game->ram[MYSMB_SQUARE2_SOUND] = 0x80U;
    }
draw_bowser:
    mysmb_objects_draw_bowsers_slot(game, slot);
    return 0U;
set_mode:
    game->ram[MYSMB_EVENT_MUSIC] = 0x80U;
    ++game->ram[0x0772U];
    mysmb_enemy_kill_all(game);
    return 1U;
}
