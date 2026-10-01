#include <string.h>
#include "game/area.h"

int main(void)
{
    static struct mysmb_game game;
    static mysmb_u8 prg[512];
    static const mysmb_u8 rows[3] = {0U, 5U, 11U};
    static const mysmb_u8 states[5] = {0xffU, 0U, 1U, 2U, 127U};
    unsigned int offset, which, slot, row_index, i;
    mysmb_u8 state, expected;
    for (offset = 0U; offset < 256U; ++offset)
    for (which = 0U; which < 5U; ++which)
    for (slot = 0U; slot < 3U; ++slot)
    for (row_index = 0U; row_index < 3U; ++row_index) {
        if (which == 0U && slot != 2U) continue;
        state = states[which];
        memset(prg, 0xfd, sizeof(prg));
        prg[0x40U + offset] = (mysmb_u8)(0x20U | rows[row_index]);
        prg[0x40U + (mysmb_u8)(offset + 1U)] = 0x23U;
        /* A distinct, valid wrong-page object makes the old read observable. */
        if (offset == 255U) prg[0x140U] = 0x69U;
        mysmb_game_initialize(&game);
        mysmb_game_bind_area_source(&game, prg, sizeof(prg));
        game.ram[0xe7U] = 0x40U;
        game.ram[0xe8U] = 0x80U;
        game.ram[0x726U] = 2U;
        game.ram[0x74eU] = 1U;
        game.ram[0x730U] = 0xffU;
        game.ram[0x731U] = 0xffU;
        game.ram[0x732U] = 0xffU;
        game.ram[0x730U + slot] = state;
        game.ram[0x72dU + slot] = (mysmb_u8)offset;
        game.ram[0x72cU] = which == 0U ? (mysmb_u8)offset :
            (mysmb_u8)(offset + 2U);
        if (!mysmb_area_process_object_state(&game)) return 1;
        expected = which == 0U ? 2U : (mysmb_u8)(state - 1U);
        if (game.ram[0x730U + slot] != expected) return 2;
        if (game.ram[0x72cU] != (mysmb_u8)(offset + 2U)) return 3;
        for (i = 0U; i < 13U; ++i)
            if (game.ram[0x6a1U + i] != (i == rows[row_index] ? 0x51U : 0U)) return 4;
        for (i = 0U; i < 3U; ++i)
            if (i != slot && game.ram[0x730U + i] != 0xffU) return 5;
    }
    /* The terminal byte is valid at the very end of a bound resource. */
    mysmb_game_initialize(&game);
    prg[0x40U] = 0xfdU;
    mysmb_game_bind_area_source(&game, prg, 0x41U);
    game.ram[0xe7U] = 0x40U;
    game.ram[0xe8U] = 0x80U;
    game.ram[0x730U] = 0xffU;
    game.ram[0x731U] = 0xffU;
    game.ram[0x732U] = 0xffU;
    if (!mysmb_area_process_object_state(&game)) return 6;
    /* A nonterminal requiring an absent second byte remains rejected. */
    prg[0x40U] = 0x25U;
    if (mysmb_area_process_object_state(&game)) return 7;
    /* InitRear stores ObjectOffset zero, returns through RdyDecode, then
     * ChkLength decrements resident slot zero before ProcessAreaData exits. */
    memset(prg, 0xfd, sizeof(prg));
    prg[0x40U] = 0x20U;
    prg[0x41U] = 0x03U;
    mysmb_game_initialize(&game);
    mysmb_game_bind_area_source(&game, prg, sizeof(prg));
    game.ram[0xe7U] = 0x40U;
    game.ram[0xe8U] = 0x80U;
    game.ram[0x0725U] = 0U;
    game.ram[0x0726U] = 2U;
    game.ram[0x072aU] = 0U;
    game.ram[0x072cU] = 0U;
    game.ram[0x0730U] = 2U;
    game.ram[0x0731U] = 0xffU;
    game.ram[0x0732U] = 0xffU;
    game.ram[0x0728U] = 1U;
    if (!mysmb_area_process_object_state(&game)) return 8;
    if (game.ram[0x0730U] != 1U) return 9;
    if (game.ram[0x0728U] != 0U) return 10;
    if (game.ram[0x072bU] != 0U) return 11;
    if (game.ram[0x072aU] != 0U) return 12;
    return 0;
}
