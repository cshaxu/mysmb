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

/* ROM $D220-$D294 SetGfxF / DrawFlameLoop / offscreen tail. */
void mysmb_objects_draw_bowser_flame(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 offset;
    mysmb_u8 index;
    mysmb_u8 bits;
    mysmb_oam_relative_enemy_position(game,slot);
    slot = game->ram[8U];
    if (game->ram[MYSMB_FLAME_ENEMY_STATE + slot] != 0U) return;

    game->ram[0U] = 0x51U;
    game->ram[1U] = (game->ram[MYSMB_FLAME_FRAME_COUNTER] & 2U) != 0U ?
        0x82U : 0x02U;
    offset = game->ram[MYSMB_FLAME_ENEMY_SPRITE + slot];
    for (index = 0U; index < 3U; ++index) {
        mysmb_u8 entry;

        entry = (mysmb_u8)(offset + index * 4U);
        game->ram[0x0200U + entry] = game->ram[MYSMB_FLAME_ENEMY_REL_Y];
        game->ram[0x0201U + entry] = game->ram[0U];
        ++game->ram[0U];
        game->ram[0x0202U + entry] = game->ram[1U];
        game->ram[0x0203U + entry] = game->ram[MYSMB_FLAME_ENEMY_REL_X];
        game->ram[MYSMB_FLAME_ENEMY_REL_X] = (mysmb_u8)(game->ram[MYSMB_FLAME_ENEMY_REL_X]+8U);
    }
    slot = game->ram[8U];
    mysmb_oam_get_enemy_offscreen_bits(game, slot);
    bits = game->ram[MYSMB_FLAME_ENEMY_OFFSCREEN];
    slot = game->ram[8U];
    offset = game->ram[MYSMB_FLAME_ENEMY_SPRITE + slot];
    if ((bits & 1U) != 0U) game->ram[0x0200U + offset + 12U] = 0xf8U;
    if ((bits & 2U) != 0U) game->ram[0x0200U + offset + 8U] = 0xf8U;
    if ((bits & 4U) != 0U) game->ram[0x0200U + offset + 4U] = 0xf8U;
    if ((bits & 8U) != 0U) game->ram[0x0200U + offset] = 0xf8U;
    mysmb_text_observer_record(game,MYSMB_TEXT_OBSERVE_FLAME,
        game->ram[0x0016U+slot],slot,game->ram[1U],1U,offset,3U,0U);
}
