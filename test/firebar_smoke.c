#include "core/area.h"
#include "game/enemy/stream.h"
#include "core/game.h"
#include "game/objects.h"

/* Synthetic lookup data tests binding and integration, not ROM equality. */
static unsigned char firebar_data[0x5000];
static void initialize(struct mysmb_game *game)
{
    mysmb_game_initialize_memory(game, 0xfeU);
    game->area_prg = firebar_data;
    game->area_prg_size = sizeof(firebar_data);
    game->ram[0x071bU] = 1U;
    game->ram[0x00b6U] = 1U;
    firebar_data[0x4ccfU] = 8U;
}

int main(void)
{
    struct mysmb_game game;
    struct mysmb_area_source source;
    mysmb_u8 short_firebar[2] = { 0U, 27U };

    /* InitShortFirebar offsets its anchor and configures its independent
     * spin arrays when the area stream supplies object $1b. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    source.prg = short_firebar;
    source.prg_size = 2U;
    game.ram[0x00eaU] = 0x80U;
    if (mysmb_enemy_stream_process_next(&game, &source) != 1U ||
        game.ram[0x0016U] != 27U || game.ram[0x0087U] != 4U ||
        game.ram[0x00cfU] != 4U || game.ram[0x0388U] != 0x28U ||
        game.ram[0x0034U] != 0U || game.ram[0x049aU] != 3U) return 1;

    /* FirebarSpin uses the low-byte carry to advance the five-bit phase. */
    initialize(&game);
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 27U;
    game.ram[0x006eU] = 0U;
    game.ram[0x0087U] = 0x40U;
    game.ram[0x00cfU] = 0x50U;
    game.ram[0x0058U] = 0xe8U;
    game.ram[0x00a0U] = 0U;
    game.ram[0x0388U] = 0x28U;
    game.ram[0x0034U] = 0U;
    mysmb_objects_step_firebars(&game);
    if (game.ram[0x0058U] != 0x10U || game.ram[0x00a0U] != 1U) return 2;

    /* Long firebars avoid their two perfectly horizontal phases. */
    game.ram[0x0016U] = 31U;
    game.ram[0x00a0U] = 8U;
    game.ram[0x0747U] = 1U;
    mysmb_objects_step_firebars(&game);
    if (game.ram[0x00a0U] != 9U) return 3;

    /* A ball at phase zero injures the player through the original shared
     * damage state handoff. */
    initialize(&game);
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 27U;
    game.ram[0x006eU] = 0U;
    game.ram[0x0087U] = 0x40U;
    game.ram[0x00cfU] = 0x50U;
    game.ram[0x0034U] = 0U;
    game.ram[0x0388U] = 0U;
    game.ram[0x00a0U] = 0U;
    game.ram[0x006dU] = 0U;
    game.ram[0x0086U] = 0x3cU;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x38U;
    game.ram[0x0207U] = 0x3cU;
    game.ram[0x0754U] = 1U;
    game.ram[0x0756U] = 1U;
    game.ram[0x000eU] = 8U;
    mysmb_objects_step_firebars(&game);
    if (game.ram[0x0756U] != 0U || game.ram[0x079eU] != 8U ||
        game.ram[0x000eU] != 10U || game.ram[0x001dU] != 1U ||
        game.ram[0x0747U] != 0xffU) return 4;
    /* With this synthetic lookup, the first outer ball is eight pixels
     * above the anchor. The source owns allocation; the child draws tiles. */
    initialize(&game);
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 27U;
    game.ram[0x006eU] = 0U;
    game.ram[0x0087U] = 0x40U;
    game.ram[0x00cfU] = 0x50U;
    game.ram[0x071aU] = 0U;
    game.ram[0x071bU] = 1U;
    game.ram[0x071cU] = 0U;
    game.ram[0x071dU] = 0U;
    game.ram[0x06e5U] = 0x20U;
    game.ram[0x0747U] = 1U;
    game.ram[0x00a0U] = 0U;
    mysmb_objects_step_firebars(&game);
    if (game.ram[0x0224U] != 0x48U || game.ram[0x0225U] != 0x64U ||
        game.ram[0x0226U] != 2U || game.ram[0x0227U] != 0x40U) return 5;

    return 0;
}
