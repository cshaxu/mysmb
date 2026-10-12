#include "terrain_entry.h"
#include "core/dispatcher.h"
#include <stdio.h>
#include "core/objects.h"
#include "core/world/world.h"
#include "core/area.h"
#include "core/player.h"
#include "core/oam/oam.h"
#include "smb1_local_rom.h"

static void mysmb_collision_initialize_memory(struct mysmb_game *game,
                                              mysmb_u8 fill)
{
    mysmb_game_initialize_memory(game, fill);
    mysmb_game_bind_area_source(game, mysmb_local_prg, MYSMB_LOCAL_PRG_SIZE);
}

#define mysmb_game_initialize_memory mysmb_collision_initialize_memory

static void mysmb_clear_block_buffers(struct mysmb_game *game)
{
    mysmb_u16 index;

    for (index = 0U; index < 0x01a0U; ++index) {
        game->ram[(mysmb_u16)(0x0500U + index)] = 0U;
    }
}

static void mysmb_setup_active_mushroom(struct mysmb_game *game,
                                        mysmb_u8 state, mysmb_u8 x, mysmb_u8 y,
                                        mysmb_u8 direction)
{
    mysmb_game_initialize_memory(game, 0xfeU);
    mysmb_clear_block_buffers(game);
    /* The complete actor now reaches ID-dependent terrain and bounds.
     * Supply the same active slot and visible screen as the ROM caller. */
    game->ram[0x0014U] = 1U;
    game->ram[0x001bU] = 0x2eU;
    game->ram[0x071aU] = 1U;
    game->ram[0x071bU] = 1U;
    game->ram[0x071cU] = 0U;
    game->ram[0x071dU] = 0xffU;
    game->ram[0x001eU + 5U] = state;
    game->ram[0x0039U] = 0U;
    game->ram[0x0046U + 5U] = 0U;
    game->ram[0x0058U + 5U] = 0U;
    game->ram[0x0401U + 5U] = 0U;
    game->ram[0x00a0U + 5U] = 0U;
    game->ram[0x00b6U + 5U] = 1U;
    game->ram[0x0417U + 5U] = 0U;
    game->ram[0x0434U + 5U] = 0U;
    game->ram[0x006eU + 5U] = 1U;
    game->ram[0x0087U + 5U] = x;
    game->ram[0x00cfU + 5U] = y;
    game->ram[0x0046U + 5U] = direction;
    game->ram[0x0747U] = 0U;
    game->ram[0x0009U] = 0U;
}

