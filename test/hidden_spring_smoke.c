#include "game/player/terrain_children.h"
#include "core/area.h"
#include "game/objects.h"
#include <stdio.h>
#include <string.h>

static unsigned int failures;
void mysmb_area_remove_coin_axe(struct mysmb_game *game, mysmb_u8 low, mysmb_u8 row)
{ (void)game; (void)low; (void)row; ++failures; }
void mysmb_objects_give_one_coin(struct mysmb_game *game)
{ (void)game; ++failures; }

int main(void)
{
    static struct mysmb_game game;
    static unsigned char expected[2048];
    unsigned int tile, pattern, i, hidden_count, spring_count;
    hidden_count = spring_count = 0U;
    for (tile = 0U; tile < 256U; ++tile) {
        if (mysmb_player_invisible_metatile((mysmb_u8)tile)) {
            ++hidden_count;
            if (tile != 95U && tile != 96U) ++failures;
        }
        if (mysmb_player_jumpspring_metatile((mysmb_u8)tile)) {
            ++spring_count;
            if (tile != 103U && tile != 104U) ++failures;
        }
        for (pattern = 0U; pattern < 4U; ++pattern) {
            for (i = 0U; i < 2048U; ++i)
                game.ram[i] = (unsigned char)(i * 17U + pattern * 73U);
            memcpy(expected, game.ram, sizeof(expected));
            if (tile == 103U || tile == 104U) {
                expected[0x709U] = 0x70U; expected[0x6dbU] = 0xf9U;
                expected[0x786U] = 3U; expected[0x70eU] = 1U;
            }
            mysmb_player_land_jumpspring(&game, (mysmb_u8)tile);
            if (memcmp(game.ram, expected, sizeof(expected))) ++failures;
        }
    }
    if (hidden_count != 2U || spring_count != 2U) ++failures;
    printf("hidden/spring: 256 predicate inputs, 1024 RAM cases, %u errors\n", failures);
    return failures ? 1 : 0;
}
