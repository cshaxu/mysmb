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

    /* AreaParserCore processes the admitted object stream after terrain and
     * before block-buffer commit, so a row object changes collision output. */
    prg[0x0040U] = 0x25U;
    prg[0x0041U] = 0x22U;
    prg[0x0042U] = 0xfdU;
    game.ram[0x00e7U] = 0x40U;
    game.ram[0x00e8U] = 0x80U;
    game.ram[0x0725U] = 0U;
    game.ram[0x0726U] = 2U;
    game.ram[0x06a0U] = 2U;
    game.ram[0x072aU] = 0U;
    game.ram[0x072bU] = 0U;
    game.ram[0x072cU] = 0U;
    game.ram[0x0730U] = 0xffU;
    game.ram[0x0731U] = 0xffU;
    game.ram[0x0732U] = 0xffU;
    if (mysmb_area_render_scenery_terrain_column(&game) == 0U ||
        game.ram[0x06a6U] != 0x51U || game.ram[0x0552U] != 0x51U ||
        game.ram[0x0732U] != 1U) return 1;
    game.ram[0x00e8U] = 0U;

    game.ram[0x06a0U] = 1U;
    game.ram[0x0742U] = 0U;
    game.ram[0x0741U] = 0U;
    game.ram[0x0743U] = 3U;
    if (mysmb_area_render_scenery_terrain_column(&game) == 0U ||
        game.ram[0x05b1U] != 0x88U || game.ram[0x05c1U] != 0U) return 1;

    /* AreaParserCore's backloading path processes row-14 control data before
     * it renders scenery and terrain.  The first stream object must therefore
     * select terrain control five in time for this same staging column. */
    prg[0x0040U] = 0x0eU;
    prg[0x0041U] = 0x25U;
    prg[0x0042U] = 0xfdU;
    prg[0x13dcU + 10U] = 1U;
    prg[0x13dcU + 11U] = 0U;
    game.ram[0x00e7U] = 0x40U;
    game.ram[0x00e8U] = 0x80U;
    game.ram[0x0725U] = 0U;
    game.ram[0x0726U] = 0U;
    game.ram[0x06a0U] = 0U;
    game.ram[0x071fU] = 0U;
    game.ram[0x0727U] = 0U;
    game.ram[0x0728U] = 1U;
    game.ram[0x0742U] = 0U;
    game.ram[0x0743U] = 0U;
    game.ram[0x072aU] = 0U;
    game.ram[0x072bU] = 0U;
    game.ram[0x072cU] = 0U;
    game.ram[0x072dU] = 0U;
    game.ram[0x072eU] = 0U;
    game.ram[0x072fU] = 0U;
    game.ram[0x0730U] = 0xffU;
    game.ram[0x0731U] = 0xffU;
    game.ram[0x0732U] = 0xffU;
    if (mysmb_area_parser_task_step(&game) == 0U) return 2;
    if (game.ram[0x071fU] != 7U) return 3;
    if (game.ram[0x0727U] != 5U) return 4;
    if (game.ram[0x0742U] != 2U) return 5;
    if (game.ram[0x06a1U] != 0x54U) return 6;
    game.ram[0x0728U] = 0U;

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
        game.ram[0x03b7U] != 1U || game.ram[0x03b9U] != 0x23U ||
        game.ram[0x03bbU] != 1U ||
        (mysmb_u8)(game.ram[0x03baU] - game.ram[0x03b6U]) != 8U ||
        game.ram[0x03f9U] != 0U ||
        game.ram[0x03ffU] != 0U) return 1;
    game.ram[0x071eU] = 0U;
    game.ram[0x071fU] = 0U;
    game.ram[0x0340U] = 0U;
    game.ram[0x0720U] = 0x20U;
    game.ram[0x0721U] = 0x80U;
    game.ram[0x0774U] = 0U;
    game.ram[0x073cU] = 8U;
    if (mysmb_area_parser_task_control(&game) == 0U ||
        game.ram[0x071eU] != 0xffU || game.ram[0x071fU] != 0U ||
        game.ram[0x0340U] != 144U || game.ram[0x0773U] != 6U ||
        game.ram[0x0774U] != 1U || game.ram[0x073cU] != 9U) return 1;

    /* ROM's bpl OutputCol branch selects buffer control six but leaves the
     * screen task unchanged while another column set remains. */
    game.ram[0x071eU] = 1U;
    game.ram[0x071fU] = 0U;
    game.ram[0x0340U] = 0U;
    game.ram[0x0720U] = 0x20U;
    game.ram[0x0721U] = 0x80U;
    game.ram[0x0774U] = 0U;
    game.ram[0x073cU] = 8U;
    if (mysmb_area_parser_task_control(&game) == 0U ||
        game.ram[0x071eU] != 0U || game.ram[0x071fU] != 0U ||
        game.ram[0x0773U] != 6U || game.ram[0x0774U] != 1U ||
        game.ram[0x073cU] != 8U) return 1;

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

    /* Row-14 changes the source-owned terrain/scenery attributes used by
     * following columns; d6 selects foreground/background-color semantics. */
    prg[0x0040U] = 0x0eU;
    prg[0x0041U] = 0x25U;
    prg[0x0042U] = 0xfdU;
    game.ram[0x0725U] = 0U;
    game.ram[0x0726U] = 0U;
    game.ram[0x072aU] = 0U;
    game.ram[0x072bU] = 0U;
    game.ram[0x072cU] = 0U;
    game.ram[0x0730U] = 0xffU;
    game.ram[0x0731U] = 0xffU;
    game.ram[0x0732U] = 0xffU;
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x0727U] != 5U || game.ram[0x0742U] != 2U) return 1;
    prg[0x0041U] = 0x45U;
    game.ram[0x072cU] = 0U;
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x0744U] != 5U || game.ram[0x0741U] != 0U) return 1;
    prg[0x0041U] = 0x42U;
    game.ram[0x072cU] = 0U;
    if (mysmb_area_process_object_state(&game) == 0U || game.ram[0x0741U] != 2U)
        return 1;

    /* A matching stream object occupies the last free slot and the existing
     * slot is revisited, not read from the stream, on the next column. */
    prg[0x0040U] = 0x27U;
    prg[0x0041U] = 0x22U;
    prg[0x0042U] = 0xfdU;
    game.ram[0x0725U] = 1U;
    game.ram[0x0726U] = 2U;
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
    /* Normal-row selector zero, value two is the collision-only hidden coin
     * block.  It must reach the persistent block buffer as $5f even though
     * its metatile is absent from the nametable before a head bump. */
    prg[0x0040U] = 0x55U;
    prg[0x0041U] = 0x02U;
    game.ram[0x0726U] = 5U;
    game.ram[0x072cU] = 0U;
    game.ram[0x0732U] = 0xffU;
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x06a6U] != 0x5fU || game.ram[0x0732U] != 0xffU) return 1;

    prg[0x0040U] = 0x45U;
    prg[0x0041U] = 0x53U;
    game.ram[0x0726U] = 4U;
    game.ram[0x072cU] = 0U;
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x06a6U] != 0x51U || game.ram[0x06a7U] != 0x51U ||
        game.ram[0x06a8U] != 0x51U || game.ram[0x06a9U] != 0x51U ||
        game.ram[0x0732U] != 0xffU) return 1;

    /* Vertical pipes are two parser columns wide and use the fixed length
     * one slot convention before drawing their top and shaft metatiles. */
    /* The first-column pipe-table entry is selected by its fixed length,
     * rather than this object's vertical height (two). */
    prg[0x0040U] = 0x68U;
    prg[0x0041U] = 0xf2U;
    game.ram[0x0726U] = 6U;
    game.ram[0x072bU] = 1U;
    game.ram[0x072cU] = 0U;
    game.ram[0x0732U] = 0xffU;
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x06a9U] != 0x12U || game.ram[0x06aaU] != 0x14U ||
        game.ram[0x06abU] != 0x14U ||
        game.ram[0x0732U] != 0U) return 1;
    game.ram[0x0726U] = 7U;
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x06a9U] != 0x13U || game.ram[0x06aaU] != 0x15U ||
        game.ram[0x06abU] != 0x15U ||
        game.ram[0x0732U] != 0xffU) return 1;

    /* Row-15 exit pipes use their fixed four-column side-pipe table; the
     * final two columns also grow a source-defined shaft above the elbow. */
    prg[0x0040U] = 0x0fU;
    prg[0x0041U] = 0x44U;
    game.ram[0x0725U] = 0U;
    game.ram[0x0726U] = 0U;
    game.ram[0x072aU] = 0U;
    game.ram[0x072bU] = 0U;
    game.ram[0x072cU] = 0U;
    game.ram[0x0730U] = 0xffU;
    game.ram[0x0731U] = 0xffU;
    game.ram[0x0732U] = 0xffU;
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x06a4U] != 0x1cU || game.ram[0x06a5U] != 0x1fU ||
        game.ram[0x0732U] != 2U) return 1;
    game.ram[0x0726U] = 1U;
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x06a4U] != 0x1dU || game.ram[0x06a5U] != 0x20U ||
        game.ram[0x0732U] != 1U) return 1;
    game.ram[0x0726U] = 2U;
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x06a1U] != 0x14U || game.ram[0x06a4U] != 0x1eU ||
        game.ram[0x06a5U] != 0x21U || game.ram[0x0732U] != 0U) return 1;

    /* FlagBalls_Residual starts at its fixed third metatile row and treats
     * the low nibble as its downward render extent without a parser slot. */
    prg[0x0040U] = 0x0fU;
    prg[0x0041U] = 0x52U;
    prg[0x0042U] = 0xfdU;
    game.ram[0x0725U] = 0U;
    game.ram[0x0726U] = 0U;
    game.ram[0x072aU] = 0U;
    game.ram[0x072bU] = 0U;
    game.ram[0x072cU] = 0U;
    game.ram[0x0730U] = 0xffU;
    game.ram[0x0731U] = 0xffU;
    game.ram[0x0732U] = 0xffU;
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x06a3U] != 0x6dU || game.ram[0x06a4U] != 0x6dU ||
        game.ram[0x06a5U] != 0x6dU || game.ram[0x0732U] != 0xffU) return 1;

    /* Special row 12 selector seven is a question-block row, not a pipe. */
    prg[0x0040U] = 0x7cU;
    prg[0x0041U] = 0x71U;
    game.ram[0x0725U] = 1U;
    game.ram[0x0726U] = 7U;
    game.ram[0x072cU] = 0U;
    game.ram[0x072aU] = 1U;
    game.ram[0x072bU] = 0U;
    game.ram[0x0732U] = 0xffU;
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x06a8U] != 0xc0U || game.ram[0x0732U] != 0U) return 1;

    /* Row-12 holes and bridges use their special table, fixed rows, and
     * horizontal length slots rather than normal-row object decoding. */
    prg[0x0040U] = 0x8cU;
    prg[0x0041U] = 0x00U;
    game.ram[0x0726U] = 8U;
    game.ram[0x072cU] = 0U;
    game.ram[0x0732U] = 0xffU;
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x06a9U] != 0U || game.ram[0x06adU] != 0U ||
        game.ram[0x0732U] != 0xffU || game.ram[0x0735U] != 0x0bU) return 1;
    prg[0x0040U] = 0x9cU;
    prg[0x0041U] = 0x22U;
    game.ram[0x0726U] = 9U;
    game.ram[0x072cU] = 0U;
    game.ram[0x0732U] = 0xffU;
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x06a7U] != 0x0bU || game.ram[0x06a8U] != 0x63U ||
        game.ram[0x0732U] != 1U) return 1;

    /* A row-12 pulley has its own first/rope/last metatile sequence while
     * using the ordinary horizontal parser-length countdown. */
    prg[0x0040U] = 0x0cU;
    prg[0x0041U] = 0x12U;
    game.ram[0x0725U] = 0U;
    game.ram[0x0726U] = 0U;
    game.ram[0x072aU] = 0U;
    game.ram[0x072bU] = 0U;
    game.ram[0x072cU] = 0U;
    game.ram[0x0730U] = 0xffU;
    game.ram[0x0731U] = 0xffU;
    game.ram[0x0732U] = 0xffU;
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x06a1U] != 0x42U || game.ram[0x0732U] != 1U) return 1;
    game.ram[0x0726U] = 1U;
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x06a1U] != 0x41U || game.ram[0x0732U] != 0U) return 1;
    game.ram[0x0726U] = 2U;
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x06a1U] != 0x43U || game.ram[0x0732U] != 0xffU) return 1;

    /* Special row 15 has its own rope and staircase table. */
    prg[0x0040U] = 0xafU;
    prg[0x0041U] = 0x00U;
    game.ram[0x0726U] = 10U;
    game.ram[0x072cU] = 0U;
    game.ram[0x0732U] = 0xffU;
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x06a1U] != 0x40U || game.ram[0x06adU] != 0x40U ||
        game.ram[0x0732U] != 0xffU) return 1;
    prg[0x0040U] = 0x0fU;
    prg[0x0041U] = 0x33U;
    game.ram[0x0726U] = 0U;
    game.ram[0x072cU] = 0U;
    game.ram[0x0732U] = 0xffU;
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x06abU] != 0x61U || game.ram[0x0732U] != 2U) return 1;

    /* Row 13 flagpole uses its low-six-bit special-object code. */
    prg[0x0040U] = 0x0dU;
    prg[0x0041U] = 0x41U;
    game.ram[0x0726U] = 0U;
    game.ram[0x072cU] = 0U;
    game.ram[0x0732U] = 0xffU;
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x06a1U] != 0x24U || game.ram[0x06a2U] != 0x25U ||
        game.ram[0x06abU] != 0x61U || game.ram[0x0732U] != 0xffU ||
        game.ram[0x0087U + 5U] != 0xf8U || game.ram[0x006eU + 5U] != 0xffU ||
        game.ram[0x00cfU + 5U] != 0x30U || game.ram[0x0016U + 5U] != 48U ||
        game.ram[0x000fU + 5U] != 1U || game.ram[0x010dU] != 0xb0U) return 1;

    /* Row-13 intro pipes share the source's four-column sideways-pipe data,
     * and its late columns establish the vertical-pipe cap and shaft. */
    prg[0x0040U] = 0x0dU;
    prg[0x0041U] = 0x40U;
    game.ram[0x0725U] = 0U;
    game.ram[0x0726U] = 0U;
    game.ram[0x072aU] = 0U;
    game.ram[0x072bU] = 0U;
    game.ram[0x072cU] = 0U;
    game.ram[0x0730U] = 0xffU;
    game.ram[0x0731U] = 0xffU;
    game.ram[0x0732U] = 0xffU;
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x06aaU] != 0x1cU || game.ram[0x06abU] != 0x1fU ||
        game.ram[0x0732U] != 2U) return 1;
    game.ram[0x0726U] = 1U;
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x06aaU] != 0x1dU || game.ram[0x06abU] != 0x20U ||
        game.ram[0x0732U] != 1U) return 1;
    game.ram[0x0726U] = 2U;
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x06a8U] != 0x10U || game.ram[0x06a9U] != 0x14U ||
        game.ram[0x06aaU] != 0x1eU || game.ram[0x06abU] != 0x21U ||
        game.ram[0x0732U] != 0U) return 1;

    /* Axe, chain, and castle bridge retain their row-13 metatile table. */
    prg[0x0040U] = 0x0dU;
    prg[0x0041U] = 0x42U;
    game.ram[0x0726U] = 0U;
    game.ram[0x072cU] = 0U;
    game.ram[0x0732U] = 0xffU;
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x06a7U] != 0xc5U || game.ram[0x0773U] != 8U) return 1;
    prg[0x0041U] = 0x44U;
    game.ram[0x072cU] = 0U;
    game.ram[0x0732U] = 0xffU;
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x06a9U] != 0x89U || game.ram[0x0732U] != 11U) return 1;

    /* AreaStyleObject chooses the header-selected tree/mushroom/cannon
     * family and tree/mushroom rows persist through their length slots. */
    prg[0x0040U] = 0x25U;
    prg[0x0041U] = 0x13U;
    game.ram[0x0726U] = 2U;
    game.ram[0x072cU] = 0U;
    game.ram[0x0732U] = 0xffU;
    game.ram[0x0733U] = 0U;
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x06a6U] != 0x16U || game.ram[0x0732U] != 2U) return 1;
    game.ram[0x0726U] = 3U;
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x06a6U] != 0x17U || game.ram[0x06a7U] != 0x4cU ||
        game.ram[0x0732U] != 1U) return 1;

    /* RenderUnderPart keeps ledge centers and palette-three foreground
     * objects, but must replace a coin block and ordinary scenery. */
    prg[0x0040U] = 0x05U;
    prg[0x0041U] = 0x57U;
    game.ram[0x0725U] = 0U;
    game.ram[0x072aU] = 0U;
    game.ram[0x072bU] = 0U;
    game.ram[0x074eU] = 1U;
    game.ram[0x0726U] = 0U;
    game.ram[0x072cU] = 0U;
    game.ram[0x0730U] = 0xffU;
    game.ram[0x0731U] = 0xffU;
    game.ram[0x0732U] = 0xffU;
    game.ram[0x06a6U] = 0x17U;
    game.ram[0x06a7U] = 0x1aU;
    game.ram[0x06a8U] = 0xc0U;
    game.ram[0x06a9U] = 0xc1U;
    game.ram[0x06aaU] = 0x4cU;
    game.ram[0x06abU] = 0x54U;
    game.ram[0x06acU] = 0x50U;
    game.ram[0x06adU] = 0x54U;
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x06a6U] != 0x17U || game.ram[0x06a7U] != 0x1aU ||
        game.ram[0x06a8U] != 0x51U || game.ram[0x06a9U] != 0xc1U ||
        game.ram[0x06aaU] != 0x51U || game.ram[0x06abU] != 0x51U ||
        game.ram[0x06acU] != 0x51U || game.ram[0x06adU] != 0x51U) return 1;

    /* ROM Hidden1UpBlock ($a065) consumes Hidden1UpFlag and then takes the
     * BrickWithItem selector-three path, which writes hidden metatile $60.
     * When the flag is clear, the same area-data selector stays invisible. */
    prg[0x0040U] = 0x06U;
    prg[0x0041U] = 0x03U;
    prg[0x0042U] = 0xfdU;
    game.ram[0x00e7U] = 0x40U;
    game.ram[0x00e8U] = 0x80U;
    game.ram[0x0725U] = 0U;
    game.ram[0x0726U] = 0U;
    game.ram[0x072aU] = 0U;
    game.ram[0x072bU] = 0U;
    game.ram[0x072cU] = 0U;
    game.ram[0x0730U] = 0xffU;
    game.ram[0x0731U] = 0xffU;
    game.ram[0x0732U] = 0xffU;
    game.ram[0x075dU] = 1U;
    game.ram[0x06a7U] = 0U;
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x075dU] != 0U || game.ram[0x06a7U] != 0x60U) return 1;
    game.ram[0x072cU] = 0U;
    game.ram[0x0730U] = 0xffU;
    game.ram[0x0731U] = 0xffU;
    game.ram[0x0732U] = 0xffU;
    game.ram[0x074eU] = 2U;
    game.ram[0x075dU] = 1U;
    game.ram[0x06a7U] = 0U;
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x075dU] != 0U || game.ram[0x06a7U] != 0x59U) return 1;
    game.ram[0x074eU] = 1U;
    game.ram[0x072cU] = 0U;
    game.ram[0x0730U] = 0xffU;
    game.ram[0x0731U] = 0xffU;
    game.ram[0x0732U] = 0xffU;
    game.ram[0x06a7U] = 0U;
    if (mysmb_area_process_object_state(&game) == 0U || game.ram[0x06a7U] != 0U)
        return 1;
    /* ROM CastleObject ($9808): AF 26 retains fixed length four before the
     * ProcessAreaData tail decrements it to three. STY $07 makes 6, the
     * second-byte low nibble, the buffer start; it writes the castle column
     * at rows 6--10 rather than using row $0f. */
    prg[0x0040U] = 0x2fU;
    prg[0x0041U] = 0x26U;
    prg[0x0042U] = 0xfdU;
    game.ram[0x00e7U] = 0x40U;
    game.ram[0x00e8U] = 0x80U;
    game.ram[0x0725U] = 1U;
    game.ram[0x0726U] = 2U;
    game.ram[0x072aU] = 1U;
    game.ram[0x072bU] = 0U;
    game.ram[0x072cU] = 0U;
    game.ram[0x0730U] = 0xffU;
    game.ram[0x0731U] = 0xffU;
    game.ram[0x0732U] = 0xffU;
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x0732U] != 3U || game.ram[0x06a9U] != 0x45U ||
        game.ram[0x06aaU] != 0x47U || game.ram[0x06abU] != 0x47U)
        return 1;
    /* CastleObject reaches its len==2 StarFlagObject leaf on the third
     * continuation: ProcessAreaData decrements after each source handler. */
    game.ram[0x0726U] = 3U;
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x0732U] != 2U || game.ram[0x000fU] != 0U) return 1;
    game.ram[0x0726U] = 4U;
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x0732U] != 1U || game.ram[0x000fU] != 1U ||
        game.ram[0x0016U] != 0x31U || game.ram[0x006eU] != 1U ||
        game.ram[0x0087U] != 0x40U || game.ram[0x00b6U] != 1U ||
        game.ram[0x00cfU] != 0x90U) return 1;
    return 0;
}
