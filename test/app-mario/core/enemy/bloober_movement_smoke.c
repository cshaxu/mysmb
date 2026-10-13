#include "core/enemy/actor_slots.h"
#include "core/enemy/movement.h"
#include <string.h>

static unsigned int gravity_calls;
void mysmb_enemy_move_slow_vertically(struct mysmb_game *game, mysmb_u8 slot)
{
    ++gravity_calls;
    game->ram[0xcfU + slot] = 0x93U;
}

/* Source-derived boundary cases. The expected RAM changes below are explicit,
 * including scratch; original-ROM route proof remains a separate check. */
int main(void)
{
    static struct mysmb_game game;
    unsigned char expected[2048];
    unsigned int n, slot;
    for (n = 0U; n < 10U; ++n) {
        memset(&game, 0, sizeof(game));
        slot = n == 1U ? 1U : 0U;
        game.ram[9U] = 2U;
        game.ram[0x7a8U + slot] = 1U;
        game.ram[0xa0U + slot] = 2U;
        game.ram[0xcfU + slot] = 0x80U;
        game.ram[0xceU] = 0x91U;
        game.ram[0x46U + slot] = 1U;
        /* No flag/ID guard at the source entry. */
        game.ram[0xfU + slot] = 0U;
        game.ram[0x16U + slot] = 0xffU;
        if (n == 1U) {
            game.ram[0x7a8U + slot] = 0U;
            game.ram[0x45U] = 1U;
        }
        if (n == 2U || n == 3U) {
            game.ram[0x7a8U] = 0U;
            game.ram[0x6eU] = n == 2U ? 0x80U : 0U;
            game.ram[0x6dU] = n == 2U ? 0U : 0xffU;
        }
        if (n == 4U) {
            game.ram[0xcfU] = 0U;
            game.ram[0x434U] = 1U;
            game.ram[9U] = 1U;
            game.ram[0x796U] = 1U;
        }
        if (n == 5U) {
            game.ram[0x1eU] = 0x20U;
        }
        if (n == 6U || n == 7U) {
            game.ram[0xa0U] = n == 6U ? 0U : 1U;
            game.ram[0x434U] = n == 6U ? 1U : 0U;
            game.ram[9U] = 0U;
        }
        if (n == 8U || n == 9U) {
            game.ram[0xceU] = 0U;
            game.ram[0x58U] = 2U;
            game.ram[0x87U] = n == 8U ? 0xffU : 0U;
            game.ram[0x6eU] = n == 8U ? 0xffU : 0U;
            game.ram[0x46U] = n == 8U ? 1U : 2U;
        }
        memcpy(expected, game.ram, sizeof(expected));
        switch (n) {
        case 0U: expected[0xcfU] = 0x81U; break;
        case 1U: expected[0xa1U] = 0U; break;
        case 2U: expected[0xa0U] = 0U; break;
        case 3U: expected[0x46U] = 2U; expected[0xcfU] = 0x81U; break;
        case 4U: expected[0xcfU] = 0xffU; break;
        case 5U: expected[0xcfU] = 0x93U; break;
        case 6U:
            expected[0xa0U] = 1U; expected[0x434U] = 2U;
            expected[0x58U] = 2U; expected[0xcfU] = 0x7eU;
            expected[0x87U] = 2U; break;
        case 7U:
            expected[0x434U] = 0xffU; expected[0x58U] = 0xffU;
            expected[0xcfU] = 0x81U; expected[0x87U] = 0xffU; break;
        case 8U:
            expected[0xa0U] = 0U; expected[0x87U] = 1U;
            expected[0x6eU] = 0U; break;
        case 9U:
            expected[0xa0U] = 0U; expected[0x87U] = 0xfeU;
            expected[0x6eU] = 0xffU; break;
        }
        gravity_calls = 0U;
        mysmb_objects_step_bloobers_slot(&game, (mysmb_u8)slot);
        if (memcmp(game.ram, expected, sizeof(expected)) != 0 ||
            gravity_calls != (n == 5U ? 1U : 0U)) return (int)n + 1;
    }
    return 0;
}
