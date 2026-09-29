#include "game/player/terrain_children.h"
#include "game/objects.h"
#include "game/area.h"
#include <stdio.h>
#include <string.h>

static struct mysmb_game game;
static mysmb_u16 erased;
static mysmb_u8 low_byte, row_byte, axe, tally;
static unsigned int calls, failures;
void mysmb_area_remove_coin_axe(struct mysmb_game *g,
    mysmb_u8 low, mysmb_u8 row)
{
    if (calls++ != 0U || low != low_byte || row != row_byte ||
        g->ram[erased] != 0U || g->ram[0x748U] != tally) ++failures;
    if (axe && (g->ram[0x772U] || g->ram[0x770U] != 2U ||
        g->ram[0x57U] != 0x18U)) ++failures;
    /* A child may overwrite the tally: INC must use its returned RAM. */
    g->ram[0x748U] = 0xffU;
}
void mysmb_objects_give_one_coin(struct mysmb_game *g)
{
    if (calls++ != 1U || axe || g->ram[0x748U] != 0U) ++failures;
}
int main(void)
{
    unsigned int high, low, row, entry, initial, cases;
    cases = 0U;
    for (high = 4U; high <= 6U; ++high)
    for (low = 0U; low < 2U; ++low)
    for (row = 0U; row < 2U; ++row)
    for (entry = 0U; entry < 2U; ++entry)
    for (initial = 0U; initial < 256U; ++initial) {
        memset(&game, 0xa5, sizeof(game));
        low_byte = low ? 0xf3U : 3U; row_byte = row ? 0xb0U : 0x10U;
        axe = (mysmb_u8)entry; tally = (mysmb_u8)initial;
        game.ram[6U] = low_byte; game.ram[7U] = (mysmb_u8)high;
        game.ram[2U] = row_byte; game.ram[0x748U] = tally;
        erased = (mysmb_u16)((high << 8U) + low_byte + row_byte);
        calls = 0U;
        if (axe) mysmb_player_handle_axe_metatile(&game, low_byte, row_byte);
        else mysmb_objects_collect_coin(&game, low_byte, row_byte);
        if (calls != (axe ? 1U : 2U) ||
            game.ram[erased - 1U] != 0xa5U || game.ram[erased + 1U] != 0xa5U)
            ++failures;
        ++cases;
    }
    printf("coin/axe chain: %u cases, %u errors\n", cases, failures);
    return failures ? 1 : 0;
}
