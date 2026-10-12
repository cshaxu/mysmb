#include "core/status.h"

enum {
    MYSMB_STATUS_MODE = 0x0770U,
    MYSMB_STATUS_BUFFER_OFFSET = 0x0300U,
    MYSMB_STATUS_BUFFER = 0x0301U,
    MYSMB_STATUS_CURRENT_PLAYER = 0x0753U,
    MYSMB_STATUS_WORLD = 0x075fU,
    MYSMB_STATUS_LEVEL = 0x075cU,
    MYSMB_STATUS_DIGITS = 0x07d7U,
    MYSMB_STATUS_TIMER = 0x07f8U,
    MYSMB_STATUS_MODIFIER = 0x0134U,
    MYSMB_STATUS_PLAYER_SCORE = 0x07ddU,
    MYSMB_STATUS_TOP_SCORE = 0x07d7U
};

static const mysmb_u8 mysmb_status_data[12] = {
    0xf0U, 6U, 0x62U, 6U, 0x62U, 6U,
    0x6dU, 2U, 0x6dU, 2U, 0x7aU, 3U
};
static const mysmb_u8 mysmb_status_offset[6] = { 6U, 12U, 18U, 24U, 30U, 36U };

static mysmb_u8 mysmb_status_output_numbers(struct mysmb_game *game, mysmb_u8 selector)
{
    mysmb_u8 offset;
    mysmb_u8 length;
    mysmb_u8 digit;
    mysmb_u8 y;

    selector = (mysmb_u8)((selector + 1U) & 0x0fU);
    if (selector >= 6U) return 1U;
    y = (mysmb_u8)(selector << 1U);
    offset = game->ram[MYSMB_STATUS_BUFFER_OFFSET];
    /* OutputNumbers keeps X at the command's first byte while it writes
     * the three-byte header, then stores that unchanged X in $02. */
    game->ram[MYSMB_STATUS_BUFFER + offset] = selector == 0U ? 0x22U : 0x20U;
    game->ram[MYSMB_STATUS_BUFFER + 1U + offset] = mysmb_status_data[y];
    length = mysmb_status_data[y + 1U];
    game->ram[MYSMB_STATUS_BUFFER + 2U + offset] = length;
    /* ROM OutputNumbers saves its live buffer pointer and digit count in
     * zero-page $02/$03 before it calculates the source digit offset. */
    game->ram[0x0003U] = length;
    game->ram[0x0002U] = offset;
    digit = (mysmb_u8)(mysmb_status_offset[selector] - length);
    while (game->ram[0x0003U] != 0U) {
        /* The ROM wraps X after STA VRAM_Buffer1+3,X, not the
         * absolute address before the store. Keep the +3 outside X. */
        game->ram[MYSMB_STATUS_BUFFER + 3U + offset] = game->ram[MYSMB_STATUS_DIGITS + digit];
        offset++;
        digit++;
        --game->ram[0x0003U];
    }
    game->ram[MYSMB_STATUS_BUFFER + 3U + offset] = 0U;
    game->ram[MYSMB_STATUS_BUFFER_OFFSET] = (mysmb_u8)(offset + 3U);
    return 1U;
}

mysmb_u8 mysmb_status_print_numbers(struct mysmb_game *game, mysmb_u8 nybbles)
{
    /* ROM PrintStatusBarNumbers retains the selector in $00 between its
     * low-nybble and high-nybble OutputNumbers calls. */
    game->ram[0x0000U] = nybbles;
    (void)mysmb_status_output_numbers(game, nybbles);
    return mysmb_status_output_numbers(game, (mysmb_u8)(game->ram[0x0000U] >> 4U));
}

mysmb_u8 mysmb_status_queue_timer(struct mysmb_game *game)
{
    return mysmb_status_print_numbers(game, 0xa4U);
}

void mysmb_status_apply_digit_modifier(struct mysmb_game *game, mysmb_u8 digit_offset)
{
    mysmb_u8 index;
    mysmb_u8 value;
    if (game->ram[MYSMB_STATUS_MODE] != 0U) {
        for (index = 5U;; --index) {
            value = (mysmb_u8)(game->ram[MYSMB_STATUS_MODIFIER + index] + game->ram[MYSMB_STATUS_DIGITS + digit_offset]);
            if (value >= 0x80U) { game->ram[MYSMB_STATUS_MODIFIER + index - 1U]--; value = 9U; }
            else if (value >= 10U) { value = (mysmb_u8)(value - 10U); game->ram[MYSMB_STATUS_MODIFIER + index - 1U]++; }
            game->ram[MYSMB_STATUS_DIGITS + digit_offset] = value;
            if (index == 0U) break;
            digit_offset--;
        }
    }
    /* ROM EraseMLoop clears from DigitModifier+5 down to -1. */
    for (index = 6U;; --index) {
        game->ram[MYSMB_STATUS_MODIFIER - 1U + index] = 0U;
        if (index == 0U) break;
    }
}

/* ROM TopScoreCheck / GetScoreDiff / CopyScore / NoTopSc. */
static void mysmb_status_top_score_check(struct mysmb_game *game,
                                          mysmb_u8 player_offset)
{
    mysmb_u8 index;
    mysmb_u8 borrow;

    borrow = 0U;
    for (index = 6U; index != 0U; --index)
        /* SBC carry compares against the full subtrahend plus borrow;
         * $ff + borrow must remain $100 for this comparison. */
        borrow = game->ram[MYSMB_STATUS_PLAYER_SCORE + player_offset + index - 1U] < (mysmb_u16)(game->ram[MYSMB_STATUS_TOP_SCORE + index - 1U] + borrow) ? 1U : 0U;
    if (borrow != 0U) return;
    for (index = 0U; index < 6U; ++index)
        game->ram[MYSMB_STATUS_TOP_SCORE + index] = game->ram[MYSMB_STATUS_PLAYER_SCORE + player_offset + index];
}

void mysmb_status_update_top_score(struct mysmb_game *game)
{
    /* Original JSR checks Mario, then the Luigi setup falls into the
     * same TopScoreCheck body. Keep that shared child in the C graph. */
    mysmb_status_top_score_check(game, 0U);
    mysmb_status_top_score_check(game, 6U);
}
