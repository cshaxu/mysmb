#include "game/oam/oam.h"

/* ROM $e4ae SixSpriteStacker through $e4be StkLp.  The caller supplies the
 * original A and Y values; each pass stores A at Sprite_Data,Y, adds eight,
 * and advances Y by one OAM record. */
void mysmb_oam_stack_six_sprite_data(struct mysmb_game *game,
                                     mysmb_u8 value, mysmb_u8 oam)
{
    mysmb_u8 count;

    for (count = 0U; count < 6U; ++count) {
        game->ram[(mysmb_u16)(0x0200U + oam)] = value;
        value = (mysmb_u8)(value + 8U);
        oam = (mysmb_u8)(oam + 4U);
    }
}
