#include "game/world/world.h"
#include "game/enemy/movement.h"

int main(void)
{
    struct mysmb_game game;

    /* ROM ImposeGravity: Y=$20, speed=$ff, dummy=$b0 and force=$50 preserve
     * both ADC carries: Y remains $20 and its high byte remains $01. */
    mysmb_game_initialize_memory(&game, 0U);
    game.ram[0x0416U + 7U] = 0xb0U;
    game.ram[0x0433U + 7U] = 0x50U;
    game.ram[0x009fU + 7U] = 0xffU;
    game.ram[0x00ceU + 7U] = 0x20U;
    game.ram[0x00b5U + 7U] = 1U;
    mysmb_world_impose_gravity_spr_object(&game, 7U, 0x50U, 3U);
    if (game.ram[0x0416U + 7U] != 0U || game.ram[0x00ceU + 7U] != 0x20U ||
        game.ram[0x00b5U + 7U] != 1U || game.ram[0x009fU + 7U] != 0xffU) return 1;

    /* ROM MoveObjectHorizontally carries X=$fe plus 4 pixels into page. */
    mysmb_game_initialize_memory(&game, 0U);
    game.ram[0x0057U + 7U] = 0x40U;
    game.ram[0x0400U + 7U] = 0U;
    game.ram[0x0086U + 7U] = 0xfeU;
    game.ram[0x006dU + 7U] = 1U;
    mysmb_world_move_spr_object_horizontally(&game, 7U);
    if (game.ram[0x0086U + 7U] != 2U || game.ram[0x006dU + 7U] != 2U) return 2;

    /* $22 + signed-$01 + carried fractional step produces $22 with an ADC
     * carry.  Page delta $ff plus that carry preserves page $03. */
    mysmb_game_initialize_memory(&game, 0U);
    game.ram[0x0057U + 1U] = 0xffU;
    game.ram[0x0400U + 1U] = 0x10U;
    game.ram[0x0086U + 1U] = 0x22U;
    game.ram[0x006dU + 1U] = 3U;
    mysmb_world_move_enemy_horizontally(&game, 0U);
    if (game.ram[0x0400U + 1U] != 0U || game.ram[0x0086U + 1U] != 0x22U ||
        game.ram[0x006dU + 1U] != 3U) return 3;
    /* ROM BlockBufferCollision carries only when the probe ADC crosses the
     * byte boundary.  The block-buffer page is the low page bit plus that
     * carry; no host-width coordinate participates. */
    if (mysmb_world_collision_page(3U, 0xf8U, 0xffU) != 3U ||
        mysmb_world_collision_page(3U, 0xf8U, 0U) != 4U) return 4;

    /* ROM PlayerCollisionCore treats a shared edge as contact and retains
     * horizontal byte-wrap as non-contact; only the source vertical branch has wrap handling. */
    mysmb_game_initialize_memory(&game, 0U);
    game.ram[0x0400U] = 0x10U; game.ram[0x0401U] = 0x20U;
    game.ram[0x0402U] = 0x20U; game.ram[0x0403U] = 0x30U;
    game.ram[0x0410U] = 0x20U; game.ram[0x0411U] = 0x20U;
    game.ram[0x0412U] = 0x30U; game.ram[0x0413U] = 0x30U;
    if (mysmb_world_boxes_collide(&game, 0x0400U, 0x0410U) == 0U) return 5;
    game.ram[0x0410U] = 0x21U;
    if (mysmb_world_boxes_collide(&game, 0x0400U, 0x0410U) != 0U) return 6;
    game.ram[0x0400U] = 0xf8U; game.ram[0x0402U] = 0x08U;
    game.ram[0x0410U] = 0xfcU; game.ram[0x0412U] = 0x04U;
    if (mysmb_world_boxes_collide(&game, 0x0400U, 0x0410U) != 0U) return 7;
    /* SprObjectCollisionCore's SecondBoxVerticalChk treats a first box that
     * wraps from $f8 through $08 as touching a second box at $04..$0c. */
    mysmb_game_initialize_memory(&game, 0U);
    game.ram[0x0400U] = 0x10U; game.ram[0x0402U] = 0x20U;
    game.ram[0x0401U] = 0xf8U; game.ram[0x0403U] = 0x08U;
    game.ram[0x0410U] = 0x10U; game.ram[0x0412U] = 0x20U;
    game.ram[0x0411U] = 0x04U; game.ram[0x0413U] = 0x0cU;
    if (mysmb_world_boxes_collide(&game, 0x0400U, 0x0410U) == 0U) return 8;
    /* ROM BoundingBoxCore uses BoundBoxCtrlData[$07] and byte arithmetic:
     * X=$fc wraps its right edge while Y remains the source-relative byte. */
    mysmb_game_initialize_memory(&game, 0U);
    mysmb_world_set_bounding_box(&game, 0x0420U, 7U, 0xfcU, 0x40U);
    if (game.ram[0x0420U] != 0xfcU || game.ram[0x0421U] != 0x40U ||
        game.ram[0x0422U] != 4U || game.ram[0x0423U] != 0x48U) return 9;
    /* ROM MoveD_EnemyVertically -> ImposeGravitySprObj: signed $ff plus
     * a carried fractional step leaves Y=$20 but ADC still carries to cancel
     * the signed high-byte decrement. */
    mysmb_game_initialize_memory(&game, 0U);
    game.ram[0x0417U] = 0xb0U;
    game.ram[0x0434U] = 0x50U;
    game.ram[0x00a0U] = 0xffU;
    game.ram[0x00cfU] = 0x20U;
    game.ram[0x00b6U] = 1U;
    mysmb_enemy_move_downward(&game, 0U, 0x3dU, 3U);
    if (game.ram[0x0417U] != 0U || game.ram[0x00cfU] != 0x20U ||
        game.ram[0x00b6U] != 1U || game.ram[0x00a0U] != 0xffU) return 10;

    return 0;
}
