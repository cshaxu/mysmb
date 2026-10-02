#include <stdio.h>
#include <string.h>

#include "game/area.h"
#include "game/game.h"
#include "game/frame_root.h"
#include "game/objects.h"
#include "smb1_local_rom.h"

/* Exercise the complete WriteGameText selector and tail family against the
 * locally bound ROM data.  Expected stream bytes are read at test time; this
 * project-owned harness does not embed a derivative message fixture. */
static int verify_game_text_selector(mysmb_u8 selector, mysmb_u8 players,
    mysmb_u8 current_player, mysmb_u8 operating_mode)
{
    struct mysmb_game game;
    mysmb_u8 offset_index;
    mysmb_u8 name_player;
    mysmb_u8 index;
    mysmb_u8 length;
    mysmb_u16 source;

    mysmb_game_initialize(&game);
    mysmb_game_bind_area_source(&game, mysmb_local_prg, MYSMB_LOCAL_PRG_SIZE);
    memset(&game.ram[0x0301U], 0xa5, 0xffU);
    game.ram[0x0300U] = 0U;
    game.ram[0x077aU] = players;
    game.ram[0x0753U] = current_player;
    game.ram[0x0770U] = operating_mode;
    game.ram[0x075aU] = 9U;
    game.ram[0x075fU] = 2U;
    game.ram[0x075cU] = 3U;
    if (selector < 2U) {
        offset_index = (mysmb_u8)(selector << 1U);
    }
    else if (selector < 4U) {
        offset_index = (mysmb_u8)(selector << 1U);
        if (players == 0U) offset_index++;
    }
    else {
        offset_index = 8U;
    }
    source = (mysmb_u16)(0x0752U + mysmb_local_prg[0x07feU + offset_index]);
    length = 0U;
    while (mysmb_local_prg[source + length] != 0xffU) {
        if (length == 0xffU) return 1;
        length++;
    }
    if (mysmb_area_queue_game_text(&game, selector) == 0U) return 1;
    for (index = 0U; index < length; ++index) {
        mysmb_u8 expected;

        expected = mysmb_local_prg[source + index];
        if (selector == 1U) {
            if (index == 7U) expected = 0x9fU;
            if (index == 8U) expected = 0U;
            if (index == 19U) expected = 3U;
            if (index == 21U) expected = 4U;
        }
        if (selector != 1U && selector < 4U && players != 0U) {
            name_player = current_player;
            if (selector == 2U && operating_mode != 3U) name_player ^= 1U;
            if (name_player != 0U && index >= 3U && index < 8U)
                expected = mysmb_local_prg[0x07edU + index - 3U];
        }
        if (selector >= 4U && index >= 27U && index <= 35U &&
            ((index - 27U) % 4U) == 0U) {
            expected = mysmb_local_prg[0x07f2U +
                (mysmb_u16)(selector - 4U) * 4U + (index - 27U) / 4U];
        }
        if (game.ram[0x0301U + index] != expected) return 1;
    }
    if (game.ram[0x0301U + length] != 0U) return 1;
    if (selector >= 4U) {
        if (game.ram[0x0300U] != 0x2cU || game.ram[0x0301U + 0x2cU] != 0U)
            return 1;
    }
    else if (game.ram[0x0300U] != 0U) {
        return 1;
    }
    return 0;
}

