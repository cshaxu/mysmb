#include "game/area.h"

static int check_id(mysmb_u8 id, int base)
{
    struct mysmb_game game;
    mysmb_u8 slot;

    mysmb_game_initialize(&game);
    for (slot = 0U; slot < 5U; ++slot) {
        game.ram[0x0016U + slot] = (slot == 0U || slot == 2U || slot == 4U)
            ? id : (mysmb_u8)(id + 1U);
        game.ram[0x000fU + slot] = (mysmb_u8)(0x30U + slot);
    }
    mysmb_area_kill_enemies(&game, id);
    if (game.ram[0x0000U] != id) return base + 1;
    for (slot = 0U; slot < 5U; ++slot) {
        if ((slot == 0U || slot == 2U || slot == 4U) &&
            game.ram[0x000fU + slot] != 0U) return base + 2 + (int)slot;
        if ((slot == 1U || slot == 3U) &&
            game.ram[0x000fU + slot] != (mysmb_u8)(0x30U + slot))
            return base + 7 + (int)slot;
    }
    return 0;
}

int main(void)
{
    int result;

    /* Source callers: PiranhaPlant=$0d at WarpNum and
     * BulletBill_CannonVar=$0b at flagpole collision. */
    result = check_id(0x0dU, 10);
    if (result != 0) return result;
    return check_id(0x0bU, 30);
}
