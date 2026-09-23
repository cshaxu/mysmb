#include "game/game.h"
#include "game/area.h"
#include "game/player.h"
#include "game/objects.h"

int main(void)
{
    struct mysmb_game game;
    struct mysmb_input input;
    struct mysmb_frame frame;
    struct mysmb_checkpoint checkpoint;
    struct mysmb_area_source area_source;
    struct mysmb_area_object area_object;
    struct mysmb_player_terrain terrain;
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
    area_prg[0x1234U] = 0x12U;
    area_prg[0x1235U] = 0x00U;
    area_prg[0x1236U] = 0xffU;
    area_source.prg = area_prg;
    area_source.prg_size = (mysmb_u16)sizeof(area_prg);

    mysmb_game_initialize(&game);
    if (game.ram[0x0754U] != 1U || game.ram[0x075aU] != 2U ||
        game.ram[0x0761U] != 2U) {
        return 1;
    }
    game.ram[0x071aU] = 3U;
    game.ram[0x074eU] = 1U;
    game.ram[0x0710U] = 2U;
    mysmb_player_initialize_entrance(&game);
    if (game.ram[0x006dU] != 3U || game.ram[0x0086U] != 0x28U ||
        game.ram[0x00b5U] != 1U || game.ram[0x00ceU] != 0xb0U ||
        game.ram[0x070aU] != 0x28U || game.ram[0x0490U] != 0xffU ||
        game.ram[0x000eU] != 7U) {
        return 1;
    }
    mysmb_player_finish_normal_entrance(&game);
    if (game.ram[0x000eU] != 8U || game.ram[0x0033U] != 1U) {
        return 1;
    }
    game.ram[0x000eU] = 7U;
    game.ram[0x0752U] = 1U;
    game.ram[0x0716U] = 1U;
    game.ram[0x0758U] = MYSMB_BUTTON_UP;
    mysmb_player_finish_normal_entrance(&game);
    if (game.ram[0x000eU] != 8U || game.ram[0x0752U] != 0U ||
        game.ram[0x0716U] != 0U || game.ram[0x0758U] != 0U) {
        return 1;
    }
    game.ram[0x000eU] = 7U;
    game.ram[0x0752U] = 2U;
    game.ram[0x00ceU] = 0x91U;
    mysmb_player_finish_normal_entrance(&game);
    if (game.ram[0x000eU] != 8U || game.ram[0x0752U] != 0U ||
        game.ram[0x00ceU] != 0x90U) {
        return 1;
    }
    game.ram[0x000eU] = 7U;
    game.ram[0x0710U] = 6U;
    game.ram[0x001dU] = 0U;
    game.ram[0x03c4U] = 0U;
    game.ram[0x0086U] = 0x20U;
    game.ram[0x0057U] = 0U;
    game.ram[0x0705U] = 0U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x30U;
    for (index = 0U; index < 40U; ++index) {
        mysmb_player_finish_normal_entrance(&game);
    }
    if (game.ram[0x000eU] != 7U || game.ram[0x0086U] <= 0x20U) {
        return 1;
    }
    game.ram[0x03c4U] = 0x20U;
    game.ram[0x06deU] = 1U;
    game.ram[0x0086U] = 0x20U;
    mysmb_player_finish_normal_entrance(&game);
    if (game.ram[0x0752U] != 2U || game.ram[0x0772U] != 0U) {
        return 1;
    }
    game.ram[0x0710U] = 2U;
    game.ram[0x001dU] = 0U;
    game.ram[0x000cU] = 0U;
    game.ram[0x000aU] = 0U;
    game.ram[0x0057U] = 0U;
    game.ram[0x0705U] = 0U;
    game.ram[0x0700U] = 0U;
    game.ram[0x0703U] = 0U;
    game.ram[0x000eU] = 8U;
    game.ram[0x0033U] = 1U;
    game.ram[0x0045U] = 1U;
    mysmb_player_configure_horizontal(&game);
    if (game.ram[0x0450U] != 0xe8U || game.ram[0x0456U] != 0x18U ||
        game.ram[0x0701U] != 0U || game.ram[0x0702U] != 0x98U) {
        return 1;
    }
    game.ram[0x0033U] = 2U;
    mysmb_player_configure_horizontal(&game);
    if (game.ram[0x0701U] != 1U || game.ram[0x0702U] != 0x30U) {
        return 1;
    }
    game.ram[0x0086U] = 0x60U;
    game.ram[0x071cU] = 0U;
    game.ram[0x071aU] = 0U;
    game.ram[0x06ffU] = 2U;
    game.ram[0x0755U] = 0x60U;
    mysmb_player_update_scroll(&game);
    if (game.ram[0x0755U] != 0x60U || game.ram[0x0775U] != 1U ||
        game.ram[0x071cU] != 1U || game.ram[0x071aU] != 0U ||
        game.ram[0x071dU] != 0U || game.ram[0x071bU] != 1U) {
        return 1;
    }
    game.ram[0x0086U] = 0x80U;
    game.ram[0x071cU] = 0xffU;
    game.ram[0x071aU] = 2U;
    game.ram[0x06ffU] = 2U;
    game.ram[0x0755U] = 0x81U;
    mysmb_player_update_scroll(&game);
    if (game.ram[0x0775U] != 2U || game.ram[0x071cU] != 1U ||
        game.ram[0x071aU] != 3U || game.ram[0x071dU] != 0U ||
        game.ram[0x071bU] != 4U) {
        return 1;
    }
    game.ram[0x071aU] = 2U;
    game.ram[0x071cU] = 0x20U;
    game.ram[0x071bU] = 3U;
    game.ram[0x071dU] = 0x1fU;
    game.ram[0x006dU] = 1U;
    game.ram[0x0086U] = 0xffU;
    game.ram[0x000cU] = MYSMB_BUTTON_LEFT;
    game.ram[0x0057U] = 0x10U;
    game.ram[0x06ffU] = 0U;
    mysmb_player_update_scroll(&game);
    if (game.ram[0x006dU] != 2U || game.ram[0x0086U] != 0x20U ||
        game.ram[0x0057U] != 0U) {
        return 1;
    }
    game.ram[0x006dU] = 3U;
    game.ram[0x0086U] = 0x30U;
    game.ram[0x000cU] = MYSMB_BUTTON_RIGHT;
    game.ram[0x0057U] = 0x10U;
    mysmb_player_update_scroll(&game);
    if (game.ram[0x006dU] != 3U || game.ram[0x0086U] != 0x0fU ||
        game.ram[0x0057U] != 0U) {
        return 1;
    }
    game.ram[0x0086U] = 0U;
    game.ram[0x006dU] = 2U;
    game.ram[0x0057U] = 2U;
    game.ram[0x0490U] = 0xffU;
    mysmb_player_impede_move(&game, 1U);
    if (game.ram[0x0086U] != 0xffU || game.ram[0x006dU] != 1U ||
        game.ram[0x0057U] != 0U || game.ram[0x0490U] != 0xfeU ||
        game.ram[0x0785U] != 0x10U) {
        return 1;
    }
    game.ram[0x0086U] = 0xffU;
    game.ram[0x006dU] = 2U;
    game.ram[0x0057U] = 0xf0U;
    game.ram[0x0490U] = 0xffU;
    mysmb_player_impede_move(&game, 2U);
    if (game.ram[0x0086U] != 0U || game.ram[0x006dU] != 3U ||
        game.ram[0x0057U] != 0U || game.ram[0x0490U] != 0xfdU) {
        return 1;
    }
    game.ram[0x0086U] = 0x23U;
    game.ram[0x006dU] = 1U;
    game.ram[0x071aU] = 1U;
    game.ram[0x071cU] = 0U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x34U;
    game.ram[0x0057U] = 2U;
    game.ram[0x0045U] = 1U;
    game.ram[0x05f2U] = 0x61U;
    if (mysmb_player_check_sides(&game) == 0U || game.ram[0x0086U] != 0x22U ||
        game.ram[0x0057U] != 0U || game.ram[0x0490U] != 0xfeU) {
        return 1;
    }
    game.ram[0x0770U] = 1U;
    game.ram[0x0753U] = 0U;
    game.ram[0x075eU] = 0U;
    game.ram[0x0748U] = 0U;
    game.ram[0x0086U] = 0x23U;
    game.ram[0x0057U] = 2U;
    game.ram[0x05f2U] = 0xc2U;
    if (mysmb_player_check_sides(&game) == 0U || game.ram[0x05f2U] != 0U ||
        game.ram[0x075eU] != 1U || game.ram[0x0748U] != 1U ||
        game.ram[0x0057U] != 2U) {
        return 1;
    }
    game.ram[0x0754U] = 1U;
    game.ram[0x0714U] = 0U;
    game.ram[0x0704U] = 0U;
    game.ram[0x0086U] = 0x20U;
    game.ram[0x006dU] = 1U;
    game.ram[0x071aU] = 1U;
    game.ram[0x071cU] = 0U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x34U;
    game.ram[0x009fU] = 0xf0U;
    game.ram[0x05f2U] = 0x61U;
    if (mysmb_player_check_head(&game) == 0U || game.ram[0x009fU] != 1U) {
        return 1;
    }
    game.ram[0x0770U] = 1U;
    game.ram[0x075eU] = 0U;
    game.ram[0x0748U] = 0U;
    game.ram[0x009fU] = 0U;
    game.ram[0x05f2U] = 0xc3U;
    if (mysmb_player_check_head(&game) == 0U || game.ram[0x05f2U] != 0U ||
        game.ram[0x075eU] != 1U || game.ram[0x0748U] != 1U ||
        game.ram[0x009fU] != 0U) {
        return 1;
    }
    game.ram[0x009fU] = 2U;
    game.ram[0x00ceU] = 0x3fU;
    game.ram[0x0433U] = 0x80U;
    game.ram[0x001dU] = 2U;
    if (mysmb_player_land_on_solid(&game, 0x61U, 4U) == 0U ||
        game.ram[0x00ceU] != 0x30U || game.ram[0x009fU] != 0U ||
        game.ram[0x0433U] != 0U || game.ram[0x001dU] != 0U) {
        return 1;
    }
    game.ram[0x0754U] = 1U;
    game.ram[0x0086U] = 0x20U;
    game.ram[0x006dU] = 1U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x34U;
    game.ram[0x009fU] = 0xf0U;
    game.ram[0x0714U] = 0U;
    game.ram[0x0784U] = 0U;
    game.ram[0x03eeU] = 0U;
    game.ram[0x05f2U] = 0xc0U;
    if (mysmb_player_check_head(&game) == 0U || game.ram[0x0026U] != 0x11U ||
        game.ram[0x05f2U] != 0x23U || game.ram[0x03e4U] != 0x20U ||
        game.ram[0x03e6U] != 0xd2U || game.ram[0x03e8U] != 0xc4U ||
        game.ram[0x00a8U] != 0xfeU || game.ram[0x009fU] != 0U ||
        game.ram[0x0784U] != 0x10U || game.ram[0x03eeU] != 1U) {
        return 1;
    }
    game.ram[0x0784U] = 0U;
    game.ram[0x009fU] = 0xf0U;
    game.ram[0x05f2U] = 0xc1U;
    if (mysmb_player_check_head(&game) == 0U || game.ram[0x001bU] != 0x2eU ||
        game.ram[0x0023U] != 1U || game.ram[0x0014U] != 1U ||
        game.ram[0x0039U] != 0U) {
        return 1;
    }
    game.ram[0x0784U] = 0U;
    game.ram[0x009fU] = 0xf0U;
    game.ram[0x05f2U] = 0x56U;
    if (mysmb_player_check_head(&game) == 0U || game.ram[0x001bU] != 0x2fU ||
        game.ram[0x0014U] != 1U || game.ram[0x0398U] != 1U) {
        return 1;
    }
    game.ram[0x0754U] = 0U;
    game.ram[0x0784U] = 0U;
    game.ram[0x03eeU] = 0U;
    game.ram[0x009fU] = 0xf0U;
    game.ram[0x0770U] = 1U;
    game.ram[0x0753U] = 0U;
    game.ram[0x07e0U] = 0U;
    game.ram[0x07e1U] = 0U;
    game.ram[0x07e2U] = 0U;
    game.ram[0x05e2U] = 0x51U;
    if (mysmb_player_check_head(&game) == 0U || game.ram[0x0026U] != 0x12U ||
        game.ram[0x05e2U] != 0x23U || game.ram[0x03ecU] != 1U ||
        game.ram[0x0060U] != 0xf0U || game.ram[0x0062U] != 0xf0U ||
        game.ram[0x00a8U] != 0xfaU || game.ram[0x00aaU] != 0xfcU ||
        game.ram[0x00d9U] != 0x38U || game.ram[0x009fU] != 0xfeU ||
        game.ram[0x07e2U] != 5U) {
        return 1;
    }
    mysmb_objects_step_blocks(&game);
    if (game.ram[0x0026U] != 0x12U || game.ram[0x008fU] != 0x1fU ||
        game.ram[0x0091U] != 0x1fU || game.ram[0x00d7U] != 0x2aU ||
        game.ram[0x00d9U] != 0x34U) {
        return 1;
    }
    game.ram[0x0754U] = 1U;
    game.ram[0x0770U] = 0U;
    game.ram[0x0086U] = 0x20U;
    game.ram[0x006dU] = 1U;
    game.ram[0x00ceU] = 0x30U;
    game.ram[0x05e2U] = 0x61U;
    if (mysmb_player_query_block(&game, 0U, 0U, 0U, &terrain) == 0U ||
        terrain.metatile != 0x61U || terrain.contact_low_nibble != 0U) {
        return 1;
    }
    game.ram[0x0086U] = 0x20U;
    game.ram[0x006dU] = 1U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x34U;
    game.ram[0x009fU] = 0U;
    game.ram[0x0416U] = 0U;
    game.ram[0x0433U] = 0U;
    game.ram[0x001dU] = 2U;
    game.ram[0x0601U] = 0U;
    game.ram[0x0602U] = 0x61U;
    game.ram[0x0770U] = 1U;
    game.ram[0x075eU] = 0U;
    game.ram[0x0748U] = 0U;
    game.ram[0x0602U] = 0xc2U;
    if (mysmb_player_check_feet(&game) == 0U || game.ram[0x0602U] != 0U ||
        game.ram[0x075eU] != 1U || game.ram[0x0748U] != 1U) {
        return 1;
    }
    game.ram[0x0601U] = 0U;
    game.ram[0x0602U] = 0x61U;
    game.ram[0x0770U] = 0U;
    mysmb_player_step(&game, 0U);
    if (game.ram[0x00ceU] != 0x30U || game.ram[0x009fU] != 0U ||
        game.ram[0x0433U] != 0U || game.ram[0x001dU] != 0U) {
        return 1;
    }
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
    game.ram[0x0782U] = 7U;
    mysmb_player_step(&game, MYSMB_BUTTON_A);
    if (game.ram[0x0782U] != 7U) {
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
    game.ram[0x071bU] = 0U;
    game.ram[0x071dU] = 0U;
    game.ram[0x00e9U] = 0x34U;
    game.ram[0x00eaU] = 0x92U;
    if (mysmb_area_spawn_next_enemy(&game, &area_source) == 0U ||
        game.ram[0x000fU] != 1U || game.ram[0x0016U] != 0U ||
        game.ram[0x006eU] != 0U || game.ram[0x0087U] != 0x10U ||
        game.ram[0x00cfU] != 0x28U || game.ram[0x0058U] != 0xf8U ||
        game.ram[0x049aU] != 3U || game.ram[0x0739U] != 2U) return 1;
    mysmb_objects_step_normal_enemies(&game);
    if (game.ram[0x0087U] != 0x0fU) return 1;
    game.ram[0x0747U] = 1U;
    mysmb_objects_step_normal_enemies(&game);
    if (game.ram[0x0087U] != 0x0fU) return 1;
    game.ram[0x0747U] = 0U;
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 0U;
    game.ram[0x006eU] = 0U;
    game.ram[0x0087U] = 0x30U;
    game.ram[0x00cfU] = 0x50U;
    game.ram[0x0046U] = 1U;
    game.ram[0x0058U] = 0x10U;
    game.ram[0x0543U] = 0x61U;
    game.ram[0x0544U] = 0x61U;
    mysmb_objects_step_normal_enemies(&game);
    if (game.ram[0x0046U] != 2U || game.ram[0x0058U] != 0xf0U ||
        game.ram[0x00cfU] != 0x58U || (game.ram[0x001eU] & 0x40U) != 0U) return 1;
    game.ram[0x0543U] = 0U;
    game.ram[0x0544U] = 0U;
    game.ram[0x001eU] = 0x40U;
    game.ram[0x00cfU] = 0x50U;
    game.ram[0x00a0U] = 0U;
    game.ram[0x0417U] = 0U;
    game.ram[0x0434U] = 0xffU;
    mysmb_objects_step_normal_enemies(&game);
    if (game.ram[0x00cfU] != 0x50U || game.ram[0x00a0U] != 1U ||
        game.ram[0x0434U] != 0x3cU || (game.ram[0x001eU] & 0x40U) == 0U) return 1;
    game.frame_number = 0UL;
    game.ram[0x0747U] = 0xffU;
    game.ram[0x000eU] = 8U;
    game.ram[0x03d0U] = 0U;
    game.ram[0x006dU] = 0U;
    game.ram[0x0086U] = 0x40U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x60U;
    game.ram[0x009fU] = 1U;
    game.ram[0x0499U] = 0U;
    game.ram[0x071aU] = 0U;
    game.ram[0x071cU] = 0U;
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 6U;
    game.ram[0x001eU] = 0U;
    game.ram[0x006eU] = 0U;
    game.ram[0x0087U] = 0x42U;
    game.ram[0x00b6U] = 1U;
    game.ram[0x00cfU] = 0x70U;
    game.ram[0x0491U] = 0U;
    game.ram[0x049aU] = 3U;
    game.ram[0x0796U] = 0U;
    game.ram[0x0791U] = 0U;
    game.ram[0x0484U] = 0U;
    mysmb_objects_step_normal_enemies(&game);
    if (game.ram[0x001eU] != 4U || game.ram[0x0796U] != 0x10U ||
        game.ram[0x009fU] != 0xfcU || game.ram[0x0110U] != 1U ||
        game.ram[0x012cU] != 0x30U || game.ram[0x0491U] != 1U) return 1;
    game.ram[0x0796U] = 0x0eU;
    mysmb_objects_step_normal_enemies(&game);
    if (game.ram[0x000fU] != 0U) return 1;
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 6U;
    game.ram[0x001eU] = 0U;
    game.ram[0x0491U] = 0U;
    game.ram[0x0756U] = 1U;
    game.ram[0x079eU] = 0U;
    game.ram[0x009fU] = 0U;
    game.ram[0x000eU] = 8U;
    game.ram[0x001dU] = 0U;
    game.ram[0x0775U] = 1U;
    game.ram[0x0747U] = 0U;
    mysmb_objects_step_normal_enemies(&game);
    if (game.ram[0x0756U] != 0U || game.ram[0x079eU] != 8U ||
        game.ram[0x000eU] != 10U || game.ram[0x001dU] != 1U ||
        game.ram[0x0747U] != 0xffU || game.ram[0x0775U] != 0U) return 1;
    game.ram[0x0747U] = 0xf0U;
    mysmb_player_step_injury_blink(&game, 0U);
    if (game.ram[0x000eU] != 10U) return 1;
    game.ram[0x0747U] = 0xc8U;
    mysmb_player_step_injury_blink(&game, 0U);
    if (game.ram[0x000eU] != 8U || game.ram[0x0747U] != 0U) return 1;
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 0U;
    game.ram[0x001eU] = 0U;
    game.ram[0x0491U] = 0U;
    game.ram[0x009fU] = 1U;
    game.ram[0x000eU] = 8U;
    game.ram[0x076aU] = 1U;
    mysmb_objects_step_normal_enemies(&game);
    if (game.ram[0x001eU] != 4U || game.ram[0x0796U] != 0x0bU ||
        game.ram[0x009fU] != 0xfcU) return 1;
    game.ram[0x0796U] = 0U;
    mysmb_objects_step_normal_enemies(&game);
    if (game.ram[0x001eU] != 0U || game.ram[0x0046U] != 1U ||
        game.ram[0x0058U] != 8U) return 1;
    game.ram[0x001eU] = 4U;
    game.ram[0x0796U] = 1U;
    game.ram[0x0491U] = 0U;
    game.ram[0x009fU] = 0U;
    game.ram[0x0756U] = 0U;
    game.frame_number = 0UL;
    mysmb_objects_step_normal_enemies(&game);
    if (game.ram[0x001eU] != 0x84U || game.ram[0x0046U] != 2U ||
        game.ram[0x0058U] != 0xd0U || game.ram[0x0110U] != 5U) return 1;
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 6U;
    game.ram[0x001eU] = 0U;
    game.ram[0x0491U] = 0U;
    game.ram[0x00cfU] = 0x70U;
    game.ram[0x0417U] = 0U;
    game.ram[0x0434U] = 0U;
    game.ram[0x079fU] = 0x23U;
    mysmb_objects_step_normal_enemies(&game);
    if (game.ram[0x001eU] != 0x22U || game.ram[0x00cfU] != 0x6eU ||
        game.ram[0x00a0U] != 0xfdU || game.ram[0x0046U] != 1U ||
        game.ram[0x0058U] != 0x10U || game.ram[0x0110U] != 1U) return 1;
    game.ram[0x079fU] = 0U;
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 6U;
    game.ram[0x001eU] = 0x22U;
    game.ram[0x006eU] = 0U;
    game.ram[0x0087U] = 0x42U;
    game.ram[0x00b6U] = 1U;
    game.ram[0x00cfU] = 0x6eU;
    game.ram[0x00a0U] = 0xfdU;
    game.ram[0x0417U] = 0U;
    game.ram[0x0434U] = 0U;
    game.ram[0x0046U] = 1U;
    game.ram[0x0058U] = 0x10U;
    game.ram[0x0401U] = 0U;
    mysmb_objects_step_normal_enemies(&game);
    if (game.ram[0x00b6U] != 1U || game.ram[0x00cfU] != 0x6bU ||
        game.ram[0x0434U] != 0x3dU) return 1;
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 8U;
    game.ram[0x001eU] = 0U;
    game.ram[0x006eU] = 0U;
    game.ram[0x0087U] = 0x40U;
    game.ram[0x006dU] = 0U;
    game.ram[0x0086U] = 0x80U;
    game.ram[0x0747U] = 0U;
    game.ram[0x0401U] = 0U;
    mysmb_objects_step_bullet_bills(&game);
    if (game.ram[0x001eU] != 1U || game.ram[0x0046U] != 1U ||
        game.ram[0x0058U] != 0x18U || game.ram[0x078aU] != 0x0aU ||
        game.ram[0x0087U] != 0x41U) return 1;
    game.ram[0x001eU] = 0U;
    game.ram[0x0087U] = 0x80U;
    game.ram[0x0086U] = 0x40U;
    game.ram[0x0401U] = 0U;
    mysmb_objects_step_bullet_bills(&game);
    if (game.ram[0x0046U] != 2U || game.ram[0x0058U] != 0xe8U ||
        game.ram[0x0087U] != 0x7eU) return 1;
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 13U;
    game.ram[0x001eU] = 0U;
    game.ram[0x0087U] = 0x40U;
    game.ram[0x00cfU] = 0x70U;
    game.ram[0x0058U] = 1U;
    game.ram[0x00a0U] = 0U;
    game.ram[0x0434U] = 0x70U;
    game.ram[0x0417U] = 0x58U;
    game.ram[0x078aU] = 0U;
    game.ram[0x0086U] = 0x80U;
    game.frame_number = 1UL;
    mysmb_objects_step_piranha_plants(&game);
    if (game.ram[0x0058U] != 0xffU || game.ram[0x00a0U] != 1U ||
        game.ram[0x00cfU] != 0x6fU) return 1;
    game.ram[0x000fU] = 0U;
    game.frame_number = 0UL;
    game.ram[0x0011U] = 1U;
    game.ram[0x0018U] = 10U;
    game.ram[0x0020U] = 0U;
    game.ram[0x0070U] = 1U;
    game.ram[0x0089U] = 0x10U;
    game.ram[0x00b8U] = 1U;
    game.ram[0x00d1U] = 0x70U;
    game.ram[0x005aU] = 0U;
    game.ram[0x0403U] = 0U;
    game.ram[0x0419U] = 0U;
    game.ram[0x0436U] = 0x70U;
    mysmb_objects_step_swimming_cheep_cheeps(&game);
    if (game.ram[0x0403U] != 0xc0U || game.ram[0x0089U] != 0x0fU ||
        game.ram[0x0419U] != 0xe0U || game.ram[0x00d1U] != 0x6fU ||
        game.ram[0x00b8U] != 1U) return 1;
    game.ram[0x0011U] = 0U;
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 12U;
    game.ram[0x001eU] = 0U;
    game.ram[0x0796U] = 0U;
    game.ram[0x00b6U] = 0U;
    game.ram[0x00cfU] = 0U;
    game.ram[0x00a0U] = 0U;
    game.ram[0x0417U] = 0U;
    game.ram[0x0434U] = 0U;
    game.ram[0x07a8U] = 0x09U;
    mysmb_objects_step_podoboos(&game);
    if (game.ram[0x00b6U] != 1U || game.ram[0x00cfU] != 0xfbU ||
        game.ram[0x00a0U] != 0xf9U || game.ram[0x0417U] != 0x89U ||
        game.ram[0x0434U] != 0xa5U || game.ram[0x0796U] != 0x0fU ||
        game.ram[0x049aU] != 9U) return 1;
    game.ram[0x000fU] = 0U;
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 7U;
    game.ram[0x001eU] = 0U;
    game.ram[0x006eU] = 1U;
    game.ram[0x0087U] = 0x40U;
    game.ram[0x00cfU] = 0x70U;
    game.ram[0x00a0U] = 0U;
    game.ram[0x0058U] = 0U;
    game.ram[0x0434U] = 0U;
    game.ram[0x0796U] = 0U;
    game.ram[0x07a8U] = 1U;
    game.frame_number = 0UL;
    mysmb_objects_step_bloobers(&game);
    if (game.ram[0x0058U] != 1U || game.ram[0x0434U] != 1U ||
        game.ram[0x00cfU] != 0x6fU || game.ram[0x0087U] != 0x3fU) return 1;
    game.ram[0x000fU] = 0U;
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 14U;
    game.ram[0x001eU] = 0U;
    game.ram[0x006eU] = 1U;
    game.ram[0x0087U] = 0x40U;
    game.ram[0x00b6U] = 1U;
    game.ram[0x00cfU] = 0x70U;
    game.ram[0x0058U] = 0xf8U;
    game.ram[0x0401U] = 0U;
    game.ram[0x00a0U] = 0U;
    game.ram[0x0417U] = 0U;
    game.ram[0x0434U] = 0U;
    mysmb_objects_step_jumping_paratroopas(&game);
    if (game.ram[0x0087U] != 0x3fU || game.ram[0x0401U] != 0x80U ||
        game.ram[0x00cfU] != 0x70U || game.ram[0x0434U] != 0x1cU) return 1;
    game.ram[0x000fU] = 0U;
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
    if (game.ram[0x075fU] != 6U || game.ram[0x0760U] != 0U ||
        game.ram[0x0766U] != 6U || game.ram[0x0767U] != 0U) {
        return 1;
    }
    mysmb_game_initialize(&game);
    game.ram[0x0770U] = 1U;
    game.ram[0x0772U] = 1U;
    game.ram[0x000eU] = 1U;
    game.ram[0x001dU] = 0U;
    game.ram[0x0490U] = MYSMB_BUTTON_UP;
    game.ram[0x074eU] = 1U;
    game.ram[0x006dU] = 1U;
    game.ram[0x071aU] = 1U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x30U;
    input.buttons = 0U;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x001dU] != 3U || game.ram[0x00ceU] != 0x2fU) {
        return 1;
    }
    mysmb_game_initialize(&game);
    game.ram[0x0770U] = 0U;
    game.ram[0x0772U] = 0U;
    game.ram[0x000eU] = 8U;
    game.ram[0x001dU] = 3U;
    game.ram[0x0490U] = 0U;
    game.ram[0x071aU] = 1U;
    game.ram[0x006dU] = 1U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x30U;
    game.ram[0x0781U] = 2U;
    game.ram[0x0782U] = 2U;
    game.ram[0x0783U] = 2U;
    game.ram[0x0785U] = 2U;
    game.ram[0x0789U] = 2U;
    game.ram[0x077fU] = 0U;
    game.ram[0x0796U] = 2U;
    input.buttons = 0U;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x0781U] != 1U || game.ram[0x0782U] != 1U ||
        game.ram[0x0783U] != 1U || game.ram[0x0785U] != 1U ||
        game.ram[0x0789U] != 1U || game.ram[0x077fU] != 0x14U ||
        game.ram[0x0796U] != 1U) {
        return 1;
    }
    game.ram[0x0747U] = 2U;
    game.ram[0x0782U] = 2U;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x0747U] != 1U || game.ram[0x0782U] != 2U) {
        return 1;
    }
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x0747U] != 0U || game.ram[0x0782U] != 1U) return 1;
    mysmb_game_initialize(&game);
    game.ram[0x0770U] = 1U;
    game.ram[0x0772U] = 2U;
    game.ram[0x000eU] = 8U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x07faU] = 1U;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x0787U] != 0x18U || game.ram[0x07faU] != 0U) return 1;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x0787U] != 0x17U) return 1;
    game.ram[0x0787U] = 0U;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x0759U] != 1U || game.ram[0x0756U] != 0U) return 1;
    mysmb_game_initialize(&game);
    game.ram[0x03e4U] = 0x20U;
    game.ram[0x03e5U] = 0x30U;
    game.ram[0x03e6U] = 4U;
    game.ram[0x03e7U] = 5U;
    game.ram[0x03e8U] = 0x61U;
    game.ram[0x03e9U] = 0x62U;
    game.ram[0x03ecU] = 1U;
    game.ram[0x03edU] = 1U;
    mysmb_objects_apply_block_replacements(&game);
    if (game.ram[0x0524U] != 0x61U || game.ram[0x0535U] != 0x62U ||
        game.ram[0x03ecU] != 0U || game.ram[0x03edU] != 0U) return 1;
    game.ram[0x0301U] = 1U;
    game.ram[0x03ecU] = 1U;
    game.ram[0x0524U] = 0U;
    mysmb_objects_apply_block_replacements(&game);
    if (game.ram[0x0524U] != 0U || game.ram[0x03ecU] != 1U) return 1;
    mysmb_objects_start_jump_coin(&game, 2U, 0x35U, 0x60U);
    if (game.ram[0x0032U] != 1U || game.ram[0x0082U] != 2U ||
        game.ram[0x009bU] != 0x35U || game.ram[0x00e3U] != 0x60U ||
        game.ram[0x00b4U] != 0xfbU) return 1;
    game.ram[0x0770U] = 1U;
    game.ram[0x0753U] = 0U;
    game.ram[0x05f2U] = 0xc2U;
    mysmb_objects_collect_coin(&game, 0xd2U, 0x20U);
    if (game.ram[0x05f2U] != 0U || game.ram[0x0748U] != 1U ||
        game.ram[0x075eU] != 1U || game.ram[0x07eeU] != 1U ||
        game.ram[0x07e1U] != 2U || game.ram[0x0134U] != 0U ||
        game.ram[0x0139U] != 0U) return 1;
    game.ram[0x075eU] = 99U;
    game.ram[0x075aU] = 2U;
    mysmb_objects_collect_coin(&game, 0xd2U, 0x20U);
    if (game.ram[0x075eU] != 0U || game.ram[0x075aU] != 3U ||
        game.ram[0x07eeU] != 2U || game.ram[0x07e1U] != 4U) return 1;
    game.ram[0x07e0U] = 0U;
    game.ram[0x07e1U] = 9U;
    mysmb_objects_collect_coin(&game, 0xd2U, 0x20U);
    if (game.ram[0x07e0U] != 1U || game.ram[0x07e1U] != 1U ||
        game.ram[0x075eU] != 1U || game.ram[0x07eeU] != 3U) return 1;
    game.ram[0x0076U] = 2U;
    game.ram[0x008fU] = 0x30U;
    game.ram[0x00d7U] = 0x60U;
    game.ram[0x0756U] = 0U;
    mysmb_objects_start_power_up(&game, 0U, 0U);
    if (game.ram[0x001bU] != 0x2eU || game.ram[0x0073U] != 2U ||
        game.ram[0x008cU] != 0x30U || game.ram[0x00bbU] != 1U ||
        game.ram[0x00d4U] != 0x58U || game.ram[0x0023U] != 1U ||
        game.ram[0x0014U] != 1U || game.ram[0x049fU] != 3U ||
        game.ram[0x0039U] != 0U || game.ram[0x03caU] != 0x20U) return 1;
    game.frame_number = 0UL;
    mysmb_objects_step_power_up(&game);
    if (game.ram[0x0023U] != 2U || game.ram[0x00d4U] != 0x57U) return 1;
    game.ram[0x0023U] = 0x11U;
    game.ram[0x00d4U] = 0x50U;
    mysmb_objects_step_power_up(&game);
    if (game.ram[0x0023U] != 0x80U || game.ram[0x00d4U] != 0x4fU ||
        game.ram[0x005dU] != 0x10U || game.ram[0x03caU] != 0U ||
        game.ram[0x004bU] != 1U) return 1;
    game.ram[0x0756U] = 2U;
    game.ram[0x000aU] = 0x40U;
    game.ram[0x000dU] = 0U;
    game.ram[0x006dU] = 1U;
    game.ram[0x071aU] = 1U;
    game.ram[0x071cU] = 0U;
    game.ram[0x0086U] = 0x30U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x50U;
    game.ram[0x0033U] = 1U;
    game.ram[0x070cU] = 4U;
    mysmb_objects_step_fireballs(&game);
    if (game.ram[0x0024U] != 1U || game.ram[0x008dU] != 0x38U ||
        game.ram[0x0074U] != 1U || game.ram[0x00d5U] != 0x54U ||
        game.ram[0x005eU] != 0x40U || game.ram[0x04a0U] != 7U) return 1;
    game.ram[0x071aU] = 0U;
    game.ram[0x071cU] = 0U;
    game.ram[0x0024U] = 1U;
    game.ram[0x008dU] = 0x30U;
    game.ram[0x0074U] = 0U;
    game.ram[0x00d5U] = 0x50U;
    game.ram[0x00a6U] = 0U;
    game.ram[0x005eU] = 0U;
    game.ram[0x041dU] = 0U;
    game.ram[0x043aU] = 0U;
    game.ram[0x0533U] = 0x61U;
    mysmb_objects_step_fireballs(&game);
    if (game.ram[0x00a6U] != 0xfdU || game.ram[0x003aU] != 1U) return 1;
    game.ram[0x00d5U] = 0x50U;
    game.ram[0x00a6U] = 0xfdU;
    game.ram[0x043aU] = 0U;
    mysmb_objects_step_fireballs(&game);
    if (game.ram[0x0024U] != 0x80U) return 1;
    game.ram[0x0756U] = 0U;
    game.ram[0x0024U] = 1U;
    game.ram[0x0074U] = 0U;
    game.ram[0x008dU] = 0x40U;
    game.ram[0x00d5U] = 0x50U;
    game.ram[0x00bcU] = 1U;
    game.ram[0x005eU] = 0U;
    game.ram[0x00a6U] = 0U;
    game.ram[0x041dU] = 0U;
    game.ram[0x043aU] = 0U;
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 0U;
    game.ram[0x001eU] = 0U;
    game.ram[0x006eU] = 0U;
    game.ram[0x0087U] = 0x40U;
    game.ram[0x00cfU] = 0x50U;
    game.frame_number = 0UL;
    mysmb_objects_step_fireballs(&game);
    if (game.ram[0x0024U] != 0x80U || (game.ram[0x001eU] & 0x20U) == 0U) return 1;
    game.ram[0x0756U] = 2U;
    mysmb_objects_start_power_up(&game, 0U, 0U);
    if (game.ram[0x0039U] != 1U) return 1;
    mysmb_objects_start_power_up(&game, 0U, 2U);
    if (game.ram[0x0039U] != 2U) return 1;
    game.ram[0x0747U] = 0U;
    game.ram[0x0023U] = 0x80U;
    game.ram[0x0039U] = 2U;
    game.ram[0x0073U] = 0U;
    game.ram[0x008cU] = 0x30U;
    game.ram[0x00d4U] = 0x50U;
    game.ram[0x00bbU] = 1U;
    game.ram[0x00a5U] = 1U;
    game.ram[0x041cU] = 0U;
    game.ram[0x0439U] = 0U;
    game.ram[0x004bU] = 1U;
    game.ram[0x005dU] = 0x10U;
    game.ram[0x0543U] = 0x61U;
    mysmb_objects_step_power_up(&game);
    if (game.ram[0x008cU] != 0x31U || game.ram[0x00d4U] != 0x58U ||
        game.ram[0x00a5U] != 0xfdU || game.ram[0x0439U] != 0U) return 1;
    game.ram[0x0747U] = 0U;
    game.ram[0x0023U] = 0x80U;
    game.ram[0x0039U] = 0U;
    game.ram[0x008cU] = 0x40U;
    mysmb_objects_step_power_up(&game);
    if (game.ram[0x008cU] != 0x41U) return 1;
    game.ram[0x0747U] = 0U;
    game.ram[0x0023U] = 0x80U;
    game.ram[0x0039U] = 0U;
    game.ram[0x0073U] = 0U;
    game.ram[0x008cU] = 0x30U;
    game.ram[0x00d4U] = 0x50U;
    game.ram[0x004bU] = 1U;
    game.ram[0x005dU] = 0x10U;
    game.ram[0x0544U] = 0x61U;
    mysmb_objects_step_power_up(&game);
    if (game.ram[0x004bU] != 2U || game.ram[0x005dU] != 0xf0U) return 1;
    game.ram[0x0747U] = 0U;
    game.ram[0x0023U] = 0xc0U;
    game.ram[0x0039U] = 0U;
    game.ram[0x0073U] = 0U;
    game.ram[0x008cU] = 0x30U;
    game.ram[0x00d4U] = 0x50U;
    game.ram[0x00bbU] = 1U;
    game.ram[0x00a5U] = 0U;
    game.ram[0x041cU] = 0U;
    game.ram[0x0439U] = 0U;
    game.ram[0x004bU] = 1U;
    game.ram[0x005dU] = 0x10U;
    game.ram[0x0543U] = 0x61U;
    mysmb_objects_step_power_up(&game);
    if (game.ram[0x00d4U] != 0x58U || game.ram[0x0023U] != 0x80U ||
        game.ram[0x00a5U] != 0U || game.ram[0x041cU] != 0U ||
        game.ram[0x0439U] != 0U) return 1;
    game.ram[0x0543U] = 0U;
    game.ram[0x0023U] = 0x80U;
    game.ram[0x00d4U] = 0x50U;
    mysmb_objects_step_power_up(&game);
    if (game.ram[0x0023U] != 0xc0U) return 1;
    game.ram[0x006dU] = 1U;
    game.ram[0x071aU] = 1U;
    game.ram[0x071cU] = 0U;
    game.ram[0x0086U] = 0x30U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x50U;
    game.ram[0x0499U] = 1U;
    game.ram[0x03d0U] = 0U;
    game.ram[0x071aU] = 1U;
    game.ram[0x071cU] = 0U;
    game.ram[0x000eU] = 8U;
    game.ram[0x001bU] = 0x2eU;
    game.ram[0x0023U] = 0x80U;
    game.ram[0x0014U] = 1U;
    game.ram[0x0073U] = 1U;
    game.ram[0x008cU] = 0x30U;
    game.ram[0x00d4U] = 0x50U;
    game.ram[0x049fU] = 3U;
    game.ram[0x0039U] = 2U;
    game.ram[0x079fU] = 0U;
    game.frame_number = 0UL;
    mysmb_objects_check_power_up_collision(&game);
    if (game.ram[0x04acU] != 0x33U || game.ram[0x04adU] != 0x64U ||
        game.ram[0x04c4U] != 0x32U || game.ram[0x04c5U] != 0x59U ||
        game.ram[0x0014U] != 0U || game.ram[0x079fU] != 0x23U) return 1;
    game.ram[0x0076U] = 1U;
    game.ram[0x008fU] = 0x30U;
    game.ram[0x00d7U] = 0x60U;
    game.ram[0x0398U] = 0U;
    game.ram[0x0399U] = 0U;
    mysmb_objects_start_vine(&game, 0U);
    if (game.ram[0x001bU] != 0x2fU || game.ram[0x0014U] != 1U ||
        game.ram[0x0073U] != 1U || game.ram[0x008cU] != 0x30U ||
        game.ram[0x00d4U] != 0x60U || game.ram[0x039dU] != 0x60U ||
        game.ram[0x039aU] != 5U || game.ram[0x0398U] != 1U) return 1;
    game.frame_number = 2UL;
    mysmb_objects_step_vine(&game);
    if (game.ram[0x00d4U] != 0x5fU || game.ram[0x0399U] != 1U) return 1;
    game.ram[0x0399U] = 0x1fU;
    game.ram[0x00d4U] = 0x60U;
    game.ram[0x0613U] = 0U;
    mysmb_objects_step_vine(&game);
    if (game.ram[0x0399U] != 0x20U || game.ram[0x00d4U] != 0x5fU ||
        game.ram[0x0613U] != 0x26U) return 1;
    game.ram[0x0754U] = 1U;
    game.ram[0x070bU] = 0U;
    game.ram[0x070dU] = 7U;
    game.ram[0x0747U] = 0xf8U;
    mysmb_player_step_change_size(&game);
    if (game.ram[0x0754U] != 0U || game.ram[0x070bU] != 1U ||
        game.ram[0x070dU] != 0U) return 1;
    game.ram[0x0747U] = 0xc4U;
    mysmb_player_step_change_size(&game);
    if (game.ram[0x0747U] != 0U || game.ram[0x000eU] != 8U) return 1;
    game.ram[0x000eU] = 12U;
    game.ram[0x0747U] = 0U;
    game.ram[0x03c4U] = 0x20U;
    game.frame_number = 8UL;
    mysmb_player_step_fire_flower(&game);
    if (game.ram[0x03c4U] != 0x22U) return 1;
    game.ram[0x0747U] = 0xc0U;
    mysmb_player_step_fire_flower(&game);
    if (game.ram[0x0747U] != 0U || game.ram[0x000eU] != 8U ||
        game.ram[0x03c4U] != 0x20U) return 1;
    game.ram[0x0770U] = 1U;
    game.ram[0x0753U] = 0U;
    game.ram[0x0756U] = 0U;
    game.ram[0x0039U] = 0U;
    game.ram[0x0014U] = 1U;
    game.ram[0x001bU] = 0x2eU;
    game.ram[0x07e0U] = 0U;
    game.ram[0x07e1U] = 0U;
    mysmb_objects_collect_power_up(&game);
    if (game.ram[0x0014U] != 0U || game.ram[0x001bU] != 0U ||
        game.ram[0x0756U] != 1U || game.ram[0x000eU] != 9U ||
        game.ram[0x0747U] != 0xffU || game.ram[0x07e0U] != 0U ||
        game.ram[0x0115U] != 6U || game.ram[0x0131U] != 0x30U) return 1;
    for (index = 0U; index < 6U; ++index) {
        mysmb_objects_step_floatey_numbers(&game);
    }
    if (game.ram[0x07e0U] != 1U || game.ram[0x0131U] != 0x2aU) return 1;
    game.ram[0x0039U] = 3U;
    game.ram[0x075aU] = 2U;
    mysmb_objects_collect_power_up(&game);
    if (game.ram[0x0115U] != 0x0bU || game.ram[0x0131U] != 0x30U ||
        game.ram[0x075aU] != 2U) return 1;
    for (index = 0U; index < 5U; ++index) {
        mysmb_objects_step_floatey_numbers(&game);
    }
    if (game.ram[0x075aU] != 2U) return 1;
    mysmb_objects_step_floatey_numbers(&game);
    if (game.ram[0x075aU] != 3U) return 1;
    game.ram[0x0039U] = 2U;
    game.ram[0x079fU] = 0U;
    mysmb_objects_collect_power_up(&game);
    if (game.ram[0x079fU] != 0x23U) return 1;
    game.ram[0x0301U] = 0U;
    game.ram[0x0026U] = 0x11U;
    game.ram[0x00beU] = 1U;
    game.ram[0x00d7U] = 0x20U;
    game.ram[0x00a8U] = 0xfcU;
    game.ram[0x0420U] = 0U;
    game.ram[0x043cU] = 0U;
    game.ram[0x03ecU] = 0U;
    for (index = 0U; index < 64U && game.ram[0x0026U] != 0U; ++index) {
        mysmb_objects_step_blocks(&game);
    }
    return game.ram[0x0026U] == 0U && game.ram[0x03ecU] == 1U ? 0 : 1;
}
