#include "game/fireball/fireball.h"

enum {
    MYSMB_PLAYER_STATUS = 0x0756U,
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

/* ROM $6298 ProcFireball_Bubble.  This label only performs fire-button
 * eligibility and slot allocation; FireballObjCore owns the two-slot step. */
void mysmb_fireball_try_spawn(struct mysmb_game *game)
{
    mysmb_u8 slot;

    if (game->ram[MYSMB_PLAYER_STATUS] < 2U ||
        (game->ram[MYSMB_PLAYER_A_B] & MYSMB_BUTTON_B) == 0U ||
        (game->ram[MYSMB_PREVIOUS_A_B] & MYSMB_BUTTON_B) != 0U ||
        game->ram[MYSMB_PLAYER_Y_HIGH] != 1U ||
        game->ram[MYSMB_PLAYER_CROUCHING] != 0U ||
        game->ram[MYSMB_PLAYER_STATE] == 3U) return;

    slot = (mysmb_u8)(game->ram[MYSMB_FIREBALL_COUNTER] & 1U);
    if (game->ram[MYSMB_FIREBALL_STATE + slot] != 0U) return;

    game->ram[MYSMB_SQUARE1_SOUND] = 0x20U;
    game->ram[MYSMB_FIREBALL_STATE + slot] = 2U;
    game->ram[MYSMB_FIREBALL_COUNTER]++;
    game->ram[MYSMB_FIREBALL_THROWING_TIMER] =
        game->ram[MYSMB_PLAYER_ANIM_TIMER_SET];
    game->ram[MYSMB_PLAYER_ANIMATION] =
        (mysmb_u8)(game->ram[MYSMB_PLAYER_ANIM_TIMER_SET] - 1U);
}