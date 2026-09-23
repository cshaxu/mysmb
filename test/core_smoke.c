#include "game/game.h"
#include "game/area.h"
#include "game/player.h"

int main(void)
{
    struct mysmb_game game;
    struct mysmb_input input;
    struct mysmb_frame frame;
    struct mysmb_checkpoint checkpoint;
    struct mysmb_area_source area_source;
    struct mysmb_area_object area_object;
    static mysmb_u8 area_prg[0x2000U];
    const mysmb_u8 title_commands[] = {
        0x20U, 0x00U, 0x02U, 0x11U, 0x12U,
        0x20U, 0x21U, 0xc2U, 0x33U, 0x00U
    };
    unsigned int index;

    for (index = 0U; index < sizeof(area_prg); ++index) {
        area_prg[index] = 0U;
    }
    area_prg[0x1cb4U] = 2U;
    area_prg[0x1cbeU] = 0x45U;
    area_prg[0x1ce2U] = 0U;
    area_prg[0x1ce9U] = 0x34U;
    area_prg[0x1d0bU] = 0x12U;
    area_prg[0x1d2aU] = 0U;
    area_prg[0x1d31U] = 0x78U;
    area_prg[0x1d53U] = 0x56U;
    area_prg[0x1f00U] = 0xedU;
    area_prg[0x1f01U] = 0xb9U;
    area_prg[0x1f02U] = 0x1dU;
    area_prg[0x1f03U] = 0x03U;
    area_prg[0x1f04U] = 0x22U;
    area_prg[0x1f05U] = 0x81U;
    area_prg[0x1f06U] = 0xfdU;
    area_source.prg = area_prg;
    area_source.prg_size = (mysmb_u16)sizeof(area_prg);

    mysmb_game_initialize(&game);
    game.ram[0x0490U] = 3U;
    game.ram[0x0450U] = 0xf0U;
    game.ram[0x0456U] = 4U;
    game.ram[0x0701U] = 0U;
    game.ram[0x0702U] = 0x20U;
    mysmb_player_step(&game, MYSMB_BUTTON_A);
    if (game.ram[0x001dU] != 1U || game.ram[0x0782U] != 0x20U ||
        game.ram[0x000dU] != MYSMB_BUTTON_A) {
        return 1;
    }
    game.ram[0x001dU] = 0U;
    mysmb_player_latch_input(&game, (mysmb_u8)(MYSMB_BUTTON_A | MYSMB_BUTTON_RIGHT));
    if (game.ram[0x000aU] != MYSMB_BUTTON_A ||
        game.ram[0x000cU] != MYSMB_BUTTON_RIGHT || game.ram[0x000bU] != 0U) {
        return 1;
    }
    game.ram[0x000cU] = MYSMB_BUTTON_RIGHT;
    game.ram[0x0490U] = MYSMB_BUTTON_RIGHT;
    game.ram[0x0057U] = 0U;
    game.ram[0x0705U] = 0xf0U;
    game.ram[0x0701U] = 0U;
    game.ram[0x0702U] = 0x20U;
    game.ram[0x0456U] = 4U;
    game.ram[0x0450U] = 0xf0U;
    mysmb_player_impose_friction(&game);
    if (game.ram[0x0057U] != 1U || game.ram[0x0705U] != 0x10U ||
        game.ram[0x0700U] != 1U) {
        return 1;
    }
    game.ram[0x0700U] = 0x1cU;
    game.ram[0x00b5U] = 2U;
    game.ram[0x00ceU] = 0x90U;
    mysmb_player_start_jump(&game, 0U);
    if (game.ram[0x0782U] != 0x20U || game.ram[0x001dU] != 1U ||
        game.ram[0x0707U] != 2U || game.ram[0x0708U] != 0x90U ||
        game.ram[0x0709U] != 0x28U || game.ram[0x070aU] != 0x90U ||
        game.ram[0x0433U] != 0U || game.ram[0x009fU] != 0xfbU) {
        return 1;
    }
    game.ram[0x009fU] = 1U;
    game.ram[0x00b5U] = 2U;
    game.ram[0x00ceU] = 0xffU;
    game.ram[0x0416U] = 0U;
    game.ram[0x0433U] = 0x80U;
    mysmb_player_impose_gravity(&game, 0x80U, 0U, 4U, 0U);
    if (game.ram[0x00ceU] != 0U || game.ram[0x00b5U] != 3U ||
        game.ram[0x009fU] != 2U || game.ram[0x0433U] != 0U) {
        return 1;
    }
    game.ram[0x009fU] = 0xf0U;
    game.ram[0x00b5U] = 3U;
    game.ram[0x00ceU] = 0U;
    game.ram[0x0416U] = 0U;
    game.ram[0x0433U] = 0U;
    mysmb_player_impose_gravity(&game, 0U, 0x20U, 4U, 1U);
    if (game.ram[0x00ceU] != 0xf0U || game.ram[0x00b5U] != 2U ||
        game.ram[0x009fU] != 0xefU || game.ram[0x0433U] != 0xe0U) {
        return 1;
    }
    game.ram[0x0057U] = 0x11U;
    game.ram[0x0086U] = 0xfeU;
    game.ram[0x006dU] = 2U;
    game.ram[0x0705U] = 0xf0U;
    mysmb_player_move_horizontally(&game);
    if (game.ram[0x0086U] != 0U || game.ram[0x006dU] != 3U ||
        game.ram[0x0705U] != 0U) {
        return 1;
    }
    game.ram[0x0057U] = 0xf0U;
    game.ram[0x0086U] = 0U;
    game.ram[0x006dU] = 3U;
    mysmb_player_move_horizontally(&game);
    if (game.ram[0x0086U] != 0xffU || game.ram[0x006dU] != 2U) {
        return 1;
    }
    game.ram[0x075fU] = 0U;
    game.ram[0x0760U] = 0U;
    if (mysmb_area_load_pointers(&game, &area_source) == 0U ||
        game.ram[0x0750U] != 0x45U || game.ram[0x074eU] != 2U ||
        game.ram[0x074fU] != 5U || game.ram[0x00e9U] != 0x34U ||
        game.ram[0x00eaU] != 0x12U || game.ram[0x00e7U] != 0x78U ||
        game.ram[0x00e8U] != 0x56U) {
        return 1;
    }
    game.ram[0x00e7U] = 0U;
    game.ram[0x00e8U] = 0x9fU;
    if (mysmb_area_parse_header(&game, &area_source) == 0U ||
        game.ram[0x0744U] != 5U || game.ram[0x0741U] != 0U ||
        game.ram[0x0710U] != 5U || game.ram[0x0715U] != 3U ||
        game.ram[0x0727U] != 9U || game.ram[0x0742U] != 3U ||
        game.ram[0x0743U] != 0U || game.ram[0x0733U] != 2U ||
        game.ram[0x00e7U] != 2U || game.ram[0x00e8U] != 0x9fU) {
        return 1;
    }
    if (mysmb_area_next_object(&game, &area_source, &area_object) == 0U ||
        area_object.is_page_control != 1U || area_object.dispatch_id != 0xffU ||
        area_object.page != 3U ||
        game.ram[0x072cU] != 2U ||
        mysmb_area_next_object(&game, &area_source, &area_object) == 0U ||
        area_object.page != 4U || area_object.dispatch_id != 0x17U ||
        area_object.behind_current_page != 0U ||
        game.ram[0x072cU] != 4U ||
        mysmb_area_next_object(&game, &area_source, &area_object) != 0U) {
        return 1;
    }
    input.buttons = 0U;
    for (index = 0U; index < 120U; ++index) {
        mysmb_game_tick(&game, &input, &frame);
    }

    if (game.frame_number != 120UL || game.ram[0x07feU] != 0U ||
        game.ram[0x07ffU] != 0xffU || game.ram[0x015fU] != 0U ||
        game.ram[0x0160U] != 0xffU || game.ram[0x01feU] != 0xffU ||
        game.ram[0x0200U] != 0xf8U || game.ram[0x0204U] != 0xf8U ||
        game.ram[0x02fcU] != 0xf8U || game.ram[0x0201U] != 0U ||
        game.name_table[0][0U] != 0x24U ||
        game.name_table[1][0x03bfU] != 0x24U ||
        game.name_table[0][0x03c0U] != 0U ||
        game.name_table[1][0x03ffU] != 0U) {
        return 1;
    }

    game.ram[0x07d7U] = 0xffU;
    mysmb_game_initialize_memory(&game, 0xd6U);
    if (game.ram[0x07d6U] != 0U || game.ram[0x07d7U] != 0xffU) {
        return 1;
    }
    /* InitializeGame restores this after its partial RAM clear. */
    game.ram[0x07a2U] = 0x18U;
    game.ram[0x0770U] = 0U;
    game.ram[0x0772U] = 3U;

    if (mysmb_game_apply_title_commands(&game, title_commands,
                                        (mysmb_u16)sizeof(title_commands)) == 0U ||
        game.name_table[0][0U] != 0x11U || game.name_table[0][1U] != 0x12U ||
        game.name_table[0][0x21U] != 0x33U ||
        game.name_table[0][0x41U] != 0x33U) {
        return 1;
    }

    input.buttons = MYSMB_BUTTON_START;
    mysmb_game_tick(&game, &input, &frame);
    mysmb_game_checkpoint(&game, &checkpoint);
    if (frame.start_pressed != 1U || frame.operating_mode != 1U ||
        frame.operating_mode_task != 0U || checkpoint.demo_timer != 0U ||
        checkpoint.operating_mode != 1U || checkpoint.operating_mode_task != 0U ||
        game.ram[0x0757U] != 1U || game.ram[0x075dU] != 1U ||
        game.ram[0x0764U] != 1U) {
        return 1;
    }

    mysmb_game_tick(&game, &input, &frame);
    if (frame.start_pressed != 0U) {
        return 1;
    }
    if (frame.operating_mode_task != 1U || game.ram[0x0720U] != 0x20U ||
        game.ram[0x0721U] != 0x80U || game.ram[0x0730U] != 0xffU ||
        game.ram[0x0732U] != 0xffU || game.ram[0x071eU] != 0x0bU) {
        return 1;
    }

    mysmb_game_initialize(&game);
    input.buttons = MYSMB_BUTTON_SELECT;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x077aU] != 1U || game.ram[0x0780U] != 0x10U) {
        return 1;
    }
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x077aU] != 1U) {
        return 1;
    }

    mysmb_game_initialize(&game);
    game.ram[0x07fdU] = 6U;
    input.buttons = (mysmb_u8)(MYSMB_BUTTON_A | MYSMB_BUTTON_START);
    mysmb_game_tick(&game, &input, &frame);
    return game.ram[0x075fU] == 6U && game.ram[0x0760U] == 0U &&
           game.ram[0x0766U] == 6U && game.ram[0x0767U] == 0U ? 0 : 1;
}
