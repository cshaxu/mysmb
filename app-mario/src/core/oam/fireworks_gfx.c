#include "core/oam/oam.h"

/* ROM $ed06 ExplosionTiles and $ed17 DrawExplosion_Fireworks.
 * Both original callers supply an index 0-2. INY wraps before DumpFourSpr;
 * base-address additions after DEY retain the original indexed addresses. */
void mysmb_oam_draw_fireworks_explosion(struct mysmb_game *game,
                                       mysmb_u8 frame, mysmb_u8 oam)
{
    static const mysmb_u8 tiles[3] = {0x68U, 0x67U, 0x66U};
    mysmb_u8 coordinate;
    mysmb_oam_dump_four_sprites(game, tiles[frame], (mysmb_u8)(oam + 1U));
    coordinate = (mysmb_u8)(game->ram[0x03baU] - 4U);
    game->ram[0x0200U + oam] = coordinate;
    game->ram[0x0208U + oam] = coordinate;
    coordinate = (mysmb_u8)(coordinate + 8U);
    game->ram[0x0204U + oam] = coordinate;
    game->ram[0x020cU + oam] = coordinate;
    coordinate = (mysmb_u8)(game->ram[0x03afU] - 4U);
    game->ram[0x0203U + oam] = coordinate;
    game->ram[0x0207U + oam] = coordinate;
    coordinate = (mysmb_u8)(coordinate + 8U);
    game->ram[0x020bU + oam] = coordinate;
    game->ram[0x020fU + oam] = coordinate;
    game->ram[0x0202U + oam] = 2U;
    game->ram[0x0206U + oam] = 0x82U;
    game->ram[0x020aU + oam] = 0x42U;
    game->ram[0x020eU + oam] = 0xc2U;
    mysmb_text_observer_record(game, MYSMB_TEXT_OBSERVE_EXPLOSION,
        0U, oam, frame, 1U, oam, 4U, 0U);
}
