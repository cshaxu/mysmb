#include "game/objects.h"
#include "game/enemy/movement.h"

enum {
    MYSMB_VRAM_BUFFER1 = 0x0300U,
    MYSMB_VRAM_BUFFER1_DATA = 0x0301U,
    MYSMB_BOWSER_BODY_CONTROLS = 0x0363U,
    MYSMB_BOWSER_FEET_TIMER = 0x0364U,
    MYSMB_BOWSER_FRONT_SLOT = 0x0368U,
    MYSMB_BRIDGE_COLLAPSE_OFFSET = 0x0369U,
    MYSMB_EVENT_MUSIC = 0x00fcU,
    MYSMB_NOISE_SOUND = 0x00fdU,
    MYSMB_SQUARE2_SOUND = 0x00feU,
    MYSMB_ENEMY_FLAG = 0x000fU,
    MYSMB_ENEMY_ID = 0x0016U,
    MYSMB_ENEMY_STATE = 0x001eU,
    MYSMB_ENEMY_Y = 0x00cfU,
    MYSMB_ENEMY_Y_SPEED = 0x00a0U,
    MYSMB_ENEMY_Y_FORCE = 0x0434U,
    MYSMB_ENEMY_FRENZY_BUFFER = 0x06cbU
};
/* ROM $d8aa-$d91d BridgeCollapse.  The collapse owns the first victory-mode
 * task: every fourth call it appends two two-tile blank rows to VRAM_Buffer1,
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
    if (slot >= 5U || game->ram[MYSMB_ENEMY_ID + slot] != 45U) {
        game->ram[MYSMB_EVENT_MUSIC] = 0x80U;
        return 1U;
    }
    state = game->ram[MYSMB_ENEMY_STATE + slot];
    if (state != 0U) {
        if ((state & 0x40U) != 0U && game->ram[MYSMB_ENEMY_Y + slot] < 0xe0U) {
            mysmb_enemy_move_downward(game, slot, 0x0fU, 2U);
            return 0U;
        }
        game->ram[MYSMB_EVENT_MUSIC] = 0x80U;
        for (index = 0U; index < 5U; ++index) game->ram[MYSMB_ENEMY_FLAG + index] = 0U;
        game->ram[MYSMB_ENEMY_FRENZY_BUFFER] = 0U;
        return 1U;
    }
    game->ram[MYSMB_BOWSER_FEET_TIMER]--;
    if (game->ram[MYSMB_BOWSER_FEET_TIMER] != 0U) return 0U;
    index = game->ram[MYSMB_BRIDGE_COLLAPSE_OFFSET];
    if (index >= 15U || game->ram[MYSMB_VRAM_BUFFER1] > 0xf5U) return 0U;
    game->ram[MYSMB_BOWSER_FEET_TIMER] = 4U;
    game->ram[MYSMB_BOWSER_BODY_CONTROLS] ^= 1U;
    offset = game->ram[MYSMB_VRAM_BUFFER1];
    low = collapse_low[index];
    game->ram[MYSMB_VRAM_BUFFER1_DATA + offset] = 0x22U;
    game->ram[MYSMB_VRAM_BUFFER1_DATA + offset + 1U] = low;
    game->ram[MYSMB_VRAM_BUFFER1_DATA + offset + 2U] = 2U;
    game->ram[MYSMB_VRAM_BUFFER1_DATA + offset + 3U] = 0x24U;
    game->ram[MYSMB_VRAM_BUFFER1_DATA + offset + 4U] = 0x24U;
    game->ram[MYSMB_VRAM_BUFFER1_DATA + offset + 5U] = 0x22U;
    game->ram[MYSMB_VRAM_BUFFER1_DATA + offset + 6U] = (mysmb_u8)(low + 0x20U);
    game->ram[MYSMB_VRAM_BUFFER1_DATA + offset + 7U] = 2U;
    game->ram[MYSMB_VRAM_BUFFER1_DATA + offset + 8U] = 0x24U;
    game->ram[MYSMB_VRAM_BUFFER1_DATA + offset + 9U] = 0x24U;
    game->ram[MYSMB_VRAM_BUFFER1_DATA + offset + 10U] = 0U;
    game->ram[MYSMB_VRAM_BUFFER1] = (mysmb_u8)(offset + 10U);
    game->ram[MYSMB_SQUARE2_SOUND] = 8U;
    game->ram[MYSMB_NOISE_SOUND] = 1U;
    game->ram[MYSMB_BRIDGE_COLLAPSE_OFFSET]++;
    if (game->ram[MYSMB_BRIDGE_COLLAPSE_OFFSET] == 15U) {
        game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 0U;
        game->ram[MYSMB_ENEMY_Y_FORCE + slot] = 0U;
        game->ram[MYSMB_ENEMY_STATE + slot] = 0x40U;
        game->ram[MYSMB_SQUARE2_SOUND] = 0x80U;
    }
    return 0U;
}
