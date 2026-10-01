#include "game/game.h"
#include "game/frame_root.h"

static mysmb_u8 mysmb_expected_joypad_saved(mysmb_u8 previous,
                                             mysmb_u8 current)
{
    if (((current & 0x30U) & previous) != 0U)
        return (mysmb_u8)(current & 0xcfU);
    return current;
}

static mysmb_u8 mysmb_expected_joypad_mask(mysmb_u8 previous,
                                            mysmb_u8 current)
{
    if (((current & 0x30U) & previous) != 0U) return previous;
    return current;
}

/* ROM $8e66 reads eight serial bits, then $8e75-$8e8f either retains the
 * prior mask or commits the complete byte.  Sweep every possible prior and
 * current image on each port so the test observes bit order, port selection
 * and both Select/Start paths rather than only one hand-picked combination. */
static int mysmb_verify_joypad_port(mysmb_u16 saved, mysmb_u16 mask)
{
    struct mysmb_game game;
    unsigned int previous;
    unsigned int current;
    mysmb_u8 expected_saved;
    mysmb_u8 expected_mask;

    for (previous = 0U; previous < 256U; ++previous) {
        for (current = 0U; current < 256U; ++current) {
            mysmb_game_initialize(&game);
            game.ram[mask] = (mysmb_u8)previous;
            if (saved == 0x06fcU) {
                mysmb_frame_root_read_joypads(&game, (mysmb_u8)current, 0U);
            }
            else {
                mysmb_frame_root_read_joypads(&game, 0U, (mysmb_u8)current);
            }
            expected_saved = mysmb_expected_joypad_saved((mysmb_u8)previous,
                                                         (mysmb_u8)current);
            expected_mask = mysmb_expected_joypad_mask((mysmb_u8)previous,
                                                       (mysmb_u8)current);
            if (game.ram[saved] != expected_saved ||
                game.ram[mask] != expected_mask) return 0;
        }
    }
    return 1;
}

int main(void)
{
    struct mysmb_game game;
    const mysmb_u8 mixed_commands[] = {
        0x20U, 0x3eU, 0x02U, 0x11U, 0x12U,
        0x24U, 0x3fU, 0xc2U, 0x33U,
        0x3fU, 0x10U, 0x41U, 0x2aU,
        0U
    };
    const mysmb_u8 chained_commands[] = {
        0x20U, 0x1fU, 0x01U, 0x44U,
        0x20U, 0x20U, 0xc2U, 0x55U,
        0U
    };

    mysmb_game_initialize(&game);
    if (mysmb_verify_joypad_port(0x06fcU, 0x074aU) == 0 ||
        mysmb_verify_joypad_port(0x06fdU, 0x074bU) == 0) return 5;
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
    game.ram[0x0000U] = 0x01U;
    game.ram[0x0001U] = 0x03U;
    game.visible_scroll_x = 0x66U;
    game.visible_scroll_y = 0x77U;
    if (mysmb_game_apply_vram_commands(&game, mixed_commands,
            (mysmb_u16)sizeof(mixed_commands)) == 0U) return 3;
    if (game.name_table[0U][0x003eU] != 0x11U ||
        game.name_table[0U][0x003fU] != 0x12U ||
        game.name_table[1U][0x003fU] != 0x33U ||
        game.name_table[1U][0x005fU] != 0x33U ||
        game.palette[0U] != 0x2aU || game.ppu_control_0 != 0x90U ||
        game.ram[0x0778U] != 0x90U || game.ram[0x0000U] != 0x0eU ||
        game.ram[0x0001U] != 0x03U || game.visible_ppu_control_0 != 0x90U ||
        game.visible_scroll_x != 0U || game.visible_scroll_y != 0U) return 4;

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
        game.ram[0x0773U] != 0U || game.ram[0x0000U] != 0x05U ||
        game.ram[0x0001U] != 0x03U) return 5;

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
        game.ram[0x0773U] != 0U || game.ram[0x0000U] != 0x07U ||
        game.ram[0x0001U] != 0x03U) return 6;

    /* Two adjacent packets exercise UpdateScreen's back-edge and the source
     * SEC/ADC indirect-pointer carry.  The final d7/d6 header also leaves
     * the physical and mirror $2000 values in vertical/repeat mode. */
    mysmb_game_initialize(&game);
    game.ppu_control_0 = 0x11U;
    game.ram[0x0778U] = 0x11U;
    game.ram[0x0000U] = 0xfbU;
    game.ram[0x0001U] = 0xffU;
    if (mysmb_game_apply_vram_commands(&game, chained_commands,
            (mysmb_u16)sizeof(chained_commands)) == 0U) return 7;
    if (game.name_table[0U][0x001fU] != 0x44U ||
        game.name_table[0U][0x0020U] != 0x55U ||
        game.name_table[0U][0x0040U] != 0x55U ||
        game.ram[0x0000U] != 0x03U || game.ram[0x0001U] != 0U ||
        game.ppu_control_0 != 0x15U || game.ram[0x0778U] != 0x15U ||
        game.visible_ppu_control_0 != 0x15U ||
        game.visible_ppu_name_table != 1U || game.visible_scroll_x != 0U ||
        game.visible_scroll_y != 0U) return 8;
    return 0;
}
