#include "game/game.h"
#include "game/player.h"

int main(void)
{
    struct mysmb_game game;
    struct mysmb_player_checkpoint checkpoint;
    unsigned int index;

    mysmb_game_initialize(&game);
    game.ram[0x0705U] = 0xa5U;
    game.ram[0x0400U] = 0xf0U;
    game.ram[0x0057U] = 1U;
    game.ram[0x006dU] = 1U;
    game.ram[0x0086U] = 0x20U;
    if (mysmb_player_move_horizontally(&game) != 1U ||
        game.ram[0x0400U] != 0U || game.ram[0x0705U] != 0xa5U ||
        game.ram[0x0086U] != 0x21U || game.ram[0x006dU] != 1U) {
        return 1;
    }
    game.ram[0x0754U] = 1U;
    game.ram[0x074eU] = 1U;
    game.ram[0x000eU] = 8U;
    game.ram[0x0490U] = 0xffU;
    game.ram[0x0033U] = 1U;
    game.ram[0x006dU] = 1U;
    game.ram[0x071aU] = 1U;
    game.ram[0x071cU] = 0U;
    game.ram[0x0086U] = 0x20U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x30U;
    game.ram[0x070aU] = 0x28U;
    for (index = 0U; index < 16U; ++index) {
        game.ram[(mysmb_u16)(0x0600U + index)] = 0x61U;
    }
    game.ram[0x0754U] = 0U;
    mysmb_player_latch_input(&game,
                             (mysmb_u8)(MYSMB_BUTTON_DOWN | MYSMB_BUTTON_RIGHT));
    if (game.ram[0x0714U] != 0U || game.ram[0x000bU] != 0U ||
        game.ram[0x000cU] != 0U) {
        return 1;
    }
    game.ram[0x0754U] = 1U;
    game.ram[0x001dU] = 0U;
    game.ram[0x074eU] = 1U;
    game.ram[0x000aU] = MYSMB_BUTTON_B;
    game.ram[0x000cU] = MYSMB_BUTTON_RIGHT;
    game.ram[0x0045U] = MYSMB_BUTTON_RIGHT;
    game.ram[0x0700U] = 0U;
    game.ram[0x0783U] = 0U;
    game.ram[0x000eU] = 0U;
    mysmb_player_configure_horizontal(&game);
    if (game.ram[0x0783U] != 0x0aU || game.ram[0x0450U] != 0xd8U ||
        game.ram[0x0456U] != 0x28U || game.ram[0x0702U] != 0xe4U) {
        return 1;
    }
    /* X_Physics branches straight to GetXPhy while airborne at $19 or
     * faster.  RunningSpeed and the $21 check are not reached on that path. */
    game.ram[0x001dU] = 1U;
    game.ram[0x0700U] = 0x21U;
    game.ram[0x0703U] = 1U;
    game.ram[0x074eU] = 1U;
    game.ram[0x0783U] = 0U;
    game.ram[0x000eU] = 0U;
    game.ram[0x0033U] = MYSMB_BUTTON_RIGHT;
    game.ram[0x0045U] = MYSMB_BUTTON_RIGHT;
    mysmb_player_configure_horizontal(&game);
    if (game.ram[0x0450U] != 0xd8U || game.ram[0x0456U] != 0x28U ||
        game.ram[0x0701U] != 0U || game.ram[0x0702U] != 0xe4U) {
        return 1;
    }
    game.ram[0x0700U] = 0x0aU;
    game.ram[0x0045U] = MYSMB_BUTTON_RIGHT;
    game.ram[0x0033U] = MYSMB_BUTTON_LEFT;
    game.ram[0x0057U] = 4U;
    game.ram[0x0705U] = 0x80U;
    mysmb_player_update_animation_speed(&game, MYSMB_BUTTON_LEFT);
    if (game.ram[0x0045U] != MYSMB_BUTTON_LEFT || game.ram[0x0057U] != 0U ||
        game.ram[0x0705U] != 0U || game.ram[0x070cU] != 7U) {
        return 1;
    }
    game.ram[0x0700U] = 0x1cU;
    mysmb_player_update_animation_speed(&game, 0U);
    if (game.ram[0x0703U] != 0x1cU || game.ram[0x070cU] != 2U) {
        return 1;
    }
    game.ram[0x074eU] = 0U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0xd0U;
    mysmb_player_latch_input(&game, MYSMB_BUTTON_A);
    if (game.ram[0x000aU] != 0U || game.ram[0x000bU] != 0U ||
        game.ram[0x000cU] != 0U) {
        return 1;
    }
    game.ram[0x074eU] = 1U;
    game.ram[0x00ceU] = 0x30U;
    /* PlayerCtrlRoutine updates Player_MovingDir after PlayerMovementSubs.
     * With no direction held, a leftward slide must select its friction from
     * the stored previous direction, then publish its new direction. */
    game.ram[0x001dU] = 0U;
    game.ram[0x0033U] = MYSMB_BUTTON_RIGHT;
    game.ram[0x0045U] = MYSMB_BUTTON_RIGHT;
    game.ram[0x0057U] = 0xf0U;
    game.ram[0x0705U] = 0U;
    game.ram[0x0700U] = 0x10U;
    game.ram[0x0703U] = 0U;
    mysmb_player_step(&game, 0U);
    if (game.ram[0x0701U] != 0U || game.ram[0x0702U] != 0x98U ||
        game.ram[0x0045U] != MYSMB_BUTTON_LEFT) {
        return 1;
    }
    game.ram[0x001dU] = 0U;
    game.ram[0x0033U] = MYSMB_BUTTON_RIGHT;
    game.ram[0x0045U] = MYSMB_BUTTON_RIGHT;
    game.ram[0x0057U] = 0U;
    game.ram[0x0705U] = 0U;
    game.ram[0x0700U] = 0U;
    for (index = 0U; index < 8U; ++index) {
        mysmb_player_step(&game, MYSMB_BUTTON_RIGHT);
    }
    mysmb_player_checkpoint(&game, &checkpoint);
    if (game.ram[0x0057U] == 0U || game.ram[0x001dU] != 0U ||
        game.ram[0x00ceU] != 0x30U ||
        checkpoint.state != 0U || checkpoint.x != game.ram[0x0086U] ||
        checkpoint.x_speed != game.ram[0x0057U] ||
        checkpoint.y != 0x30U || checkpoint.y_high != 1U) {
        return 1;
    }
    mysmb_player_step(&game, (mysmb_u8)(MYSMB_BUTTON_A | MYSMB_BUTTON_RIGHT));
    /* GameEngine SaveAB publishes this after PlayerCtrlRoutine returns. */
    game.ram[0x000dU] = game.ram[0x000aU];
    if (game.ram[0x001dU] != 1U || game.ram[0x00ceU] >= 0x30U ||
        game.ram[0x009fU] < 0x80U || game.ram[0x0782U] != 0x20U) {
        return 1;
    }
    mysmb_player_step(&game, (mysmb_u8)(MYSMB_BUTTON_A | MYSMB_BUTTON_RIGHT));
    game.ram[0x000dU] = game.ram[0x000aU];
    if (game.ram[0x0709U] == game.ram[0x070aU] ||
        game.ram[0x0433U] != 0x40U) {
        return 1;
    }
    mysmb_player_step(&game, MYSMB_BUTTON_RIGHT);
    if (game.ram[0x0709U] != game.ram[0x070aU]) {
        return 1;
    }
    game.ram[0x001dU] = 2U;
    game.ram[0x0709U] = 0x20U;
    game.ram[0x070aU] = 0x28U;
    game.ram[0x009fU] = 1U;
    game.ram[0x0433U] = 0U;
    game.ram[0x0416U] = 0U;
    mysmb_player_step(&game, 0U);
    if (game.ram[0x0709U] != 0x28U || game.ram[0x0433U] != 0x28U) {
        return 1;
    }
    game.ram[0x001dU] = 1U;
    game.ram[0x0709U] = 0x20U;
    game.ram[0x009fU] = 0U;
    game.ram[0x0433U] = 0U;
    game.ram[0x0416U] = 0U;
    mysmb_player_step(&game, 0U);
    if (game.ram[0x0709U] != 0x28U || game.ram[0x0433U] != 0x28U) {
        return 1;
    }
    game.ram[0x001dU] = 3U;
    game.ram[0x0490U] = MYSMB_BUTTON_UP;
    game.ram[0x000cU] = 0U;
    game.ram[0x00ceU] = 0x30U;
    game.ram[0x0416U] = 0U;
    mysmb_player_step(&game, MYSMB_BUTTON_UP);
    if (game.ram[0x009fU] != 0xffU || game.ram[0x0433U] != 0x20U ||
        game.ram[0x070cU] != 4U || game.ram[0x00ceU] != 0x2fU) {
        return 1;
    }
    game.ram[0x0490U] = MYSMB_BUTTON_RIGHT;
    game.ram[0x0086U] = 0x20U;
    game.ram[0x006dU] = 1U;
    game.ram[0x0033U] = MYSMB_BUTTON_RIGHT;
    game.ram[0x0789U] = 0U;
    mysmb_player_step(&game, MYSMB_BUTTON_RIGHT);
    if (game.ram[0x0086U] != 0x2eU || game.ram[0x006dU] != 1U ||
        game.ram[0x0789U] != 0x18U || game.ram[0x0033U] != MYSMB_BUTTON_LEFT) {
        return 1;
    }
    game.ram[0x001dU] = 0U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x30U;
    game.ram[0x0490U] = MYSMB_BUTTON_UP;
    game.ram[0x000eU] = 1U;
    mysmb_player_step_auto_climb(&game);
    if (game.ram[0x001dU] != 3U || game.ram[0x00ceU] != 0x2fU) {
        return 1;
    }
    if (game.ram[0x0490U] != MYSMB_BUTTON_UP) {
        return 1;
    }
    game.ram[0x00b5U] = 0U;
    game.ram[0x00ceU] = 0xe3U;
    game.ram[0x0752U] = 0U;
    game.ram[0x0774U] = 0U;
    game.ram[0x0772U] = 1U;
    mysmb_player_step_auto_climb(&game);
    if (game.ram[0x0752U] != 2U || game.ram[0x0774U] != 1U ||
        game.ram[0x0772U] != 0U) {
        return 1;
    }
    game.ram[0x001dU] = 1U;
    game.ram[0x0704U] = 1U;
    game.ram[0x0782U] = 0U;
    game.ram[0x009fU] = 0U;
    game.ram[0x00ceU] = 0x20U;
    game.ram[0x000dU] = 0U;
    mysmb_player_step(&game, MYSMB_BUTTON_A);
    if (game.ram[0x0709U] != 0x0dU || game.ram[0x070aU] != 0x0aU ||
        game.ram[0x009fU] != 0xfeU || game.ram[0x0782U] != 0x20U) {
        return 1;
    }
    game.ram[0x00ceU] = 0x10U;
    game.ram[0x009fU] = 0U;
    game.ram[0x000dU] = 0U;
    mysmb_player_step(&game, MYSMB_BUTTON_RIGHT);
    if (game.ram[0x0709U] != 0x18U || game.ram[0x0033U] != MYSMB_BUTTON_RIGHT) {
        return 1;
    }
    /* LRAir fixes the gravity force during the PlayerDeath engine state,
     * regardless of the ordinary falling force selected above it. */
    game.ram[0x000eU] = 0x0bU;
    game.ram[0x001dU] = 1U;
    game.ram[0x009fU] = 0xfcU;
    game.ram[0x0709U] = 0x70U;
    game.ram[0x070aU] = 0x70U;
    game.ram[0x000aU] = MYSMB_BUTTON_A;
    game.ram[0x000dU] = MYSMB_BUTTON_A;
    mysmb_player_step(&game, MYSMB_BUTTON_A);
    if (game.ram[0x0709U] != 0x28U) {
        return 1;
    }
    /* PlayerHole changes a completed death fall to the PlayerLoseLife
     * dispatcher only after its event-music gate is clear. */
    game.ram[0x000eU] = 0x0bU;
    game.ram[0x001dU] = 1U;
    game.ram[0x00b5U] = 4U;
    game.ram[0x00ceU] = 0x20U;
    game.ram[0x009fU] = 0U;
    game.ram[0x0416U] = 0U;
    game.ram[0x0433U] = 0U;
    game.ram[0x0709U] = 0U;
    game.ram[0x0759U] = 0U;
    game.ram[0x0743U] = 0U;
    game.ram[0x07b1U] = 0U;
    game.ram[0x0723U] = 0U;
    mysmb_player_step(&game, 0U);
    if (game.ram[0x000eU] != 6U || game.ram[0x0723U] != 1U) {
        return 1;
    }
    for (index = 0U; index < 0x0100U; ++index) {
        game.ram[(mysmb_u16)(0x0500U + index)] = 0U;
    }
    game.ram[0x0754U] = 1U;
    game.ram[0x0704U] = 0U;
    game.ram[0x0714U] = 0U;
    game.ram[0x001dU] = 2U;
    game.ram[0x006dU] = 1U;
    game.ram[0x0086U] = 0x28U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x30U;
    game.ram[0x009fU] = 0U;
    game.ram[0x0603U] = 0x61U;
    if (mysmb_player_check_feet(&game) == 0U || game.ram[0x001dU] != 0U) {
        return 1;
    }
    game.ram[0x001dU] = 2U;
    game.ram[0x009fU] = 2U;
    game.ram[0x0603U] = 0x26U;
    if (mysmb_player_check_feet(&game) != 0U || game.ram[0x001dU] != 2U) {
        return 1;
    }
    game.ram[0x0603U] = 1U;
    game.ram[0x0602U] = 0x61U;
    if (mysmb_player_check_feet(&game) != 0U || game.ram[0x001dU] != 2U) {
        return 1;
    }
    game.ram[0x0603U] = 0x61U;
    game.ram[0x0602U] = 0U;
    game.ram[0x0754U] = 0U;
    game.ram[0x001dU] = 0U;
    mysmb_player_step(&game, MYSMB_BUTTON_DOWN);
    if (game.ram[0x0499U] != 2U) {
        return 1;
    }
    game.ram[0x000bU] = MYSMB_BUTTON_DOWN;
    game.ram[0x074eU] = 3U;
    if (mysmb_player_handle_vertical_pipe(&game, 0x10U, 0x11U) == 0U ||
        game.ram[0x000eU] != 3U || game.ram[0x06deU] != 0x30U ||
        game.ram[0x03c4U] != 0x20U) {
        return 1;
    }
    game.ram[0x06deU] = 1U;
    game.ram[0x00ceU] = 0x40U;
    mysmb_player_step_vertical_pipe(&game);
    if (game.ram[0x00ceU] != 0x41U || game.ram[0x0752U] != 2U ||
        game.ram[0x0772U] != 0U) {
        return 1;
    }
    game.ram[0x000eU] = 2U;
    game.ram[0x06deU] = 1U;
    game.ram[0x0086U] = 0x20U;
    mysmb_player_step_side_pipe(&game);
    if (game.ram[0x0752U] != 2U || game.ram[0x0772U] != 0U) {
        return 1;
    }
    for (index = 0U; index < 0x0100U; ++index) {
        game.ram[(mysmb_u16)(0x0500U + index)] = 0U;
    }
    game.ram[0x0754U] = 1U;
    game.ram[0x0704U] = 0U;
    game.ram[0x0714U] = 0U;
    game.ram[0x001dU] = 2U;
    game.ram[0x0789U] = 0U;
    game.ram[0x000eU] = 8U;
    game.ram[0x0033U] = MYSMB_BUTTON_RIGHT;
    game.ram[0x0057U] = 0x10U;
    game.ram[0x0705U] = 0x80U;
    game.ram[0x006dU] = 1U;
    game.ram[0x0086U] = 0x28U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x30U;
    game.ram[0x071cU] = 0U;
    game.ram[0x05f3U] = 0x26U;
    game.ram[0x05f2U] = 0x26U;
    if (mysmb_player_check_sides(&game) == 0U || game.ram[0x001dU] != 3U ||
        game.ram[0x0086U] != 0x19U || game.ram[0x0057U] != 0U ||
        game.ram[0x0705U] != 0U) {
        return 1;
    }
    game.ram[0x001dU] = 2U;
    game.ram[0x0789U] = 0U;
    game.ram[0x0086U] = 0x28U;
    game.ram[0x00ceU] = 0x30U;
    game.ram[0x0057U] = 0U;
    game.ram[0x009fU] = 0U;
    mysmb_player_step(&game, 0U);
    if (game.ram[0x0789U] != 0x18U) {
        return 1;
    }
    return 0;
}
