#include "core/frame_root.h"
#include "core/area.h"
#include "game/player.h"

/* Palette callers must never enter player control. */
void mysmb_player_step(struct mysmb_game *game, mysmb_u8 buttons)
{
    (void)buttons;
    game->ram[0x03c4U] = 0xffU;
}

static unsigned int music_calls;
static unsigned int parser_calls;
static mysmb_u8 parser_scroll;
static mysmb_u8 parser_offset;

void mysmb_game_get_area_music(struct mysmb_game *game)
{
    ++music_calls;
    game->ram[0x00fbU] = 0x40U;
}

mysmb_u8 mysmb_area_parser_task_step(struct mysmb_game *game)
{
    ++parser_calls;
    parser_scroll = game->ram[0x073dU];
    parser_offset = game->ram[0x0340U];
    return 1U;
}

int main(void)
{
    static struct mysmb_game game;
    static const unsigned int stars[] = {0U, 1U, 4U, 7U, 8U, 255U};
    static const unsigned int frames[] = {0U, 7U, 8U, 15U, 16U, 255U};
    unsigned int y, star, frame, interval, scroll, task, control;
    unsigned int expected, active, expected_music;

    for (y = 0U; y < 256U; ++y)
    for (star = 0U; star < 6U; ++star)
    for (frame = 0U; frame < 6U; ++frame)
    for (interval = 0U; interval < 2U; ++interval) {
        game.ram[0xb5U] = (mysmb_u8)y;
        game.ram[0x79fU] = (mysmb_u8)stars[star];
        game.ram[9U] = (mysmb_u8)frames[frame];
        game.ram[0x77fU] = (mysmb_u8)interval;
        game.ram[0x3c4U] = 0xa7U;
        music_calls = 0U;
        mysmb_game_cycle_player_palette(&game);
        /* The source CMP/BPL clear range is 0..1 or 130..255, not just
         * normal on-screen coordinates. Check every possible high byte. */
        active = y < 2U || y >= 130U;
        expected_music = active && stars[star] == 4U && interval == 0U;
        expected = (active && stars[star] == 0U) ? 0U :
            (frames[frame] / (stars[star] < 8U ? 8U : 2U)) % 4U;
        if (music_calls != expected_music || game.ram[0x3c4U] != 0xa4U + expected)
            return 1;
    }
    for (scroll = 0U; scroll < 256U; ++scroll)
    for (task = 0U; task < 2U; ++task)
    for (control = 0U; control < 2U; ++control) {
        game.ram[0x73dU] = (mysmb_u8)scroll;
        game.ram[0x71fU] = task != 0U ? 7U : 0U;
        game.ram[0x773U] = control != 0U ? 6U : 0U;
        game.ram[0x340U] = 0xa5U;
        parser_calls = 0U;
        mysmb_game_step_area_parser(&game);
        active = control == 0U && (task != 0U || (scroll >= 32U && scroll < 160U));
        expected = active && task == 0U ? scroll - 32U : scroll;
        if (parser_calls != active || game.ram[0x73dU] != expected ||
            game.ram[0x340U] != (active && task == 0U ? 0U : 0xa5U)) return 2;
        if (active && (parser_scroll != expected ||
            parser_offset != (task == 0U ? 0U : 0xa5U))) return 3;
    }
    return 0;
}
