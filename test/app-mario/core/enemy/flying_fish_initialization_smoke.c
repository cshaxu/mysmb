#include "core/enemy/frenzy.h"
#include <stdio.h>
#include <string.h>

static struct mysmb_game game;
static unsigned char expected[2048];

int main(void)
{
    static const unsigned char player_speeds[8] = {0U,1U,7U,8U,24U,25U,127U,255U};
    static const unsigned char timers[4] = {16U,96U,32U,72U};
    static const unsigned char speeds[12] = {14U,5U,6U,14U,28U,32U,16U,12U,30U,34U,24U,20U};
    static const unsigned char positions[16] = {128U,48U,64U,128U,48U,80U,80U,112U,32U,64U,128U,160U,112U,64U,144U,104U};
    unsigned int slot, hard, speed, random, timer, first, third, bias, index, scratch, cases;
    unsigned long world;
    cases = 0U;
    for (slot = 0U; slot < 6U; ++slot) for (timer = 1U; timer < 256U; ++timer) {
        memset(&game, 0, sizeof(game));
        memset(game.ram, 0xa5, sizeof(game.ram));
        game.ram[0x78fU] = (mysmb_u8)timer;
        memcpy(expected, game.ram, sizeof(expected));
        mysmb_enemy_init_flying_cheep_frenzy(&game, (mysmb_u8)slot);
        if (memcmp(expected, game.ram, sizeof(expected))) return 1;
        ++cases;
    }
    for (slot = 0U; slot < 6U; ++slot) for (hard = 0U; hard < 2U; ++hard)
    for (speed = 0U; speed < 8U; ++speed) for (random = 0U; random < 256U; ++random) {
        memset(&game, 0, sizeof(game));
        memset(game.ram, 0xa5, sizeof(game.ram));
        first = random & 3U;
        timer = (random >> 2U) & 3U;
        third = random >> 4U;
        game.ram[0x78fU] = 0U;
        game.ram[0x6ccU] = hard ? 0xffU : 0U;
        game.ram[0x57U] = player_speeds[speed];
        game.ram[0x7a7U + slot] = (mysmb_u8)first;
        game.ram[0x7a8U + slot] = (mysmb_u8)timer;
        game.ram[0x7a9U + slot] = (mysmb_u8)third;
        game.ram[0x86U] = (mysmb_u8)(random * 17U);
        game.ram[0x6dU] = (random & 0x80U) ? 0xffU : 0U;
        memcpy(expected, game.ram, sizeof(expected));
        expected[0x49aU + slot] = 9U;
        expected[0x46U + slot] = 2U;
        expected[0xa0U + slot] = 0U;
        expected[0x434U + slot] = 0U;
        expected[0x78fU] = timers[timer];
        expected[0U] = (unsigned char)(hard ? 4U : 3U);
        if (slot < (hard ? 4U : 3U)) {
            bias = speed == 0U ? 0U : (player_speeds[speed] < 25U ? 4U : 8U);
            scratch = timer == 0U ? bias + first : third;
            expected[0U] = (unsigned char)scratch;
            expected[1U] = (unsigned char)first;
            expected[0xa0U + slot] = 0xfbU;
            index = speed == 0U ? scratch : bias + first;
            expected[0x58U + slot] = speeds[bias + first];
            expected[0x46U + slot] = 1U;
            if (speed == 0U && (index & 2U)) {
                expected[0x58U + slot] = (unsigned char)(256U - speeds[first]);
                expected[0x46U + slot] = 2U;
            }
            world = (unsigned long)game.ram[0x6dU] * 256UL + game.ram[0x86U];
            world = (index & 2U) ? world + positions[index] : world - positions[index];
            expected[0x87U + slot] = (unsigned char)(world & 255UL);
            expected[0x6eU + slot] = (unsigned char)((world >> 8U) & 255UL);
            expected[0x0fU + slot] = 1U;
            expected[0xb6U + slot] = 1U;
            expected[0xcfU + slot] = 0xf8U;
        }
        mysmb_enemy_init_flying_cheep_frenzy(&game, (mysmb_u8)slot);
        if (memcmp(expected, game.ram, sizeof(expected))) {
            printf("slot=%u hard=%u player=%u random=%u mismatch\n",
                slot, hard, (unsigned int)player_speeds[speed], random);
            return 2;
        }
        ++cases;
    }
    printf("%u flying-fish initializer footprints match\n", cases);
    return 0;
}
