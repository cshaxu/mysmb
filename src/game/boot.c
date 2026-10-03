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

/* ROM $8014-$8056 warm/cold reset continuation. Start and its two hardware
 * polling barriers are represented by the shared startup continuation below. */
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
    if (warm_boot != 0U &&
        game->ram[MYSMB_BOOT_WARM_BOOT_VALIDATION] != 0xa5U)
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
    mysmb_game_write_ppu_control(game,
        (mysmb_u8)(game->ram[MYSMB_BOOT_PPU_CONTROL_MIRROR] | 0x80U));
    game->oam_dma_primed = 1U;
    game->startup_phase = 4U;
}

void mysmb_game_power_on(struct mysmb_game *game)
{
    /* Construction is not an instruction in Start. Source startup itself
     * preserves warm RAM and the attached immutable resources. */
    memset(game, 0, sizeof(*game));
    mysmb_game_begin_startup(game);
}

/* ROM $8000-$8013 Start/VBlank1/VBlank2. CPU flags/stack and polling cycles
 * are hardware ABI; each supplied event represents an observed VBlank. */
void mysmb_game_begin_startup(struct mysmb_game *game)
{
    game->ppu_control_0 = 0x10U;
    game->visible_ppu_control_0 = 0x10U;
    game->visible_ppu_name_table = 0U;
    game->startup_phase = 1U;
}

mysmb_u8 mysmb_game_startup_step(struct mysmb_game *game,
                               mysmb_u8 vblank_available)
{
    if (game->startup_phase == 1U || game->startup_phase == 2U) {
        if (vblank_available != 0U) {
            game->startup_phase++;
            /* VBlank2 falls straight into warm/cold initialization; it does
             * not wait for a third boundary. The next boundary owns NMI. */
            if (game->startup_phase == 3U) mysmb_game_reset(game);
        }
        return 0U;
    }
    return game->startup_phase == 4U ? 1U : 0U;
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

/* ROM $8eed-$8ef3 WritePPUReg1: physical register before RAM mirror. */
void mysmb_game_write_ppu_control(struct mysmb_game *game, mysmb_u8 value)
{
    game->ppu_control_0 = value;
    game->visible_ppu_control_0 = value;
    game->visible_ppu_name_table = (mysmb_u8)(value & 3U);
    game->ram[MYSMB_BOOT_PPU_CONTROL_MIRROR] = value;
}

/* ROM $8ee6-$8eec InitScroll: incoming A is written twice, then returns. */
void mysmb_game_init_scroll(struct mysmb_game *game, mysmb_u8 value)
{
    game->visible_scroll_x = value;
    game->visible_scroll_y = value;
}

/* ROM $8e2d-$8e5a WriteNTAddr through the shared InitScroll tail. */
static void mysmb_game_write_name_table(struct mysmb_game *game,
                                      mysmb_u8 table)
{
    mysmb_u16 offset;

    for (offset = 0U; offset < 0x03c0U; ++offset)
        game->name_table[table][offset] = 0x24U;
    game->ram[0x0300U] = 0U;
    game->ram[0x0301U] = 0U;
    for (offset = 0x03c0U; offset < 0x0400U; ++offset)
        game->name_table[table][offset] = 0U;
    game->ram[0x073fU] = 0U;
    game->ram[0x0740U] = 0U;
    game->scroll_x = 0U;
    game->scroll_y = 0U;
    mysmb_game_init_scroll(game, 0U);
}

/* ROM $8e19-$8e5b InitializeNameTables. Status read resets the hardware
 * address latch; direct name-table storage does not retain that latch. */
void mysmb_game_initialize_name_tables(struct mysmb_game *game)
{
    mysmb_game_write_ppu_control(game,
        (mysmb_u8)((game->ram[MYSMB_BOOT_PPU_CONTROL_MIRROR] | 0x10U) & 0xf0U));
    game->ppu_name_table = 0U;
    mysmb_game_write_name_table(game, 1U);
    mysmb_game_write_name_table(game, 0U);
}

