#include "game/oam/oam.h"
#include "game/objects.h"

enum {
    MYSMB_VINE_ENEMY_SPRITE_OFFSET = 0x06e5U,
    MYSMB_VINE_OBJECT_OFFSET = 0x039aU,
    MYSMB_VINE_START_Y = 0x039dU,
    MYSMB_VINE_RELATIVE_X = 0x03aeU,
    MYSMB_VINE_RELATIVE_Y = 0x03b9U
};

/* ROM $e433 VineYPosAdder and $e435 DrawVine through $e4ad return. Each active vine stack owns six consecutive
 * OAM entries.  The top stack has the distinct $e0 cap; the remaining leaves
 * are $e1 with the original alternating horizontal position and flip bit. */
void mysmb_objects_draw_vine(struct mysmb_game *game, mysmb_u8 vine_index)
{
    static const mysmb_u8 y_adder[2] = { 0U, 0x30U };
    mysmb_u8 sprite_slot;
    mysmb_u8 oam;
    mysmb_u8 x;
    mysmb_u8 y;
    mysmb_u8 row;

    game->ram[0U] = vine_index;
    sprite_slot = game->ram[MYSMB_VINE_OBJECT_OFFSET + vine_index];
    oam = game->ram[MYSMB_VINE_ENEMY_SPRITE_OFFSET + sprite_slot];
    game->ram[2U] = oam;
    y = (mysmb_u8)(game->ram[MYSMB_VINE_RELATIVE_Y] + y_adder[vine_index]);
    mysmb_oam_stack_six_sprite_data(game, y, oam);

    /* The absolute indexed stores precede the byte-indexed tile loop. */
    x = game->ram[MYSMB_VINE_RELATIVE_X];
    game->ram[0x0203U + oam] = x;
    game->ram[0x020bU + oam] = x;
    game->ram[0x0213U + oam] = x;
    x = (mysmb_u8)(x + 6U);
    game->ram[0x0207U + oam] = x;
    game->ram[0x020fU + oam] = x;
    game->ram[0x0217U + oam] = x;
    game->ram[0x0202U + oam] = 0x21U;
    game->ram[0x020aU + oam] = 0x21U;
    game->ram[0x0212U + oam] = 0x21U;
    game->ram[0x0206U + oam] = 0x61U;
    game->ram[0x020eU + oam] = 0x61U;
    game->ram[0x0216U + oam] = 0x61U;

    /* VineTL runs to completion before the cap and clipping phases. */
    for (row = 0U; row < 6U; ++row) {
        game->ram[0x0201U + (mysmb_u8)(oam + row * 4U)] = 0xe1U;
    }
    oam = game->ram[2U];
    if (game->ram[0U] == 0U) game->ram[0x0201U + oam] = 0xe0U;

    /* SkpVTop -> ChkFTop -> NextVSp is a separate six-sprite loop. */
    for (row = 0U; row < 6U; ++row) {
        mysmb_u8 row_oam;
        mysmb_u8 row_y;

        row_oam = (mysmb_u8)(oam + row * 4U);
        row_y = game->ram[(mysmb_u16)(0x0200U + row_oam)];
        if ((mysmb_u8)(game->ram[MYSMB_VINE_START_Y] - row_y) >= 0x64U) {
            game->ram[(mysmb_u16)(0x0200U + row_oam)] = 0xf8U;
        }
    }
    mysmb_text_observer_record(game, MYSMB_TEXT_OBSERVE_VINE,
        vine_index, sprite_slot, 0U, 1U, oam, 6U, 0U);
}

