#include "game/game.h"
#include "game/objects.h"
#include "game/enemy/frenzy.h"
#include <string.h>

static int test_star_flag_oam(void)
{
    struct mysmb_game game;

    memset(&game, 0, sizeof(game));
    game.ram[0x000fU + 2U] = 1U;
    game.ram[0x0016U + 2U] = 49U;
    game.ram[0x0087U + 2U] = 0x90U;
    game.ram[0x00cfU + 2U] = 0x80U;
    game.ram[0x071cU] = 0x20U;
    game.ram[0x06e5U + 2U] = 0x40U;
    game.ram[0x0746U] = 3U;
    game.ram[0x06d7U] = 0xffU;
    mysmb_objects_step_star_flags(&game);
    if (game.ram[0x00cfU + 2U] != 0x7fU) return 1;
    if (game.ram[0x0240U] != 0x87U || game.ram[0x0241U] != 0x57U ||
        game.ram[0x0242U] != 0x22U || game.ram[0x0243U] != 0x78U) return 2;
    if (game.ram[0x0244U] != 0x87U || game.ram[0x0245U] != 0x56U ||
        game.ram[0x0247U] != 0x70U) return 3;
    if (game.ram[0x0248U] != 0x7fU || game.ram[0x0249U] != 0x55U ||
        game.ram[0x024bU] != 0x78U) return 4;
    if (game.ram[0x024cU] != 0x7fU || game.ram[0x024dU] != 0x54U ||
        game.ram[0x024fU] != 0x70U) return 5;
    return 0;
}

static int test_fireworks(void)
{
    struct mysmb_game game;

    memset(&game, 0, sizeof(game));
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 22U;
    game.ram[0x0087U] = 0x50U;
    game.ram[0x00cfU] = 0x60U;
    game.ram[0x071cU] = 0x20U;
    game.ram[0x06e5U] = 0x60U;
    game.ram[0x0058U] = 0U;
    game.ram[0x00a0U] = 1U;
    mysmb_objects_step_fireworks(&game);
    if (game.ram[0x0058U] != 1U || game.ram[0x00a0U] != 8U) return 10;
    if (game.ram[0x0260U] != 0x5cU || game.ram[0x0261U] != 0x67U ||
        game.ram[0x0262U] != 2U || game.ram[0x0263U] != 0x2cU) return 11;
    if (game.ram[0x0264U] != 0x64U || game.ram[0x0266U] != 0x82U ||
        game.ram[0x0268U] != 0x5cU || game.ram[0x026aU] != 0x42U ||
        game.ram[0x026cU] != 0x64U || game.ram[0x026eU] != 0xc2U) return 12;
    game.ram[0x0058U] = 2U;
    game.ram[0x00a0U] = 1U;
    mysmb_objects_step_fireworks(&game);
    if (game.ram[0x000fU] != 0U || game.ram[0x0058U] != 3U) return 13;
    return 0;
}

static int test_firework_frenzy(void)
{
    struct mysmb_game game;

    memset(&game, 0, sizeof(game));
    game.ram[0x06cbU] = 22U;
    game.ram[0x06d7U] = 3U;
    game.ram[0x000fU + 2U] = 1U;
    game.ram[0x0016U + 2U] = 49U;
    game.ram[0x001eU + 2U] = 0U;
    game.ram[0x006eU + 2U] = 1U;
    game.ram[0x0087U + 2U] = 0x90U;
    mysmb_enemy_step_firework_frenzy(&game);
    if (game.ram[0x078fU] != 0x20U || game.ram[0x06d7U] != 2U) return 20;
    if (game.ram[0x000fU] != 1U || game.ram[0x0016U] != 22U ||
        game.ram[0x006eU] != 1U || game.ram[0x0087U] != 0xc0U ||
        game.ram[0x00cfU] != 0x70U || game.ram[0x0058U] != 0U ||
        game.ram[0x00a0U] != 8U) return 21;
    return 0;
}

int main(void)
{
    int result;

    result = test_star_flag_oam();
    if (result != 0) return result;
    result = test_fireworks();
    if (result != 0) return result;
    return test_firework_frenzy();
}