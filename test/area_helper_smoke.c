#include <string.h>
#include "game/area.h"

int main(void)
{
    static struct mysmb_game game;
    static mysmb_u8 prg[1024];
    unsigned int slot, offset, row, state, value;
    mysmb_u8 length, carry;
    mysmb_u16 base;
    mysmb_game_initialize(&game);
    mysmb_game_bind_area_source(&game, prg, sizeof(prg));
    /* A nonaligned pointer distinguishes Y wrap from effective-address wrap. */
    base = 0xf3U;
    game.ram[0xe7U] = 0xf3U;
    game.ram[0xe8U] = 0x80U;
    for (slot = 0U; slot < 3U; ++slot)
    for (offset = 0U; offset < 256U; ++offset)
    for (row = 0U; row < 16U; ++row) {
        memset(prg, 0xe5, sizeof(prg));
        game.ram[0x72dU + slot] = (mysmb_u8)offset;
        prg[base + offset] = (mysmb_u8)(0xb0U | row);
        prg[base + (mysmb_u8)(offset + 1U)] =
            (mysmb_u8)(0xa0U | ((row + 7U) & 15U));
        game.ram[7U] = 0xccU;
        length = mysmb_area_get_large_object_attributes(&game, (mysmb_u8)slot);
        if (game.ram[7U] != row || length != ((row + 7U) & 15U)) return 1;
    }
    for (slot = 0U; slot < 3U; ++slot)
    for (state = 0U; state < 256U; ++state)
    for (value = 0U; value < 256U; ++value) {
        memset(&game.ram[0x730U], 0x57, 3U);
        game.ram[0x730U + slot] = (mysmb_u8)state;
        game.ram[7U] = 0x62U;
        carry = mysmb_area_check_fixed_length(&game, (mysmb_u8)slot,
                                               (mysmb_u8)value);
        if (carry != (state >= 128U ? 1U : 0U)) return 2;
        if (game.ram[0x730U + slot] != (state >= 128U ? value : state)) return 3;
        if (game.ram[7U] != 0x62U ||
            game.ram[0x730U + ((slot + 1U) % 3U)] != 0x57U ||
            game.ram[0x730U + ((slot + 2U) % 3U)] != 0x57U) return 4;
    }
    for (slot = 0U; slot < 3U; ++slot)
    for (state = 0U; state < 256U; ++state)
    for (value = 0U; value < 16U; ++value) {
        game.ram[0x72dU + slot] = 255U;
        prg[base + 255U] = 0xbcU;
        prg[base] = (mysmb_u8)(0xe0U | value);
        game.ram[0x730U + slot] = (mysmb_u8)state;
        game.ram[7U] = 0xccU;
        length = 0xccU;
        carry = mysmb_area_check_large_length(&game, (mysmb_u8)slot, &length);
        if (carry != (state >= 128U ? 1U : 0U) ||
            game.ram[0x730U + slot] != (state >= 128U ? value : state)) return 5;
        if (length != value || game.ram[7U] != 12U) return 6;
    }
    for (value = 0U; value < 256U; ++value) {
        game.ram[0x726U] = (mysmb_u8)value;
        game.ram[7U] = (mysmb_u8)value;
        if (mysmb_area_object_x_position(&game) != (value % 16U) * 16U) return 7;
        if (mysmb_area_object_y_position(&game) != ((value + 2U) % 16U) * 16U) return 8;
        if (game.ram[0x726U] != value || game.ram[7U] != value) return 9;
    }
    return 0;
}