int main(void)
{
    struct mysmb_game game;
    struct mysmb_game expected;
    struct mysmb_area_source source;
    struct mysmb_area_object object;
    struct mysmb_input input;
    struct mysmb_frame frame;
    mysmb_u8 count;
    mysmb_u8 metatile;
    mysmb_u8 palette;
    mysmb_u8 rotation;
    mysmb_u16 graphics;

    mysmb_game_initialize(&game);
    source.prg = mysmb_local_prg;
    source.prg_size = MYSMB_LOCAL_PRG_SIZE;
    mysmb_game_bind_area_source(&game, source.prg, source.prg_size);
    input.buttons2 = 0U;
    input.buttons = MYSMB_BUTTON_START;
    mysmb_game_tick(&game, &input, &frame);
    input.buttons2 = 0U;
    input.buttons = 0U;
    mysmb_game_tick(&game, &input, &frame);
    if (frame.operating_mode != 1U || frame.operating_mode_task != 1U ||
        game.ram[0x0750U] != 0x25U || game.ram[0x074eU] != 1U ||
        game.ram[0x0710U] != 2U || game.ram[0x0727U] != 1U ||
        game.ram[0x0742U] != 2U) {
        return 1;
    }
    /* The original ScreenRoutines task chain owns screen clearing, status
     * text, intermediate display, and area graphics before GameCoreRoutine. */
    for (count = 0U; count < 200U && game.ram[0x0772U] != 3U; ++count) {
        mysmb_game_tick(&game, &input, &frame);
    }
    if (game.ram[0x0772U] != 3U || game.ram[0x05b0U] != 0x54U ||
        game.ram[0x05c0U] != 0x54U || game.ram[0x0687U] != 0x54U ||
        game.ram[0x0688U] != 0U || game.ram[0x0606U] != 0xc0U ||
        game.ram[0x0640U] != 0xc0U || game.ram[0x0644U] != 0x51U ||
        game.ram[0x0645U] != 0xc1U || game.ram[0x0646U] != 0x51U ||
        game.ram[0x0647U] != 0xc0U || game.ram[0x0648U] != 0U) return 1;
    /* ROM $88ae uses the $8b08 metatile graphics pointer table to turn the
     * collision metatile at page 0, column 0, row 11 into four PPU tiles. */
    metatile = game.ram[0x05b0U];
    palette = (mysmb_u8)(metatile >> 6U);
    graphics = (mysmb_u16)(mysmb_local_prg[0x0b08U + palette] |
        ((mysmb_u16)mysmb_local_prg[0x0b0cU + palette] << 8U));
    graphics = (mysmb_u16)(graphics - 0x8000U + (mysmb_u16)(metatile & 0x3fU) * 4U);
    if (game.name_table[0][0x0340U] != mysmb_local_prg[graphics] ||
        game.name_table[0][0x0341U] != mysmb_local_prg[(mysmb_u16)(graphics + 2U)] ||
        game.name_table[0][0x0360U] != mysmb_local_prg[(mysmb_u16)(graphics + 1U)] ||
        game.name_table[0][0x0361U] != mysmb_local_prg[(mysmb_u16)(graphics + 3U)]) return 1;
    /* Screen task 2 has already committed the ROM-owned top status stream. */
    if (game.name_table[0][0x0043U] != mysmb_local_prg[0x0755U] ||
        game.name_table[0][0x0052U] != mysmb_local_prg[0x075dU]) return 1;

    mysmb_area_queue_bottom_status_line(&game);
    if (game.ram[0x0300U] != 20U || game.ram[0x0301U] != 0x20U ||
        game.ram[0x0302U] != 0x6dU || game.ram[0x0303U] != 2U ||
        game.ram[0x0306U] != 0x20U || game.ram[0x0307U] != 0x62U ||
        game.ram[0x0308U] != 6U) return 1;
    /* ColorRotation queues a $3f0c update and the following NMI commits it. */
    game.ram[0x0009U] = 0U;
    game.ram[0x06d4U] = 0U;
    game.ram[0x0300U] = 0U;
    mysmb_area_step_palette_rotation(&game);
    if (game.ram[0x0300U] != 7U || game.ram[0x0301U] != 0x3fU ||
        game.ram[0x0302U] != 0x0cU || game.ram[0x0303U] != 4U ||
        game.ram[0x0304U] != mysmb_local_prg[0x09d1U + 4U] ||
        game.ram[0x0305U] != mysmb_local_prg[0x09c3U]) return 1;
    rotation = game.ram[0x06d4U];
    if (mysmb_game_apply_vram_commands(&game, &game.ram[0x0301U], 8U) == 0U) return 1;
    game.ram[0x0300U] = 0U;
    if (game.ram[0x0300U] != 0U || game.palette[12U] != mysmb_local_prg[0x09d5U] ||
        game.palette[13U] != mysmb_local_prg[0x09c3U] ||
        game.palette[14U] != mysmb_local_prg[0x09d7U] ||
        game.palette[15U] != mysmb_local_prg[0x09d8U] || rotation != 1U) return 1;
    input.buttons2 = 0U;
    input.buttons = MYSMB_BUTTON_A;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x000eU] != 7U ||
        game.ram[0x006dU] != 0U || game.ram[0x0086U] != 0x28U ||
        game.ram[0x00b5U] != 1U || game.ram[0x00ceU] != 0xb0U) {
        return 1;
    }
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x000eU] != 8U || game.ram[0x001dU] != 0U) {
        return 1;
    }
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x001dU] != 1U) {
        return 1;
    }
    /* PlayerEndWorld calls LoadAreaPointer immediately after incrementing
     * WorldNumber, before it leaves victory mode for game-mode task zero. */
    mysmb_game_initialize(&expected);
    mysmb_game_bind_area_source(&expected, source.prg, source.prg_size);
    expected.ram[0x075fU] = 1U;
    expected.ram[0x0760U] = 0U;
    if (mysmb_area_load_area_pointer(&expected, &source) == 0U) return 1;
    mysmb_game_initialize(&game);
    mysmb_game_bind_area_source(&game, source.prg, source.prg_size);
    game.ram[0x0770U] = 2U;
    game.ram[0x0772U] = 4U;
    game.ram[0x075fU] = 0U;
    game.ram[0x0760U] = 3U;
    game.ram[0x075cU] = 2U;
    game.ram[0x07a1U] = 0U;
    input.buttons2 = 0U;
    input.buttons = 0U;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x0770U] != 1U || game.ram[0x0772U] != 0U ||
        game.ram[0x075fU] != 1U || game.ram[0x0760U] != 0U ||
        game.ram[0x0750U] != expected.ram[0x0750U] ||
        game.ram[0x074eU] != expected.ram[0x074eU] ||
        game.ram[0x074fU] != expected.ram[0x074fU] ||
        game.ram[0x00e7U] != expected.ram[0x00e7U] ||
        game.ram[0x00e8U] != expected.ram[0x00e8U] ||
        game.ram[0x00e9U] != expected.ram[0x00e9U] ||
        game.ram[0x00eaU] != expected.ram[0x00eaU]) return 1;

    /* RunGameTimer decrements the live digits and appends its $207a command;
     * the following frame's NMI consumes it into the PPU name table. */
    mysmb_game_initialize(&game);
    mysmb_game_bind_area_source(&game, source.prg, source.prg_size);
    game.ram[0x0770U] = 1U;
    /* A live GameCore task, never an out-of-table JumpEngine selector. */
    game.ram[0x0772U] = 3U;
    game.ram[0x000eU] = 8U;
    game.ram[0x00b5U] = 0U;
    game.ram[0x0787U] = 0U;
    game.ram[0x07f8U] = 3U;
    game.ram[0x07f9U] = 4U;
    game.ram[0x07faU] = 5U;
    input.buttons2 = 0U;
    input.buttons = 0U;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x07f8U] != 3U || game.ram[0x07f9U] != 4U ||
        game.ram[0x07faU] != 4U || game.ram[0x0300U] != 6U ||
        game.ram[0x0301U] != 0x20U || game.ram[0x0302U] != 0x7aU ||
        game.ram[0x0303U] != 3U || game.ram[0x0304U] != 3U ||
        game.ram[0x0305U] != 4U || game.ram[0x0306U] != 4U) return 1;
    mysmb_game_tick(&game, &input, &frame);
    if (game.name_table[0][0x007aU] != 3U || game.name_table[0][0x007bU] != 4U ||
        game.name_table[0][0x007cU] != 4U) return 1;

    /* TopStatusBarLine reaches WriteGameText, whose source does not call
     * SetVRAMOffset: the command begins at $0301 while $0300 remains zero. */
    game.ram[0x0300U] = 0U;
    if (mysmb_area_queue_top_status_line(&game) == 0U || game.ram[0x0300U] != 0U ||
        game.ram[0x0301U] != 0x20U || game.ram[0x0302U] != 0x43U) return 1;
    /* CheckPlayerName also applies to selector-zero top status text. */
    game.ram[0x0300U] = 0U;
    game.ram[0x077aU] = 1U;
    game.ram[0x0753U] = 1U;
    if (mysmb_area_queue_top_status_line(&game) == 0U ||
        game.ram[0x0304U] != mysmb_local_prg[0x07edU] ||
        game.ram[0x0308U] != mysmb_local_prg[0x07f1U]) return 1;

    /* Exercise the same two-player name path through the original screen
     * task-two entry, rather than treating the text writer as a second
     * gameplay path.  WriteTopStatusLine always reaches IncSubtask after
     * TopStatusBarLine -> WriteGameText -> CheckPlayerName -> NameLoop. */
    mysmb_game_initialize(&game);
    mysmb_game_bind_area_source(&game, source.prg, source.prg_size);
    game.ram[0x0300U] = 0U;
    game.ram[0x073cU] = 2U;
    game.ram[0x0770U] = 1U;
    game.ram[0x077aU] = 1U;
    game.ram[0x0753U] = 1U;
    mysmb_game_step_screen_routine(&game);
    if (game.ram[0x073cU] != 3U || game.ram[0x0300U] != 0U ||
        game.ram[0x0301U] != 0x20U || game.ram[0x0302U] != 0x43U ||
        game.ram[0x0304U] != mysmb_local_prg[0x07edU] ||
        game.ram[0x0308U] != mysmb_local_prg[0x07f1U]) return 1;
    game.ram[0x077aU] = 0U;
    game.ram[0x0753U] = 0U;
    game.ram[0x0300U] = 0U;

    /* GameTextOffsets begins with the two zero offsets for top status and
     * lives, followed by the distinct two-/one-player Time Up and Game Over
     * offsets, then the shared Warp Zone stream.  These are direct local-ROM
     * bytes, not positions inferred from the assembly listing. */
    if (mysmb_local_prg[0x07feU] != 0U || mysmb_local_prg[0x07ffU] != 0U ||
        mysmb_local_prg[0x0800U] != 0x27U || mysmb_local_prg[0x0801U] != 0x27U ||
        mysmb_local_prg[0x0802U] != 0x46U || mysmb_local_prg[0x0803U] != 0x4eU ||
        mysmb_local_prg[0x0804U] != 0x59U || mysmb_local_prg[0x0805U] != 0x61U ||
        mysmb_local_prg[0x0806U] != 0x6eU || mysmb_local_prg[0x0778U] != 0xffU ||
        mysmb_local_prg[0x0797U] != 0xffU || mysmb_local_prg[0x07aaU] != 0xffU ||
        mysmb_local_prg[0x07bfU] != 0xffU || mysmb_local_prg[0x07ecU] != 0xffU)
        return 1;

    /* The source selector family is one contiguous data/copy/tail chain.
     * Cover every selector plus both player-name decisions in one matrix. */
    if (verify_game_text_selector(0U, 0U, 0U, 1U) != 0 ||
        verify_game_text_selector(0U, 1U, 1U, 1U) != 0 ||
        verify_game_text_selector(1U, 0U, 0U, 1U) != 0 ||
        verify_game_text_selector(2U, 0U, 0U, 1U) != 0 ||
        verify_game_text_selector(2U, 1U, 0U, 1U) != 0 ||
        verify_game_text_selector(2U, 1U, 1U, 1U) != 0 ||
        verify_game_text_selector(3U, 0U, 0U, 3U) != 0 ||
        verify_game_text_selector(3U, 1U, 0U, 3U) != 0 ||
        verify_game_text_selector(3U, 1U, 1U, 3U) != 0 ||
        verify_game_text_selector(4U, 0U, 0U, 1U) != 0 ||
        verify_game_text_selector(5U, 0U, 0U, 1U) != 0 ||
        verify_game_text_selector(6U, 0U, 0U, 1U) != 0) return 1;

    /* WriteGameText selector one copies the ROM lives screen and patches
     * its life/world/level positions before the normal VRAM transfer. */
    game.ram[0x075aU] = 2U;
    game.ram[0x075fU] = 1U;
    game.ram[0x075cU] = 3U;
    if (mysmb_area_queue_game_text(&game, 1U) == 0U || game.ram[0x0301U] != 0x21U ||
        game.ram[0x0300U] != 0U || game.ram[0x0302U] != 0xcdU || game.ram[0x0309U] != 3U ||
        game.ram[0x0314U] != 2U || game.ram[0x0316U] != 4U) return 1;
    if (mysmb_game_apply_vram_commands(&game, &game.ram[0x0301U], 0x0100U) == 0U ||
        game.name_table[0][0x01d2U] != 3U || game.name_table[0][0x0151U] != 2U ||
        game.name_table[0][0x0153U] != 4U) return 1;
    /* ROM PutLives uses one digit plus a crown tile once NumberofLives is 9. */
    game.ram[0x0300U] = 0U;
    game.ram[0x075aU] = 9U;
    if (mysmb_area_queue_game_text(&game, 1U) == 0U || game.ram[0x0308U] != 0x9fU ||
        game.ram[0x0309U] != 0U) return 1;
    game.ram[0x0300U] = 0U;
    if (mysmb_area_queue_game_text(&game, 4U) == 0U || game.ram[0x0300U] != 0x2cU ||
        game.ram[0x031cU] != mysmb_local_prg[0x07f2U] ||
        game.ram[0x0320U] != mysmb_local_prg[0x07f3U] ||
        game.ram[0x0324U] != mysmb_local_prg[0x07f4U]) return 1;
    game.ram[0x0300U] = 0U;
    if (mysmb_area_queue_game_text(&game, 5U) == 0U || game.ram[0x0300U] != 0x2cU ||
        game.ram[0x031cU] != mysmb_local_prg[0x07f6U] ||
        game.ram[0x0320U] != mysmb_local_prg[0x07f7U] ||
        game.ram[0x0324U] != mysmb_local_prg[0x07f8U]) return 1;
    game.ram[0x0300U] = 0U;
    if (mysmb_area_queue_game_text(&game, 6U) == 0U || game.ram[0x0300U] != 0x2cU ||
        game.ram[0x031cU] != mysmb_local_prg[0x07faU] ||
        game.ram[0x0320U] != mysmb_local_prg[0x07fbU] ||
        game.ram[0x0324U] != mysmb_local_prg[0x07fcU]) return 1;

    /* GetPlayerColors selects fiery colors, but preserves the original
     * background-color source for the first `$3f10` palette byte. */
    game.ram[0x0300U] = 0U;
    game.ram[0x0753U] = 1U;
    game.ram[0x0756U] = 2U;
    game.ram[0x0744U] = 0U;
    game.ram[0x074eU] = 1U;
    if (mysmb_area_queue_player_palette(&game) == 0U || game.ram[0x0300U] != 7U ||
        game.ram[0x0301U] != 0x3fU || game.ram[0x0302U] != 0x10U ||
        game.ram[0x0303U] != 4U || game.ram[0x0304U] != mysmb_local_prg[0x05d0U] ||
        game.ram[0x0305U] != mysmb_local_prg[0x05e0U] ||
        game.ram[0x0306U] != mysmb_local_prg[0x05e1U] ||
        game.ram[0x0307U] != mysmb_local_prg[0x05e2U]) return 1;
    if (mysmb_game_apply_vram_commands(&game, &game.ram[0x0301U], 0x0100U) == 0U ||
        game.palette[0U] != mysmb_local_prg[0x05d0U] ||
        game.palette[0x11U] != mysmb_local_prg[0x05e0U] ||
        game.palette[0x12U] != mysmb_local_prg[0x05e1U] ||
        game.palette[0x13U] != mysmb_local_prg[0x05e2U] ||
        game.palette[0x10U] != 0U) return 1;
    game.ram[0x0300U] = 0U;
    if (mysmb_area_sync_player_palette(&game) != 0U || game.ram[0x0300U] != 0U)
        return 1;
    game.ram[0x0756U] = 0U;
    if (mysmb_area_sync_player_palette(&game) == 0U || game.ram[0x0300U] != 7U ||
        game.ram[0x0305U] != mysmb_local_prg[0x05dcU]) return 1;
    /* HandlePowerUpCollision changes a super player to fiery and immediately
     * calls GetPlayerColors. The game-core entry must therefore append the
     * original $3f10 command, before its UpToFiery route change. */
    mysmb_game_initialize(&game);
    mysmb_game_bind_area_source(&game, source.prg, source.prg_size);
    game.ram[0x0300U] = 0U;
    game.ram[0x0744U] = 0U;
    game.ram[0x074eU] = 1U;
    game.ram[0x0753U] = 0U;
    game.ram[0x0756U] = 1U;
    game.ram[0x0039U] = 0U;
    mysmb_objects_collect_power_up(&game, 5U);
    if (game.ram[0x0756U] != 2U || game.ram[0x000eU] != 12U ||
        game.ram[0x0300U] != 7U || game.ram[0x0301U] != 0x3fU ||
        game.ram[0x0302U] != 0x10U || game.ram[0x0303U] != 4U ||
        game.ram[0x0304U] != mysmb_local_prg[0x05d0U] ||
        game.ram[0x0305U] != mysmb_local_prg[0x05e0U] ||
        game.ram[0x0306U] != mysmb_local_prg[0x05e1U] ||
        game.ram[0x0307U] != mysmb_local_prg[0x05e2U]) return 1;

    mysmb_game_initialize(&game);
    mysmb_game_bind_area_source(&game, source.prg, source.prg_size);
    input.buttons2 = 0U;
    input.buttons = MYSMB_BUTTON_START;
    mysmb_game_tick(&game, &input, &frame);
    input.buttons2 = 0U;
    input.buttons = 0U;
    for (count = 0U; count < 200U && game.ram[0x0772U] != 3U; ++count) {
        mysmb_game_tick(&game, &input, &frame);
    }
    if (game.ram[0x0772U] != 3U) return 1;
    for (count = 0U; count < 3U; ++count) {
        mysmb_game_tick(&game, &input, &frame);
    }
    if (game.ram[0x000eU] != 8U || game.ram[0x001dU] != 0U ||
        game.ram[0x0086U] != 0x28U || game.ram[0x00ceU] != 0xb0U) return 1;
    input.buttons2 = 0U;
    input.buttons = MYSMB_BUTTON_RIGHT;
    for (count = 0U; count < 156U; ++count) {
        mysmb_game_tick(&game, &input, &frame);
    }
    if (game.ram[0x001dU] != 0U || game.ram[0x006dU] != 0U ||
        game.ram[0x0086U] != 0xf4U || game.ram[0x00b5U] != 1U ||
        game.ram[0x00ceU] != 0xb0U || game.ram[0x0057U] != 0x18U ||
        game.ram[0x009fU] != 0U || game.ram[0x071aU] != 0U ||
        game.ram[0x071cU] != 0x84U) return 1;
    for (count = 0U; count < 84U; ++count) {
        mysmb_game_tick(&game, &input, &frame);
    }
    if (game.ram[0x0770U] != 1U || game.ram[0x000eU] != 11U ||
        game.ram[0x001dU] != 1U) return 1;

    mysmb_game_initialize(&game);
    if (mysmb_area_load_area_pointer(&game, &source) == 0U ||
        game.ram[0x0750U] != 0x25U || game.ram[0x074eU] != 1U ||
        mysmb_area_get_data_addresses(&game, &source) == 0U) {
        return 1;
    }
    count = 0U;
    while (count < 32U && mysmb_area_next_object(&game, &source, &object) != 0U) {
        count++;
    }
    if (count == 0U) {
        return 1;
    }

    /* SetupGameOver dispatches the same ScreenRoutines chain.  At task 6,
     * DisplayIntermediate selects GameOverInter, queues selector 3, and
     * advances the operating-mode task before the next NMI commits the text. */
    mysmb_game_initialize(&game);
    mysmb_game_bind_area_source(&game, mysmb_local_prg, MYSMB_LOCAL_PRG_SIZE);
    game.ram[0x0770U] = 3U;
    game.ram[0x0772U] = 0U;
    input.buttons2 = 0U;
    input.buttons = 0U;
    for (count = 0U; count < 8U; ++count) mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x0772U] != 2U || game.ram[0x07a0U] != 0x12U ||
        game.ram[0x0774U] != 0U ||
        game.name_table[0][0x020bU] != mysmb_local_prg[0x0752U +
            mysmb_local_prg[0x07feU + 7U] + 3U]) return 1;

    /* W1-2's original area stream has the row-13 Warp object at PRG
     * $2cd5: `$6d,$c5`. Point the persistent parser at that real entry with
     * its source page/column preconditions; no synthetic area data is used. */
    mysmb_game_initialize(&game);
    mysmb_game_bind_area_source(&game, mysmb_local_prg, MYSMB_LOCAL_PRG_SIZE);
    game.ram[0x00e7U] = 0xd5U;
    game.ram[0x00e8U] = 0xacU;
    game.ram[0x0725U] = 1U;
    game.ram[0x0726U] = 6U;
    game.ram[0x072aU] = 0U;
    game.ram[0x0730U] = 0xffU;
    game.ram[0x0731U] = 0xffU;
    game.ram[0x0732U] = 0xffU;
    game.ram[0x074eU] = 2U;
    /* ROM WorldNumber=0 selects WarpNum's default selector 4 (4-3-2). */
    game.ram[0x075fU] = 0U;
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x06d6U] != 4U || game.ram[0x0300U] != 0x2cU ||
        mysmb_game_apply_vram_commands(&game, &game.ram[0x0301U], 0x0100U) == 0U ||
        game.name_table[0][0x0584U] != mysmb_local_prg[0x0752U +
            mysmb_local_prg[0x07feU + 8U] + 3U] ||
        game.ram[0x031cU] != mysmb_local_prg[0x07f2U] ||
        game.ram[0x0320U] != mysmb_local_prg[0x07f3U] ||
        game.ram[0x0324U] != mysmb_local_prg[0x07f4U]) return 1;

    /* After a timer death restarts game mode, ScreenRoutines task 4 takes
     * DisplayTimeUp's OutputInter route before the normal area parser. */
    mysmb_game_initialize(&game);
    mysmb_game_bind_area_source(&game, mysmb_local_prg, MYSMB_LOCAL_PRG_SIZE);
    game.ram[0x0770U] = 1U;
    game.ram[0x0772U] = 1U;
    game.ram[0x073cU] = 4U;
    game.ram[0x0759U] = 1U;
    input.buttons2 = 0U;
    input.buttons = 0U;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x0759U] != 0U || game.ram[0x073cU] != 5U ||
        game.ram[0x07a0U] != 7U || game.ram[0x0300U] != 0U ||
        game.ram[0x0301U] != 0x22U) return 1;
    mysmb_game_tick(&game, &input, &frame);
    if (game.name_table[0][0x020cU] != mysmb_local_prg[0x0752U +
        mysmb_local_prg[0x07feU + 5U] + 3U]) return 1;

    printf("area_pointer=%02x type=%u enemy=%02x%02x area=%02x%02x header=%u/%u/%u objects=%u\n",
           game.ram[0x0750U], game.ram[0x074eU], game.ram[0x00eaU],
           game.ram[0x00e9U], game.ram[0x00e8U], game.ram[0x00e7U],
           game.ram[0x0710U], game.ram[0x0727U], game.ram[0x0742U], count);
    return 0;
}