int main(void)
{
    struct mysmb_game game;
    mysmb_u8 step;
    /* PlayerBGCollision sets collision bits before its bottom-screen guard.
     * At Y=$cf it must not run the head/feet/side probes. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    mysmb_clear_block_buffers(&game);
    game.ram[0x000eU] = 4U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0xcfU;
    game.ram[0x001dU] = 0U;
    game.ram[0x0490U] = 0U;
    game.ram[0x0754U] = 1U;
    mysmb_player_step(&game, 0U);
    if (game.ram[0x0490U] != 0xffU) return 45;
    /* ROM small-Mario feet use probe entries $0f/$10: X+3 and X+12,
     * with Y+32 for both.  At the 1-1 landing reproduced from the ROM trace,
     * the right probe lands on the brick while the left probe remains empty. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    mysmb_clear_block_buffers(&game);
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x70U;
    game.ram[0x009fU] = 2U;
    game.ram[0x006dU] = 1U;
    game.ram[0x0086U] = 0x34U;
    game.ram[0x001dU] = 1U;
    game.ram[0x0754U] = 1U;
    game.ram[0x0644U] = 0x51U;
    mysmb_test_terrain_entry(&game);
    if (mysmb_player_check_feet(&game) == 0U || game.ram[0x001dU] != 0U ||
        game.ram[0x00ceU] != 0x70U || game.ram[0x009fU] != 0U) return 10;
    /* ChkInvisibleMTiles handles a hidden coin or 1-up sampled by either
     * foot by branching to DoPlayerSideCheck before LandPlyr. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    mysmb_clear_block_buffers(&game);
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x70U;
    game.ram[0x009fU] = 2U;
    game.ram[0x006dU] = 1U;
    game.ram[0x0086U] = 0x34U;
    game.ram[0x001dU] = 1U;
    game.ram[0x0754U] = 1U;
    game.ram[0x0644U] = 0x5fU;
    mysmb_test_terrain_entry(&game);
    if (mysmb_player_check_feet(&game) != 0U || game.ram[0x001dU] != 1U ||
        game.ram[0x00ceU] != 0x70U || game.ram[0x009fU] != 2U) return 29;
    game.ram[0x0644U] = 0x60U;
    mysmb_test_terrain_entry(&game);
    if (mysmb_player_check_feet(&game) != 0U || game.ram[0x001dU] != 1U ||
        game.ram[0x00ceU] != 0x70U || game.ram[0x009fU] != 2U) return 30;
    /* CheckForCoinMTiles queues the coin-grab sound before HandleCoinMetatile
     * removes the sampled foot coin and updates its score/tally state. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    mysmb_clear_block_buffers(&game);
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x70U;
    game.ram[0x009fU] = 2U;
    game.ram[0x006dU] = 1U;
    game.ram[0x0086U] = 0x34U;
    game.ram[0x001dU] = 1U;
    game.ram[0x0754U] = 1U;
    game.ram[0x0644U] = 0xc2U;
    game.ram[0x00feU] = 0U;
    mysmb_test_terrain_entry(&game);
    if (mysmb_player_check_feet(&game) != 2U || game.ram[0x0644U] != 0U ||
        game.ram[0x00feU] != 1U) return 37;
    /* Original DC64 route with only left C5 keeps that tile: HandleAxeMetatile
     * consumes the last (right) query coordinates, producing VRAM column 48. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    mysmb_clear_block_buffers(&game);
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x70U;
    game.ram[0x009fU] = 2U;
    game.ram[0x006dU] = 1U;
    game.ram[0x0086U] = 0x34U;
    game.ram[0x001dU] = 1U;
    game.ram[0x0754U] = 1U;
    game.ram[0x074eU] = 1U;
    game.ram[0x0643U] = 0xc5U;
    game.ram[0x034bU] = 0U;
    mysmb_test_terrain_entry(&game);
    if (mysmb_player_check_feet(&game) != 2U || game.ram[0x0643U] != 0xc5U ||
        game.ram[0x0644U] != 0U ||
        game.ram[0x0772U] != 0U || game.ram[0x0770U] != 2U ||
        game.ram[0x0057U] != 0x18U || game.ram[0x0773U] != 6U ||
        game.ram[0x0341U] != 0x26U || game.ram[0x0342U] != 0x48U ||
        game.ram[0x0343U] != 2U || game.ram[0x0344U] != 0x24U ||
        game.ram[0x0348U] != 2U || game.ram[0x0349U] != 0x24U) return 38;
    /* ChkForLandJumpSpring initializes the shared spring handoff before
     * LandPlyr.  The object handler later consumes these exact RAM bytes. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    mysmb_clear_block_buffers(&game);
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x70U;
    game.ram[0x009fU] = 2U;
    game.ram[0x006dU] = 1U;
    game.ram[0x0086U] = 0x34U;
    game.ram[0x001dU] = 1U;
    game.ram[0x0754U] = 1U;
    game.ram[0x0644U] = 0x67U;
    game.ram[0x0709U] = 0xaaU;
    game.ram[0x06dbU] = 0xaaU;
    game.ram[0x0786U] = 0xaaU;
    game.ram[0x070eU] = 0U;
    mysmb_test_terrain_entry(&game);
    if (mysmb_player_check_feet(&game) == 0U || game.ram[0x0709U] != 0x70U ||
        game.ram[0x06dbU] != 0xf9U || game.ram[0x0786U] != 3U ||
        game.ram[0x070eU] != 1U || game.ram[0x001dU] != 0U ||
        game.ram[0x00ceU] != 0x70U || game.ram[0x009fU] != 0U) return 34;
    /* A live JumpspringAnimCtrl takes InitSteP: state returns to normal,
     * but position, vertical motion, and animation-owned bytes stay intact. */
    game.ram[0x00ceU] = 0x73U;
    game.ram[0x009fU] = 3U;
    game.ram[0x0433U] = 0x55U;
    game.ram[0x001dU] = 2U;
    game.ram[0x0709U] = 0x88U;
    game.ram[0x06dbU] = 0xf9U;
    game.ram[0x0786U] = 2U;
    game.ram[0x070eU] = 2U;
    mysmb_test_terrain_entry(&game);
    if (mysmb_player_check_feet(&game) == 0U || game.ram[0x001dU] != 0U ||
        game.ram[0x00ceU] != 0x73U || game.ram[0x009fU] != 3U ||
        game.ram[0x0433U] != 0x55U || game.ram[0x0709U] != 0x88U ||
        game.ram[0x06dbU] != 0xf9U || game.ram[0x0786U] != 2U ||
        game.ram[0x070eU] != 2U) return 35;
    /* At contact nibble $05, ChkFootMTile passes Player_MovingDir to
     * ImpedePlayerMove instead of taking LandPlyr. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    mysmb_clear_block_buffers(&game);
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x75U;
    game.ram[0x009fU] = 2U;
    game.ram[0x006dU] = 1U;
    game.ram[0x0086U] = 0x34U;
    game.ram[0x0057U] = 0x10U;
    game.ram[0x0045U] = 1U;
    game.ram[0x001dU] = 2U;
    game.ram[0x0754U] = 1U;
    game.ram[0x0490U] = 0xffU;
    game.ram[0x0644U] = 0x51U;
    mysmb_test_terrain_entry(&game);
    if (mysmb_player_check_feet(&game) != MYSMB_PLAYER_FEET_TERMINAL_IMPEDE ||
        game.ram[0x0086U] != 0x33U ||
        game.ram[0x0057U] != 0U || game.ram[0x0785U] != 0x10U ||
        game.ram[0x0490U] != 0xfeU || game.ram[0x00ceU] != 0x75U ||
        game.ram[0x009fU] != 2U || game.ram[0x001dU] != 2U) return 36;
    /* ROM SideCheckLoop first reaches the opposite-side probe ($00=$02).  With rightward speed, ImpedePlayerMove clears d1 but must not push Mario left. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    mysmb_clear_block_buffers(&game);
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x30U;
    game.ram[0x006dU] = 0U;
    game.ram[0x0086U] = 0x20U;
    game.ram[0x001dU] = 2U;
    game.ram[0x0754U] = 1U;
    game.ram[0x0045U] = MYSMB_BUTTON_RIGHT;
    game.ram[0x0057U] = 0x10U;
    game.ram[0x0705U] = 0x80U;
    game.ram[0x000eU] = 8U;
    game.ram[0x0522U] = 0x61U;
    mysmb_test_terrain_entry(&game);
    if (mysmb_player_check_sides(&game) == 0U) return 11;
    if (game.ram[0x0086U] != 0x20U || game.ram[0x0057U] != 0x10U ||
        game.ram[0x0490U] != 0xfdU || game.ram[0x0705U] != 0x80U) return 12;

    /* ChkJumpspringMetatiles reaches StopPlayerMove while the spring is
     * idle, but exits without a wall-stop once its animation owns the tile. */
    game.ram[0x070eU] = 0U;
    game.ram[0x0490U] = 0U;
    game.ram[0x0522U] = 0x67U;
    mysmb_test_terrain_entry(&game);
    if (mysmb_player_check_sides(&game) == 0U ||
        game.ram[0x0490U] != 0xfdU || game.ram[0x0057U] != 0x10U) return 32;
    game.ram[0x070eU] = 1U;
    game.ram[0x0490U] = 0U;
    mysmb_test_terrain_entry(&game);
    if (mysmb_player_check_sides(&game) == 0U ||
        game.ram[0x0490U] != 0xffU || game.ram[0x0057U] != 0x10U) return 33;

    /* PipeDwnS queues $10 only on the first clear Player_SprAttrib, then
     * sets its pipe bit, selects the page-zero timer, and enters routine 2. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    mysmb_clear_block_buffers(&game);
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x30U;
    game.ram[0x006dU] = 0U;
    game.ram[0x0086U] = 0x23U;
    game.ram[0x001dU] = 0U;
    game.ram[0x0754U] = 1U;
    game.ram[0x0033U] = MYSMB_BUTTON_RIGHT;
    game.ram[0x03c4U] = 0U;
    game.ram[0x071aU] = 0U;
    game.ram[0x06deU] = 0U;
    game.ram[0x000eU] = 8U;
    game.ram[0x00ffU] = 0U;
    game.ram[0x0522U] = 0x6cU;
    mysmb_test_terrain_entry(&game);
    if (mysmb_player_check_sides(&game) == 0U ||
        game.ram[0x03c4U] != 0x20U || game.ram[0x00ffU] != 0x10U ||
        game.ram[0x06deU] != 0xa0U || game.ram[0x000eU] != 2U) return 31;

    /* PlayerHeadCollision still bounces an ordinary brick for small Mario.
     * The brick is not in BlockBumpedChk, but the ROM sets Y speed to zero
     * through BumpBlock and retains the metatile for the block object. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    mysmb_clear_block_buffers(&game);
    game.ram[0x0754U] = 1U;
    game.ram[0x074eU] = 1U;
    game.ram[0x006dU] = 1U;
    game.ram[0x0086U] = 0x20U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x34U;
    game.ram[0x009fU] = 0xf0U;
    /* Small Mario selects BlockBufferAdderData[$02]=$0e, whose head probe
     * is X+8,Y+18.  At (X,Y)=(20,34), this is block-buffer $05f2. */
    game.ram[0x05f2U] = 0x51U;
    mysmb_test_terrain_entry(&game);
    if (mysmb_player_check_head(&game) == 0U ||
        game.ram[0x0026U] != 0x11U || game.ram[0x03e8U] != 0x51U ||
        game.ram[0x05f2U] != 0x23U || game.ram[0x009fU] != 0U ||
        game.ram[0x0784U] != 0x10U) return 13;

    /* A head-touched scene coin is AwardTouchedCoin: its terminal result
     * prevents PlayerBGCollision from continuing to feet or side probes. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    mysmb_clear_block_buffers(&game);
    game.ram[0x0754U] = 1U;
    game.ram[0x006dU] = 1U;
    game.ram[0x0086U] = 0x20U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x34U;
    game.ram[0x009fU] = 0xf0U;
    game.ram[0x05f2U] = 0xc2U;
    mysmb_test_terrain_entry(&game);
    if (mysmb_player_check_head(&game) != 2U || game.ram[0x05f2U] != 0U ||
        game.ram[0x00feU] != 1U) return 46;
    /* HeadChk branches through NYSpd in water before PlayerHeadCollision:
     * the non-solid brick remains in the block buffer and no block starts. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    mysmb_clear_block_buffers(&game);
    game.ram[0x0754U] = 1U;
    game.ram[0x074eU] = 0U;
    game.ram[0x006dU] = 1U;
    game.ram[0x0086U] = 0x20U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x34U;
    game.ram[0x009fU] = 0xf0U;
    game.ram[0x0026U] = 0U;
    game.ram[0x0784U] = 0U;
    game.ram[0x05f2U] = 0x51U;
    mysmb_test_terrain_entry(&game);
    if (mysmb_player_check_head(&game) == 0U || game.ram[0x009fU] != 1U ||
        game.ram[0x0026U] != 0U || game.ram[0x05f2U] != 0x51U ||
        game.ram[0x0784U] != 0U) return 31;

    /* A live BlockBounceTimer takes HeadChk directly to NYSpd, so a
     * non-solid block stays untouched while upward motion is cancelled. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    mysmb_clear_block_buffers(&game);
    game.ram[0x0754U] = 1U;
    game.ram[0x074eU] = 1U;
    game.ram[0x006dU] = 1U;
    game.ram[0x0086U] = 0x20U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x34U;
    game.ram[0x009fU] = 0xf0U;
    game.ram[0x0784U] = 1U;
    game.ram[0x0026U] = 0U;
    game.ram[0x05f2U] = 0x51U;
    mysmb_test_terrain_entry(&game);
    if (mysmb_player_check_head(&game) == 0U || game.ram[0x009fU] != 1U ||
        game.ram[0x0026U] != 0U || game.ram[0x05f2U] != 0x51U) return 35;

    /* SolidOrClimb queues Sfx_Bump for solid blocks, except the $26
     * climbing metatile handled by the source branch. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    mysmb_clear_block_buffers(&game);
    game.ram[0x0754U] = 1U;
    game.ram[0x074eU] = 1U;
    game.ram[0x006dU] = 1U;
    game.ram[0x0086U] = 0x20U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x34U;
    game.ram[0x009fU] = 0xf0U;
    game.ram[0x00ffU] = 0U;
    game.ram[0x05f2U] = 0x61U;
    mysmb_test_terrain_entry(&game);
    if (mysmb_player_check_head(&game) == 0U || game.ram[0x009fU] != 1U ||
        game.ram[0x00ffU] != 2U) return 34;

    /* InitBlock_XY_Pos uses the carry from Player_X + 8 before masking to
     * a metatile boundary.  At X=$02 the resulting X is zero but the page
     * must remain unchanged. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    mysmb_clear_block_buffers(&game);
    game.ram[0x0754U] = 1U;
    game.ram[0x006dU] = 1U;
    game.ram[0x0086U] = 2U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x34U;
    game.ram[0x0520U] = 0xc4U;
    if (mysmb_objects_start_head_bump(&game, 0xc4U, 0U, 0x20U) == 0U ||
        game.ram[0x008fU] != 0U || game.ram[0x0076U] != 1U ||
        game.ram[0x03eaU] != 1U) return 16;

    /* Hidden coin blocks are $5f in the collision buffer.  They are absent
     * from scenery only; PlayerHeadCollision must still enter BumpBlock. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    mysmb_clear_block_buffers(&game);
    game.ram[0x0754U] = 1U;
    game.ram[0x074eU] = 1U;
    game.ram[0x006dU] = 1U;
    game.ram[0x0086U] = 0x20U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x34U;
    game.ram[0x009fU] = 0xf0U;
    game.ram[0x05f2U] = 0x5fU;
    mysmb_test_terrain_entry(&game);
    if (mysmb_player_check_head(&game) == 0U ||
        game.ram[0x0026U] != 0x11U || game.ram[0x03e8U] != 0xc4U ||
        game.ram[0x05f2U] != 0x23U || game.ram[0x009fU] != 0U ||
        game.ram[0x0784U] != 0x10U) return 14;
    for (step = 0U; step < 24U; ++step) {
        mysmb_area_apply_block_replacements(&game);
        /* NMI has consumed the previous VRAM command before the next frame. */
        game.ram[0x0301U] = 0U;
        mysmb_game_engine_blocks(&game);
    }
    if (game.ram[0x05f2U] != 0xc4U) return 15;
    /* PowerUpObjHandler calls RunPUSubs from state 6.  GameCore invokes this
     * collision routine after the handler, so state 6 must not be rejected
     * simply because d7 has not yet been set. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    mysmb_clear_block_buffers(&game);
    game.ram[0x001bU] = 0x2eU;
    game.ram[0x0023U] = 6U;
    game.ram[0x0014U] = 1U;
    game.ram[0x0073U] = 1U;
    game.ram[0x008cU] = 0x30U;
    game.ram[0x00d4U] = 0x50U;
    game.ram[0x049fU] = 3U;
    /* The first World 1-1 fire flower is type 1 while Mario is big. */
    game.ram[0x0039U] = 1U;
    game.ram[0x0756U] = 1U;
    game.ram[0x006dU] = 1U;
    game.ram[0x0086U] = 0x30U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x50U;
    game.ram[0x0499U] = 1U;
    game.ram[0x03d0U] = 0U;
    game.ram[0x071aU] = 1U;
    game.ram[0x071cU] = 0U;
    game.ram[0x000eU] = 8U;
    game.ram[0x0009U] = 0U;
    /* PlayerEnemyCollision consumes boxes prepared by PlayerGfxHandler and
     * RunPUSubs.  This isolated fixture supplies that source-owned RAM. */
    game.ram[0x03d8U + 5U] = 0U;
    mysmb_world_set_bounding_box(&game, 0x04acU, game.ram[0x0499U],
                                   0x30U, game.ram[0x00ceU]);
    mysmb_world_set_bounding_box(&game, 0x04b0U + 5U * 4U,
                                   game.ram[0x049fU], 0x30U,
                                   game.ram[0x00d4U]);
    mysmb_objects_check_power_up_collision(&game);
    if (game.ram[0x001bU] != 0U || game.ram[0x0023U] != 0U ||
        game.ram[0x0014U] != 0U || game.ram[0x0756U] != 2U ||
        game.ram[0x000eU] != 12U) return 2;
    /* PlayerCollisionCore preserves an overlap that crosses the native
     * byte boundary.  A conventional host AABB test rejects this flower. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x001bU] = 0x2eU;
    game.ram[0x0023U] = 6U;
    game.ram[0x0014U] = 1U;
    game.ram[0x0039U] = 1U;
    game.ram[0x0756U] = 1U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x50U;
    game.ram[0x000eU] = 8U;
    game.ram[0x0009U] = 0U;
    /* CheckPlayerVertical rejects only $f0-$ff.  A partial top-row mask
     * such as $10 remains a valid player/power-up collision frame. */
    game.ram[0x03d0U] = 0x10U;
    game.ram[0x03d8U + 5U] = 0U;
    game.ram[0x04acU] = 0xfeU; game.ram[0x04aeU] = 0x0aU;
    game.ram[0x04adU] = 0x50U; game.ram[0x04afU] = 0x60U;
    game.ram[0x04c4U] = 0x02U; game.ram[0x04c6U] = 0x0eU;
    game.ram[0x04c5U] = 0x50U; game.ram[0x04c7U] = 0x60U;
    mysmb_objects_check_power_up_collision(&game);
    if (game.ram[0x001bU] != 0U || game.ram[0x0756U] != 2U ||
        game.ram[0x000eU] != 12U) return 20;

    /* ChkUnderEnemy uses BlockBuffer_Y_Adder[$15]=$18, selecting row $20
     * at Y=$29.  The $15 passed by the ROM is an adder-table index. */
    mysmb_setup_active_mushroom(&game, 0xc0U, 0U, 0x29U, 1U);
    game.ram[0x05f0U] = 0x61U;
    mysmb_objects_step_power_up(&game);
    if (game.ram[0x00cfU + 5U] != 0x28U ||
        game.ram[0x001eU + 5U] != 0x80U) return 3;

    /* LandEnemyProperly sends D-F through the falling-state transition. */
    mysmb_setup_active_mushroom(&game, 0x80U, 0U, 0x2dU, 1U);
    game.ram[0x05f0U] = 0x61U;
    mysmb_objects_step_power_up(&game);
    if (game.ram[0x00cfU + 5U] != 0x2dU ||
        game.ram[0x001eU + 5U] != 0xc0U) return 4;

    /* On a flat floor, ChkUnderEnemy samples row $20 while
     * DoEnemySideCheck samples row $10.  The mushroom must remain grounded
     * and advance horizontally instead of treating its floor as a wall. */
    mysmb_setup_active_mushroom(&game, 0x80U, 0U, 0x28U, 1U);
    game.ram[0x0058U + 5U] = 0x10U;
    game.ram[0x05f0U] = 0x61U;
    for (step = 0U; step < 4U; ++step) {
        mysmb_objects_step_power_up(&game);
    }
    if (game.ram[0x0087U + 5U] != 4U ||
        game.ram[0x00cfU + 5U] != 0x28U ||
        game.ram[0x001eU + 5U] != 0x80U ||
        game.ram[0x0046U + 5U] != 1U) return 7;


    /* A mushroom that has entered d6 falling state must use the same
     * LandEnemyProperly two-pass landing as the ROM, then resume horizontal
     * movement.  The floor is block-buffer page two, row $b0: Y=$90 advances through the d-f
     * transition and settles at Y=$b8. */
    mysmb_setup_active_mushroom(&game, 0xc0U, 0U, 0x90U, 1U);
    game.ram[0x0058U + 5U] = 0x10U;
    for (step = 0U; step < 16U; ++step) {
        game.ram[0x0680U + step] = 0x54U;
    }
    for (step = 0U; step < 64U; ++step) {
        mysmb_objects_step_power_up(&game);
    }
    if (game.ram[0x00cfU + 5U] != 0xb8U ||
        game.ram[0x001eU + 5U] != 0x80U ||
        game.ram[0x0087U + 5U] == 0U ||
        game.ram[0x0046U + 5U] != 1U) return 14;
    /* EnemyLanding -> InitVStf clears Y speed and force but deliberately
     * retains Enemy_YMF_Dummy.  The retained fractional phase controls the
     * next fall of a mushroom after it walks off a ledge. */
    mysmb_setup_active_mushroom(&game, 0xc0U, 0U, 0x28U, 1U);
    game.ram[0x00a0U + 5U] = 0U;
    game.ram[0x0417U + 5U] = 0x6eU;
    game.ram[0x0434U + 5U] = 0U;
    game.ram[0x05f0U] = 0x61U;
    mysmb_objects_step_power_up(&game);
    if (game.ram[0x00cfU + 5U] != 0x28U ||
        game.ram[0x001eU + 5U] != 0x80U ||
        game.ram[0x0417U + 5U] != 0x6eU ||
        game.ram[0x00a0U + 5U] != 0U ||
        game.ram[0x0434U + 5U] != 0U) return 21;
    /* Star power-ups use MoveJumpingEnemy -> EnemyJump.  Once downward
     * speed reaches the source threshold, the bottom probe lands it at Y|8,
     * clears force, and immediately assigns the next upward speed $fd. */
    mysmb_setup_active_mushroom(&game, 0x80U, 0U, 0x29U, 1U);
    game.ram[0x0039U] = 2U;
    game.ram[0x00a0U + 5U] = 1U;
    game.ram[0x05f0U] = 0x61U;
    mysmb_objects_step_power_up(&game);
    if (game.ram[0x00cfU + 5U] != 0x28U ||
        game.ram[0x00a0U + 5U] != 0xfdU ||
        game.ram[0x0434U + 5U] != 0U) return 46;

    /* EnemyJump always reaches DoEnemySideCheck, but that routine returns
     * inside the status bar before any side block can reverse the star. */
    mysmb_setup_active_mushroom(&game, 0x80U, 0U, 0x10U, 1U);
    game.ram[0x0039U] = 2U;
    game.ram[0x0058U + 5U] = 0x10U;
    game.ram[0x05f1U] = 0x61U;
    mysmb_objects_step_power_up(&game);
    if (game.ram[0x0046U + 5U] != 1U ||
        game.ram[0x0058U + 5U] != 0x10U) return 47;
    /* DoEnemySideCheck uses left (X,Y+14), not X+4. */
    mysmb_setup_active_mushroom(&game, 0x80U, 0x2cU, 0x30U, 2U);
    /* RXSpd negates the existing 4.4 speed; this active left-moving
     * mushroom carries $f0 and must become $10. */
    game.ram[0x0058U + 5U] = 0xf0U;
    game.ram[0x05f2U] = 0xc0U;
    mysmb_objects_step_power_up(&game);
    if (game.ram[0x0046U + 5U] != 1U ||
        game.ram[0x0058U + 5U] != 0x10U) return 5;

    /* DoEnemySideCheck uses right (X+16,Y+14), not X+20. */
    mysmb_setup_active_mushroom(&game, 0x80U, 0x2dU, 0x30U, 1U);
    /* The equivalent right-moving state has $10 and must become $f0. */
    game.ram[0x0058U + 5U] = 0x10U;
    game.ram[0x05f3U] = 0xc0U;
    mysmb_objects_step_power_up(&game);
    if (game.ram[0x0046U + 5U] != 2U ||
        game.ram[0x0058U + 5U] != 0xf0U) return 6;
    /* First World 1-1 fire flower: exercise the real SetupPowerUp reveal
     * state before PlayerEnemyCollision, rather than injecting a finished
     * enemy box.  Big Mario strikes the normal mushroom/flower block, which
     * SetupPowerUp changes to PowerUpType=$01, then collects it after state 6. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    mysmb_clear_block_buffers(&game);
    game.ram[0x000eU] = 8U;
    game.ram[0x071aU] = 1U;
    game.ram[0x071bU] = 1U;
    game.ram[0x071cU] = 0U;
    game.ram[0x071dU] = 0xffU;
    game.ram[0x0754U] = 0U;
    game.ram[0x0756U] = 1U;
    game.ram[0x006dU] = 1U;
    game.ram[0x0086U] = 0x30U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x30U;
    game.ram[0x0499U] = 0U;
    game.ram[0x04acU] = 0x32U;
    game.ram[0x04adU] = 0x38U;
    game.ram[0x04aeU] = 0x3eU;
    game.ram[0x04afU] = 0x50U;
    game.ram[0x0076U] = 1U;
    game.ram[0x008fU] = 0x30U;
    game.ram[0x00d7U] = 0x40U;
    game.ram[0x0039U] = 0U;
    mysmb_objects_start_power_up(&game, 0U);
    for (step = 0U; step < 16U; ++step) {
        game.ram[0x0009U] = step;
        mysmb_objects_step_power_up(&game);
    }
    if (game.ram[0x0039U] != 1U || game.ram[0x001bU] != 0x2eU ||
        game.ram[0x0023U] != 5U) return 16;
    game.ram[0x0009U] = 16U;
    /* The first state-six frame runs the complete original collision tail. */
    mysmb_objects_step_power_up(&game);
    if (game.ram[0x001bU] != 0U || game.ram[0x0014U] != 0U ||
        game.ram[0x0756U] != 2U || game.ram[0x000eU] != 12U) return 17;
    /* OffscreenBoundsCheck clears the full enemy-object record when an
     * ordinary enemy passes the ROM's bytewise left boundary. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x071aU] = 1U;
    game.ram[0x071bU] = 1U;
    game.ram[0x071cU] = 0U;
    game.ram[0x071dU] = 0xffU;
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 6U;
    game.ram[0x001eU] = 0x33U;
    game.ram[0x006eU] = 0U;
    game.ram[0x0087U] = 0xb6U;
    game.ram[0x0110U] = 1U;
    game.ram[0x0796U] = 2U;
    game.ram[0x0125U] = 3U;
    game.ram[0x03c5U] = 4U;
    game.ram[0x078aU] = 5U;
    game.ram[0x078eU] = 0x55U;
    mysmb_objects_check_enemy_offscreen_bounds(&game, 0U);
    if (game.ram[0x000fU] != 0U || game.ram[0x0016U] != 0U ||
        game.ram[0x001eU] != 0U || game.ram[0x0110U] != 0U ||
        game.ram[0x0796U] != 0U || game.ram[0x0125U] != 0U ||
        game.ram[0x03c5U] != 0U || game.ram[0x078aU] != 0U ||
        game.ram[0x078eU] != 0x55U) return 18;

    /* Right-side piranha plants are a source exemption and must retain the
     * object record even when beyond ScreenRight + $48. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x071aU] = 1U;
    game.ram[0x071bU] = 1U;
    game.ram[0x071cU] = 0U;
    game.ram[0x071dU] = 0xffU;
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 13U;
    game.ram[0x006eU] = 2U;
    game.ram[0x0087U] = 0x50U;
    mysmb_objects_check_enemy_offscreen_bounds(&game, 0U);
    if (game.ram[0x000fU] == 0U || game.ram[0x0016U] != 13U) return 19;
    /* RelativeEnemyPosition uses the fixed enemy scratch pair after
     * VariableObjOfsRelPos; its source slot changes inputs, not outputs. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x071cU] = 0x20U;
    game.ram[0x0087U + 3U] = 0x44U;
    game.ram[0x00cfU + 3U] = 0x70U;
    mysmb_oam_relative_enemy_position(&game, 3U);
    if (game.ram[0x03aeU] != 0x24U || game.ram[0x03b9U] != 0x70U) return 25;
    /* FireballEnemyCollision executes only on even frames, scans five
     * ordinary slots in descending order, and records the first source hit.
     * It must not use a host world-coordinate collision substitute. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x0024U] = 1U;
    game.ram[0x0009U] = 0U;
    game.ram[0x04c8U] = 0x40U;
    game.ram[0x04c9U] = 0x50U;
    game.ram[0x04caU] = 0x4cU;
    game.ram[0x04cbU] = 0x60U;
    game.ram[0x000fU + 4U] = 1U;
    game.ram[0x0016U + 4U] = 6U;
    game.ram[0x001eU + 4U] = 0U;
    game.ram[0x03d8U + 4U] = 0U;
    game.ram[0x04c0U] = 0x40U;
    game.ram[0x04c1U] = 0x50U;
    game.ram[0x04c2U] = 0x4cU;
    game.ram[0x04c3U] = 0x60U;
    /* The ROM keeps scanning after slot four hits. */
    game.ram[0x000fU + 3U] = 1U;
    game.ram[0x0016U + 3U] = 6U;
    game.ram[0x001eU + 3U] = 0U;
    game.ram[0x03d8U + 3U] = 0U;
    game.ram[0x04bcU] = 0x40U;
    game.ram[0x04bdU] = 0x50U;
    game.ram[0x04beU] = 0x4cU;
    game.ram[0x04bfU] = 0x60U;
    mysmb_world_fireball_enemy_collision(&game, 0U);
    if (game.ram[0x0024U] != 0x80U || game.ram[0x001eU + 4U] != 0x22U ||
        game.ram[0x001eU + 3U] != 0x22U) return 22;
    game.ram[0x0024U] = 1U;
    game.ram[0x0009U] = 1U;
    mysmb_world_fireball_enemy_collision(&game, 0U);
    if (game.ram[0x0024U] != 1U || game.ram[0x001eU + 4U] != 0x22U) return 23;
    game.ram[0x0009U] = 0U;
    game.ram[0x0016U + 4U] = 0U;
    game.ram[0x001eU + 4U] = 2U;
    game.ram[0x000fU + 3U] = 1U;
    game.ram[0x0016U + 3U] = 6U;
    game.ram[0x001eU + 3U] = 0U;
    game.ram[0x03d8U + 3U] = 0U;
    game.ram[0x04bcU] = 0x40U;
    game.ram[0x04bdU] = 0x50U;
    game.ram[0x04beU] = 0x4cU;
    game.ram[0x04bfU] = 0x60U;
    mysmb_world_fireball_enemy_collision(&game, 0U);
    if (game.ram[0x0024U] != 0x80U || game.ram[0x001eU + 3U] != 0x22U) return 24;
    /* HandleEnemyFBallCol calls RelativeEnemyPosition before the normal
     * ChkToStunEnemies branch, then allocates the Floatey score from that
     * fixed scratch.  The direction is the source bytewise X difference. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x071cU] = 0x20U;
    game.ram[0x0086U] = 0x20U;
    game.ram[0x074eU] = 1U;
    game.ram[0x000fU + 2U] = 1U;
    game.ram[0x0016U + 2U] = 6U;
    game.ram[0x001eU + 2U] = 0U;
    game.ram[0x0087U + 2U] = 0x60U;
    game.ram[0x00cfU + 2U] = 0x70U;
    game.ram[0x0001U] = 2U; /* FireballEnemyCDLoop's live enemy offset. */
    mysmb_world_handle_fireball_enemy_hit(&game, 2U);
    if (game.ram[0x001eU + 2U] != 0x22U ||
        game.ram[0x00cfU + 2U] != 0x6eU ||
        game.ram[0x00a0U + 2U] != 0xfdU ||
        game.ram[0x0046U + 2U] != 1U ||
        game.ram[0x0058U + 2U] != 0x10U ||
        game.ram[0x0110U + 2U] != 1U ||
        game.ram[0x0117U + 2U] != 0x40U ||
        game.ram[0x011eU + 2U] != 0x6eU ||
        game.ram[0x012cU + 2U] != 0x30U || game.ram[0x00ffU] != 8U) return 26;

    /* PlayerEnemyDiff returns the page subtraction after the low-X borrow.
     * Here low X is negative, but the next page makes the enemy rightward. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x071cU] = 0U;
    game.ram[0x006dU] = 1U;
    game.ram[0x0086U] = 0x20U;
    game.ram[0x074eU] = 1U;
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 6U;
    game.ram[0x006eU] = 2U;
    game.ram[0x0087U] = 0x10U;
    game.ram[0x00cfU] = 0x70U;
    mysmb_world_handle_fireball_enemy_hit(&game, 0U);
    if (game.ram[0x0046U] != 1U || game.ram[0x0058U] != 0x10U) return 28;
    /* The PiranhaPlant equality CMP leaves carry set, so its source ADC is
     * Y+$19 before ChkToStunEnemies; do not round it down to $18. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x071cU] = 0x20U;
    game.ram[0x0086U] = 0x20U;
    game.ram[0x074eU] = 1U;
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 13U;
    game.ram[0x001eU] = 0U;
    game.ram[0x0087U] = 0x30U;
    game.ram[0x00cfU] = 0x50U;
    mysmb_world_handle_fireball_enemy_hit(&game, 0U);
    if (game.ram[0x00cfU] != 0x67U || game.ram[0x001eU] != 0x22U ||
        game.ram[0x0016U] != 13U || game.ram[0x0117U] != 0x10U) return 27;
    /* BlockBumpedChk's multi-coin path initializes BrickCoinTimer only
     * once, sets the linked flag, and uses $c4 once that timer has expired. */
    mysmb_game_initialize_memory(&game, 0U);
    mysmb_clear_block_buffers(&game);
    game.ram[0x0754U] = 1U;
    game.ram[0x006dU] = 1U;
    game.ram[0x0086U] = 0x20U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x70U;
    /* PlayerHeadCollision reloads the source tile after its VRAM child. */
    game.ram[0x0520U] = 0x58U;
    if (mysmb_objects_start_head_bump(&game, 0x58U, 0U, 0x20U) == 0U ||
        game.ram[0x06bcU] != 1U || game.ram[0x079dU] != 0x0bU ||
        game.ram[0x03e8U] != 0x58U) return 47;
    game.ram[0x06bcU] = 1U;
    game.ram[0x079dU] = 0U;
    game.ram[0x0521U] = 0x5dU;
    if (mysmb_objects_start_head_bump(&game, 0x5dU, 1U, 0x20U) == 0U ||
        game.ram[0x06bcU] != 1U || game.ram[0x079dU] != 0U ||
        game.ram[0x03e9U] != 0xc4U) return 48;
    return 0;
}
