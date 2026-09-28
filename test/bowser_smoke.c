#include "game/area.h"
#include "game/enemy/stream.h"
#include "game/game.h"
#include "game/objects.h"
#include "game/enemy/frenzy.h"
#include "game/fireball/fireball.h"

int main(void)
{
    struct mysmb_game game;
    struct mysmb_area_source source;
    struct mysmb_input input;
    struct mysmb_frame frame;
    mysmb_u8 bowser_data[2] = { 0U, 45U };
    mysmb_u8 flame_data[2] = { 0xf0U, 21U };

    /* InitBowser duplicates the object before setting front-half fields.
     * It clears the bridge offset but does not initialize the bounding box. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    source.prg = bowser_data;
    source.prg_size = 2U;
    game.ram[0x00eaU] = 0x80U;
    game.ram[0x049aU] = 0x37U;
    game.ram[0x0369U] = 0x19U;
    if (mysmb_enemy_stream_process_next(&game, &source) != 1U ||
        game.ram[0x0016U] != 45U || game.ram[0x0366U] != 0U ||
        game.ram[0x0364U] != 0x20U || game.ram[0x0365U] != 2U ||
        game.ram[0x0790U] != 0xdfU || game.ram[0x0483U] != 5U ||
        game.ram[0x049aU] != 0x37U || game.ram[0x0369U] != 0U ||
        game.ram[0x06cfU] != 1U || game.ram[0x0010U] != 0x80U ||
        game.ram[0x00b7U] != 1U || game.ram[0x078aU] != 0x20U) return 1;

    /* RunBowser advances from the saved origin, chooses its original random
     * range, and applies the $0f slow vertical gravity. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 45U;
    game.ram[0x006eU] = 0U;
    game.ram[0x0087U] = 0x40U;
    game.ram[0x00b6U] = 1U;
    game.ram[0x00cfU] = 0x70U;
    game.ram[0x0366U] = 0x40U;
    game.ram[0x0364U] = 2U;
    game.ram[0x0365U] = 2U;
    /* InitBowser reserves a distinct rear slot before RunBowser renders. */
    game.ram[0x06cfU] = 1U;
    game.ram[0x006dU] = 0U;
    game.ram[0x0086U] = 0x20U;
    game.frame_number = 0UL;
    mysmb_objects_step_bowsers(&game);
    if (game.ram[0x0087U] != 0x42U || game.ram[0x06dcU] != 0x21U ||
        game.ram[0x0434U] != 0x0fU || game.ram[0x0364U] != 1U) return 2;

    /* A Bowser flame request spawns from the current front-half mouth. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x06cbU] = 21U;
    game.ram[0x0017U] = 21U;
    game.ram[0x078fU] = 0U;
    game.ram[0x0368U] = 0U;
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 45U;
    game.ram[0x006eU] = 0U;
    game.ram[0x0087U] = 0x80U;
    game.ram[0x00cfU] = 0x70U;
    game.ram[0x07a9U] = 0U;
    game.ram[0x00fdU] = 0x40U;
    game.ram[0x00feU] = 0x10U;
    mysmb_enemy_init_bowser_flame_frenzy(&game, 1U);
    if (game.ram[0x0010U] != 1U || game.ram[0x0017U] != 21U ||
        game.ram[0x0088U] != 0x72U || game.ram[0x00d0U] != 0x78U ||
        game.ram[0x0435U] != 1U || game.ram[0x06cbU] != 0U ||
        game.ram[0x00fdU] != 0x42U || game.ram[0x00feU] != 0x10U) return 3;

    /* A real $15 stream record enters InitEnemyFrenzy in slot two.  With no
     * Bowser front present it uses the source timer/PRNG/right-extent route. */
    mysmb_game_initialize_memory(&game, 0U);
    source.prg = flame_data;
    source.prg_size = sizeof(flame_data);
    game.ram[0x00e9U] = 0U;
    game.ram[0x00eaU] = 0x80U;
    game.ram[0x0739U] = 0U;
    game.ram[0x073aU] = 0U;
    game.ram[0x071bU] = 0U;
    game.ram[0x071dU] = 0xc0U;
    if (mysmb_enemy_stream_process_current(&game, &source, 2U) != 1U ||
        game.ram[0x0011U] != 1U || game.ram[0x0018U] != 21U ||
        game.ram[0x0089U] != 0xe0U || game.ram[0x00d1U] != 0x90U ||
        game.ram[0x078fU] != 0xdfU || game.ram[0x0739U] != 2U) return 4;
    /* The fifth fireball uses HurtBowser: it becomes the world identity and
     * enters the original defeated-state route. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    /* FireballObjCore now observes the ROM offscreen mask before enemy
     * collision, so this direct fixture must provide a real screen window. */
    game.ram[0x071aU] = 0U;
    game.ram[0x071bU] = 1U;
    game.ram[0x071cU] = 0U;
    game.ram[0x071dU] = 0xffU;
    game.frame_number = 0UL;
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 45U;
    game.ram[0x001eU] = 0U;
    game.ram[0x006eU] = 0U;
    game.ram[0x0087U] = 0x80U;
    game.ram[0x00cfU] = 0x70U;
    game.ram[0x0483U] = 1U;
    /* FireballEnemyCollision consumes the bounding boxes already generated
     * by each enemy's graphics route.  Supply that source-owned preparation
     * explicitly in this isolated owner fixture. */
    game.ram[0x049aU] = 10U;
    game.ram[0x03aeU] = 0x80U;
    game.ram[0x03b9U] = 0x70U;
    game.ram[0x03d1U] = 0U;
    mysmb_objects_update_enemy_bounding_box(&game, 0U);
    game.ram[0x0024U] = 1U;
    game.ram[0x0074U] = 0U;
    game.ram[0x008dU] = 0x80U;
    game.ram[0x00bcU] = 1U;
    game.ram[0x00d5U] = 0x80U;
    game.ram[0x005eU] = 0U;
    game.ram[0x00a6U] = 0U;
    game.ram[0x043aU] = 0U;
    game.ram[0x04a0U] = 7U;
    game.ram[0x0407U] = 0U;
    mysmb_fireball_step(&game);
    if (game.ram[0x0483U] != 0U || game.ram[0x0016U] != 6U ||
        game.ram[0x001eU] != 0x23U || game.ram[0x00a0U] != 0xfeU ||
        game.ram[0x0024U] != 0x80U || game.ram[0x00feU] != 0x80U ||
        game.ram[0x0110U] != 9U || game.ram[0x00ffU] != 8U) return 4;

    /* BridgeCollapse erases its axe/chain/bridge metatiles in the ordinary
     * NMI buffer, two name-table rows at a time, every four calls. */
    mysmb_game_initialize(&game);
    game.ram[0x0368U] = 0U;
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 45U;
    game.ram[0x001eU] = 0U;
    game.ram[0x0364U] = 1U;
    if (mysmb_objects_step_bridge_collapse(&game) != 0U ||
        game.ram[0x0300U] != 10U || game.ram[0x0301U] != 0x22U ||
        game.ram[0x0302U] != 0x1aU || game.ram[0x0303U] != 2U ||
        game.ram[0x0304U] != 0x24U || game.ram[0x0305U] != 0x24U ||
        game.ram[0x0306U] != 0x22U || game.ram[0x0307U] != 0x3aU ||
        game.ram[0x030aU] != 0x24U || game.ram[0x030bU] != 0U ||
        game.ram[0x0369U] != 1U || game.ram[0x00feU] != 8U ||
        game.ram[0x00fdU] != 1U) return 5;
    game.ram[0x0770U] = 2U;
    game.ram[0x0772U] = 1U;
    input.buttons2 = 0U;
    input.buttons = 0U;
    mysmb_game_tick(&game, &input, &frame);
    if (game.name_table[0U][0x021aU] != 0x24U ||
        game.name_table[0U][0x023aU] != 0x24U) return 6;

    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x0368U] = 0U;
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 45U;
    game.ram[0x001eU] = 0U;
    game.ram[0x0364U] = 1U;
    game.ram[0x0369U] = 14U;
    if (mysmb_objects_step_bridge_collapse(&game) != 0U ||
        game.ram[0x0369U] != 15U || game.ram[0x001eU] != 0x40U ||
        game.ram[0x00feU] != 0x80U) return 7;
    game.ram[0x00cfU] = 0xe0U;
    if (mysmb_objects_step_bridge_collapse(&game) == 0U ||
        game.ram[0x000fU] != 0U || game.ram[0x00fcU] != 0x80U) return 8;
    return 0;
}
