#include "game/oam/oam.h"

enum {
    MYSMB_FIREBALL_RELATIVE_X = 0x03afU,
    MYSMB_FIREBALL_RELATIVE_Y = 0x03baU,
    MYSMB_FIREBALL_SPRITE_OFFSET = 0x06f1U,
    MYSMB_ALT_SPRITE_OFFSET = 0x06ecU,
    MYSMB_FRAME_COUNTER = 0x0009U
};
/* ROM DrawFireball / DrawFirebar. */
void mysmb_oam_draw_fireball(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 oam_offset;
    mysmb_u8 relative_x;
    mysmb_u8 attributes;
    relative_x = game->ram[MYSMB_FIREBALL_RELATIVE_X];
    oam_offset = game->ram[MYSMB_FIREBALL_SPRITE_OFFSET + slot];
    attributes = (game->ram[MYSMB_FRAME_COUNTER] & 0x10U) != 0U ? 0xc2U : 2U;
    game->ram[(mysmb_u16)(0x0200U + oam_offset)] = game->ram[MYSMB_FIREBALL_RELATIVE_Y];
    game->ram[(mysmb_u16)(0x0201U + oam_offset)] =
        (mysmb_u8)(0x64U ^ ((game->ram[MYSMB_FRAME_COUNTER] >> 2U) & 1U));
    game->ram[(mysmb_u16)(0x0202U + oam_offset)] = attributes;
    game->ram[(mysmb_u16)(0x0203U + oam_offset)] = relative_x;
}
/* Existing DrawExplosion_Fireball child, including its state advance moved
 * from the caller. Sprite layout retains the graphics owner's pending proof. */
void mysmb_oam_draw_fireball_explosion(struct mysmb_game *game,
                                                  mysmb_u8 slot)
{
    mysmb_u8 state;
    mysmb_u8 explosion_index;
    mysmb_u8 tile;
    mysmb_u8 oam_offset;
    mysmb_u8 relative_x;
    mysmb_u8 y;
    state = game->ram[0x0024U + slot];
    explosion_index = (mysmb_u8)((state >> 1U) & 7U);
    game->ram[0x0024U + slot] = (mysmb_u8)(state + 1U);
    if (explosion_index >= 3U) {
        game->ram[0x0024U + slot] = 0U;
        return;
    }
    tile = (mysmb_u8)(0x68U - explosion_index);
    relative_x = game->ram[MYSMB_FIREBALL_RELATIVE_X];
    oam_offset = game->ram[MYSMB_ALT_SPRITE_OFFSET + slot];
    y = (mysmb_u8)(game->ram[MYSMB_FIREBALL_RELATIVE_Y] - 4U);
    game->ram[(mysmb_u16)(0x0200U + oam_offset)] = y;
    game->ram[(mysmb_u16)(0x0204U + oam_offset)] = y;
    y = (mysmb_u8)(y + 8U);
    game->ram[(mysmb_u16)(0x0208U + oam_offset)] = y;
    game->ram[(mysmb_u16)(0x020cU + oam_offset)] = y;
    game->ram[(mysmb_u16)(0x0201U + oam_offset)] = tile;
    game->ram[(mysmb_u16)(0x0205U + oam_offset)] = tile;
    game->ram[(mysmb_u16)(0x0209U + oam_offset)] = tile;
    game->ram[(mysmb_u16)(0x020dU + oam_offset)] = tile;
    game->ram[(mysmb_u16)(0x0202U + oam_offset)] = 2U;
    game->ram[(mysmb_u16)(0x0206U + oam_offset)] = 0x82U;
    game->ram[(mysmb_u16)(0x020aU + oam_offset)] = 0x42U;
    game->ram[(mysmb_u16)(0x020eU + oam_offset)] = 0xc2U;
    relative_x = (mysmb_u8)(relative_x - 4U);
    game->ram[(mysmb_u16)(0x0203U + oam_offset)] = relative_x;
    game->ram[(mysmb_u16)(0x0207U + oam_offset)] = relative_x;
    relative_x = (mysmb_u8)(relative_x + 8U);
    game->ram[(mysmb_u16)(0x020bU + oam_offset)] = relative_x;
    game->ram[(mysmb_u16)(0x020fU + oam_offset)] = relative_x;
}
