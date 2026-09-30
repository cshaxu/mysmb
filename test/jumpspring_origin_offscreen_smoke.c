#include "game/objects.h"
#include "game/oam/oam.h"
#include <stdio.h>
#include <string.h>

static unsigned int erasures;
static unsigned int errors;

mysmb_u8 mysmb_objects_get_enemy_offscreen_bits(
    const struct mysmb_game *game, mysmb_u8 slot)
{
    (void)game;
    (void)slot;
    return 0U;
}

void mysmb_oam_relative_enemy_position(struct mysmb_game *game, mysmb_u8 slot)
{
    (void)game;
    (void)slot;
}

void mysmb_oam_draw_jumpspring(struct mysmb_game *game, mysmb_u8 slot)
{
    (void)game;
    (void)slot;
}

void mysmb_objects_erase_enemy(struct mysmb_game *game, mysmb_u8 slot)
{
    (void)game;
    (void)slot;
    ++erasures;
}

int main(void)
{
    static struct mysmb_game game;
    const mysmb_u8 slot = 0U;

    memset(&game, 0, sizeof(game));
    /* Original JumpspringHandler reaches OffscreenBoundsCheck with object
     * $32.  At screen origin the source's SBC borrow wraps the left edge to
     * page $ff, pixel $b8; a page-zero spring is therefore retained. */
    game.ram[0x0016U + slot] = 0x32U;
    game.ram[0x000fU + slot] = 1U;
    game.ram[0x071aU] = 0U;
    game.ram[0x071cU] = 0U;
    game.ram[0x071bU] = 1U;
    game.ram[0x071dU] = 0U;
    game.ram[0x006eU + slot] = 0U;
    game.ram[0x0087U + slot] = 0U;

    mysmb_objects_step_jumpspring(&game, slot);
    if (erasures != 0U || game.ram[0x000fU + slot] != 1U ||
        game.ram[0U] != 0xffU || game.ram[1U] != 0xb8U ||
        game.ram[2U] != 1U || game.ram[3U] != 0x48U) {
        ++errors;
    }
    printf("jumpspring screen-origin offscreen cases=1 errors=%u\n", errors);
    return errors != 0U;
}
