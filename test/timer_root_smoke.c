#include "game/frame_root.h"

static void mysmb_timer_fill(struct mysmb_game *game, mysmb_u8 value)
{
    mysmb_u8 index;

    for (index = 0U; index <= 0x23U; ++index)
        game->ram[(mysmb_u16)(0x0780U + index)] = value;
}

static int mysmb_timer_check(const struct mysmb_game *game, mysmb_u8 last,
                             mysmb_u8 changed, mysmb_u8 unchanged)
{
    mysmb_u8 index;

    for (index = 0U; index <= 0x23U; ++index) {
        if (index <= last) {
            if (game->ram[(mysmb_u16)(0x0780U + index)] != changed) return 1;
        }
        else if (game->ram[(mysmb_u16)(0x0780U + index)] != unchanged) return 1;
    }
    return 0;
}

int main(void)
{
    struct mysmb_game game;

    mysmb_game_initialize(&game);
    mysmb_timer_fill(&game, 2U);
    game.ram[0x0747U] = 2U;
    game.ram[0x077fU] = 5U;
    mysmb_game_tick_player_timers(&game);
    if (game.ram[0x0747U] != 1U || game.ram[0x077fU] != 5U ||
        mysmb_timer_check(&game, 0x23U, 2U, 2U) != 0) return 1;

    mysmb_timer_fill(&game, 2U);
    game.ram[0x0747U] = 1U;
    game.ram[0x077fU] = 1U;
    mysmb_game_tick_player_timers(&game);
    if (game.ram[0x0747U] != 0U || game.ram[0x077fU] != 0U ||
        mysmb_timer_check(&game, 0x14U, 1U, 2U) != 0) return 2;

    mysmb_timer_fill(&game, 2U);
    game.ram[0x0747U] = 0U;
    game.ram[0x077fU] = 0U;
    mysmb_game_tick_player_timers(&game);
    if (game.ram[0x077fU] != 0x14U ||
        mysmb_timer_check(&game, 0x23U, 1U, 1U) != 0) return 3;
    return 0;
}