#include "game/oam/oam.h"
#include "game/objects.h"

enum {
    MYSMB_FLAME_ENEMY_FLAG = 0x000fU,
    MYSMB_FLAME_ENEMY_ID = 0x0016U,
    MYSMB_FLAME_ENEMY_STATE = 0x001eU,
    MYSMB_FLAME_ENEMY_X = 0x0087U,
    MYSMB_FLAME_ENEMY_Y = 0x00cfU,
    MYSMB_FLAME_ENEMY_REL_X = 0x03aeU,
    MYSMB_FLAME_ENEMY_REL_Y = 0x03b9U,
    MYSMB_FLAME_ENEMY_OFFSCREEN = 0x03d1U,
    MYSMB_FLAME_ENEMY_SPRITE = 0x06e5U,
    MYSMB_FLAME_SCREEN_LEFT_X = 0x071cU,
    MYSMB_FLAME_FRAME_COUNTER = 0x0009U
};

/* ROM ProcBowserFlame / DrawFlameLoop ($d?-$d?): a normal-state Bowser
 * flame owns three consecutive OAM entries after its movement update. */
void mysmb_objects_draw_bowser_flame(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 offset;
    mysmb_u8 index;
    mysmb_u8 bits;
    mysmb_u8 attributes;
    mysmb_u8 relative_x;
    mysmb_u8 relative_y;

    if (slot >= 5U || game->ram[MYSMB_FLAME_ENEMY_FLAG + slot] == 0U ||
        game->ram[MYSMB_FLAME_ENEMY_ID + slot] != 21U) return;
    relative_x = (mysmb_u8)(game->ram[MYSMB_FLAME_ENEMY_X + slot] -
                             game->ram[MYSMB_FLAME_SCREEN_LEFT_X]);
    relative_y = game->ram[MYSMB_FLAME_ENEMY_Y + slot];
    game->ram[MYSMB_FLAME_ENEMY_REL_X] = relative_x;
    game->ram[MYSMB_FLAME_ENEMY_REL_Y] = relative_y;
    if (game->ram[MYSMB_FLAME_ENEMY_STATE + slot] != 0U) return;

    attributes = (game->ram[MYSMB_FLAME_FRAME_COUNTER] & 2U) != 0U ?
        0x82U : 0x02U;
    offset = game->ram[MYSMB_FLAME_ENEMY_SPRITE + slot];
    for (index = 0U; index < 3U; ++index) {
        mysmb_u8 entry;

        entry = (mysmb_u8)(offset + index * 4U);
        game->ram[0x0200U + entry] = relative_y;
        game->ram[0x0201U + entry] = (mysmb_u8)(0x51U + index);
        game->ram[0x0202U + entry] = attributes;
        game->ram[0x0203U + entry] = relative_x;
        relative_x = (mysmb_u8)(relative_x + 8U);
    }
    bits = mysmb_objects_get_enemy_x_offscreen_bits(game, slot);
    game->ram[MYSMB_FLAME_ENEMY_OFFSCREEN + slot] = bits;
    if ((bits & 1U) != 0U) game->ram[0x0200U + offset + 12U] = 0xf8U;
    if ((bits & 2U) != 0U) game->ram[0x0200U + offset + 8U] = 0xf8U;
    if ((bits & 4U) != 0U) game->ram[0x0200U + offset + 4U] = 0xf8U;
    if ((bits & 8U) != 0U) game->ram[0x0200U + offset] = 0xf8U;
}

