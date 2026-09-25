#include "game/area.h"
#include "game/enemy/stream.h"
#include "game/game.h"
#include "game/objects.h"

int main(void)
{
    struct mysmb_game game;
    struct mysmb_area_source source;
    mysmb_u8 lift_data[2] = { 0U, 38U };

    /* InitLargeLiftUp uses the original signed vertical pair. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    source.prg = lift_data;
    source.prg_size = 2U;
    game.ram[0x00eaU] = 0x80U;
    if (mysmb_enemy_stream_process_next(&game, &source) != 1U ||
        game.ram[0x0016U] != 38U || game.ram[0x00a0U] != 0xffU ||
        game.ram[0x0434U] != 0x10U || game.ram[0x049aU] != 5U) return 1;

    /* A rider is snapped to the deck and inherits its fractional lift delta. */
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
    mysmb_objects_step_platforms(&game);
    if (game.ram[0x00cfU] != 0x7fU || game.ram[0x00ceU] != 0x5fU ||
        game.ram[0x009fU] != 0U || game.ram[0x0433U] != 0U) return 2;

    /* Horizontal decks move a standing player and expose the scroll delta
     * consumed by the native player route on its following frame. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 40U;
    game.ram[0x006eU] = 0U;
    game.ram[0x0087U] = 0x40U;
    game.ram[0x00b6U] = 1U;
    game.ram[0x00cfU] = 0x80U;
    game.ram[0x0058U] = 0x10U;
    game.ram[0x006dU] = 0U;
    game.ram[0x0086U] = 0x40U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x60U;
    game.ram[0x009fU] = 0U;
    mysmb_objects_step_platforms(&game);
    if (game.ram[0x0087U] != 0x41U || game.ram[0x0086U] != 0x41U ||
        game.ram[0x03a1U] != 1U) return 3;

    /* The paired balance platforms move in opposite directions on contact. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x000fU] = 1U;
    game.ram[0x0010U] = 1U;
    game.ram[0x0016U] = 36U;
    game.ram[0x0017U] = 36U;
    game.ram[0x001eU] = 1U;
    game.ram[0x001fU] = 0U;
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
    mysmb_objects_step_platforms(&game);
    if (game.ram[0x00cfU] != 0x81U) return 4;
    if (game.ram[0x00d0U] != 0x7fU) return 5;
    return 0;
}
