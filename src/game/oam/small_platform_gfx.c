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

/* ROM $ed66 DrawSmallPlatform through $edde ExSPl. Byte INY offsets
 * wrap before dump calls; absolute-indexed sprite stores retain their base. */
void mysmb_objects_draw_small_platform(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 oam;
    mysmb_u8 coordinate;
    mysmb_u8 original_y;
    mysmb_u8 offscreen;

    oam = game->ram[MYSMB_SMALL_PLATFORM_SPRITE_OFFSET + slot];
    mysmb_oam_dump_six_sprites(game, 0x5bU, (mysmb_u8)(oam + 1U));
    mysmb_oam_dump_six_sprites(game, 2U, (mysmb_u8)(oam + 2U));
    coordinate = game->ram[MYSMB_SMALL_PLATFORM_REL_X];
    game->ram[0x0203U + oam] = coordinate;
    game->ram[0x020fU + oam] = coordinate;
    coordinate = (mysmb_u8)(coordinate + 8U);
    game->ram[0x0207U + oam] = coordinate;
    game->ram[0x0213U + oam] = coordinate;
    coordinate = (mysmb_u8)(coordinate + 8U);
    game->ram[0x020bU + oam] = coordinate;
    game->ram[0x0217U + oam] = coordinate;
    original_y = game->ram[MYSMB_SMALL_PLATFORM_ENEMY_Y + slot];
    coordinate = original_y < 0x20U ? 0xf8U : original_y;
    mysmb_oam_dump_three_sprites(game, coordinate, oam);
    coordinate = (mysmb_u8)(original_y + 0x80U);
    if (coordinate < 0x20U) coordinate = 0xf8U;
    game->ram[0x020cU + oam] = coordinate;
    game->ram[0x0210U + oam] = coordinate;
    game->ram[0x0214U + oam] = coordinate;
    offscreen = game->ram[MYSMB_SMALL_PLATFORM_OFFSCREEN];
    if ((offscreen & 8U) != 0U) {
        game->ram[0x0200U + oam] = 0xf8U;
        game->ram[0x020cU + oam] = 0xf8U;
    }
    if ((offscreen & 4U) != 0U) {
        game->ram[0x0204U + oam] = 0xf8U;
        game->ram[0x0210U + oam] = 0xf8U;
    }
    if ((offscreen & 2U) != 0U) {
        game->ram[0x0208U + oam] = 0xf8U;
        game->ram[0x0214U + oam] = 0xf8U;
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
    /* ROM DrawLargePlatform restores ObjectOffset after stacking relative X,
     * then loads Enemy_Y_Position,x for DumpFourSpr.  Relative Y belongs to
     * the positioning phase and is not this OAM producer's source. */
    mysmb_oam_stack_six_sprite_data(game, x, (mysmb_u8)(oam + 3U));
    y = game->ram[MYSMB_SMALL_PLATFORM_ENEMY_Y + slot];
    mysmb_oam_dump_four_sprites(game, y, oam);
    /* SetLast2Platform is reached by both paths.  The source leaves A as
     * Enemy_Y_Position for the ordinary path, and replaces it with $f8 for
     * castle/secondary-hard mode before storing both final rows. */
    if (game->ram[0x074eU] == 3U || game->ram[0x06ccU] != 0U)
        y = 0xf8U;
    /* ROM SetLast2Platform writes these directly, first +16 then +20.
     * It does not enter DumpTwoSpr or reverse their store order. */
    game->ram[(mysmb_u16)(0x0210U + oam)] = y;
    game->ram[(mysmb_u16)(0x0214U + oam)] = y;
    tile = game->ram[0x0743U] != 0U ? 0x75U : 0x5bU;
    mysmb_oam_dump_six_sprites(game, tile, (mysmb_u8)(oam + 1U));
    mysmb_oam_dump_six_sprites(game, 2U, (mysmb_u8)(oam + 2U));
    /* INX changes the source SprObject index from the enemy base ($6e/$87)
     * to its common-array index ($6d/$86).  It therefore still reads this
     * platform's Enemy_PageLoc and Enemy_X_Position, not slot + 1. */
    offscreen = mysmb_oam_get_x_offscreen_bits(game, (mysmb_u8)(slot + 1U),
        game->ram[0x006eU + slot],
        game->ram[MYSMB_SMALL_PLATFORM_ENEMY_X + slot]);

    for (column = 0U; column < 6U; ++column) {
        mysmb_u16 row_address;

        /* SChk2-SChk6 keep Y fixed and change the absolute store base. */
        row_address = (mysmb_u16)(0x0200U + oam + column * 4U);
        if ((offscreen & 0x80U) != 0U)
            game->ram[row_address] = 0xf8U;
        offscreen = (mysmb_u8)(offscreen << 1U);
    }
    if ((game->ram[MYSMB_SMALL_PLATFORM_OFFSCREEN] & 0x80U) != 0U)
        mysmb_oam_move_six_sprites_offscreen(game, oam);
}
