#include "core/player.h"
#include <stdio.h>
#include <string.h>

static struct mysmb_game game;
static unsigned char expected[2048];

int main(void)
{
    unsigned int side, speed, edge, i, position, failures;
    unsigned long cases;
    int delta;
    failures = 0U; cases = 0UL;
    for (side = 0U; side < 256U; ++side) {
        for (speed = 0U; speed < 256U; ++speed) {
            for (edge = 0U; edge < 4U; ++edge) {
                memset(game.ram, 0xa5, sizeof(game.ram));
                game.ram[0U] = (mysmb_u8)side;
                game.ram[0x57U] = (mysmb_u8)speed;
                game.ram[0x86U] = (edge & 1U) ? 255U : 0U;
                game.ram[0x6dU] = (edge & 2U) ? 255U : 0U;
                memcpy(expected, game.ram, sizeof(expected));
                delta = 0;
                if (side == 1U && speed < 128U) delta = -1;
                if (side != 1U && (speed == 0U || speed > 128U)) delta = 1;
                if (delta) {
                    position = (unsigned int)expected[0x6dU] * 256U + expected[0x86U];
                    position = (unsigned int)(position + delta);
                    expected[0x86U] = (unsigned char)position;
                    expected[0x6dU] = (unsigned char)(position >> 8U);
                    expected[0U] = delta < 0 ? 255U : 0U;
                    expected[0x57U] = 0U; expected[0x785U] = 16U;
                }
                expected[0x490U] &= side == 1U ? 254U : 253U;
                mysmb_player_impede_move(&game, (mysmb_u8)side);
                for (i = 0U; i < 2048U; ++i) {
                    if (game.ram[i] != expected[i]) { ++failures; break; }
                }
                ++cases;
            }
        }
    }
    printf("impede cases=%lu failures=%u\n", cases, failures);
    return failures ? 1 : 0;
}
