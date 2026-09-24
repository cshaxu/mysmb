#include "game/objects.h"

enum {
    MYSMB_SCREEN_LEFT_X = 0x071cU,
    MYSMB_SCREEN_LEFT_PAGE = 0x071aU,
    MYSMB_ENEMY_X = 0x0087U,
    MYSMB_ENEMY_PAGE = 0x006eU,
    MYSMB_ENEMY_BOUND_BOX = 0x049aU,
    MYSMB_ENEMY_OFFSCREEN_BITS = 0x03d1U,
    MYSMB_ENEMY_OFFSCREEN_BITS_MASKED = 0x03d8U,
    MYSMB_BOUNDING_BOX_ENEMY = 0x04b0U
};

/* ROM GetEnemyBoundBox / GetMaskedOffScrBits.  It is kept in a separate
 * compilation unit so the 16-bit OpenNT compiler can retain objects.c below
 * its per-segment code limit. */
void mysmb_objects_update_enemy_bounding_box(struct mysmb_game *game,
                                             mysmb_u8 slot)
{
    mysmb_u8 x_difference;
    mysmb_u8 page_difference;
    mysmb_u8 borrow;
    mysmb_u8 mask;
    mysmb_u8 masked;
    mysmb_u16 address;

    x_difference = (mysmb_u8)(game->ram[MYSMB_ENEMY_X + slot] -
                               game->ram[MYSMB_SCREEN_LEFT_X]);
    borrow = 0U;
    if (game->ram[MYSMB_ENEMY_X + slot] < game->ram[MYSMB_SCREEN_LEFT_X]) {
        borrow = 1U;
    }
    page_difference = (mysmb_u8)(game->ram[MYSMB_ENEMY_PAGE + slot] -
                                  game->ram[MYSMB_SCREEN_LEFT_PAGE] - borrow);
    mask = 0x44U;
    if (page_difference < 0x80U && (page_difference != 0U || x_difference != 0U)) {
        mask = 0x48U;
    }
    masked = (mysmb_u8)(mask & game->ram[MYSMB_ENEMY_OFFSCREEN_BITS + slot]);
    game->ram[MYSMB_ENEMY_OFFSCREEN_BITS_MASKED + slot] = masked;
    address = (mysmb_u16)(MYSMB_BOUNDING_BOX_ENEMY + slot * 4U);
    if (masked != 0U) {
        game->ram[address] = 0xffU;
        game->ram[address + 1U] = 0xffU;
        game->ram[address + 2U] = 0xffU;
        game->ram[address + 3U] = 0xffU;
        return;
    }
    mysmb_objects_set_bounding_box(game, address,
        game->ram[MYSMB_ENEMY_BOUND_BOX + slot],
        game->ram[0x03aeU + slot], game->ram[0x03b9U + slot]);
}
