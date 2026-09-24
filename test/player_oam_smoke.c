#include "game/player.h"

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
    game.ram[0x0086U] = 0x40U;
    game.ram[0x00ceU] = 0x60U;
    game.ram[0x0033U] = MYSMB_BUTTON_RIGHT;
    game.ram[0x03c4U] = 2U;
    mysmb_player_draw_oam(&game);
    if (game.ram[0x03adU] != 0x40U || game.ram[0x03b8U] != 0x60U ||
        game.ram[0x0204U] != 0x60U || game.ram[0x0205U] != 0x20U ||
        game.ram[0x0206U] != 2U || game.ram[0x0207U] != 0x40U ||
        game.ram[0x0208U] != 0x60U || game.ram[0x0209U] != 0x21U ||
        game.ram[0x020aU] != 2U || game.ram[0x020bU] != 0x48U ||
        game.ram[0x021cU] != 0x78U || game.ram[0x021dU] != 0x26U ||
        game.ram[0x021fU] != 0x40U) return 1;
    game.ram[0x0033U] = MYSMB_BUTTON_LEFT;
    mysmb_player_draw_oam(&game);
    if (game.ram[0x0205U] != 0x21U || game.ram[0x0206U] != 0x42U ||
        game.ram[0x0209U] != 0x20U || game.ram[0x020aU] != 0x42U) return 1;
    return 0;
}
