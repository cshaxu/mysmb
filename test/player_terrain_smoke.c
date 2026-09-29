#include "game/player.h"
#include "game/player/terrain_children.h"
#include "game/objects.h"
#include <stdio.h>
#include <string.h>

static struct mysmb_game game;
static mysmb_u8 tiles[2], lows[2], probes, event, errors, expected_tile;

mysmb_u8 mysmb_world_query_player_probe(struct mysmb_game *g,
    mysmb_u8 *index, mysmb_u8 entry, struct mysmb_player_terrain *result)
{
    unsigned int n;
    (void)g;
    n = probes++;
    if (n > 1U || *index != n || entry != MYSMB_TERRAIN_FEET)
        { ++errors; return 0U; }
    ++*index;
    result->metatile = tiles[n];
    result->contact_low_nibble = lows[n];
    result->block_address_low = (mysmb_u8)(16U + n);
    result->block_row_offset = (mysmb_u8)(64U + n);
    return 1U;
}
mysmb_u8 mysmb_player_coin_metatile(struct mysmb_game *g, mysmb_u8 tile)
{
    if (tile != 0xc2U && tile != 0xc3U) return 0U;
    g->ram[0xfeU] = 1U;
    return 1U;
}
void mysmb_objects_collect_coin(struct mysmb_game *g,
    mysmb_u8 low, mysmb_u8 row)
{
    (void)g;
    if (low != 15U + probes || row != 63U + probes) ++errors;
    event = 1U;
}
mysmb_u8 mysmb_world_is_climbable(const struct mysmb_game *game, mysmb_u8 tile)
{ (void)game; return tile == 0x26U ? 1U : 0U; }
mysmb_u8 mysmb_world_is_solid(const struct mysmb_game *game, mysmb_u8 tile)
{
    static const mysmb_u8 upper[4] = { 0x10U, 0x61U, 0x88U, 0xc4U };
    (void)game; return tile >= upper[tile >> 6U] ? 1U : 0U;
}
void mysmb_player_handle_axe_metatile(struct mysmb_game *g,
    mysmb_u8 low, mysmb_u8 row)
{
    (void)g;
    if (probes != 2U || low != 17U || row != 65U) ++errors;
    event = 2U;
}
void mysmb_player_impede_move(struct mysmb_game *g, mysmb_u8 side)
{
    if (g->ram[0U] != side || side != 2U) ++errors;
    event = 3U;
}
void mysmb_player_land_jumpspring(struct mysmb_game *g, mysmb_u8 tile)
{
    if (tile != expected_tile || g->ram[0xceU] != 0x83U) ++errors;
    event = 4U;
}
mysmb_u8 mysmb_player_handle_vertical_pipe(struct mysmb_game *g,
    mysmb_u8 left, mysmb_u8 right)
{
    if (event != 4U || left != tiles[0] || right != tiles[1] ||
        g->ram[0xceU] != 0x80U || g->ram[0x9fU] != 1U ||
        g->ram[0x433U] != 0xa5U || g->ram[0x484U] != 0xa5U) ++errors;
    event = 5U;
    return 0U;
}
mysmb_u8 mysmb_player_handle_climbing(struct mysmb_game *g,
    const struct mysmb_player_terrain *terrain)
{ (void)g; (void)terrain; ++errors; return 0U; }
mysmb_u8 mysmb_objects_start_head_bump(struct mysmb_game *g,
    mysmb_u8 tile, mysmb_u8 low, mysmb_u8 row)
{ (void)g; (void)tile; (void)low; (void)row; ++errors; return 0U; }

static void reset(mysmb_u8 left, mysmb_u8 right)
{
    memset(&game, 0, sizeof(game));
    tiles[0] = left; tiles[1] = right;
    lows[0] = 9U; lows[1] = 3U;
    probes = event = 0U;
    game.ram[0xceU] = 0x83U;
    game.ram[0xb5U] = 1U;
    game.ram[0x9fU] = 1U;
    game.ram[0x433U] = game.ram[0x484U] = 0xa5U;
    game.ram[0x1dU] = 2U;
    game.ram[0x45U] = 2U;
    game.ram[0U] = game.ram[1U] = 0xa5U;
    expected_tile = left ? left : right;
}
int main(void)
{
    mysmb_u8 result;
    reset(0xc2U, 1U);
    result = mysmb_player_check_feet(&game);
    if (result != 2U || probes != 1U || event != 1U ||
        game.ram[0U] != 0xa5U || game.ram[1U] != 0xa5U) ++errors;
    reset(0U, 0xc3U);
    if (mysmb_player_check_feet(&game) != 2U || probes != 2U || event != 1U)
        ++errors;
    reset(0U, 0xc5U);
    if (mysmb_player_check_feet(&game) != 2U || event != 2U) ++errors;
    reset(0xc5U, 0U);
    if (mysmb_player_check_feet(&game) != 2U || event != 2U) ++errors;
    reset(1U, 0U);
    if (mysmb_player_check_feet(&game) != 1U || event != 5U ||
        game.ram[0x9fU] || game.ram[0x433U] || game.ram[0x484U] ||
        game.ram[0x1dU]) ++errors;
    reset(0U, 1U);
    if (mysmb_player_check_feet(&game) != 1U || event != 5U) ++errors;
    reset(1U, 0U); lows[1] = 5U;
    if (mysmb_player_check_feet(&game) != MYSMB_PLAYER_FEET_TERMINAL_IMPEDE ||
        event != 3U || game.ram[0xceU] != 0x83U) ++errors;
    reset(1U, 0U); game.ram[0x70eU] = 1U;
    if (mysmb_player_check_feet(&game) != 1U || event ||
        game.ram[0x1dU] || game.ram[0xceU] != 0x83U) ++errors;
    reset(0x5fU, 1U);
    if (mysmb_player_check_feet(&game) || event || game.ram[0x1dU] != 2U)
        ++errors;
    printf("terrain foot call-order errors=%u\n", (unsigned int)errors);
    return errors ? 1 : 0;
}

/* Isolated terrain caller contracts. The real pure leaves are verified
 * independently by the S4 original-ROM and native predicate checks. */
mysmb_u8 mysmb_player_invisible_metatile(mysmb_u8 tile)
{ return tile == 0x5fU || tile == 0x60U ? 1U : 0U; }
mysmb_u8 mysmb_player_jumpspring_metatile(mysmb_u8 tile)
{ return tile == 0x67U || tile == 0x68U ? 1U : 0U; }
