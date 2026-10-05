#include "core/dispatcher.h"
#include "core/objects.h"
#include <string.h>

int main(void)
{
    struct mysmb_game game;

    /* Only CPU RAM is reset by the original InitializeMemory routine.
     * Give the test's host-side ROM bindings defined null values. */
    memset(&game, 0, sizeof(game));

    /* ImposeGravity uses SprObject_YMF_Dummy + ObjectOffset: block is $09,
     * jump coin is $0d.  The neighbouring bytes belong to other objects. */
    mysmb_game_initialize_memory(&game, 0U);
    game.ram[0x0026U] = 1U;
    game.ram[0x00d7U] = 0x40U;
    game.ram[0x00a8U] = 0U;
    game.ram[0x043cU] = 0x50U;
    game.ram[0x041fU] = 0xb0U;
    game.ram[0x0420U] = 0U;
    game.ram[0x06ecU] = 0x20U;
    mysmb_game_engine_blocks(&game);
    if (game.ram[0x00d7U] != 0x41U || game.ram[0x041fU] != 0U ||
        game.ram[0x0420U] != 0U) return 1;

    mysmb_game_initialize_memory(&game, 0U);
    game.ram[0x002aU + 8U] = 1U;
    game.ram[0x00dbU + 8U] = 0x40U;
    game.ram[0x00acU + 8U] = 0U;
    game.ram[0x0440U + 8U] = 0x50U;
    game.ram[0x0423U + 8U] = 0xb0U;
    game.ram[0x0424U + 8U] = 0U;
    game.ram[0x06f3U + 8U] = 0x40U;
    mysmb_objects_step_misc(&game);
    if (game.ram[0x00dbU + 8U] != 0x41U || game.ram[0x0423U + 8U] != 0U ||
        game.ram[0x0424U + 8U] != 0U) return 2;

    /* ProcHammerObj moves with the same generic offset $0d: X force is $040d. */
    mysmb_game_initialize_memory(&game, 0U);
    game.ram[0x002aU + 1U] = 0x81U;
    game.ram[0x000fU] = 1U;
    game.ram[0x0747U] = 0U;
    game.ram[0x06aeU + 1U] = 0U;
    game.ram[0x0093U + 1U] = 0x40U;
    game.ram[0x0064U + 1U] = 1U;
    game.ram[0x040dU + 1U] = 0xffU;
    game.ram[0x0407U + 1U] = 0U;
    mysmb_objects_step_misc(&game);
    if (game.ram[0x0093U + 1U] != 0x41U ||
        game.ram[0x040dU + 1U] != 0x0fU || game.ram[0x0407U + 1U] != 0U) return 3;

    /* ProcJumpCoin follows CMP #$05/BNE: it becomes the floatey-number
     * state only on exactly $05, never by a broad C comparison. */
    mysmb_game_initialize_memory(&game, 0U);
    game.ram[0x002aU + 8U] = 1U;
    game.ram[0x00acU + 8U] = 5U;
    game.ram[0x06f3U + 8U] = 0x40U;
    mysmb_objects_step_misc(&game);
    if (game.ram[0x002aU + 8U] != 2U || game.ram[0x0241U] != 0xf7U ||
        game.ram[0x0245U] != 0xfbU) return 4;

    /* JumpEngine ASL clears carry for every legal BlockCode index.
     * With slot eight empty, both $c0 and $5d therefore subtract $11. */
    mysmb_game_initialize_memory(&game, 0U);
    game.ram[0x0754U] = 1U;
    game.ram[0x006dU] = 1U;
    game.ram[0x0086U] = 0x20U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x34U;
    game.ram[0x0612U] = 0xc0U;
    (void)mysmb_objects_start_head_bump(&game, 0xc0U, 0xf2U, 0x20U);
    if (game.ram[0x002aU + 8U] != 1U || game.ram[0x00dbU + 8U] != 0x2fU) return 4;

    mysmb_game_initialize_memory(&game, 0U);
    game.ram[0x0754U] = 1U;
    game.ram[0x006dU] = 1U;
    game.ram[0x0086U] = 0x20U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x34U;
    game.ram[0x0612U] = 0x5dU;
    (void)mysmb_objects_start_head_bump(&game, 0x5dU, 0xf2U, 0x20U);
    if (game.ram[0x002aU + 8U] != 1U || game.ram[0x00dbU + 8U] != 0x2fU) return 5;
    return 0;
}
