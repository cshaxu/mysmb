#include "core/fireball/fireball.h"

enum {
    MYSMB_PLAYER_A_B = 0x000aU,
    MYSMB_PREVIOUS_A_B = 0x000dU,
    MYSMB_PLAYER_Y_HIGH = 0x00b5U,
    MYSMB_PLAYER_CROUCHING = 0x0714U,
    MYSMB_PLAYER_STATE = 0x001dU,
    MYSMB_PLAYER_ANIMATION = 0x0781U,
    MYSMB_FIREBALL_THROWING_TIMER = 0x0711U,
    MYSMB_PLAYER_ANIM_TIMER_SET = 0x070cU,
    MYSMB_FIREBALL_STATE = 0x0024U,
    MYSMB_FIREBALL_COUNTER = 0x06ceU,
    MYSMB_SQUARE1_SOUND = 0x00ffU
};

/* The post-PlayerStatus creation branch of ROM source line 6298 ProcFireball_Bubble.
 * mysmb_fireball_step owns that label's sole PlayerStatus partition; this
 * routine begins at the following fire-button eligibility test. */
void mysmb_fireball_try_spawn(struct mysmb_game *game)
{
    mysmb_u8 slot;

    if ((game->ram[MYSMB_PLAYER_A_B] & MYSMB_BUTTON_B) == 0U ||
        (game->ram[MYSMB_PREVIOUS_A_B] & MYSMB_BUTTON_B) != 0U) return;

    slot = (mysmb_u8)(game->ram[MYSMB_FIREBALL_COUNTER] & 1U);
    if (game->ram[MYSMB_FIREBALL_STATE + slot] != 0U) return;

    if (game->ram[MYSMB_PLAYER_Y_HIGH] != 1U ||
        game->ram[MYSMB_PLAYER_CROUCHING] != 0U ||
        game->ram[MYSMB_PLAYER_STATE] == 3U) return;

    game->ram[MYSMB_SQUARE1_SOUND] = 0x20U;
    game->ram[MYSMB_FIREBALL_STATE + slot] = 2U;
    game->ram[MYSMB_FIREBALL_THROWING_TIMER] =
        game->ram[MYSMB_PLAYER_ANIM_TIMER_SET];
    game->ram[MYSMB_PLAYER_ANIMATION] =
        (mysmb_u8)(game->ram[MYSMB_PLAYER_ANIM_TIMER_SET] - 1U);
    game->ram[MYSMB_FIREBALL_COUNTER]++;
}

/* ProcFireball_Bubble/ProcFireballs: status is read once before both slots;
 * child returns may affect the following area's bubble gate. */
void mysmb_fireball_step(struct mysmb_game *game)
{
    if (game->ram[0x0756U] >= 2U) {
        mysmb_fireball_try_spawn(game);
        mysmb_fireball_step_object(game, 0U);
        mysmb_fireball_step_object(game, 1U);
    }
    mysmb_fireball_step_bubbles(game);
}

/* ProcAirBubbles/BublLoop/BublExit: source-ordered caller only. */
void mysmb_fireball_step_bubbles(struct mysmb_game *game)
{
    mysmb_u8 slot;
    if (game->ram[0x074eU] != 0U) return;
    slot = 2U;
    do {
        game->ram[0x0008U] = slot;
        mysmb_fireball_check_bubble(game, slot);
        mysmb_fireball_relative_bubble_position(game, slot);
        mysmb_fireball_get_bubble_offscreen_bits(game, slot);
        mysmb_fireball_draw_bubble(game, slot);
        --slot;
    } while (slot != 0xffU);
}
