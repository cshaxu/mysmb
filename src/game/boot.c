#include "game/game.h"
#include <string.h>

enum {
    MYSMB_BOOT_OPER_MODE = 0x0770U,
    MYSMB_BOOT_OPER_MODE_TASK = 0x0772U,
    MYSMB_BOOT_PSEUDORANDOM = 0x07a7U,
    MYSMB_BOOT_WARM_BOOT_VALIDATION = 0x07ffU,
    MYSMB_BOOT_OAM = 0x0200U,
    MYSMB_BOOT_PPU_CONTROL_MIRROR = 0x0778U
};

void mysmb_game_submit_oam(struct mysmb_game *game);

/* Owner of the ROM reset/cold-boot subtree.  This file deliberately contains
 * no host or platform policy: every target enters the same CPU RAM and PPU
 * state before the shared NMI frame root begins. */

/* ROM $8000-$8035 Start/WBootCheck/ColdBoot, excluding the two hardware
 * vblank waits and the final endless loop.  The host owns neither branch: this
 * shared state transition is used identically by every target. */
void mysmb_game_reset(struct mysmb_game *game)
{
    mysmb_u8 index;
    mysmb_u8 warm_boot;

    warm_boot = 1U;
    /* WBootCheck starts with X=$05 and decrements through TopScoreDisplay.
     * There are no writes between digits, but retain its observable branch
     * order so the first invalid digit follows the ROM route. */
    index = 5U;
    do {
        if (game->ram[(mysmb_u16)(0x07d7U + index)] >= 10U) {
            warm_boot = 0U;
            break;
        }
        index = (mysmb_u8)(index - 1U);
    } while (index != 0xffU);
    if (game->ram[MYSMB_BOOT_WARM_BOOT_VALIDATION] != 0xa5U)
        warm_boot = 0U;
    mysmb_game_initialize_memory(game, warm_boot != 0U ? 0xd6U : 0xfeU);
    /* ColdBoot returns from InitializeMemory with A == 0, then writes that
     * accumulator value to $4011 before it resets OperMode. */
    game->apu_delta_counter_load = 0U;
    game->apu_registers[17U] = 0U;
    game->ram[MYSMB_BOOT_OPER_MODE] = 0U;
    game->ram[MYSMB_BOOT_WARM_BOOT_VALIDATION] = 0xa5U;
    game->ram[MYSMB_BOOT_PSEUDORANDOM] = 0xa5U;
    /* ColdBoot's LDA #$0f / STA $4015 enables the four non-DMC channels.
     * This portable output is shared by every target; the host may only
     * present it. */
    game->apu_channel_enable = 0x0fU;
    game->apu_registers[21U] = 0x0fU;
    /* ColdBoot writes $06 directly to $2001; it is not the later NMI mirror. */
    game->ppu_mask = 0x06U;
    game->visible_ppu_mask = 0x06U;
    mysmb_game_move_all_sprites_offscreen(game);
    mysmb_game_initialize_name_tables(game);
    game->ram[0x0774U]++;
    /* The final WritePPUReg1 restores the $2000 mirror with NMI enabled.
     * CPU OAM is first transferred by the following shared NMI frame. */
    game->ppu_control_0 =
        (mysmb_u8)(game->ram[MYSMB_BOOT_PPU_CONTROL_MIRROR] | 0x80U);
    game->ram[MYSMB_BOOT_PPU_CONTROL_MIRROR] = game->ppu_control_0;
    game->visible_ppu_control_0 = game->ppu_control_0;
    game->oam_dma_primed = 1U;
}

void mysmb_game_power_on(struct mysmb_game *game)
{
    /* Start clears the CPU-only state and writes $10 to physical $2000 before
     * it polls VBlank1 and VBlank2.  The mirror remains zero until ColdBoot's
     * InitializeNameTables path writes it. */
    memset(game, 0, sizeof(*game));
    game->visible_ppu_control_0 = 0x10U;
}

void mysmb_game_initialize(struct mysmb_game *game)
{
    /* Compatibility fixture setup retains historical focused-test behavior.
     * Product composition roots use mysmb_game_power_on instead. */
    mysmb_game_power_on(game);
    mysmb_game_reset(game);
    /* The host container needs a defined presentation backing store before
     * its first NMI.  T22 owns the source $4014 transfer cadence; this copy
     * only initializes the C container and does not decide any game state. */
    mysmb_game_submit_oam(game);
    game->oam_dma_primed = 0U;
    game->area_prg = 0;
    game->area_prg_size = 0U;
    game->title_data = 0;
    game->title_data_size = 0U;
    game->title_icon_data = 0;
    game->title_icon_data_size = 0U;
    game->area_command_count = 0U;
    /* InitializeGame has completed before GameMenuRoutine becomes task 3. */
    game->ram[MYSMB_BOOT_OPER_MODE] = 0U;
    game->ram[MYSMB_BOOT_OPER_MODE_TASK] = 3U;
    game->ram[MYSMB_BOOT_WARM_BOOT_VALIDATION] = 0xa5U;
    game->ram[MYSMB_BOOT_PSEUDORANDOM] = 0xa5U;
    /* The first recorder-visible title NMI follows InitializeGame before the
     * native tick decrements the title countdown. */
    game->ram[0x07a2U] = 0x19U;
    game->frame_number = 0UL;
}

