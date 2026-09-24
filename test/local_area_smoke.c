#include <stdio.h>

#include "game/area.h"
#include "game/game.h"
#include "smb1_local_rom.h"

int main(void)
{
    struct mysmb_game game;
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
    input.buttons = MYSMB_BUTTON_START;
    mysmb_game_tick(&game, &input, &frame);
    input.buttons = 0U;
    mysmb_game_tick(&game, &input, &frame);
    if (frame.operating_mode != 1U || frame.operating_mode_task != 1U ||
        game.ram[0x0750U] != 0x25U || game.ram[0x074eU] != 1U ||
        game.ram[0x0710U] != 2U || game.ram[0x0727U] != 1U ||
        game.ram[0x0742U] != 2U || game.ram[0x05b0U] != 0x54U ||
        game.ram[0x05c0U] != 0x54U || game.ram[0x0687U] != 0x54U ||
        game.ram[0x0688U] != 0U || game.ram[0x0606U] != 0xc0U ||
        game.ram[0x0640U] != 0xc0U || game.ram[0x0644U] != 0x51U ||
        game.ram[0x0645U] != 0xc1U || game.ram[0x0646U] != 0x51U ||
        game.ram[0x0647U] != 0xc0U || game.ram[0x0648U] != 0U) {
        return 1;
    }
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
    /* The selected ground-area palette is a ROM $8cc8 VRAM command stream,
     * not a host palette choice. */
    if (game.palette[0U] != mysmb_local_prg[0x0ccbU] ||
        game.palette[31U] != mysmb_local_prg[0x0ceaU]) return 1;
    /* Screen task 2 queues the ROM-owned top-status command stream. */
    if (game.ram[0x0300U] == 0U || game.ram[0x0301U] != mysmb_local_prg[0x0752U] ||
        game.ram[0x0302U] != mysmb_local_prg[0x0753U]) return 1;
    if (mysmb_game_apply_vram_commands(&game, &game.ram[0x0301U], 0x0100U) == 0U) return 1;
    game.ram[0x0300U] = 0U;
    if (game.name_table[0][0x0043U] != mysmb_local_prg[0x0755U] ||
        game.name_table[0][0x0052U] != mysmb_local_prg[0x075dU]) return 1;
    mysmb_area_queue_bottom_status_line(&game);
    if (game.ram[0x0300U] != 20U || game.ram[0x0301U] != 0x20U ||
        game.ram[0x0302U] != 0x62U || game.ram[0x0303U] != 6U) return 1;
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
    input.buttons = MYSMB_BUTTON_A;
    mysmb_game_tick(&game, &input, &frame);
    if (game.area_command_count != 1U ||
        game.area_commands[0].dispatch_id == 0xffU || game.ram[0x000eU] != 7U ||
        game.ram[0x006dU] != 0U || game.ram[0x0086U] != 0x28U ||
        game.ram[0x00b5U] != 1U || game.ram[0x00ceU] != 0xb0U) {
        return 1;
    }
    if (game.area_commands[0].page != 1U || game.area_commands[0].column != 0U ||
        game.area_commands[0].row != 7U || game.area_commands[0].dispatch_id != 0x17U ||
        game.ram[0x0640U] != 0xc0U) return 1;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x000eU] != 8U || game.ram[0x001dU] != 0U) {
        return 1;
    }
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x001dU] != 1U) {
        return 1;
    }
    /* RunGameTimer decrements the live digits and appends its $207a command;
     * the following frame's NMI consumes it into the PPU name table. */
    mysmb_game_initialize(&game);
    mysmb_game_bind_area_source(&game, source.prg, source.prg_size);
    game.ram[0x0770U] = 1U;
    game.ram[0x0772U] = 0x7fU;
    game.ram[0x000eU] = 8U;
    game.ram[0x00b5U] = 0U;
    game.ram[0x0787U] = 0U;
    game.ram[0x07f8U] = 3U;
    game.ram[0x07f9U] = 4U;
    game.ram[0x07faU] = 5U;
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

    /* WriteGameText selector one copies the ROM lives screen and patches
     * its life/world/level positions before the normal VRAM transfer. */
    game.ram[0x075aU] = 2U;
    game.ram[0x075fU] = 1U;
    game.ram[0x075cU] = 3U;
    if (mysmb_area_queue_game_text(&game, 1U) == 0U || game.ram[0x0301U] != 0x21U ||
        game.ram[0x0302U] != 0xcdU || game.ram[0x0309U] != 3U ||
        game.ram[0x0314U] != 2U || game.ram[0x0316U] != 4U) return 1;
    if (mysmb_game_apply_vram_commands(&game, &game.ram[0x0301U], 0x0100U) == 0U ||
        game.name_table[0][0x01d2U] != 3U || game.name_table[0][0x0151U] != 2U ||
        game.name_table[0][0x0153U] != 4U) return 1;
    game.ram[0x0300U] = 0U;
    if (mysmb_area_queue_game_text(&game, 4U) == 0U || game.ram[0x0300U] != 0x2cU ||
        game.ram[0x031cU] != mysmb_local_prg[0x07f2U] ||
        game.ram[0x0320U] != mysmb_local_prg[0x07f3U] ||
        game.ram[0x0324U] != mysmb_local_prg[0x07f4U]) return 1;

    mysmb_game_initialize(&game);
    mysmb_game_bind_area_source(&game, source.prg, source.prg_size);
    input.buttons = MYSMB_BUTTON_START;
    mysmb_game_tick(&game, &input, &frame);
    input.buttons = 0U;
    for (count = 0U; count < 3U; ++count) {
        mysmb_game_tick(&game, &input, &frame);
    }
    if (game.ram[0x000eU] != 8U || game.ram[0x001dU] != 0U ||
        game.ram[0x0086U] != 0x28U || game.ram[0x00ceU] != 0xb0U) return 1;
    input.buttons = MYSMB_BUTTON_RIGHT;
    for (count = 0U; count < 156U; ++count) {
        mysmb_game_tick(&game, &input, &frame);
    }
    if (game.ram[0x001dU] != 0U || game.ram[0x006dU] != 0U ||
        game.ram[0x0086U] != 0xf6U || game.ram[0x00b5U] != 1U ||
        game.ram[0x00ceU] != 0xb0U || game.ram[0x0057U] != 0x18U ||
        game.ram[0x009fU] != 0U || game.ram[0x071aU] != 0U ||
        game.ram[0x071cU] != 0x86U) return 1;
    for (count = 0U; count < 84U; ++count) {
        mysmb_game_tick(&game, &input, &frame);
    }
    if (game.ram[0x0770U] != 1U || game.ram[0x000eU] != 11U ||
        game.ram[0x001dU] != 1U) return 1;

    mysmb_game_initialize(&game);
    if (mysmb_area_load_pointers(&game, &source) == 0U ||
        game.ram[0x0750U] != 0x25U || game.ram[0x074eU] != 1U ||
        mysmb_area_parse_header(&game, &source) == 0U) {
        return 1;
    }
    count = 0U;
    while (count < 32U && mysmb_area_next_object(&game, &source, &object) != 0U) {
        count++;
    }
    if (count == 0U) {
        return 1;
    }
    printf("area_pointer=%02x type=%u enemy=%02x%02x area=%02x%02x header=%u/%u/%u objects=%u\n",
           game.ram[0x0750U], game.ram[0x074eU], game.ram[0x00eaU],
           game.ram[0x00e9U], game.ram[0x00e8U], game.ram[0x00e7U],
           game.ram[0x0710U], game.ram[0x0727U], game.ram[0x0742U], count);
    return 0;
}
