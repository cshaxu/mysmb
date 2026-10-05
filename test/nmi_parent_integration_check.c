#include "game/frame_root.h"

static mysmb_u8 rotate_first_byte(mysmb_u8 first, mysmb_u8 second)
{
    mysmb_u8 carry;

    carry = ((first & 2U) ^ (second & 2U)) != 0U ? 1U : 0U;
    return (mysmb_u8)((first >> 1U) | (carry != 0U ? 0x80U : 0U));
}

static int check_unpaused_nmi_order(void)
{
    struct mysmb_game game;
    struct mysmb_input input;
    mysmb_u8 mode;
    mysmb_u8 task;
    mysmb_u8 index;

    mysmb_game_power_on(&game);
    mysmb_game_reset(&game);
    game.ppu_control_0 = 0x95U;
    game.ram[0x0778U] = 0x15U;
    game.ram[0x0779U] = 0x01U;
    game.ram[0x0774U] = 0U;
    game.ram[0x073fU] = 0x34U;
    game.ram[0x0740U] = 0x56U;
    game.ram[0x0009U] = 0x24U;
    game.ram[0x077fU] = 1U;
    game.ram[0x0780U] = 3U;
    game.ram[0x0794U] = 5U;
    game.ram[0x07a7U] = 0x03U;
    game.ram[0x07a8U] = 0x02U;
    game.ram[0x0722U] = 1U;
    for (index = 0U; index < 64U; ++index) {
        game.ram[(mysmb_u16)(0x0200U + index * 4U)] =
            (mysmb_u8)(0x20U + index);
    }
    game.ram[0x0773U] = 0U;
    game.ram[0x0300U] = 5U;
    game.ram[0x0301U] = 0x20U;
    game.ram[0x0302U] = 0x00U;
    game.ram[0x0303U] = 0x43U;
    game.ram[0x0304U] = 0x29U;
    game.ram[0x0305U] = 0U;
    input.buttons = 0U;
    input.buttons2 = 0U;

    (void)mysmb_frame_root_begin(&game, &input, &mode, &task);

    if (game.visible_sprite0_split != 1U) return 10;
    game.ram[0x0722U] = 0U;
    if (game.visible_sprite0_split != 1U) return 11;
    /* $4014 observes old OAM before MoveSpritesOffscreen clears slots 1-63. */
    if (game.visible_oam[0U] != 0x20U || game.visible_oam[4U] != 0x21U ||
        game.ram[0x0200U] != 0x20U || game.ram[0x0204U] != 0xf8U) return 1;
    /* UpdateScreen precedes InitBuffer, preserving the packet then clearing it. */
    if (game.name_table[0U][0U] != 0x29U ||
        game.name_table[0U][1U] != 0x29U ||
        game.name_table[0U][2U] != 0x29U || game.ram[0x0300U] != 0U ||
        game.ram[0x0301U] != 0U || game.ram[0x0773U] != 0U) return 2;
    /* At the pre-dispatch boundary, the physical $2000 write retains d7 clear. */
    /* The horizontal VRAM packet clears the $2000 increment bit before
     * WritePPUReg1 restores the mirror and NMI-enable bit at RTI. */
    if (game.ram[0x0778U] != 0x11U || game.ram[0x0779U] != 0x1fU ||
        game.ppu_mask != 0x1fU || game.visible_ppu_control_0 != 0x11U ||
        game.visible_ppu_name_table != 1U || game.visible_scroll_x != 0x34U ||
        game.visible_scroll_y != 0x56U) return 3;
    /* SpriteShuffler follows random rotation and overwrites its RAM00 scratch. */
    if (game.ram[0x0009U] != 0x25U || game.ram[0x0780U] != 2U ||
        game.ram[0x0794U] != 4U ||
        game.ram[0x07a7U] != rotate_first_byte(0x03U, 0x02U) ||
        game.ram[0U] != 0x28U) return 4;
    return 0;
}

static int check_pause_gate_order(void)
{
    struct mysmb_game game;
    struct mysmb_input input;
    mysmb_u8 mode;
    mysmb_u8 task;

    mysmb_game_power_on(&game);
    mysmb_game_reset(&game);
    game.ram[0x0770U] = 2U;
    game.ram[0x0776U] = 0U;
    game.ram[0x0009U] = 0x44U;
    game.ram[0x077fU] = 3U;
    game.ram[0x0780U] = 7U;
    game.ram[0x07a7U] = 0x03U;
    game.ram[0x07a8U] = 0x02U;
    input.buttons = MYSMB_BUTTON_START;
    input.buttons2 = 0U;

    if (mysmb_frame_root_begin(&game, &input, &mode, &task) == 0U) return 5;
    /* ReadJoypads and PauseRoutine precede the timer gate; LFSR still runs. */
    if (game.ram[0x06fcU] != MYSMB_BUTTON_START || game.ram[0x0776U] != 0x81U ||
        game.ram[0x0777U] != 0x2bU || game.ram[0x00faU] != 1U ||
        game.ram[0x0009U] != 0x44U || game.ram[0x077fU] != 3U ||
        game.ram[0x0780U] != 7U ||
        game.ram[0x07a7U] != rotate_first_byte(0x03U, 0x02U) ||
        game.ram[0U] != 0x02U) return 6;
    return 0;
}

