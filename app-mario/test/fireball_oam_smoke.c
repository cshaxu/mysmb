#include "core/fireball/fireball.h"
#include "core/oam/oam.h"
#include "core/world/world.h"

int main(void)
{
    static struct mysmb_game game;

    /* ProcFireball_Bubble queues Sfx_Fireball only on a new valid fireball. */
    mysmb_game_initialize_memory(&game, 0U);
    game.ram[0x0756U] = 2U;
    game.ram[0x000aU] = 0x40U;
    game.ram[0x000dU] = 0U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x40U;
    game.ram[0x0086U] = 0x40U;
    game.ram[0x006dU] = 0U;
    game.ram[0x0033U] = 1U;
    game.ram[0x06f1U] = 0x20U;
    game.ram[0x070cU] = 6U;
    game.ram[0x071dU] = 0xffU;
    game.ram[0x071aU] = 0U;
    game.ram[0x071bU] = 0U;
    game.ram[0x071cU] = 0U;
    game.ram[0x0714U] = 0U;
    game.ram[0x001dU] = 0U;
    mysmb_fireball_step(&game);
    if (game.ram[0x00ffU] != 0x20U || game.ram[0x0024U] != 1U ||
        game.ram[0x0711U] != 6U || game.ram[0x0781U] != 5U) return 14;
    game.ram[0x00ffU] = 0U;
    game.ram[0x000dU] = 0x40U;
    mysmb_fireball_step(&game);
    if (game.ram[0x00ffU] != 0U) return 15;
    /* ProcFireball_Bubble branches straight to ProcAirBubbles when Mario
     * is not fiery.  An existing slot must not move, collide, or draw. */
    mysmb_game_initialize_memory(&game, 0U);
    game.ram[0x0756U] = 1U;
    game.ram[0x074eU] = 1U;
    game.ram[0x0024U] = 1U;
    game.ram[0x0074U] = 0U;
    game.ram[0x008dU] = 0x40U;
    game.ram[0x00bcU] = 1U;
    game.ram[0x00d5U] = 0x50U;
    game.ram[0x005eU] = 0x40U;
    game.ram[0x00a6U] = 0U;
    mysmb_fireball_step(&game);
    if (game.ram[0x0024U] != 1U || game.ram[0x008dU] != 0x40U ||
        game.ram[0x00d5U] != 0x50U) return 24;
    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x0756U] = 2U;
    game.frame_number = 4UL;
    game.ram[0x0009U] = (mysmb_u8)(4UL);
    game.ram[0x0024U] = 1U;
    game.ram[0x0074U] = 0U;
    game.ram[0x008dU] = 0x40U;
    game.ram[0x00d5U] = 0x40U;
    game.ram[0x00bcU] = 1U;
    game.ram[0x005eU] = 0U;
    game.ram[0x00a6U] = 0U;
    game.ram[0x04a0U] = 7U;
    game.ram[0x06f1U] = 0x20U;
    game.ram[0x070cU] = 6U;
    game.ram[0x071aU] = 0U;
    game.ram[0x071bU] = 0U;
    game.ram[0x071cU] = 0U;
    game.ram[0x071dU] = 0xffU;
    mysmb_fireball_step(&game);
    if (game.ram[0x0220U] != 0x40U || game.ram[0x0221U] != 0x65U ||
        game.ram[0x0222U] != 2U || game.ram[0x0223U] != 0x40U) return 1;
    /* GetFireballBoundBox uses SprObject offset seven against the common
     * $04ac bounding-box base: slot zero belongs at $04c8, never $04cc. */
    if (game.ram[0x04c8U] != 0x40U) return 8;
    if (game.ram[0x04c9U] != 0x40U) return 9;
    if (game.ram[0x04caU] != 0x48U) return 10;
    if (game.ram[0x04cbU] != 0x48U) return 11;
    /* Slot one still writes the fixed FBall_Rel_* and FBall_OffscreenBits
     * cells; only its SprObject input and bounding-box/OAM destinations vary. */
    game.ram[0x0025U] = 1U;
    game.ram[0x0075U] = 0U;
    game.ram[0x008eU] = 0x50U;
    game.ram[0x00d6U] = 0x50U;
    game.ram[0x00bdU] = 1U;
    game.ram[0x04a1U] = 7U;
    game.ram[0x06f2U] = 0x30U;
    game.ram[0x03d2U] = 0xffU;
    mysmb_fireball_step(&game);
    if (game.ram[0x0025U] != 1U || game.ram[0x03afU] != 0x50U ||
        game.ram[0x03baU] != 0x50U || game.ram[0x03d2U] != 0U) return 12;
    if (game.ram[0x04ccU] != 0x50U || game.ram[0x04cdU] != 0x50U ||
        game.ram[0x04ceU] != 0x58U || game.ram[0x04cfU] != 0x58U) return 13;

    game.frame_number = 0x10UL;
    game.ram[0x0009U] = (mysmb_u8)(0x10UL);
    game.ram[0x0024U] = 1U;
    game.ram[0x008dU] = 0x50U;
    game.ram[0x00d5U] = 0x50U;
    mysmb_fireball_step(&game);
    if (game.ram[0x0220U] != 0x50U || game.ram[0x0221U] != 0x64U ||
        game.ram[0x0222U] != 2U || game.ram[0x0223U] != 0x50U) return 2;
    /* FireballObjCore clears only when FBall_OffscreenBits & $cc is set.
     * The source permits anchors from $08 through $f7; both outer eight-pixel
     * bands are discarded by the source mask. */
    mysmb_game_initialize_memory(&game, 0U);
    game.ram[0x071aU] = 0U;
    game.ram[0x071bU] = 0U;
    game.ram[0x071cU] = 0U;
    game.ram[0x071dU] = 0xffU;
    game.ram[0x0024U] = 1U;
    game.ram[0x0074U] = 0U;
    game.ram[0x008dU] = 0U;
    game.ram[0x00bcU] = 1U;
    game.ram[0x00d5U] = 0x50U;
    game.ram[0x06f1U] = 0x20U;
    game.ram[0x070cU] = 6U;
    mysmb_fireball_step(&game);
    if (game.ram[0x0024U] != 0U ||
        (game.ram[0x03d2U] & 0xccU) == 0U) return 4;
    game.ram[0x0024U] = 1U;
    game.ram[0x008dU] = 8U;
    mysmb_fireball_step(&game);
    if (game.ram[0x0024U] != 1U ||
        (game.ram[0x03d2U] & 0xccU) != 0U) return 5;
    game.ram[0x0024U] = 1U;
    game.ram[0x008dU] = 0xf7U;
    mysmb_fireball_step(&game);
    if (game.ram[0x0024U] != 1U ||
        (game.ram[0x03d2U] & 0xccU) != 0U) return 6;
    game.ram[0x0024U] = 1U;
    game.ram[0x008dU] = 0xffU;
    mysmb_fireball_step(&game);
    if (game.ram[0x0024U] != 0U ||
        (game.ram[0x03d2U] & 0xccU) == 0U) return 7;
    /* Direct ROM GetFireballOffscreenBits boundary table.  This isolates
     * the source offscreen primitive from motion: its final byte is the
     * horizontal high nybble shifted down plus the vertical bits shifted up.
     * FireballObjCore subsequently erases only when this byte & $cc is set. */
    mysmb_game_initialize_memory(&game, 0U);
    game.ram[0x0756U] = 2U;
    game.ram[0x071aU] = 0U;
    game.ram[0x071bU] = 0U;
    game.ram[0x071cU] = 0U;
    game.ram[0x071dU] = 0xffU;
    game.ram[0x0074U] = 0U;
    game.ram[0x00bcU] = 1U;
    game.ram[0x00d5U] = 0x50U;
    game.ram[0x008dU] = 0U;
    mysmb_oam_get_fireball_offscreen_bits(&game, 0U);
    if (game.ram[0x03d2U] != 0x08U) return 16;
    game.ram[0x008dU] = 8U;
    mysmb_oam_get_fireball_offscreen_bits(&game, 0U);
    if (game.ram[0x03d2U] != 0U) return 17;
    game.ram[0x008dU] = 0xf7U;
    mysmb_oam_get_fireball_offscreen_bits(&game, 0U);
    if (game.ram[0x03d2U] != 3U) return 18;
    game.ram[0x008dU] = 0xffU;
    mysmb_oam_get_fireball_offscreen_bits(&game, 0U);
    if (game.ram[0x03d2U] != 7U) return 19;

    /* ROM FireballBGCollision probes (X+4, (Y+8)&$f0)-$20.  It clears a
     * stale bounce flag above the status bar and for non-solid metatiles,
     * bounces once on a solid, then explodes on the next solid contact. */
    mysmb_game_initialize_memory(&game, 0U);
    game.ram[0x008dU] = 0x40U;
    game.ram[0x0074U] = 0U;
    game.ram[0x00d5U] = 0x50U;
    game.ram[0x00a6U] = 0U;
    game.ram[0x003aU] = 0U;
    game.ram[0x0024U] = 1U;
    game.ram[0x0534U] = 0x61U;
    mysmb_world_fireball_background_collision(&game, 0U);
    if (game.ram[0x00a6U] != 0xfdU || game.ram[0x003aU] != 1U ||
        game.ram[0x00d5U] != 0x50U || game.ram[0x0024U] != 1U) return 20;
    mysmb_world_fireball_background_collision(&game, 0U);
    if (game.ram[0x0024U] != 0x80U || game.ram[0x00ffU] != 2U) return 21;
    game.ram[0x0024U] = 1U;
    game.ram[0x003aU] = 1U;
    game.ram[0x00a6U] = 0U;
    game.ram[0x0534U] = 0xc2U;
    mysmb_world_fireball_background_collision(&game, 0U);
    if (game.ram[0x003aU] != 0U || game.ram[0x0024U] != 1U) return 22;
    game.ram[0x003aU] = 1U;
    game.ram[0x00d5U] = 0x17U;
    mysmb_world_fireball_background_collision(&game, 0U);
    if (game.ram[0x003aU] != 0U) return 23;
    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x0756U] = 2U;
    game.ram[0x0024U] = 0x80U;
    game.ram[0x008dU] = 0x40U;
    game.ram[0x00d5U] = 0x40U;
    game.ram[0x06ecU] = 0x30U;
    mysmb_fireball_step(&game);
    if (game.ram[0x0024U] != 0x81U || game.ram[0x0230U] != 0x3cU ||
        game.ram[0x0234U] != 0x44U || game.ram[0x0238U] != 0x3cU ||
        game.ram[0x023cU] != 0x44U || game.ram[0x0231U] != 0x68U ||
        game.ram[0x023dU] != 0x68U || game.ram[0x0232U] != 2U ||
        game.ram[0x0236U] != 0x82U || game.ram[0x023aU] != 0x42U ||
        game.ram[0x023eU] != 0xc2U || game.ram[0x0233U] != 0x3cU ||
        game.ram[0x0237U] != 0x3cU || game.ram[0x023bU] != 0x44U ||
        game.ram[0x023fU] != 0x44U) return 3;
    /* ROM DrawFirebar's second LSR pair carries original FrameCounter bit 3.
     * Frame 8 flips both axes; frame 16 has the unflipped palette byte. */
    mysmb_game_initialize_memory(&game, 0U);
    game.ram[0x06f1U] = 0x20U;
    game.ram[0x03afU] = 0x50U;
    game.ram[0x03baU] = 0x60U;
    game.ram[0x0009U] = 8U;
    mysmb_oam_draw_fireball(&game, 0U);
    if (game.ram[0x0221U] != 0x64U || game.ram[0x0222U] != 0xc2U) return 25;
    game.ram[0x0009U] = 16U;
    mysmb_oam_draw_fireball(&game, 0U);
    if (game.ram[0x0221U] != 0x64U || game.ram[0x0222U] != 2U) return 26;
    return 0;
}