/* Translation of ROM $90cc-$90e6 (InitializeMemory). */
void mysmb_game_initialize_memory(struct mysmb_game *game, mysmb_u8 initial_y)
{
    mysmb_u8 page;
    mysmb_u8 offset;

    page = 0x07U;
    offset = initial_y;
    game->ram[0x0006U] = 0U;
    do {
        game->ram[0x0007U] = page;
        do {
            if (page != 0x01U || offset < 0x60U) {
                game->ram[(mysmb_u16)((mysmb_u16)page * 0x0100U + offset)] = 0U;
            }
            offset = (mysmb_u8)(offset - 1U);
        } while (offset != 0xffU);
        page = (mysmb_u8)(page - 1U);
    } while (page != 0xffU);
}

/* ROM $8225-$8230 SprInitLoop. Both source entry selectors share this
 * owner; only Y bytes are written and the eight-bit index wraps to zero. */
static void mysmb_game_sprite_init_loop(struct mysmb_game *game,
                                        mysmb_u8 offset)
{
    do {
        game->ram[(mysmb_u16)(MYSMB_BOOT_OAM + offset)] = 0xf8U;
        offset = (mysmb_u8)(offset + 4U);
    } while (offset != 0U);
}

/* ROM $8220: LDY #0 followed by BIT skips the other entry's LDY #4. */
void mysmb_game_move_all_sprites_offscreen(struct mysmb_game *game)
{
    mysmb_game_sprite_init_loop(game, 0U);
}

/* ROM $8223: LDY #4 preserves sprite zero before the common loop. */
void mysmb_game_move_sprites_offscreen(struct mysmb_game *game)
{
    mysmb_game_sprite_init_loop(game, 4U);
}

/* ROM NMI $4014 transfer after PPU_SPR_ADDR is reset to zero. */
void mysmb_game_submit_oam(struct mysmb_game *game)
{
    mysmb_u16 offset;

    for (offset = 0U; offset < 0x0100U; ++offset)
        game->visible_oam[offset] = game->ram[(mysmb_u16)(MYSMB_BOOT_OAM + offset)];
}

/* Translation of ROM $8e19-$8e5b (InitializeNameTables). */
void mysmb_game_initialize_name_tables(struct mysmb_game *game)
{
    mysmb_u8 table;
    mysmb_u8 control;
    mysmb_u16 offset;

    /* WriteNTAddr receives $24 before $20: PPU name table 1 is cleared
     * before name table 0.  Preserve that observable PPU write order. */
    table = 1U;
    do {
        for (offset = 0U; offset < 0x03c0U; ++offset) {
            game->name_table[table][offset] = 0x24U;
        }
        for (offset = 0x03c0U; offset < 0x0400U; ++offset) {
            game->name_table[table][offset] = 0U;
        }
        if (table == 0U) break;
        table = 0U;
    } while (1);
    game->ram[0x0300U] = 0U;
    game->ram[0x0301U] = 0U;
    game->ram[0x073fU] = 0U;
    game->ram[0x0740U] = 0U;
    /* InitializeNameTables sets the PPU pattern-table arrangement then
     * InitScroll commits zero scroll.  Palette values remain the domain of
     * ScreenRoutines/ColorRotation and are initialized separately by T10. */
    /* InitializeNameTables performs ORA #$10 / AND #$f0 before
     * WritePPUReg1.  The upper nibble (notably the NMI-enable bit) is an
     * input from the caller and must survive this name-table reset. */
    control = (mysmb_u8)((game->ram[MYSMB_BOOT_PPU_CONTROL_MIRROR] | 0x10U) &
        0xf0U);
    game->ppu_control_0 = control;
    game->ram[MYSMB_BOOT_PPU_CONTROL_MIRROR] = control;
    game->ppu_name_table = 0U;
    game->scroll_x = 0U;
    game->scroll_y = 0U;
    /* Unlike the usual mirror changes made by OperModeExecutionTree, the
     * source routine ends by writing $2005 twice (InitScroll) while this
     * NMI is still active.  Publish that physical transfer now so the
     * current output frame agrees with the ROM at InitScreen/GameOver. */
    game->visible_ppu_control_0 = control;
    game->visible_ppu_name_table = 0U;
    game->visible_scroll_x = 0U;
    game->visible_scroll_y = 0U;
}

