#include "core/game.h"
#include "game/objects.h"
#include "game/enemy/frenzy.h"
#include "game/enemy/stream.h"
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
    if (game.ram[0x00cfU + 2U] != 0x7fU || game.ram[0x03aeU] != 0x70U ||
        game.ram[0x03b9U] != 0x7fU) return 1;
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

static int test_star_flag_task_zero_exits_without_oam(void)
{
    struct mysmb_game game;

    memset(&game, 0, sizeof(game));
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 49U;
    game.ram[0x06e5U] = 0x30U;
    memset(game.ram + 0x0230U, 0xf8, 16U);
    game.ram[0x06cbU] = 0x7fU;
    mysmb_objects_step_star_flags(&game);
    if (game.ram[0x06cbU] != 0U) return 6;
    if (game.ram[0x0230U] != 0xf8U || game.ram[0x0231U] != 0xf8U ||
        game.ram[0x023cU] != 0xf8U || game.ram[0x023fU] != 0xf8U) return 7;
    return 0;
}
static int test_star_flag_timer_tick(void)
{
    struct mysmb_game game;

    memset(&game, 0, sizeof(game));
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 49U;
    game.ram[0x0746U] = 2U;
    /* Original DigitsMathRoutine deliberately locks digits in title mode. */
    game.ram[0x0770U] = 1U;
    game.ram[0x0009U] = 4U;
    game.ram[0x07f8U] = 1U;
    mysmb_objects_step_star_flags(&game);
    if (game.ram[0x00feU] != 0x10U || game.ram[0x07f8U] != 0U ||
        game.ram[0x07f9U] != 9U || game.ram[0x07faU] != 9U ||
        game.ram[0x07e2U] != 5U) return 6;
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
    if (game.ram[0x0058U] != 1U || game.ram[0x00a0U] != 8U ||
        game.ram[0x03aeU] != 0x30U || game.ram[0x03b9U] != 0x60U ||
        game.ram[0x03afU] != 0x30U || game.ram[0x03baU] != 0x60U) return 10;
    if (game.ram[0x0260U] != 0x5cU || game.ram[0x0261U] != 0x67U ||
        game.ram[0x0262U] != 2U || game.ram[0x0263U] != 0x2cU) return 11;
    if (game.ram[0x0264U] != 0x64U || game.ram[0x0266U] != 0x82U ||
        game.ram[0x0268U] != 0x5cU || game.ram[0x026aU] != 0x42U ||
        game.ram[0x026cU] != 0x64U || game.ram[0x026eU] != 0xc2U) return 12;
    game.ram[0x0058U] = 2U;
    game.ram[0x00a0U] = 1U;
    mysmb_objects_step_fireworks(&game);
    if (game.ram[0x000fU] != 0U || game.ram[0x0058U] != 3U ||
        game.ram[0x00feU] != 0x08U) return 13;
    return 0;
}

static int test_firework_frenzy(void)
{
    struct mysmb_game game;

    memset(&game, 0, sizeof(game));
    game.ram[0x06cbU] = 22U;
    game.ram[0x0016U] = 22U;
    game.ram[0x078fU] = 0U;
    game.ram[0x06d7U] = 3U;
    game.ram[0x000fU + 2U] = 1U;
    game.ram[0x0016U + 2U] = 49U;
    game.ram[0x001eU + 2U] = 0U;
    game.ram[0x006eU + 2U] = 1U;
    game.ram[0x0087U + 2U] = 0x90U;
    mysmb_enemy_init_fireworks_frenzy(&game, 0U);
    if (game.ram[0x078fU] != 0x20U || game.ram[0x06d7U] != 2U) return 20;
    if (game.ram[0x000fU] != 1U) return 40;
    if (game.ram[0x0016U] != 22U) return 41;
    if (game.ram[0x006eU] != 1U) return 42;
    if (game.ram[0x0087U] != 0xc0U) return 43;
    if (game.ram[0x00cfU] != 0x70U) return 44;
    if (game.ram[0x0058U] != 0U) return 45;
    if (game.ram[0x00a0U] != 8U) return 46;
    return 0;
}

static int test_firework_stream_record(void)
{
    static const mysmb_u8 prg[] = { 0xf0U, 22U };
    struct mysmb_game game;
    struct mysmb_area_source source;

    memset(&game, 0, sizeof(game));
    source.prg = prg;
    source.prg_size = sizeof(prg);
    game.ram[0x00eaU] = 0x80U;
    game.ram[0x071dU] = 0xc0U;
    game.ram[0x06d7U] = 3U;
    game.ram[0x000fU + 5U] = 1U;
    game.ram[0x0016U + 5U] = 49U;
    game.ram[0x006eU + 5U] = 1U;
    game.ram[0x0087U + 5U] = 0x90U;
    if (mysmb_enemy_stream_process_current(&game, &source, 1U) != 1U) return 47;
    if (game.ram[0x0010U] != 1U) return 48;
    if (game.ram[0x0017U] != 22U) return 49;
    if (game.ram[0x006fU] != 1U) return 50;
    if (game.ram[0x0088U] != 0xc0U) return 51;
    if (game.ram[0x00d0U] != 0x70U) return 52;
    if (game.ram[0x0059U] != 0U) return 53;
    if (game.ram[0x00a1U] != 8U) return 54;
    if (game.ram[0x0739U] != 2U) return 55;
    return 0;
}
int main(void)
{
    int result;

    result = test_star_flag_oam();
    if (result != 0) return result;
    result = test_star_flag_task_zero_exits_without_oam();
    if (result != 0) return result;
    result = test_star_flag_timer_tick();
    if (result != 0) return result;
    result = test_fireworks();
    if (result != 0) return result;
    result = test_firework_frenzy();
    if (result != 0) return result;
    return test_firework_stream_record();
}
