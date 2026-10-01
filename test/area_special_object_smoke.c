#include <string.h>

#include "game/area.h"
#include "game/game.h"

static void set_object(struct mysmb_game *game, mysmb_u8 prg[0x100U],
                       mysmb_u8 first, mysmb_u8 second)
{
    memset(prg, 0, 0x100U);
    prg[0x40U] = first;
    prg[0x41U] = second;
    prg[0x42U] = 0xfdU;
    mysmb_game_initialize(game);
    mysmb_game_bind_area_source(game, prg, 0x100U);
    game->ram[0x00e7U] = 0x40U;
    game->ram[0x00e8U] = 0x80U;
    game->ram[0x0725U] = 0U;
    game->ram[0x0726U] = (mysmb_u8)(first >> 4U);
    game->ram[0x072aU] = 0U;
    game->ram[0x072bU] = 0U;
    game->ram[0x072cU] = 0U;
    game->ram[0x0730U] = 0xffU;
    game->ram[0x0731U] = 0xffU;
    game->ram[0x0732U] = 0xffU;
}

int main(void)
{
    struct mysmb_game game;
    static mysmb_u8 prg[0x100U];
    mysmb_u8 row;

    /* ScrollLockObject_Warp: selector, text call, Piranha clear, then lock. */
    set_object(&game, prg, 0x0dU, 0x45U);
    game.ram[0x074eU] = 1U;
    game.ram[0x075fU] = 0U;
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 13U;
    game.ram[0x0010U] = 1U;
    game.ram[0x0017U] = 12U;
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x06d6U] != 4U || game.ram[0x0723U] != 1U ||
        game.ram[0x000fU] != 0U || game.ram[0x0010U] != 1U) return 1;

    /* ScrollLockObject_Warp starts at four only in world zero.  In later
     * worlds it selects five, then increments once more for a ground area. */
    set_object(&game, prg, 0x0dU, 0x45U);
    game.ram[0x075fU] = 1U;
    game.ram[0x074eU] = 1U;
    if (mysmb_area_process_object_state(&game) == 0U || game.ram[0x06d6U] != 6U)
        return 15;
    set_object(&game, prg, 0x0dU, 0x45U);
    game.ram[0x075fU] = 1U;
    game.ram[0x074eU] = 2U;
    if (mysmb_area_process_object_state(&game) == 0U || game.ram[0x06d6U] != 5U)
        return 16;
    set_object(&game, prg, 0x0dU, 0x45U);
    game.ram[0x074eU] = 2U;
    if (mysmb_area_process_object_state(&game) == 0U || game.ram[0x06d6U] != 4U)
        return 17;

    /* The two ordinary scroll-lock selectors each invert the same byte. */
    set_object(&game, prg, 0x0dU, 0x46U);
    if (mysmb_area_process_object_state(&game) == 0U || game.ram[0x0723U] != 1U)
        return 2;
    set_object(&game, prg, 0x0dU, 0x47U);
    if (mysmb_area_process_object_state(&game) == 0U || game.ram[0x0723U] != 1U)
        return 3;

    /* AreaFrenzy scans IDs 4 down through 0; an existing frenzy cancels the
     * queue, otherwise the exact table value survives to EnemyFrenzyQueue. */
    set_object(&game, prg, 0x0dU, 0x48U);
    game.ram[0x001aU] = 20U;
    if (mysmb_area_process_object_state(&game) == 0U || game.ram[0x06cdU] != 0U)
        return 4;
    set_object(&game, prg, 0x0dU, 0x48U);
    if (mysmb_area_process_object_state(&game) == 0U || game.ram[0x06cdU] != 20U)
        return 5;

    /* TreeLedge's middle branch writes the ledge directly, then sends $4c
     * through RenderUnderPart for every lower metatile row. */
    set_object(&game, prg, 0x15U, 0x12U);
    game.ram[0x0733U] = 0U;
    game.ram[0x0726U] = 1U;
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x06a6U] != 0x16U || game.ram[0x0732U] != 1U) return 6;
    memset(&game.ram[0x06a1U], 0, 13U);
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x06a6U] != 0x17U || game.ram[0x0732U] != 0U) return 7;
    for (row = 6U; row <= 12U; ++row)
        if (game.ram[0x06a1U + row] != 0x4cU) return 8;

    /* MushroomLedge uses the saved half length at its center and fills the
     * stem from the row below the top all the way to the staging bottom. */
    set_object(&game, prg, 0x15U, 0x12U);
    game.ram[0x0733U] = 1U;
    game.ram[0x0726U] = 1U;
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x06a6U] != 0x19U || game.ram[0x0736U + 2U] != 1U) return 9;
    memset(&game.ram[0x06a1U], 0, 13U);
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x06a6U] != 0x1aU || game.ram[0x06a7U] != 0x4fU) return 10;
    for (row = 7U; row <= 12U; ++row)
        if (game.ram[0x06a1U + row] != 0x50U) return 11;

    /* PulleyRopeObject selects left pulley, rope, then right pulley as the
     * parser's post-handler decrement advances the original length byte. */
    set_object(&game, prg, 0x1cU, 0x12U);
    game.ram[0x0726U] = 1U;
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x06a1U] != 0x42U || game.ram[0x0732U] != 1U) return 12;
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x06a1U] != 0x41U || game.ram[0x0732U] != 0U) return 13;
    if (mysmb_area_process_object_state(&game) == 0U || game.ram[0x06a1U] != 0x43U)
        return 14;

    /* QuestionBlockRow_Low shares the saved row/length path with the high
     * entry, but begins at row seven. */
    set_object(&game, prg, 0x0cU, 0x70U);
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x06a8U] != 0xc0U) return 18;

    /* The three bridge selectors choose rows six, seven and nine, then
     * render one body metatile immediately beneath the rail. */
    set_object(&game, prg, 0x0cU, 0x20U);
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x06a7U] != 0x0bU || game.ram[0x06a8U] != 0x63U) return 19;
    set_object(&game, prg, 0x0cU, 0x30U);
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x06a8U] != 0x0bU || game.ram[0x06a9U] != 0x63U) return 20;
    set_object(&game, prg, 0x0cU, 0x40U);
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x06aaU] != 0x0bU || game.ram[0x06abU] != 0x63U) return 21;

    /* FlagBalls_Residual begins at row two and uses the second-byte low
     * nibble as its inclusive downward extent. */
    set_object(&game, prg, 0x0fU, 0x53U);
    if (mysmb_area_process_object_state(&game) == 0U) return 22;
    for (row = 2U; row <= 5U; ++row)
        if (game.ram[0x06a1U + row] != 0x6dU) return 23;
    return 0;
}