static int check_rti_control_restore(void)
{
    struct mysmb_game game;
    struct mysmb_input input;
    struct mysmb_frame frame;

    mysmb_game_power_on(&game);
    mysmb_game_reset(&game);
    game.ppu_control_0 = 0x15U;
    game.ram[0x0778U] = 0x15U;
    /* A paused title boundary takes SkipMainOper but still executes the
     * source PLA / ORA #$80 / STA $2000 tail. */
    game.ram[0x0776U] = 1U;
    input.buttons = 0U;
    input.buttons2 = 0U;
    mysmb_game_frame_initialize(&frame);
    mysmb_frame_root_step(&game, &input, &frame);
    if (game.visible_sprite0_split != 0U) return 12;
    if (game.visible_ppu_control_0 != 0x95U ||
        game.visible_ppu_name_table != 1U) return 7;
    return 0;
}

/* Original $808f-$80a5 and $80de-$80e3 have distinct physical-mask phases. */
static int check_display_mask_phases(void)
{
    struct mysmb_game game;
    mysmb_u16 mask;
    mysmb_u8 disabled;
    mysmb_u8 mirror;

    for (disabled = 0U; disabled < 2U; ++disabled) {
        for (mask = 0U; mask < 256U; ++mask) {
            mysmb_game_power_on(&game);
            mysmb_game_reset(&game);
            game.ram[0x0779U] = (mysmb_u8)mask;
            game.ram[0x0774U] = disabled;
            game.ram[0x0773U] = 0U;
            game.ram[0x0301U] = 0U;
            mirror = disabled != 0U ? (mysmb_u8)(mask & 0xe6U) :
                                     (mysmb_u8)(mask | 0x1eU);
            mysmb_game_commit_display_state(&game);
            if (game.ram[0x0779U] != mirror ||
                game.ppu_mask != (mysmb_u8)(mirror & 0xe7U) ||
                game.visible_ppu_mask != game.ppu_mask) return 8;
            /* Change the source mirror to prove a reload, not cached restore. */
            game.ram[0x0779U] = (mysmb_u8)(mirror ^ 1U);
            mysmb_game_commit_vram_buffer(&game);
            if (game.ppu_mask != game.ram[0x0779U] ||
                game.visible_ppu_mask != game.ppu_mask ||
                game.ram[0x0773U] != 0U || game.ram[0x0300U] != 0U ||
                game.ram[0x0301U] != 0U) return 9;
        }
    }
    return 0;
}

static int check_setup_page_handoff(void)
{
    struct mysmb_game game;
    struct mysmb_input input;
    struct mysmb_frame frame;
    mysmb_u8 mode,task,page,control,old_control;

    input.buttons=input.buttons2=0U;
    /* Setup writes the page into RAM during dispatch. The current NMI keeps
     * its saved physical control;the following NMI must consume new RAM. */
    for(page=0U;page<16U;++page) {
        mysmb_game_initialize(&game);
        old_control=(mysmb_u8)(0x10U|((page&1U)^1U));
        game.ppu_control_0=old_control;
        game.ram[0x0778U]=old_control;
        game.ram[0x0770U]=1U;game.ram[0x0772U]=2U;
        game.ram[0x071aU]=page;
        mysmb_game_tick(&game,&input,&frame);
        control=(mysmb_u8)(0x10U|(page&1U));
        if(game.ram[0x0778U]!=control ||
           game.visible_ppu_control_0!=(mysmb_u8)(old_control|0x80U))return 1;
        (void)mysmb_frame_root_begin(&game,&input,&mode,&task);
        if(game.ram[0x0778U]!=control || game.ppu_control_0!=control ||
           game.visible_ppu_name_table!=(page&1U))return 2;
    }
    /* A RAM-only source write must preserve every control bit except NMI
     * enable,even when the cached register has the opposite value. */
    for(page=0U;page<128U;++page) {
        game.ppu_control_0=(mysmb_u8)(page^0x7fU);
        game.ram[0x0778U]=(mysmb_u8)(page|0x80U);
        mysmb_game_commit_display_state(&game);
        if(game.ram[0x0778U]!=page || game.ppu_control_0!=page ||
           game.visible_ppu_name_table!=(page&3U))return 3;
    }
    return 0;
}

int main(void)
{
    int result;

    result = check_setup_page_handoff();
    if (result != 0) return 50 + result;
    result = check_display_mask_phases();
    if (result != 0) return 40 + result;
    result = check_unpaused_nmi_order();
    if (result != 0) return 10 + result;
    result = check_pause_gate_order();
    if (result != 0) return 20 + result;
    result = check_rti_control_restore();
    if (result != 0) return 30 + result;
    return 0;
}
