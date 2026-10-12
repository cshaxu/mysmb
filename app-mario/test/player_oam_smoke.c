#include "core/player.h"
#include "core/oam/oam.h"

int main(void)
{
    struct mysmb_game game;
    static mysmb_u8 prg[0x7000U];
    mysmb_u8 index;

    mysmb_game_initialize(&game);
    mysmb_game_bind_area_source(&game, prg, (mysmb_u16)sizeof(prg));
    prg[0x6e09U] = 0U;
    for (index = 0U; index < 8U; ++index)
        prg[(mysmb_u16)(0x6e17U + index)] = (mysmb_u8)(0x20U + index);
    game.ram[0x06e4U] = 4U;
    game.ram[0x071aU] = 0U;
    game.ram[0x071bU] = 1U;
    game.ram[0x0086U] = 0x40U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x60U;
    game.ram[0x0033U] = MYSMB_BUTTON_RIGHT;
    game.ram[0x03c4U] = 2U;
    mysmb_oam_draw_player(&game);
    if (game.ram[0x03adU] != 0x40U || game.ram[0x0755U] != 0x40U ||
        game.ram[0x03b8U] != 0x60U ||
        game.ram[0x0204U] != 0x60U || game.ram[0x0205U] != 0x20U ||
        game.ram[0x0206U] != 2U || game.ram[0x0207U] != 0x40U ||
        game.ram[0x0208U] != 0x60U || game.ram[0x0209U] != 0x21U ||
        game.ram[0x020aU] != 2U || game.ram[0x020bU] != 0x48U ||
        game.ram[0x021cU] != 0x78U || game.ram[0x021dU] != 0x26U ||
        game.ram[0x021fU] != 0x40U) return 1;
    game.ram[0x0033U] = MYSMB_BUTTON_RIGHT;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0xe6U;
    mysmb_oam_draw_player(&game);
    if (game.ram[0x03d0U] != 0x10U ||
        game.ram[0x021cU] != 0xf8U || game.ram[0x0220U] != 0xf8U) return 2;
    /* ROM GetOffScreenBitsSet shifts the horizontal table result down into
     * the low nibble before OR-ing the vertical result into the high nibble.
     * This is the source fixture at the first left-edge transition. */
    game.ram[0x071aU] = 0U;
    game.ram[0x071bU] = 1U;
    game.ram[0x071cU] = 0xf9U;
    game.ram[0x071dU] = 0xf8U;
    game.ram[0x006dU] = 0U;
    game.ram[0x0086U] = 0xf9U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0xb0U;
    mysmb_oam_draw_player(&game);
    if (game.ram[0x03d0U] != 0x08U) return 4;
    game.ram[0x0033U] = MYSMB_BUTTON_LEFT;
    mysmb_oam_draw_player(&game);
    if (game.ram[0x0205U] != 0x21U || game.ram[0x0206U] != 0x42U ||
        game.ram[0x0209U] != 0x20U || game.ram[0x020aU] != 0x42U) return 1;
    for (index = 0U; index < 8U; ++index)
        prg[(mysmb_u16)(0x6e17U + 0xb8U + index)] = (mysmb_u8)(0x40U + index);
    /* Synthetic table values prove that the intermediate path reads its
     * six source bytes and copies the following sprite's attribute. */
    prg[0x6f9eU] = 0x54U;
    prg[0x6f9fU] = 1U;
    prg[0x6fa0U] = 0U;
    prg[0x6fa1U] = 0x64U;
    prg[0x6fa2U] = 0xfeU;
    prg[0x6fa3U] = 4U;
    game.ram[0x0226U] = 3U;
    game.ram[0x0222U] = 0x20U;
    mysmb_oam_draw_intermediate_player(&game);
    if (game.ram[0x0204U] != 0x54U || game.ram[0x0205U] != 0x40U ||
        game.ram[0x0207U] != 0x64U || game.ram[0x0208U] != 0x54U ||
        game.ram[0x0209U] != 0x41U || game.ram[0x020bU] != 0x6cU ||
        game.ram[0x021cU] != 0x6cU || game.ram[0x021dU] != 0x46U ||
        game.ram[0x021fU] != 0x64U || game.ram[0x0222U] != 0x43U ||
        game.ram[0U] != 0x46U || game.ram[1U] != 0x47U ||
        game.ram[2U] != 0x74U || game.ram[3U] != 1U ||
        game.ram[4U] != 0U || game.ram[5U] != 0x64U ||
        game.ram[6U] != 0xfeU || game.ram[7U] != 0U) return 1;
    /* ROM ChkForPlayerAttrib treats graphics offset $c8 like PlayerKilled:
     * it flips the right sprites of both the third and fourth rows. */
    for (index = 0U; index < 8U; ++index)
        prg[(mysmb_u16)(0x6e17U + 0xc8U + index)] = (mysmb_u8)(0x60U + index);
    prg[0x6e16U] = 0xc8U;
    game.ram[0x070bU] = 1U;
    game.ram[0x070dU] = 0U;
    game.ram[0x0009U] = 1U;
    game.ram[0x0754U] = 0U;
    game.ram[0x0033U] = MYSMB_BUTTON_RIGHT;
    game.ram[0x03c4U] = 0U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x60U;
    mysmb_oam_draw_player(&game);
    if (game.ram[0x06d5U] != 0xc8U || game.ram[0x0216U] != 0U ||
        game.ram[0x021aU] != 0x40U || game.ram[0x021eU] != 0U ||
        game.ram[0x0222U] != 0x40U) return 3;
    return 0;
}
