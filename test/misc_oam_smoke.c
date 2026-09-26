#include "game/objects.h"

int main(void)
{
    struct mysmb_game game;
    mysmb_u8 slot;

    mysmb_game_initialize_memory(&game, 0xfeU);
    game.frame_number = 2UL;
    game.ram[0x0009U] = (mysmb_u8)(2UL);
    game.ram[0x002aU] = 2U;
    game.ram[0x007aU] = 1U;
    game.ram[0x0093U] = 0x50U;
    game.ram[0x00dbU] = 0x40U;
    game.ram[0x06f3U] = 0x20U;
    game.ram[0x071aU] = 1U;
    game.ram[0x071cU] = 0x10U;
    mysmb_objects_step_misc(&game);
    if (game.ram[0x0220U] != 0x3fU || game.ram[0x0221U] != 0xf7U ||
        game.ram[0x0222U] != 2U || game.ram[0x0223U] != 0x40U ||
        game.ram[0x0224U] != 0x3fU || game.ram[0x0225U] != 0xfbU ||
        game.ram[0x0226U] != 2U || game.ram[0x0227U] != 0x48U) return 1;

    mysmb_game_initialize_memory(&game, 0xfeU);
    game.frame_number = 4UL;
    game.ram[0x0009U] = (mysmb_u8)(4UL);
    game.ram[0x002aU] = 1U;
    game.ram[0x007aU] = 0U;
    game.ram[0x0093U] = 0x30U;
    game.ram[0x00dbU] = 0x40U;
    game.ram[0x00acU] = 0U;
    game.ram[0x0440U] = 0U;
    game.ram[0x06f3U] = 0x30U;
    mysmb_objects_step_misc(&game);
    if (game.ram[0x0230U] != 0x40U || game.ram[0x0231U] != 0x62U ||
        game.ram[0x0232U] != 2U || game.ram[0x0233U] != 0x30U ||
        game.ram[0x0234U] != 0x48U || game.ram[0x0235U] != 0x62U ||
        game.ram[0x0236U] != 0x82U || game.ram[0x0237U] != 0x30U) return 2;

    /* ProcJumpCoin calls ImposeGravity with generic-object offset $0d, so
     * Misc_YMF_Dummy begins at $0416+$0d=$0423.  A carry from slot eight
     * ($042b) moves the coin by one pixel; $042c is Bubble_YMF_Dummy. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x0009U] = 4U;
    game.ram[0x002aU + 8U] = 1U;
    game.ram[0x00dbU + 8U] = 0x40U;
    game.ram[0x00acU + 8U] = 0U;
    game.ram[0x0440U + 8U] = 0x50U;
    game.ram[0x0423U + 8U] = 0xb0U;
    game.ram[0x0424U + 8U] = 0U;
    game.ram[0x06f3U + 8U] = 0x40U;
    mysmb_objects_step_misc(&game);
    if (game.ram[0x00dbU + 8U] != 0x41U ||
        game.ram[0x0423U + 8U] != 0U ||
        game.ram[0x0240U] != 0x41U) return 3;
    /* ProcJumpCoin carries Misc_X_Position overflow into Misc_PageLoc. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    for (slot = 0U; slot <= 8U; ++slot) game.ram[0x002aU + slot] = 0U;
    game.frame_number = 1UL;
    game.ram[0x0009U] = 1U;
    game.ram[0x071aU] = 0U;
    game.ram[0x071bU] = 1U;
    game.ram[0x071cU] = 0U;
    game.ram[0x071dU] = 0U;
    game.ram[0x002aU] = 2U;
    game.ram[0x007aU] = 3U;
    game.ram[0x0093U] = 0xf8U;
    game.ram[0x00c2U] = 0U;
    game.ram[0x00dbU] = 0x40U;
    game.ram[0x06f3U] = 0x20U;
    game.ram[0x0775U] = 0x10U;
    mysmb_objects_step_misc(&game);
    if (game.ram[0x002aU] != 3U || game.ram[0x0093U] != 0x08U ||
        game.ram[0x007aU] != 4U) return 4;
    /* MiscObjectsCore begins at slot 8 and decrements to slot 0.  Its
     * relative/offscreen outputs are fixed scratch bytes, so the final values
     * must come from the lowest active slot, not the highest one. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    for (slot = 0U; slot <= 8U; ++slot) game.ram[0x002aU + slot] = 0U;
    game.frame_number = 1UL;
    game.ram[0x0009U] = 1U;
    game.ram[0x071aU] = 0U;
    game.ram[0x071bU] = 1U;
    game.ram[0x071cU] = 0U;
    game.ram[0x071dU] = 0U;
    game.ram[0x002aU] = 2U;
    game.ram[0x007aU] = 0U;
    game.ram[0x0093U] = 0x11U;
    game.ram[0x00c2U] = 0U;
    game.ram[0x00dbU] = 0x40U;
    game.ram[0x06f3U] = 0x20U;
    game.ram[0x002aU + 8U] = 2U;
    game.ram[0x007aU + 8U] = 0U;
    game.ram[0x0093U + 8U] = 0x88U;
    game.ram[0x00c2U + 8U] = 0U;
    game.ram[0x00dbU + 8U] = 0x50U;
    game.ram[0x06f3U + 8U] = 0x40U;
    mysmb_objects_step_misc(&game);
    if (game.ram[0x03b3U] != 0x11U || game.ram[0x03beU] != 0x40U ||
        game.ram[0x002aU] != 3U || game.ram[0x002aU + 8U] != 3U) return 4;

    return 0;
}