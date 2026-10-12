#include "core/dispatcher.h"
#include "core/area.h"

static unsigned int sequence[15];
static unsigned int count;
static unsigned int failed;
static const struct mysmb_area_source *expected_source;

void mysmb_fireball_step(struct mysmb_game *game)
{
    if (count != 0U) failed = 1U;
    sequence[count++] = 100U;
    game->ram[8U] = 0xa5U;
}
void mysmb_enemy_core_step_slot(struct mysmb_game *game,
    const struct mysmb_area_source *source, mysmb_u8 slot)
{
    if (source != expected_source || game->ram[8U] != slot || slot >= 6U)
        failed = 1U;
    sequence[count++] = 200U + slot;
}
void mysmb_objects_step_floatey_number(struct mysmb_game *game, mysmb_u8 slot)
{
    if (game->ram[8U] != slot || slot >= 6U) failed = 1U;
    sequence[count++] = 300U + slot;
}
void mysmb_objects_step_block(struct mysmb_game *game, mysmb_u8 slot)
{
    if (game->ram[8U] != slot || slot >= 2U) failed = 1U;
    sequence[count++] = 400U + slot;
}

int main(void)
{
    static struct mysmb_game game;
    struct mysmb_area_source source;
    unsigned int mode, slot;

    source.prg = 0; source.prg_size = 0U;
    for (mode = 0U; mode < 2U; ++mode) {
        expected_source = mode == 0U ? 0 : &source;
        count = 0U; failed = 0U;
        mysmb_game_engine_actors(&game, expected_source);
        if (failed || count != 13U || sequence[0] != 100U || game.ram[8U] != 5U)
            return 1;
        for (slot = 0U; slot < 6U; ++slot)
            if (sequence[1U+slot*2U] != 200U+slot ||
                sequence[2U+slot*2U] != 300U+slot) return 2;
        mysmb_game_engine_blocks(&game);
        if (failed || count != 15U || sequence[13U] != 401U ||
            sequence[14U] != 400U || game.ram[8U] != 0U) return 3;
    }
    return 0;
}
