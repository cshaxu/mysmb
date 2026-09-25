#include "game/objects.h"

enum {
    MYSMB_FIREBAR_ENEMY_SPRITE_OFFSET = 0x06e5U,
    MYSMB_FIREBAR_ALT_SPRITE_OFFSET = 0x06ecU,
    MYSMB_FIREBAR_SPRITE_OFFSET_CONTROL = 0x03eeU,
    MYSMB_FIREBAR_FRAME_COUNTER = 0x0009U
};

void mysmb_objects_draw_firebar_ball(struct mysmb_game *game, mysmb_u8 slot,
                                     mysmb_u8 ball, mysmb_u8 x, mysmb_u8 y,
                                     mysmb_u8 anchor_y)
{
    mysmb_u8 base;
    mysmb_u8 offset;
    mysmb_u8 tile;
    mysmb_u8 attribute;

    base = game->ram[MYSMB_FIREBAR_ENEMY_SPRITE_OFFSET + slot];
    if (ball >= 5U) base = game->ram[MYSMB_FIREBAR_ALT_SPRITE_OFFSET +
        game->ram[MYSMB_FIREBAR_SPRITE_OFFSET_CONTROL]];
    offset = (mysmb_u8)(base + (ball < 5U ? (ball + 1U) * 4U :
                                               (ball - 5U) * 4U));
    tile = (mysmb_u8)(0x64U ^ ((game->ram[MYSMB_FIREBAR_FRAME_COUNTER] >> 2U) & 1U));
    attribute = (mysmb_u8)(2U | (((game->ram[MYSMB_FIREBAR_FRAME_COUNTER] >> 3U) & 1U) != 0U ? 0xc0U : 0U));
    game->ram[(mysmb_u16)(0x0200U + offset)] =
        (mysmb_u8)((x >= 0xf0U || anchor_y == 0xf8U) ? 0xf8U : y);
    game->ram[(mysmb_u16)(0x0201U + offset)] = tile;
    game->ram[(mysmb_u16)(0x0202U + offset)] = attribute;
    game->ram[(mysmb_u16)(0x0203U + offset)] = x;
}
