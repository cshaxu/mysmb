#include "game/game.h"
#include "game/player.h"

static int test_normal_entry(void)
{
    struct mysmb_game game;

    mysmb_game_initialize(&game);
    game.ram[0x071aU] = 3U;
    game.ram[0x074eU] = 1U;
    game.ram[0x0710U] = 2U;
    game.ram[0x0752U] = 0U;
    game.ram[0x0715U] = 2U;
    game.ram[0x0757U] = 1U;
    game.ram[0x079fU] = 0x23U;
    game.ram[0x0755U] = 0xa5U;
    mysmb_player_initialize_entrance(&game);
    if (game.ram[0x006dU] != 3U || game.ram[0x070aU] != 0x28U ||
        game.ram[0x0033U] != 1U || game.ram[0x00b5U] != 1U ||
        game.ram[0x001dU] != 0U || game.ram[0x0490U] != 0xffU ||
        game.ram[0x075bU] != 0U || game.ram[0x0704U] != 0U ||
        game.ram[0x0086U] != 0x28U || game.ram[0x00ceU] != 0xb0U ||
        game.ram[0x03c4U] != 0U || game.ram[0x0755U] != 0xa5U ||
        game.ram[0x07f8U] != 3U || game.ram[0x07f9U] != 0U ||
        game.ram[0x07faU] != 1U || game.ram[0x0757U] != 0U ||
        game.ram[0x079fU] != 0U || game.ram[0x000eU] != 7U) return 1;
    return 0;
}

static int test_alternate_entry(void)
{
    struct mysmb_game game;

    mysmb_game_initialize(&game);
    game.ram[0x074eU] = 1U;
    game.ram[0x0710U] = 7U;
    game.ram[0x0752U] = 2U;
    game.ram[0x0715U] = 0U;
    game.ram[0x07f8U] = 9U;
    mysmb_player_initialize_entrance(&game);
    if (game.ram[0x0086U] != 0x38U || game.ram[0x00ceU] != 0xf0U ||
        game.ram[0x03c4U] != 0x20U || game.ram[0x07f8U] != 9U ||
        game.ram[0x000eU] != 7U) return 1;
    return 0;
}

static int test_vine_entry(void)
{
    struct mysmb_game game;

    mysmb_game_initialize(&game);
    game.ram[0x071aU] = 3U;
    game.ram[0x074eU] = 1U;
    game.ram[0x0710U] = 0U;
    game.ram[0x0758U] = 1U;
    mysmb_player_initialize_entrance(&game);
    if (game.ram[0x001dU] != 3U || game.ram[0x008fU] != 0x30U ||
        game.ram[0x0076U] != 3U || game.ram[0x03eaU] != 3U ||
        game.ram[0x00beU] != 1U || game.ram[0x00d7U] != 0xf0U ||
        game.ram[0x001bU] != 0x2fU || game.ram[0x0014U] != 1U ||
        game.ram[0x0073U] != 3U || game.ram[0x008cU] != 0x30U ||
        game.ram[0x00d4U] != 0xf0U || game.ram[0x039aU] != 5U ||
        game.ram[0x0398U] != 1U || game.ram[0x00feU] != 4U ||
        game.ram[0x000eU] != 7U) return 1;
    return 0;
}

static int test_water_entry(void)
{
    struct mysmb_game game;

    mysmb_game_initialize(&game);
    game.ram[0x071aU] = 3U;
    game.ram[0x074eU] = 0U;
    game.ram[0x0710U] = 0U;
    game.ram[0x0007U] = 1U;
    mysmb_player_initialize_entrance(&game);
    if (game.ram[0x0704U] != 1U || game.ram[0x0083U] != 3U ||
        game.ram[0x009cU] != 0x30U || game.ram[0x00e4U] != 8U ||
        game.ram[0x00cbU] != 1U || game.ram[0x0792U] != 0x20U ||
        game.ram[0x000eU] != 7U) return 1;
    return 0;
}

int main(void)
{
    if (test_normal_entry() != 0) return 1;
    if (test_alternate_entry() != 0) return 2;
    if (test_vine_entry() != 0) return 3;
    if (test_water_entry() != 0) return 4;
    return 0;
}
