#include "game/area.h"
#include "game/game.h"
#include "game/objects.h"

int main(void)
{
    struct mysmb_game game;
    struct mysmb_area_source source;
    mysmb_u8 bowser_data[2] = { 0U, 45U };

    /* InitBowser establishes the front-half state owners; its rear half is
     * drawing-only and therefore absent from the portable core. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    source.prg = bowser_data;
    source.prg_size = 2U;
    game.ram[0x00eaU] = 0x80U;
    if (mysmb_area_spawn_next_enemy(&game, &source) != 1U ||
        game.ram[0x0016U] != 45U || game.ram[0x0366U] != 0U ||
        game.ram[0x0364U] != 0x20U || game.ram[0x0365U] != 2U ||
        game.ram[0x0790U] != 0xdfU || game.ram[0x0483U] != 5U ||
        game.ram[0x049aU] != 10U) return 1;

    /* RunBowser advances from the saved origin, chooses its original random
     * range, and applies the $0f slow vertical gravity. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 45U;
    game.ram[0x006eU] = 0U;
    game.ram[0x0087U] = 0x40U;
    game.ram[0x00b6U] = 1U;
    game.ram[0x00cfU] = 0x70U;
    game.ram[0x0366U] = 0x40U;
    game.ram[0x0364U] = 2U;
    game.ram[0x0365U] = 2U;
    game.ram[0x006dU] = 0U;
    game.ram[0x0086U] = 0x20U;
    game.frame_number = 0UL;
    mysmb_objects_step_bowsers(&game);
    if (game.ram[0x0087U] != 0x42U || game.ram[0x06dcU] != 0x21U ||
        game.ram[0x0434U] != 0x0fU || game.ram[0x0364U] != 1U) return 2;

    /* A Bowser flame request spawns from the current front-half mouth. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x06cbU] = 21U;
    game.ram[0x0368U] = 0U;
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 45U;
    game.ram[0x006eU] = 0U;
    game.ram[0x0087U] = 0x80U;
    game.ram[0x00cfU] = 0x70U;
    game.ram[0x07a9U] = 0U;
    mysmb_objects_step_bowser_flame_frenzy(&game);
    if (game.ram[0x0010U] != 1U || game.ram[0x0017U] != 21U ||
        game.ram[0x0088U] != 0x72U || game.ram[0x00d0U] != 0x78U ||
        game.ram[0x0435U] != 1U || game.ram[0x06cbU] != 0U) return 3;

    /* The fifth fireball uses HurtBowser: it becomes the world identity and
     * enters the original defeated-state route. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    game.frame_number = 0UL;
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 45U;
    game.ram[0x001eU] = 0U;
    game.ram[0x006eU] = 0U;
    game.ram[0x0087U] = 0x80U;
    game.ram[0x00cfU] = 0x70U;
    game.ram[0x0483U] = 1U;
    game.ram[0x0024U] = 1U;
    game.ram[0x0074U] = 0U;
    game.ram[0x008dU] = 0x80U;
    game.ram[0x00bcU] = 1U;
    game.ram[0x00d5U] = 0x80U;
    game.ram[0x005eU] = 0U;
    game.ram[0x00a6U] = 0U;
    game.ram[0x043aU] = 0U;
    game.ram[0x0407U] = 0U;
    mysmb_objects_step_fireballs(&game);
    if (game.ram[0x0483U] != 0U || game.ram[0x0016U] != 6U ||
        game.ram[0x001eU] != 0x23U || game.ram[0x00a0U] != 0xfeU ||
        game.ram[0x0024U] != 0x80U) return 4;
    return 0;
}
