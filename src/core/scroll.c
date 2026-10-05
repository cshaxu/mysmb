#include "core/player.h"
#include "core/oam/oam.h"

/* ROM $b038 GetScreenPosition. Shared by InitializeArea and ScrollScreen. */
void mysmb_player_get_screen_position(struct mysmb_game *game)
{
    mysmb_u8 left;
    left = game->ram[0x071cU];
    game->ram[0x071dU] = (mysmb_u8)(left + 0xffU);
    game->ram[0x071bU] = (mysmb_u8)(game->ram[0x071aU] +
                                     (left != 0U ? 1U : 0U));
}

/* ROM $b000-$b033 ChkPOffscr, KeepOnscr, InitPlatScrl. The source tests
 * the raw GetXOffscreenBits byte, not a host-width world-position bound. */
static void clamp_screen_edge(struct mysmb_game *game)
{
    static const mysmb_u8 subtract[2] = { 0U, 0x10U }; /* $b034 */
    static const mysmb_u8 buttons[2] = { 1U, 2U };    /* $b036 */
    mysmb_u8 bits;
    mysmb_u8 edge;
    mysmb_u8 x;

    bits = mysmb_oam_get_x_offscreen_bits(game, 0U, game->ram[0x006dU],
                                         game->ram[0x0086U]);
    game->ram[0U] = bits;
    edge = (bits & 0x80U) != 0U ? 0U : 1U;
    if (edge == 0U || (bits & 0x20U) != 0U) {
        x = game->ram[0x071cU + edge];
        game->ram[0x0086U] = (mysmb_u8)(x - subtract[edge]);
        game->ram[0x006dU] = (mysmb_u8)(game->ram[0x071aU + edge] -
            (x < subtract[edge] ? 1U : 0U));
        if (game->ram[0x000cU] != buttons[edge]) game->ram[0x0057U] = 0U;
    }
    game->ram[0x03a1U] = 0U;
}

/* ROM $afc4 ScrollScreen, including its tail into ChkPOffscr. */
void mysmb_player_scroll_screen(struct mysmb_game *game, mysmb_u8 amount)
{
    mysmb_u8 left;
    left = game->ram[0x071cU];
    game->ram[0x0775U] = amount;
    game->ram[0x073dU] = (mysmb_u8)(game->ram[0x073dU] + amount);
    game->ram[0x071cU] = (mysmb_u8)(left + amount);
    game->ram[0x073fU] = game->ram[0x071cU];
    game->ram[0x071aU] = (mysmb_u8)(game->ram[0x071aU] +
        (game->ram[0x071cU] < left ? 1U : 0U));
    game->ram[0x0778U] = (mysmb_u8)((game->ram[0x0778U] & 0xfeU) |
                                     (game->ram[0x071aU] & 1U));
    mysmb_player_get_screen_position(game);
    game->ram[0x0795U] = 8U;
    clamp_screen_edge(game);
    /* Synchronize the game's existing mirror cache; physical visible PPU
     * state is still committed by the following NMI, never by this caller. */
    game->ppu.scroll_x = game->ram[0x073fU];
    game->ppu.scroll_y = game->ram[0x0740U];
    game->ppu.ppu_control_0 = game->ram[0x0778U];
    game->ppu.ppu_name_table = (mysmb_u8)(game->ram[0x0778U] & 3U);
}

/* ROM $af93-$afc3 ScrollHandler/ChkNearMid and $affb InitScrlAmt. */
void mysmb_player_update_scroll(struct mysmb_game *game)
{
    mysmb_u8 force;
    mysmb_u8 amount;
    force = (mysmb_u8)(game->ram[0x06ffU] + game->ram[0x03a1U]);
    game->ram[0x06ffU] = force;
    if (game->ram[0x0723U] != 0U || game->ram[0x0755U] < 0x50U ||
        game->ram[0x0785U] != 0U ||
        ((mysmb_u8)(force - 1U) & 0x80U) != 0U) {
        game->ram[0x0775U] = 0U;
        clamp_screen_edge(game);
        return;
    }
    amount = force;
    if (force >= 2U && game->ram[0x0755U] < 0x70U) --amount;
    mysmb_player_scroll_screen(game, amount);
}
