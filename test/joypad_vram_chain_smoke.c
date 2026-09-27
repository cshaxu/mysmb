#include "game/game.h"
#include "game/frame_root.h"

int main(void)
{
    struct mysmb_game game;
    const mysmb_u8 mixed_commands[] = {
        0x20U, 0x3eU, 0x02U, 0x11U, 0x12U,
        0x24U, 0x3fU, 0xc2U, 0x33U,
        0x3fU, 0x10U, 0x41U, 0x2aU,
        0U
    };

    mysmb_game_initialize(&game);
    game.ram[0x074aU] = 0U;
    game.ram[0x074bU] = 0U;
    mysmb_frame_root_read_joypads(&game,
        (mysmb_u8)(MYSMB_BUTTON_A | MYSMB_BUTTON_START | MYSMB_BUTTON_LEFT),
        (mysmb_u8)(MYSMB_BUTTON_B | MYSMB_BUTTON_SELECT | MYSMB_BUTTON_RIGHT));
    if (game.ram[0x06fcU] != (MYSMB_BUTTON_A | MYSMB_BUTTON_START |
                              MYSMB_BUTTON_LEFT) ||
        game.ram[0x06fdU] != (MYSMB_BUTTON_B | MYSMB_BUTTON_SELECT |
                              MYSMB_BUTTON_RIGHT) ||
        game.ram[0x074aU] != game.ram[0x06fcU] ||
        game.ram[0x074bU] != game.ram[0x06fdU]) return 1;
    mysmb_frame_root_read_joypads(&game,
        (mysmb_u8)(MYSMB_BUTTON_A | MYSMB_BUTTON_START | MYSMB_BUTTON_LEFT),
        (mysmb_u8)(MYSMB_BUTTON_B | MYSMB_BUTTON_SELECT | MYSMB_BUTTON_RIGHT));
    if (game.ram[0x06fcU] != (MYSMB_BUTTON_A | MYSMB_BUTTON_LEFT) ||
        game.ram[0x06fdU] != (MYSMB_BUTTON_B | MYSMB_BUTTON_RIGHT)) return 2;

    game.ppu_control_0 = 0x90U;
    game.ram[0x0778U] = 0x90U;
    game.visible_scroll_x = 0x66U;
    game.visible_scroll_y = 0x77U;
    if (mysmb_game_apply_vram_commands(&game, mixed_commands,
            (mysmb_u16)sizeof(mixed_commands)) == 0U) return 3;
    if (game.name_table[0U][0x003eU] != 0x11U ||
        game.name_table[0U][0x003fU] != 0x12U ||
        game.name_table[1U][0x003fU] != 0x33U ||
        game.name_table[1U][0x005fU] != 0x33U ||
        game.palette[0U] != 0x2aU || game.ppu_control_0 != 0x90U ||
        game.ram[0x0778U] != 0x90U || game.visible_scroll_x != 0U ||
        game.visible_scroll_y != 0U) return 4;

    /* The NMI-side selector must route Buffer1 through the same packet
     * interpreter, then clear the source header exactly as InitBuffer does.
     * These two packets make the d6 repeat and d7 vertical forms observable
     * without a platform renderer. */
    game.ram[0x0773U] = 0U;
    game.ram[0x0300U] = 5U;
    game.ram[0x0301U] = 0x20U;
    game.ram[0x0302U] = 0x00U;
    game.ram[0x0303U] = 0x43U;
    game.ram[0x0304U] = 0x29U;
    game.ram[0x0305U] = 0U;
    mysmb_game_commit_vram_buffer(&game);
    if (game.name_table[0U][0U] != 0x29U ||
        game.name_table[0U][1U] != 0x29U ||
        game.name_table[0U][2U] != 0x29U ||
        game.ram[0x0300U] != 0U || game.ram[0x0301U] != 0U ||
        game.ram[0x0773U] != 0U) return 5;

    game.ram[0x0773U] = 0U;
    game.ram[0x0300U] = 7U;
    game.ram[0x0301U] = 0x20U;
    game.ram[0x0302U] = 0x10U;
    game.ram[0x0303U] = 0x83U;
    game.ram[0x0304U] = 0x11U;
    game.ram[0x0305U] = 0x22U;
    game.ram[0x0306U] = 0x33U;
    game.ram[0x0307U] = 0U;
    mysmb_game_commit_vram_buffer(&game);
    if (game.name_table[0U][0x0010U] != 0x11U ||
        game.name_table[0U][0x0030U] != 0x22U ||
        game.name_table[0U][0x0050U] != 0x33U ||
        game.ram[0x0300U] != 0U || game.ram[0x0301U] != 0U ||
        game.ram[0x0773U] != 0U) return 6;
    return 0;
}
