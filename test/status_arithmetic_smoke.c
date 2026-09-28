#include "game/status.h"
#include "game/frame_root.h"

#include <string.h>

static int mysmb_status_test_digits(void)
{
    struct mysmb_game game;
    mysmb_u8 index;

    memset(&game, 0, sizeof(game));
    game.ram[0x0770U] = 1U;
    game.ram[0x07d7U + 0x0bU] = 9U;
    game.ram[0x0134U + 5U] = 1U;
    game.ram[0x0133U] = 0x5aU;
    game.ram[0x013aU] = 0xa5U;
    mysmb_status_apply_digit_modifier(&game, 0x0bU);
    if (game.ram[0x07d7U + 0x0bU] != 0U) return 11;
    if (game.ram[0x07d7U + 0x0aU] != 1U) return 12;
    for (index = 0U; index <= 6U; ++index)
        if (game.ram[0x0133U + index] != 0U) return 2;
    if (game.ram[0x013aU] != 0xa5U) return 13;

    memset(&game, 0, sizeof(game));
    game.ram[0x0770U] = 1U;
    game.ram[0x0134U + 5U] = 0xffU;
    game.ram[0x0133U] = 0x5aU;
    game.ram[0x013aU] = 0xa5U;
    mysmb_status_apply_digit_modifier(&game, 0x0bU);
    for (index = 0U; index < 6U; ++index)
        if (game.ram[0x07d7U + 0x06U + index] != 9U) return 3;
    for (index = 0U; index <= 6U; ++index)
        if (game.ram[0x0133U + index] != 0U) return 4;
    if (game.ram[0x013aU] != 0xa5U) return 5;

    memset(&game, 0, sizeof(game));
    game.ram[0x0770U] = 2U;
    game.ram[0x000eU] = 8U;
    game.ram[0x07f8U] = 1U;
    if (mysmb_game_run_timer(&game) == 0U || game.ram[0x07faU] != 9U ||
        game.ram[0x0787U] != 0x18U) return 6;
    return 0;
}

static int mysmb_status_test_output(void)
{
    struct mysmb_game game;
    mysmb_u8 index;

    memset(&game, 0, sizeof(game));
    for (index = 0U; index < 6U; ++index) game.ram[0x07d7U + 6U + index] = index;
    game.ram[0x07d7U + 22U] = 4U;
    game.ram[0x07d7U + 23U] = 2U;
    if (mysmb_status_queue_score_coin(&game) == 0U) return 11;
    if (game.ram[0x0300U] != 14U) return 12;
    if (game.ram[0x0301U] != 0x20U || game.ram[0x0302U] != 0x6dU ||
        game.ram[0x0303U] != 2U || game.ram[0x0304U] != 4U ||
        game.ram[0x0305U] != 2U) return 13;
    if (game.ram[0x0306U] != 0x20U || game.ram[0x0307U] != 0x62U ||
        game.ram[0x0308U] != 6U || game.ram[0x0309U] != 0x24U ||
        game.ram[0x030fU] != 0U) return 14;

    memset(&game, 0, sizeof(game));
    game.ram[0x0753U] = 1U;
    game.ram[0x07d7U + 12U] = 7U;
    game.ram[0x07d7U + 28U] = 4U;
    game.ram[0x07d7U + 29U] = 2U;
    if (mysmb_status_queue_score_coin(&game) == 0U || game.ram[0x0300U] != 14U ||
        game.ram[0x0301U] != 0x20U || game.ram[0x0302U] != 0x6dU ||
        game.ram[0x0304U] != 4U || game.ram[0x0305U] != 2U ||
        game.ram[0x0307U] != 0x62U || game.ram[0x0308U] != 6U ||
        game.ram[0x0309U] != 7U) return 15;

    memset(&game, 0, sizeof(game));
    if (mysmb_status_queue_title_score(&game) == 0U || game.ram[0x0300U] != 9U ||
        game.ram[0x0301U] != 0x22U || game.ram[0x0302U] != 0xf0U ||
        game.ram[0x0303U] != 6U || game.ram[0x0304U] != 0x24U ||
        game.ram[0x030aU] != 0U) return 16;

    memset(&game, 0, sizeof(game));
    game.ram[0x07f8U] = 1U; game.ram[0x07f9U] = 2U; game.ram[0x07faU] = 3U;
    if (mysmb_status_queue_timer(&game) == 0U || game.ram[0x0300U] != 6U ||
        game.ram[0x0301U] != 0x20U || game.ram[0x0302U] != 0x7aU ||
        game.ram[0x0303U] != 3U || game.ram[0x0304U] != 1U ||
        game.ram[0x0306U] != 3U) return 2;
    return 0;
}

static int mysmb_status_test_top_score(void)
{
    struct mysmb_game game;
    mysmb_u8 index;

    memset(&game, 0, sizeof(game));
    game.ram[0x07d7U] = 1U;
    game.ram[0x07d8U] = 2U;
    game.ram[0x07d9U] = 3U;
    game.ram[0x07ddU] = 1U;
    game.ram[0x07deU] = 2U;
    game.ram[0x07dfU] = 4U;
    mysmb_status_update_top_score(&game);
    if (game.ram[0x07d7U] != 1U || game.ram[0x07d8U] != 2U ||
        game.ram[0x07d9U] != 4U) return 21;

    for (index = 0U; index < 6U; ++index)
        game.ram[0x07ddU + index] = 0U;
    game.ram[0x07e3U] = 1U;
    game.ram[0x07e4U] = 2U;
    game.ram[0x07e5U] = 5U;
    mysmb_status_update_top_score(&game);
    if (game.ram[0x07d7U] != 1U || game.ram[0x07d8U] != 2U ||
        game.ram[0x07d9U] != 5U) return 22;

    for (index = 0U; index < 6U; ++index) {
        game.ram[0x07ddU + index] = 0U;
        game.ram[0x07e3U + index] = 0U;
    }
    mysmb_status_update_top_score(&game);
    if (game.ram[0x07d7U] != 1U || game.ram[0x07d8U] != 2U ||
        game.ram[0x07d9U] != 5U) return 23;
    return 0;
}

int main(void)
{
    int result;
    result = mysmb_status_test_digits();
    if (result != 0) return result;
    result = mysmb_status_test_output();
    if (result != 0) return result;
    return mysmb_status_test_top_score();
}
