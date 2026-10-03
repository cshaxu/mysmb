#include "game/enemy/core.h"
#include "game/enemy/actor_slots.h"
#include "game/enemy/movement.h"
#include "game/objects.h"
#include "game/oam/oam.h"

/* ROM $C90A-$C933: data provenance for the original JumpEngine scratch. */
static const mysmb_u16 movement_targets[21] = {
    0xca77U,0xca77U,0xca77U,0xca77U,0xca77U,0xc9d8U,0xca77U,
    0xcb89U,0xcc36U,0xc934U,0xcc4aU,0xcc4aU,0xc9b0U,0xd3b0U,
    0xcaf9U,0xcaffU,0xcb25U,0xcf28U,0xca77U,0xc934U,0xcedfU
};

/* ROM $c905 EnemyMovementSubs: only IDs $00-$14 use this vector.
 * Child algorithms retain their own proof status. */
void mysmb_enemy_movement_dispatch(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 id;
    mysmb_u16 target;
    id = game->ram[0x0016U + slot];
    target = movement_targets[id];
    game->ram[4U] = 9U;
    game->ram[5U] = 0xc9U;
    game->ram[6U] = (mysmb_u8)target;
    game->ram[7U] = (mysmb_u8)(target >> 8U);
    switch (id) {
    case 0U: case 1U: case 2U: case 3U: case 4U: case 6U: case 18U:
        mysmb_enemy_move_normal(game, slot); break;
    case 5U: mysmb_objects_step_hammer_bros_slot(game, slot); break;
    case 7U: mysmb_objects_step_bloobers_slot(game, slot); break;
    case 8U: mysmb_objects_step_bullet_bills_slot(game, slot); break;
    case 9U: case 19U: break; /* Original NoMoveCode. */
    case 10U: case 11U: mysmb_objects_step_swimming_cheep_cheeps_slot(game, slot); break;
    case 12U: mysmb_objects_step_podoboos_slot(game, slot); break;
    case 13U: mysmb_objects_step_piranha_plants_slot(game, slot); break;
    case 14U: mysmb_enemy_move_jumping(game, slot); break;
    case 15U: mysmb_objects_step_red_paratroopas_slot(game, slot); break;
    case 16U: mysmb_objects_step_flying_green_paratroopas_slot(game, slot); break;
    case 17U: mysmb_enemy_step_lakitus_slot(game, slot); break;
    case 20U: mysmb_objects_step_flying_cheep_cheeps_slot(game, slot); break;
    }
}

/* ROM $c8e0 RunNormalEnemies through SkipMove. No graphics-handled result
 * or collision result may skip the remaining source caller sequence. */
static void run_normal(struct mysmb_game *game, mysmb_u8 slot,
                        mysmb_u8 preserve_collision_boxes)
{
    game->ram[0x03c5U + slot] = 0U;
    mysmb_oam_get_enemy_offscreen_bits(game, slot);
    mysmb_oam_relative_enemy_position(game, slot);
    (void)mysmb_objects_draw_normal_enemy_graphics(game, slot);
    mysmb_objects_update_enemy_bounding_box(game, slot);
    mysmb_objects_enemy_background_current(game, slot);
    mysmb_objects_step_enemy_collisions_current(game, slot);
    mysmb_objects_player_enemy_current(game, slot, preserve_collision_boxes);
    if (game->ram[0x0747U] == 0U) mysmb_enemy_movement_dispatch(game, slot);
    mysmb_objects_check_enemy_offscreen_bounds(game, slot);
}

void mysmb_objects_step_normal_enemy(struct mysmb_game *game, mysmb_u8 slot)
{
    run_normal(game, slot, 1U);
}

/* Retained aggregate test/legacy interface supplies its own player boxes.
 * GameEngine calls only the single-slot entry above. */
void mysmb_objects_step_normal_enemies(struct mysmb_game *game)
{
    mysmb_u8 slot;
    for (slot = 0U; slot < 5U; ++slot) {
        if (game->ram[0x000fU + slot] != 0U) run_normal(game, slot, 0U);
    }
}
