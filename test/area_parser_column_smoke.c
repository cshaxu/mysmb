#include "game/game.h"
#include "game/area.h"

int main(void)
{
    struct mysmb_game game;
    static mysmb_u8 prg[0x1600U];
    unsigned int index;

    for (index = 0U; index < sizeof(prg); ++index) prg[index] = 0U;
    prg[0x12f7U] = 0U;
    prg[0x12faU + 18U] = 0x32U;
    prg[0x138aU + 3U] = 0x10U;
    prg[0x138aU + 4U] = 0x11U;
    prg[0x138aU + 5U] = 0x12U;
    prg[0x13aeU + 1U] = 13U;
    prg[0x13b1U + 13U + 4U] = 0x55U;
    prg[0x13b1U + 13U + 6U] = 0x50U;
    prg[0x13b1U + 13U + 7U] = 0x51U;
    prg[0x13d8U] = 0x69U;
    prg[0x13d8U + 1U] = 0x54U;
    prg[0x13d8U + 2U] = 0x52U;
    prg[0x13d8U + 3U] = 0x62U;
    prg[0x13dcU + 2U] = 0U;
    prg[0x13dcU + 3U] = 0x18U;
    prg[0x1504U] = 0x10U;
    prg[0x1504U + 1U] = 0x51U;
    prg[0x1504U + 2U] = 0x88U;
    prg[0x1504U + 3U] = 0xc0U;
    prg[0x0b08U] = 0U;
    prg[0x0b0cU] = 0x80U;
    prg[0x0b0dU] = 0x80U;
    prg[0x0b0eU] = 0x80U;
    prg[0x0b0fU] = 0x80U;
    prg[0x0040U] = 0x40U;
    prg[0x0041U] = 0x41U;
    prg[0x0042U] = 0x42U;
    prg[0x0043U] = 0x43U;

    mysmb_game_initialize(&game);
    mysmb_game_bind_area_source(&game, prg, (mysmb_u16)sizeof(prg));
    game.ram[0x0725U] = 1U;
    game.ram[0x0726U] = 2U;
    game.ram[0x06a0U] = 0U;
    game.ram[0x0742U] = 1U;
    game.ram[0x0741U] = 2U;
    game.ram[0x074eU] = 1U;
    game.ram[0x0727U] = 1U;
    if (mysmb_area_render_scenery_terrain_column(&game) == 0U ||
        game.ram[0x0530U] != 0x10U || game.ram[0x0540U] != 0x55U ||
        game.ram[0x0550U] != 0x12U || game.ram[0x0560U] != 0U ||
        game.ram[0x0570U] != 0x51U || game.ram[0x05b0U] != 0x54U ||
        game.ram[0x05c0U] != 0x54U) return 1;

    game.ram[0x06a0U] = 1U;
    game.ram[0x0742U] = 0U;
    game.ram[0x0741U] = 0U;
    game.ram[0x0743U] = 3U;
    if (mysmb_area_render_scenery_terrain_column(&game) == 0U ||
        game.ram[0x05b1U] != 0x88U || game.ram[0x05c1U] != 0U) return 1;

    game.ram[0x0725U] = 0U;
    game.ram[0x0726U] = 0U;
    game.ram[0x06a0U] = 0U;
    game.ram[0x071fU] = 0U;
    game.ram[0x0720U] = 0x20U;
    game.ram[0x0721U] = 0x80U;
    game.ram[0x0340U] = 0U;
    game.ram[0x0743U] = 0U;
    if (mysmb_area_parser_task_step(&game) == 0U ||
        game.ram[0x071fU] != 7U || game.ram[0x0726U] != 0U ||
        game.ram[0x06a0U] != 0U) return 1;
    if (mysmb_area_parser_task_step(&game) == 0U ||
        game.ram[0x071fU] != 6U || game.ram[0x0340U] != 29U ||
        game.ram[0x0341U] != 0x20U || game.ram[0x0342U] != 0x80U ||
        game.ram[0x0343U] != 0x9aU || game.ram[0x0773U] != 6U) return 1;
    if (mysmb_area_parser_task_step(&game) == 0U ||
        mysmb_area_parser_task_step(&game) == 0U ||
        mysmb_area_parser_task_step(&game) == 0U ||
        mysmb_area_parser_task_step(&game) == 0U ||
        mysmb_area_parser_task_step(&game) == 0U ||
        mysmb_area_parser_task_step(&game) == 0U) return 1;
    if (game.ram[0x071fU] != 0U || game.ram[0x0340U] != 144U ||
        game.ram[0x037bU] != 0x20U || game.ram[0x037cU] != 0x82U ||
        game.ram[0x037dU] != 0x9aU || game.ram[0x03b5U] != 0x23U ||
        game.ram[0x03b7U] != 1U || game.ram[0x03f9U] != 0U ||
        game.ram[0x03ffU] != 0U) return 1;
    game.ram[0x071eU] = 0U;
    game.ram[0x071fU] = 0U;
    game.ram[0x0340U] = 0U;
    game.ram[0x0720U] = 0x20U;
    game.ram[0x0721U] = 0x80U;
    if (mysmb_area_parser_task_control(&game) == 0U ||
        game.ram[0x071eU] != 0xffU || game.ram[0x071fU] != 0U ||
        game.ram[0x0340U] != 144U || game.ram[0x0773U] != 6U) return 1;

    /* ProcessAreaData page-control entries advance without using a slot. */
    prg[0x0040U] = 0x0dU;
    prg[0x0041U] = 0x01U;
    prg[0x0042U] = 0xfdU;
    game.ram[0x00e7U] = 0x40U;
    game.ram[0x00e8U] = 0x80U;
    game.ram[0x0725U] = 1U;
    game.ram[0x0726U] = 2U;
    game.ram[0x072aU] = 0U;
    game.ram[0x072bU] = 0U;
    game.ram[0x072cU] = 0U;
    game.ram[0x072dU] = 0U;
    game.ram[0x072eU] = 0U;
    game.ram[0x072fU] = 0U;
    game.ram[0x0730U] = 0xffU;
    game.ram[0x0731U] = 0xffU;
    game.ram[0x0732U] = 0xffU;
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x072aU] != 1U || game.ram[0x072cU] != 2U ||
        game.ram[0x072dU] != 0U || game.ram[0x072eU] != 0U ||
        game.ram[0x072fU] != 0U) return 1;

    /* A matching stream object occupies the last free slot and the existing
     * slot is revisited, not read from the stream, on the next column. */
    prg[0x0040U] = 0x27U;
    prg[0x0041U] = 0x22U;
    prg[0x0042U] = 0xfdU;
    game.ram[0x072aU] = 1U;
    game.ram[0x072cU] = 0U;
    game.ram[0x0743U] = 0U;
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x072fU] != 0U || game.ram[0x0732U] != 1U ||
        game.ram[0x06a8U] != 0x51U || game.ram[0x072cU] != 2U) return 1;
    game.ram[0x0726U] = 3U;
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x0732U] != 0U || game.ram[0x06a8U] != 0x51U ||
        game.ram[0x072cU] != 2U) return 1;

    /* Small objects and vertical columns render once and retain an empty
     * parser length slot, unlike horizontal row families. */
    prg[0x0040U] = 0x34U;
    prg[0x0041U] = 0x04U;
    prg[0x0042U] = 0xfdU;
    game.ram[0x0726U] = 3U;
    game.ram[0x072cU] = 0U;
    game.ram[0x0732U] = 0xffU;
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x06a5U] != 0x55U || game.ram[0x0732U] != 0xffU) return 1;
    prg[0x0040U] = 0x45U;
    prg[0x0041U] = 0x53U;
    game.ram[0x0726U] = 4U;
    game.ram[0x072cU] = 0U;
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x06a6U] != 0x51U || game.ram[0x06a7U] != 0x51U ||
        game.ram[0x06a8U] != 0x51U || game.ram[0x06a9U] != 0x51U ||
        game.ram[0x0732U] != 0xffU) return 1;
    return 0;
}
