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
