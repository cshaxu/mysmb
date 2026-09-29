#include "game/enemy/background.h"
#include "game/objects.h"
#include "game/world/world.h"
#include <string.h>

static unsigned int land_calls, side_calls, bump_calls;
static mysmb_u8 difference;

void mysmb_world_land_enemy(struct mysmb_game *game, mysmb_u8 slot)
{ (void)game; (void)slot; ++land_calls; }
void mysmb_objects_check_enemy_side(struct mysmb_game *game, mysmb_u8 slot)
{ (void)game; (void)slot; ++side_calls; }
void mysmb_objects_bump_enemy(struct mysmb_game *game, mysmb_u8 slot)
{ (void)game; (void)slot; ++bump_calls; }
mysmb_u8 mysmb_enemy_player_difference(struct mysmb_game *game, mysmb_u8 slot)
{ (void)game; (void)slot; return difference; }
void mysmb_objects_step_enemy_jump_terrain(struct mysmb_game *game, mysmb_u8 slot)
{ (void)game; (void)slot; }
void mysmb_objects_step_hammer_terrain(struct mysmb_game *game, mysmb_u8 slot)
{ (void)game; (void)slot; }
mysmb_u8 mysmb_objects_is_solid_terrain(mysmb_u8 tile)
{ return tile; }
mysmb_u8 mysmb_world_query_enemy_block(struct mysmb_game *game, mysmb_u8 slot,
    mysmb_u8 adder, mysmb_u8 side, struct mysmb_enemy_terrain *terrain)
{ (void)game; (void)slot; (void)adder; (void)side; (void)terrain; return 0U; }
void mysmb_objects_kill_enemy_above_block(struct mysmb_game *game, mysmb_u8 slot)
{ (void)game; (void)slot; }
void mysmb_objects_setup_floatey_from_relative(struct mysmb_game *game,
    mysmb_u8 slot, mysmb_u8 score)
{ (void)game; (void)slot; (void)score; }

static int check(unsigned int land, unsigned int side, unsigned int bump)
{ return land_calls == land && side_calls == side && bump_calls == bump ? 0 : 1; }
static void reset(struct mysmb_game *game)
{
    memset(game, 0, sizeof(*game)); land_calls = side_calls = bump_calls = 0U;
    difference = 0U;
}

int main(void)
{
    static struct mysmb_game game;
    static mysmb_u8 program[0x6100];
    struct mysmb_enemy_terrain terrain;
    memset(&terrain, 0, sizeof(terrain));
    terrain.contact_low_nibble = 8U;

    reset(&game); game.ram[0x001eU] = 0x40U;
    mysmb_objects_enemy_land_from_probe(&game, 0U, &terrain);
    if (check(1U, 0U, 0U) || game.ram[0x001eU] != 0U) return 1;
    reset(&game); game.ram[0x001eU] = 0x80U;
    mysmb_objects_enemy_land_from_probe(&game, 0U, &terrain);
    if (check(0U, 1U, 0U)) return 2;
    reset(&game); game.ram[0x001eU] = 2U; game.ram[0x0016U] = 18U;
    mysmb_objects_enemy_land_from_probe(&game, 0U, &terrain);
    if (check(1U, 0U, 0U) || game.ram[0x0796U] != 0U || game.ram[0x001eU] != 3U) return 3;
    reset(&game); game.ram[0x001eU] = 2U; game.ram[0x0016U] = 1U;
    mysmb_objects_enemy_land_from_probe(&game, 0U, &terrain);
    if (check(1U, 0U, 0U) || game.ram[0x0796U] != 0x10U) return 4;
    reset(&game); game.ram[0x001eU] = 1U; game.ram[0x0016U] = 18U;
    game.ram[9U] = 1U; game.ram[0x0046U] = 1U; difference = 0U;
    mysmb_objects_enemy_land_from_probe(&game, 0U, &terrain);
    if (check(0U, 0U, 1U) || game.ram[0x0058U] != 8U) return 5;
    reset(&game); game.ram[0x001eU] = 5U; game.ram[0x0016U] = 6U;
    mysmb_objects_enemy_land_from_probe(&game, 0U, &terrain);
    if (check(1U, 0U, 0U) || game.ram[0x001eU] != 0U) return 6;
    reset(&game); game.ram[0x001eU] = 3U;
    mysmb_objects_enemy_land_from_probe(&game, 0U, &terrain);
    if (check(0U, 0U, 0U)) return 7;
    reset(&game); terrain.contact_low_nibble = 0x0dU;
    game.ram[0x0016U] = 3U; game.ram[0x001eU] = 0U;
    mysmb_objects_enemy_land_from_probe(&game, 0U, &terrain);
    if (check(0U, 0U, 1U)) return 8;
    reset(&game); game.area_prg = program; game.area_prg_size = sizeof(program);
    program[0xdfb9U - 0x8000U + 6U] = 0x5aU; game.ram[0x001eU] = 6U;
    mysmb_objects_enemy_no_ground(&game, 0U);
    if (check(0U, 1U, 0U) || game.ram[0x001eU] != 0x5aU) return 9;
    return 0;
}
