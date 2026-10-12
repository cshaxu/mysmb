#include "core/area.h"
#include "core/enemy/stream.h"
#include "core/game.h"
#include "core/objects.h"
#include "core/world/world.h"
#include <string.h>

/* Engine dispatch receives player bounds, screen edges and object controls.
 * Direct actor tests supply these inputs before each frame. */
static void prepare_contact(struct mysmb_game *game)
{
    game->ram[8U] = 0U;
    game->ram[0xeU] = 8U;
    game->ram[0x71aU] = 0U; game->ram[0x71cU] = 0U;
    game->ram[0x71bU] = 0U; game->ram[0x71dU] = 0xffU;
    game->ram[0x49aU] = 6U; game->ram[0x49bU] = 6U;
    mysmb_world_set_bounding_box(game, 0x4acU, 0U,
        game->ram[0x86U], game->ram[0xceU]);
}

int main(void)
{
    struct mysmb_game game;
    struct mysmb_area_source source;
    mysmb_u8 lift_data[2] = { 0U, 38U };

    /* InitLargeLiftUp uses the signed vertical pair, +12 positioning and
     * the non-castle, non-hard large-platform box. */
    memset(&game, 0, sizeof(game));
    mysmb_game_initialize_memory(&game, 0xfeU);
    source.prg = lift_data;
    source.prg_size = 2U;
    game.ram[0x00eaU] = 0x80U;
    if (mysmb_enemy_stream_process_next(&game, &source) != 1U ||
        game.ram[0x0016U] != 38U || game.ram[0x00a0U] != 0xffU ||
        game.ram[0x0434U] != 0x10U || game.ram[0x049aU] != 6U ||
        game.ram[0x0087U] != 0x0cU) return 1;

    /* A rider is snapped to the deck and inherits its fractional lift delta. */
    memset(&game, 0, sizeof(game));
    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 38U;
    game.ram[0x006eU] = 0U;
    game.ram[0x0087U] = 0x40U;
    game.ram[0x00b6U] = 1U;
    game.ram[0x00cfU] = 0x80U;
    game.ram[0x00a0U] = 0xffU;
    game.ram[0x0434U] = 0x10U;
    game.ram[0x006dU] = 0U;
    game.ram[0x0086U] = 0x40U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x60U;
    game.ram[0x009fU] = 0U;
    prepare_contact(&game);
    mysmb_objects_step_platforms(&game);
    if (game.ram[0x00cfU] != 0x7fU || game.ram[0x00ceU] != 0x5fU ||
        game.ram[0x009fU] != 0U || game.ram[0x0433U] != 0U) return 2;

    /* Horizontal counter phase two moves right. A non-counter frame keeps
     * secondary speed $10 and exposes the rider's one-pixel scroll delta. */
    memset(&game, 0, sizeof(game));
    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 40U;
    game.ram[0x006eU] = 0U;
    game.ram[0x0087U] = 0x40U;
    game.ram[0x00b6U] = 1U;
    game.ram[0x00cfU] = 0x80U;
    game.ram[0x0058U] = 0x10U;
    game.ram[0x00a0U] = 2U;
    game.ram[0x0009U] = 1U;
    game.ram[0x006dU] = 0U;
    game.ram[0x0086U] = 0x40U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x60U;
    game.ram[0x009fU] = 0U;
    prepare_contact(&game);
    mysmb_objects_step_platforms(&game);
    if (game.ram[0x0087U] != 0x41U || game.ram[0x0086U] != 0x41U ||
        game.ram[0x03a1U] != 1U) return 3;

    /* BalancePlatform accumulates fractional speed on first contact; its
     * paired, negative-state deck does not run a second movement owner. */
    memset(&game, 0, sizeof(game));
    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x000fU] = 1U;
    game.ram[0x0010U] = 1U;
    game.ram[0x0016U] = 36U;
    game.ram[0x0017U] = 36U;
    game.ram[0x001eU] = 1U;
    game.ram[0x001fU] = 0xffU;
    game.ram[0x006eU] = 0U;
    game.ram[0x006fU] = 0U;
    game.ram[0x0087U] = 0x40U;
    game.ram[0x0088U] = 0x80U;
    game.ram[0x00b6U] = 1U;
    game.ram[0x00b7U] = 1U;
    game.ram[0x00cfU] = 0x80U;
    game.ram[0x00d0U] = 0x80U;
    game.ram[0x006dU] = 0U;
    game.ram[0x0086U] = 0x40U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x60U;
    game.ram[0x009fU] = 0U;
    prepare_contact(&game);
    mysmb_objects_step_platforms(&game);
    if (game.ram[0x00cfU] != 0x80U || game.ram[0x00d0U] != 0x80U ||
        game.ram[0x0434U] != 5U) return 4;
    /* A whole-pixel speed moves the rider's deck down and the peer up. */
    game.ram[0x00a0U] = 1U;
    prepare_contact(&game);
    mysmb_objects_step_platforms(&game);
    if (game.ram[0x00cfU] != 0x81U) return 4;
    if (game.ram[0x00d0U] != 0x7fU) return 5;
    return 0;
}
