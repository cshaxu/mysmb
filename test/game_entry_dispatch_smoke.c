#include <string.h>
#include "game/dispatcher.h"

static unsigned int calls;
static unsigned int sequence;
static unsigned int failed;
static mysmb_u8 post_task;
static mysmb_u8 selected;

/* Parent seam only; the real helper is checked against original ROM roots. */
void mysmb_game_jump_engine_state(struct mysmb_game *game,
                                 mysmb_u16 ret, mysmb_u8 selector)
{
    if (ret != 0xaee1U || selector != game->ram[0x0772U] || calls != 0U)
        failed = 1U;
}

void mysmb_area_initialize(struct mysmb_game *game)
{ (void)game; ++calls; sequence = sequence * 10U + 1U; }
void mysmb_game_step_screen_routine(struct mysmb_game *game)
{ (void)game; ++calls; sequence = sequence * 10U + 2U; }
void mysmb_game_secondary_setup(struct mysmb_game *game)
{ (void)game; ++calls; sequence = sequence * 10U + 3U; }
void mysmb_game_routines(struct mysmb_game *game)
{
    ++calls; sequence = sequence * 10U + 4U;
    if (game->ram[0x6fcU] != selected) failed = 1U;
    game->ram[0x772U] = post_task;
}
void mysmb_game_engine(struct mysmb_game *game)
{
    if (game->ram[0x772U] < 3U) failed = 1U;
    ++calls; sequence = sequence * 10U + 5U;
}

int main(void)
{
    static struct mysmb_game game;
    unsigned int task, player;
    for (task = 0U; task < 3U; ++task) {
        memset(&game, 0, sizeof(game));
        game.ram[0x772U] = (mysmb_u8)task;
        calls = 0U; sequence = 0U; failed = 0U;
        mysmb_game_mode(&game);
        if (failed || calls != 1U || sequence != task + 1U) return 1;
    }
    for (player = 0U; player < 2U; ++player)
    for (task = 0U; task < 256U; ++task) {
        memset(&game, 0, sizeof(game));
        game.ram[0x772U] = 3U;
        game.ram[0x753U] = (mysmb_u8)player;
        game.ram[0x6fcU] = 0x5aU; game.ram[0x6fdU] = 0xa5U;
        selected = player == 0U ? 0x5aU : 0xa5U;
        post_task = (mysmb_u8)task;
        calls = 0U; sequence = 0U; failed = 0U;
        mysmb_game_mode(&game);
        if (failed || game.ram[0x6fcU] != selected || game.ram[0x6fdU] != 0xa5U) return 2;
        if (calls != (task < 3U ? 1U : 2U) || sequence != (task < 3U ? 4U : 45U)) return 3;
    }
    return 0;
}
