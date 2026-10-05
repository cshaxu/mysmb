#include "game/player/terrain_children.h"
#include "core/area.h"
#include <stdio.h>
#include <string.h>

static unsigned int calls, failures;
static struct mysmb_game game;
static unsigned char prg[32768];

void mysmb_area_kill_enemies(struct mysmb_game *g, mysmb_u8 id)
{
    ++calls;
    if (id != 0x33U || g->ram[0x33U] != 1U || g->ram[0x723U] != 0U ||
        g->ram[0xfcU] != 0x55U || g->ram[0x713U] != 0x66U) ++failures;
    g->ram[0U] = id;
    /* Score and captured Y must use the state after the real child returns. */
    g->ram[0xceU] = 0x90U;
}

int main(void)
{
    struct mysmb_player_terrain terrain;
    unsigned int i, n, before;
    unsigned char initial[2048];
    memset(&terrain, 0, sizeof(terrain));
    for (i = 0U; i < 256U; ++i) {
        memset(&game, 0, sizeof(game));
        game.ram[0x86U] = 0x40U; game.ram[0x33U] = 1U;
        terrain.contact_low_nibble = (mysmb_u8)i; terrain.metatile = 0x27U;
        memcpy(initial, game.ram, sizeof(initial));
        (void)mysmb_player_handle_climbing(&game, &terrain);
        if (i < 6U || i >= 10U) {
            if (memcmp(initial, game.ram, sizeof(initial))) ++failures;
        } else if (game.ram[0x1dU] != 3U || game.ram[0x86U] != 0xf9U)
            ++failures;
    }
    for (n = 0U; n < 3U; ++n) {
        memset(&game, 0, sizeof(game));
        game.ram[0xeU] = n == 0U ? 8U : (n == 1U ? 4U : 5U);
        game.ram[0x723U] = 255U; game.ram[0x86U] = 0x40U;
        game.ram[0xfcU] = 0x55U; game.ram[0x713U] = 0x66U;
        game.ram[0x33U] = 2U; game.ram[0x10fU] = 0x77U;
        terrain.metatile = 0x24U; terrain.contact_low_nibble = 8U;
        before = calls;
        (void)mysmb_player_handle_climbing(&game, &terrain);
        if (calls != before + (n == 0U ? 1U : 0U)) ++failures;
        if (n == 0U && (game.ram[0x10fU] != 4U || game.ram[0x70fU] != 0x90U ||
            game.ram[0xfcU] != 0x80U || game.ram[0x713U] != 0x40U)) ++failures;
        if (n != 0U && (game.ram[0x10fU] != 0x77U || game.ram[0xfcU] != 0x55U ||
            game.ram[0x713U] != 0x66U)) ++failures;
        if (game.ram[0xeU] != (n == 2U ? 5U : 4U) ||
            game.ram[0x723U] != (n == 2U ? 255U : 0U)) ++failures;
    }
    /* Distinct bound bytes prove raw absolute indexing, including facing0
     * and values beyond the two normal entries, without normalizing them. */
    for (i = 0U; i < sizeof(prg); ++i) prg[i] = (unsigned char)(i * 13U);
    for (i = 0U; i < 256U; ++i) {
        memset(&game, 0, sizeof(game));
        game.area_prg = prg; game.area_prg_size = sizeof(prg);
        game.ram[0x33U] = (mysmb_u8)i; game.ram[0x86U] = 0x40U;
        game.ram[0x71bU] = 255U;
        terrain.metatile = 0x27U;
        (void)mysmb_player_handle_climbing(&game, &terrain);
        if (game.ram[0x86U] != prg[0x5e24U + i] ||
            game.ram[0x6dU] != (mysmb_u8)(255U + prg[0x5e26U + i])) ++failures;
    }
    printf("climbing: 515 scenarios, %u errors\n", failures);
    return failures ? 1 : 0;
}
