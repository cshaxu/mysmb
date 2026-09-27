#include "game/status.h"

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
    game->ram[MYSMB_STATUS_BUFFER + offset++] = selector == 0U ? 0x22U : 0x20U;
    game->ram[MYSMB_STATUS_BUFFER + offset++] = mysmb_status_data[y];
    length = mysmb_status_data[y + 1U];
    game->ram[MYSMB_STATUS_BUFFER + offset++] = length;
    digit = (mysmb_u8)(mysmb_status_offset[selector] - length);
    while (length-- != 0U)
        game->ram[MYSMB_STATUS_BUFFER + offset++] = game->ram[MYSMB_STATUS_DIGITS + digit++];
    game->ram[MYSMB_STATUS_BUFFER + offset] = 0U;
    game->ram[MYSMB_STATUS_BUFFER_OFFSET] = offset;
    return 1U;
}

static mysmb_u8 mysmb_status_print_numbers(struct mysmb_game *game, mysmb_u8 nybbles)
{
    (void)mysmb_status_output_numbers(game, nybbles);
    return mysmb_status_output_numbers(game, (mysmb_u8)(nybbles >> 4U));
}

mysmb_u8 mysmb_status_queue_score_coin(struct mysmb_game *game)
{
    mysmb_u8 player;
    mysmb_u8 offset;
    if (game->ram[MYSMB_STATUS_BUFFER_OFFSET] > 0xf1U) return 0U;
    player = (mysmb_u8)(game->ram[MYSMB_STATUS_CURRENT_PLAYER] & 1U);
    if (mysmb_status_print_numbers(game, player != 0U ? 0x13U : 0x02U) == 0U) return 0U;
    offset = game->ram[MYSMB_STATUS_BUFFER_OFFSET];
    if (game->ram[MYSMB_STATUS_BUFFER + offset - 6U] == 0U)
        game->ram[MYSMB_STATUS_BUFFER + offset - 6U] = 0x24U;
    return 1U;
}

mysmb_u8 mysmb_status_queue_timer(struct mysmb_game *game)
{
    return mysmb_status_print_numbers(game, 0xa4U);
}

mysmb_u8 mysmb_status_queue_title_score(struct mysmb_game *game)
{
    if (mysmb_status_print_numbers(game, 0xfaU) == 0U) return 0U;
    if (game->ram[MYSMB_STATUS_BUFFER + game->ram[MYSMB_STATUS_BUFFER_OFFSET] - 6U] == 0U)
        game->ram[MYSMB_STATUS_BUFFER + game->ram[MYSMB_STATUS_BUFFER_OFFSET] - 6U] = 0x24U;
    return 1U;
}

mysmb_u8 mysmb_status_queue_bottom_line(struct mysmb_game *game)
{
    mysmb_u8 offset;
    if (game->ram[MYSMB_STATUS_BUFFER_OFFSET] != 0U) return 0U;
    if (mysmb_status_queue_score_coin(game) == 0U) return 0U;
    offset = game->ram[MYSMB_STATUS_BUFFER_OFFSET];
    game->ram[MYSMB_STATUS_BUFFER + offset++] = 0x20U;
    game->ram[MYSMB_STATUS_BUFFER + offset++] = 0x73U;
    game->ram[MYSMB_STATUS_BUFFER + offset++] = 3U;
    game->ram[MYSMB_STATUS_BUFFER + offset++] = (mysmb_u8)(game->ram[MYSMB_STATUS_WORLD] + 1U);
    game->ram[MYSMB_STATUS_BUFFER + offset++] = 0x28U;
    game->ram[MYSMB_STATUS_BUFFER + offset++] = (mysmb_u8)(game->ram[MYSMB_STATUS_LEVEL] + 1U);
    game->ram[MYSMB_STATUS_BUFFER + offset] = 0U;
    game->ram[MYSMB_STATUS_BUFFER_OFFSET] = offset;
    return 1U;
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
    for (index = 0U; index <= 6U; ++index)
        game->ram[MYSMB_STATUS_MODIFIER - 1U + index] = 0U;
}

void mysmb_status_update_top_score(struct mysmb_game *game)
{
    mysmb_u8 player_offset;
    mysmb_u8 index;
    mysmb_u8 borrow;
    for (player_offset = 0U; player_offset <= 6U; player_offset = (mysmb_u8)(player_offset + 6U)) {
        borrow = 0U;
        for (index = 6U; index != 0U; --index)
            borrow = game->ram[MYSMB_STATUS_PLAYER_SCORE + player_offset + index - 1U] < (mysmb_u8)(game->ram[MYSMB_STATUS_TOP_SCORE + index - 1U] + borrow) ? 1U : 0U;
        if (borrow == 0U) for (index = 0U; index < 6U; ++index)
            game->ram[MYSMB_STATUS_TOP_SCORE + index] = game->ram[MYSMB_STATUS_PLAYER_SCORE + player_offset + index];
    }
}
