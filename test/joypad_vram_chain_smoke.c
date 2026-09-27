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
    return 0;
}
