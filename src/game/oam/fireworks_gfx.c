#include "game/oam/oam.h"

/* Existing DrawExplosion_Fireworks body extracted from the actor. Original
 * generic explosion scratch/layout proof remains with its graphics owner. */
void mysmb_oam_draw_fireworks_explosion(struct mysmb_game *game,
                                       mysmb_u8 frame, mysmb_u8 oam)
{
    static const mysmb_u8 tiles[3] = {0x68U,0x67U,0x66U};
    mysmb_u8 x, y;
    x = game->ram[0x03afU];
    y = game->ram[0x03baU];
    game->ram[0x0200U + oam] = (mysmb_u8)(y - 4U);
    game->ram[0x0204U + oam] = (mysmb_u8)(y + 4U);
    game->ram[0x0208U + oam] = (mysmb_u8)(y - 4U);
    game->ram[0x020cU + oam] = (mysmb_u8)(y + 4U);
    game->ram[0x0201U + oam] = tiles[frame];
    game->ram[0x0205U + oam] = tiles[frame];
    game->ram[0x0209U + oam] = tiles[frame];
    game->ram[0x020dU + oam] = tiles[frame];
    game->ram[0x0202U + oam] = 2U;
    game->ram[0x0206U + oam] = 0x82U;
    game->ram[0x020aU + oam] = 0x42U;
    game->ram[0x020eU + oam] = 0xc2U;
    game->ram[0x0203U + oam] = (mysmb_u8)(x - 4U);
    game->ram[0x0207U + oam] = (mysmb_u8)(x - 4U);
    game->ram[0x020bU + oam] = (mysmb_u8)(x + 4U);
    game->ram[0x020fU + oam] = (mysmb_u8)(x + 4U);
}
