#include "game/oam/oam.h"
#include "game/objects.h"

/* ROM DrawSmallPlatform.  The caller invokes this after the source-equivalent
 * collision phase and before MoveSmallPlatform changes the world position. */
enum {
    MYSMB_SMALL_PLATFORM_ENEMY_X = 0x0087U,
    MYSMB_SMALL_PLATFORM_ENEMY_Y = 0x00cfU,
    MYSMB_SMALL_PLATFORM_REL_X = 0x03aeU,
    MYSMB_SMALL_PLATFORM_REL_Y = 0x03b9U,
    MYSMB_SMALL_PLATFORM_OFFSCREEN = 0x03d1U,
    MYSMB_SMALL_PLATFORM_SPRITE_OFFSET = 0x06e5U
};

void mysmb_objects_draw_small_platform(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 oam;
    mysmb_u8 x;
    mysmb_u8 y;
    mysmb_u8 offscreen;
    mysmb_u8 column;

    oam = game->ram[MYSMB_SMALL_PLATFORM_SPRITE_OFFSET + slot];
    x = game->ram[MYSMB_SMALL_PLATFORM_REL_X];
    y = game->ram[MYSMB_SMALL_PLATFORM_ENEMY_Y + slot];
    offscreen = game->ram[MYSMB_SMALL_PLATFORM_OFFSCREEN];

    for (column = 0U; column < 3U; ++column) {
        mysmb_u8 row_offset;
        mysmb_u8 column_x;
        mysmb_u8 first_y;
        mysmb_u8 second_y;

        row_offset = (mysmb_u8)(oam + column * 4U);
        column_x = (mysmb_u8)(x + column * 8U);
        first_y = y < 0x20U ? 0xf8U : y;
        second_y = (mysmb_u8)(y + 0x80U);
        if (second_y < 0x20U) second_y = 0xf8U;
        if ((offscreen & (mysmb_u8)(8U >> column)) != 0U) {
            first_y = 0xf8U;
            second_y = 0xf8U;
        }
        game->ram[0x0200U + row_offset] = first_y;
        game->ram[0x0201U + row_offset] = 0x5bU;
        game->ram[0x0202U + row_offset] = 2U;
        game->ram[0x0203U + row_offset] = column_x;
        row_offset = (mysmb_u8)(oam + 12U + column * 4U);
        game->ram[0x0200U + row_offset] = second_y;
        game->ram[0x0201U + row_offset] = 0x5bU;
        game->ram[0x0202U + row_offset] = 2U;
        game->ram[0x0203U + row_offset] = column_x;
    }
}
void mysmb_objects_draw_large_platform(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 oam;
    mysmb_u8 x;
    mysmb_u8 y;
    mysmb_u8 tile;
    mysmb_u8 offscreen;
    mysmb_u8 column;

    oam = game->ram[MYSMB_SMALL_PLATFORM_SPRITE_OFFSET + slot];
    /* DrawLargePlatform saves the source OAM offset in $02 before changing
     * Y to the X-coordinate byte.  Later code may observe that ROM scratch. */
    game->ram[2U] = oam;
    x = game->ram[MYSMB_SMALL_PLATFORM_REL_X];
    y = game->ram[MYSMB_SMALL_PLATFORM_REL_Y];
    tile = game->ram[0x0743U] != 0U ? 0x75U : 0x5bU;
    mysmb_oam_stack_six_sprite_data(game, x, (mysmb_u8)(oam + 3U));
    mysmb_oam_dump_four_sprites(game, y, oam);
    /* SetLast2Platform is reached by both paths.  The source leaves A as
     * Enemy_Y_Position for the ordinary path, and replaces it with $f8 for
     * castle/secondary-hard mode before storing both final rows. */
    if (game->ram[0x074eU] == 3U || game->ram[0x06ccU] != 0U)
        y = 0xf8U;
    mysmb_oam_dump_two_sprites(game, y, (mysmb_u8)(oam + 16U));
    mysmb_oam_dump_six_sprites(game, tile, (mysmb_u8)(oam + 1U));
    mysmb_oam_dump_six_sprites(game, 2U, (mysmb_u8)(oam + 2U));
    /* INX changes the source SprObject index from the enemy base ($6e/$87)
     * to its common-array index ($6d/$86).  It therefore still reads this
     * platform's Enemy_PageLoc and Enemy_X_Position, not slot + 1. */
    offscreen = mysmb_oam_get_x_offscreen_bits(game, (mysmb_u8)(slot + 1U),
        game->ram[0x006eU + slot],
        game->ram[MYSMB_SMALL_PLATFORM_ENEMY_X + slot]);

    for (column = 0U; column < 6U; ++column) {
        mysmb_u8 row_offset;

        row_offset = (mysmb_u8)(oam + column * 4U);
        if ((offscreen & 0x80U) != 0U)
            game->ram[0x0200U + row_offset] = 0xf8U;
        offscreen = (mysmb_u8)(offscreen << 1U);
    }
    if ((game->ram[MYSMB_SMALL_PLATFORM_OFFSCREEN] & 0x80U) != 0U)
        mysmb_oam_move_six_sprites_offscreen(game, oam);
}
