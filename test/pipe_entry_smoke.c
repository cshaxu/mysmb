#include "game/player.h"
#include <stdio.h>
#include <string.h>

static struct mysmb_game game;
static unsigned char prg[32768], expected[2048];
static unsigned int failures, cases;

static void initialize(void)
{
    unsigned int i;
    for (i = 0U; i < 2048U; ++i) game.ram[i] = (unsigned char)(i * 19U + 7U);
    game.area_prg = prg; game.area_prg_size = sizeof(prg);
    game.ram[0x6d6U] = 0U;
    game.ram[0x75dU] = game.ram[0x757U] = 255U;
}
static void accepted(void)
{
    expected[0x6deU] = 0x30U; expected[0xeU] = 3U;
    expected[0xffU] = 0x10U; expected[0x3c4U] = 0x20U;
}
int main(void)
{
    static const unsigned char zones[5] = { 0U, 1U, 2U, 3U, 0x80U };
    static const unsigned char xs[4] = { 0x5fU, 0x60U, 0x9fU, 0xa0U };
    unsigned int buttons, left, right, z, x, i, index;
    mysmb_u8 result;
    for (i = 0U; i < 16U; ++i) {
        prg[0x7f2U + i] = (unsigned char)(51U + i);
        prg[0x1cb4U + 50U + i] = (unsigned char)(200U + i);
        prg[0x1cbcU + 200U + i] = (unsigned char)(0x80U + i);
    }
    prg[0x7f2U] = 0U;
    prg[0x1cb4U + 255U] = 250U;
    prg[0x1cbcU + 250U] = 0xe5U;
    for (buttons = 0U; buttons < 256U; ++buttons) {
        for (left = 0U; left < 2U; ++left) {
            for (right = 0U; right < 2U; ++right) {
                initialize(); game.ram[0xbU] = (mysmb_u8)buttons;
                memcpy(expected, game.ram, sizeof(expected));
                if ((buttons & 4U) && left && right) accepted();
                result = mysmb_player_handle_vertical_pipe(&game,
                    left ? 0x10U : 0U, right ? 0x11U : 0U);
                if (result != ((buttons & 4U) && left && right ? 1U : 0U) ||
                    memcmp(game.ram, expected, sizeof(expected))) ++failures;
                ++cases;
            }
        }
    }
    for (z = 0U; z < 5U; ++z) {
        for (x = 0U; x < 4U; ++x) {
            initialize(); game.ram[0xbU] = 4U;
            game.ram[0x6d6U] = zones[z]; game.ram[0x86U] = xs[x];
            memcpy(expected, game.ram, sizeof(expected)); accepted();
            if (z != 0U) {
                index = ((unsigned int)zones[z] & 3U) * 4U + (x == 0U ? 0U : (x == 3U ? 2U : 1U));
                expected[0x75fU] = index ? (unsigned char)(50U + index) : 255U;
                expected[0x750U] = index ? (unsigned char)(0x80U + index) : 0xe5U;
                expected[0xfcU] = 0x80U;
                expected[0x751U] = expected[0x760U] = expected[0x75cU] = expected[0x752U] = 0U;
                expected[0x75dU] = expected[0x757U] = 0U;
            }
            if (!mysmb_player_handle_vertical_pipe(&game, 0x10U, 0x11U) ||
                memcmp(game.ram, expected, sizeof(expected))) ++failures;
            ++cases;
        }
    }
    printf("pipe entry: %u full-RAM cases, %u errors\n", cases, failures);
    return failures ? 1 : 0;
}
