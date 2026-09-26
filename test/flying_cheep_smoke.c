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

    /* The fixture starts with an ordinary current-slot $14 stream record. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    source.prg = frenzy_data;
    source.prg_size = 2U;
    game.ram[0x00e9U] = 0U;
    game.ram[0x00eaU] = 0x80U;
    game.ram[0x0739U] = 0U;
    game.ram[0x073aU] = 0U;
    game.ram[0x073bU] = 0U;
    game.ram[0x000fU] = 0U;
    /* ProcessEnemyData -> InitEnemyObject -> CheckpointEnemyID ->
     * InitEnemyFrenzy initializes $14 in this current stream slot. */
    game.ram[0x071bU] = 0U;
    game.ram[0x071dU] = 0U;
    game.ram[0x006dU] = 1U;
    game.ram[0x0086U] = 0x40U;
    game.ram[0x0057U] = 0U;
    game.ram[0x07a7U] = 2U;
    game.ram[0x07a8U] = 0U;
    if (mysmb_enemy_stream_process_next(&game, &source) != 1U ||
        game.ram[0x06cbU] != 20U || game.ram[0x0739U] != 2U ||
        game.ram[0x000fU] != 1U ||
        game.ram[0x078fU] != 0x10U ||
        game.ram[0x0016U] != 20U || game.ram[0x0046U] != 2U ||
        game.ram[0x0058U] != 0xfaU || game.ram[0x006eU] != 1U ||
        game.ram[0x0087U] != 0x80U || game.ram[0x00b6U] != 1U ||
        game.ram[0x00cfU] != 0xf8U || game.ram[0x00a0U] != 0xfbU ||
        game.ram[0x049aU] != 9U) return 2;

    /* AreaFrenzy enqueues $14; ChkEnemyFrenzy consumes it in the same
     * current ObjectOffset before it attempts to read enemy stream data. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x06cdU] = 20U;
    game.ram[0x006dU] = 1U;
    game.ram[0x0086U] = 0x40U;
    game.ram[0x07a9U] = 2U;
    game.ram[0x07aaU] = 0U;
    if (mysmb_enemy_stream_process_current(&game, 0, 2U) != 1U ||
        game.ram[0x06cdU] != 0U || game.ram[0x06cbU] != 20U ||
        game.ram[0x0011U] != 1U || game.ram[0x0018U] != 20U ||
        game.ram[0x078fU] != 0x10U || game.ram[0x0070U] != 1U ||
        game.ram[0x0089U] != 0x80U || game.ram[0x00b8U] != 1U ||
        game.ram[0x00d1U] != 0xf8U) return 3;
    /* With an unexpired timer, InitFlyingCheepCheep returns but the ROM
     * ChkEnemyFrenzy activation flag remains live in the current slot. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x06cdU] = 20U;
    game.ram[0x078fU] = 1U;
    if (mysmb_enemy_stream_process_current(&game, 0, 1U) != 1U ||
        game.ram[0x000fU + 1U] != 1U || game.ram[0x0016U + 1U] != 20U ||
        game.ram[0x001eU + 1U] != 0U || game.ram[0x078fU] != 1U) return 4;
    /* In normal difficulty a free fourth slot consumes the random timer but
     * does not create a fourth simultaneous flying fish. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x06cbU] = 20U;
    game.ram[0x000fU] = 1U;
    game.ram[0x0010U] = 1U;
    game.ram[0x0011U] = 1U;
    mysmb_enemy_init_flying_cheep_frenzy(&game, 3U);
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
