#include "game/world/world.h"

static void set_box(struct mysmb_game *game, mysmb_u16 address,
                    mysmb_u8 left, mysmb_u8 top,
                    mysmb_u8 right, mysmb_u8 bottom)
{
    game->ram[address] = left;
    game->ram[(mysmb_u16)(address + 1U)] = top;
    game->ram[(mysmb_u16)(address + 2U)] = right;
    game->ram[(mysmb_u16)(address + 3U)] = bottom;
}

int main(void)
{
    struct mysmb_game game;
    mysmb_u16 first = 0x04acU;
    mysmb_u16 second = 0x04b0U;

    /* FirstBoxGreater returns before vertical comparison: $07 remains one. */
    mysmb_game_initialize_memory(&game, 0U);
    set_box(&game, first, 0x10U, 0x20U, 0x18U, 0x28U);
    set_box(&game, second, 0x30U, 0x20U, 0x38U, 0x28U);
    if (mysmb_world_boxes_collide(&game, first, second) != 0U ||
        game.ram[6U] != 4U || game.ram[7U] != 1U) return 1;

    /* Horizontal collision reaches the vertical pass; its no-hit terminal
     * leaves the decremented counter at zero. */
    mysmb_game_initialize_memory(&game, 0U);
    set_box(&game, first, 0x10U, 0x20U, 0x20U, 0x28U);
    set_box(&game, second, 0x18U, 0x30U, 0x28U, 0x38U);
    if (mysmb_world_boxes_collide(&game, first, second) != 0U ||
        game.ram[6U] != 4U || game.ram[7U] != 0U) return 2;

    /* Equality is collision at both source comparisons; after both axes the
     * counter wraps to $ff and Y/RAM06 returns to the original offset. */
    mysmb_game_initialize_memory(&game, 0U);
    set_box(&game, first, 0x10U, 0x20U, 0x20U, 0x30U);
    set_box(&game, second, 0x10U, 0x20U, 0x20U, 0x30U);
    if (mysmb_world_boxes_collide(&game, first, second) == 0U ||
        game.ram[6U] != 4U || game.ram[7U] != 0xffU) return 3;

    /* SecondBoxVerticalChk accepts the intentional one-byte vertical wrap. */
    mysmb_game_initialize_memory(&game, 0U);
    set_box(&game, first, 0x10U, 0xf8U, 0x20U, 0x08U);
    set_box(&game, second, 0x10U, 0x04U, 0x20U, 0x0cU);
    if (mysmb_world_boxes_collide(&game, first, second) == 0U ||
        game.ram[6U] != 4U || game.ram[7U] != 0xffU) return 4;
    return 0;
}
