#include "game/game.h"
#include "game/area.h"
#include "game/enemy/stream.h"
#include "game/objects.h"
#include "game/enemy/frenzy.h"

int main(void)
{
    struct mysmb_game game;
    struct mysmb_area_source source;
    mysmb_u8 frenzy_data[2] = { 0U, 20U };

    /* InitEnemyFrenzy retains the $14 request instead of allocating an
     * ordinary stream object. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    source.prg = frenzy_data;
    source.prg_size = 2U;
    game.ram[0x00eaU] = 0x80U;
    if (mysmb_enemy_stream_process_next(&game, &source) != 1U ||
        game.ram[0x06cbU] != 20U || game.ram[0x0739U] != 2U ||
        game.ram[0x000fU] != 0U) return 1;

    /* InitFlyingCheepCheep uses the original timer, PRNG tables, player
     * page-relative position, and direction choice. */
    game.ram[0x006dU] = 1U;
    game.ram[0x0086U] = 0x40U;
    game.ram[0x0057U] = 0U;
    game.ram[0x07a8U] = 2U;
    game.ram[0x07a9U] = 0U;
    mysmb_enemy_step_flying_cheep_frenzy(&game);
    if (game.ram[0x078fU] != 0x10U || game.ram[0x000fU] != 1U ||
        game.ram[0x0016U] != 20U || game.ram[0x0046U] != 2U ||
        game.ram[0x0058U] != 0xfaU || game.ram[0x006eU] != 1U ||
        game.ram[0x0087U] != 0x80U || game.ram[0x00b6U] != 1U ||
        game.ram[0x00cfU] != 0xf8U || game.ram[0x00a0U] != 0xfbU ||
        game.ram[0x049aU] != 9U) return 2;

    /* In normal difficulty a free fourth slot consumes the random timer but
     * does not create a fourth simultaneous flying fish. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x06cbU] = 20U;
    game.ram[0x000fU] = 1U;
    game.ram[0x0010U] = 1U;
    game.ram[0x0011U] = 1U;
    mysmb_enemy_step_flying_cheep_frenzy(&game);
    if (game.ram[0x078fU] != 0x10U || game.ram[0x0012U] != 0U ||
        game.ram[0x049dU] != 9U) return 3;

    /* ROM MoveFlyingCheepCheep: live fish moves horizontally and uses the
     * lighter $0d downward gravity. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 20U;
    game.ram[0x001eU] = 0U;
    game.ram[0x006eU] = 0U;
    game.ram[0x0087U] = 0x40U;
    game.ram[0x00b6U] = 1U;
    game.ram[0x00cfU] = 0x70U;
    game.ram[0x0058U] = 0x10U;
    game.ram[0x0401U] = 0U;
    game.ram[0x0417U] = 0U;
    game.ram[0x0434U] = 0U;
    game.ram[0x0747U] = 0U;
    mysmb_objects_step_flying_cheep_cheeps(&game);
    if (game.ram[0x0087U] != 0x41U || game.ram[0x0434U] != 0x0dU ||
        game.ram[0x00cfU] != 0x70U) return 4;

    /* TimerControl freezes a live fish before either axis advances. */
    game.ram[0x0747U] = 1U;
    mysmb_objects_step_flying_cheep_cheeps(&game);
    if (game.ram[0x0087U] != 0x41U || game.ram[0x0434U] != 0x0dU) return 5;

    /* Defeated fish follows the shared falling-object gravity instead. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 20U;
    game.ram[0x001eU] = 0x20U;
    game.ram[0x0087U] = 0x40U;
    game.ram[0x00b6U] = 1U;
    game.ram[0x00cfU] = 0x70U;
    game.ram[0x0058U] = 0x10U;
    mysmb_objects_step_flying_cheep_cheeps(&game);
    if (game.ram[0x0087U] != 0x40U || game.ram[0x0434U] != 0x1cU ||
        game.ram[0x00cfU] != 0x70U) return 6;
    return 0;
}
