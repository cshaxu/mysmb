#include "game/enemy/core.h"
#include "game/enemy/actor_slots.h"
#include "game/enemy/distance.h"
#include "game/enemy/frenzy.h"
#include "game/enemy/init_targets.h"
#include "game/enemy/loop.h"
#include "game/enemy/movement.h"
#include "game/objects.h"

/* ROM $D061 PRandomRange and $D065-$D17A RunBowser/BowserControl.
 * KillAllEnemies remains the shared loop owner; graphics is a separate child. */
void mysmb_enemy_run_bowser(struct mysmb_game *g, mysmb_u8 slot)
{
    static const mysmb_u8 random_range[4] = {0x21U,0x41U,0x11U,0x31U};
    mysmb_u8 value, direction;
    if ((g->ram[0x001eU + slot] & 0x20U) != 0U) {
        if (g->ram[0x00cfU + slot] < 0xe0U)
            mysmb_enemy_move_d_bowser(g, slot);
        else mysmb_enemy_kill_all(g);
        return;
    }
    g->ram[0x06cbU] = 0U;
    if (g->ram[0x0747U] != 0U) goto check_fire;
    if ((g->ram[0x0363U] & 0x80U) != 0U) goto hammer_check;
    --g->ram[0x0364U];
    if (g->ram[0x0364U] == 0U) {
        g->ram[0x0364U] = 0x20U;
        g->ram[0x0363U] ^= 1U;
    }
    if ((g->ram[9U] & 0x0fU) == 0U) g->ram[0x0046U + slot] = 2U;
    if (g->ram[0x078aU + slot] != 0U) {
        if ((mysmb_enemy_player_difference(g, slot) & 0x80U) != 0U) {
            g->ram[0x0046U + slot] = 1U;
            g->ram[0x0365U] = 2U;
            g->ram[0x078aU + slot] = 0x20U;
            g->ram[0x0790U] = 0x20U;
            if (g->ram[0x0087U + slot] >= 0xc8U) goto hammer_check;
        }
    }
    if ((g->ram[9U] & 3U) != 0U) goto hammer_check;
    if (g->ram[0x0087U + slot] == g->ram[0x0366U])
        g->ram[0x06dcU] = random_range[g->ram[0x07a7U + slot] & 3U];
    g->ram[0x0087U + slot] = (mysmb_u8)(g->ram[0x0087U + slot] + g->ram[0x0365U]);
    if (g->ram[0x0046U + slot] == 1U) goto hammer_check;
    direction = 0xffU;
    value = (mysmb_u8)(g->ram[0x0087U + slot] - g->ram[0x0366U]);
    if ((value & 0x80U) != 0U) {
        value = (mysmb_u8)(0U - value);
        direction = 1U;
    }
    if (value >= g->ram[0x06dcU]) g->ram[0x0365U] = direction;
hammer_check:
    value = g->ram[0x078aU + slot];
    if (value != 0U) {
        if (value == 1U) {
            --g->ram[0x00cfU + slot];
            mysmb_enemy_init_vertical_state(g, slot);
            g->ram[0x00a0U + slot] = 0xfeU;
        }
    }
    else {
        mysmb_enemy_move_slow_vertically(g, slot);
        slot = g->ram[8U];
        if (g->ram[0x075fU] >= 5U && (g->ram[9U] & 3U) == 0U) {
            (void)mysmb_objects_spawn_hammer(g);
            slot = g->ram[8U];
        }
        if (g->ram[0x00cfU + slot] >= 0x80U)
            g->ram[0x078aU + slot] = random_range[g->ram[0x07a7U + slot] & 3U];
    }
check_fire:
    if (g->ram[0x075fU] != 7U && g->ram[0x075fU] >= 5U) goto graphics;
    if (g->ram[0x0790U] != 0U) goto graphics;
    g->ram[0x0790U] = 0x20U;
    g->ram[0x0363U] ^= 0x80U;
    if ((g->ram[0x0363U] & 0x80U) != 0U) goto check_fire;
    value = mysmb_enemy_set_flame_timer(g);
    if (g->ram[0x06ccU] != 0U) value = (mysmb_u8)(value - 0x10U);
    g->ram[0x0790U] = value;
    g->ram[0x06cbU] = 21U;
graphics:
    mysmb_objects_draw_bowsers_slot(g, slot);
}
