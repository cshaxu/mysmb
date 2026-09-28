#include "game/enemy/core.h"
#include "game/enemy/actor_slots.h"
#include "game/enemy/movement.h"
#include "game/objects.h"
#include "game/oam/oam.h"

/* ROM $c905 EnemyMovementSubs: only IDs $00-$14 use this vector.
 * Child algorithms retain their own proof status. */
void mysmb_enemy_movement_dispatch(struct mysmb_game *game, mysmb_u8 slot)
{
    switch (game->ram[0x0016U + slot]) {
    case 0U: case 1U: case 2U: case 3U: case 4U: case 6U: case 18U:
        mysmb_enemy_move_normal(game, slot); break;
    case 5U: mysmb_objects_step_hammer_bros_slot(game, slot); break;
    case 7U: mysmb_objects_step_bloobers_slot(game, slot); break;
    case 8U: mysmb_objects_step_bullet_bills_slot(game, slot); break;
    case 9U: case 19U: break; /* Original NoMoveCode. */
    case 10U: case 11U: mysmb_objects_step_swimming_cheep_cheeps_slot(game, slot); break;
    case 12U: mysmb_objects_step_podoboos_slot(game, slot); break;
    case 13U: mysmb_objects_step_piranha_plants_slot(game, slot); break;
    case 14U: mysmb_objects_step_jumping_paratroopas_slot(game, slot); break;
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
    game->ram[0x03d1U] = mysmb_objects_get_enemy_offscreen_bits(game, slot);
    mysmb_oam_relative_enemy_position(game, slot);
    if (game->ram[0x0016U + slot] == 6U) mysmb_objects_draw_goomba(game, slot);
    else (void)mysmb_objects_draw_normal_enemy_graphics(game, slot);
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
