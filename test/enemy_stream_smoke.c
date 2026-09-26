#include "game/area.h"
#include "game/enemy/stream.h"

int main(void)
{
    struct mysmb_game game;
    struct mysmb_area_source source;
    static mysmb_u8 prg[0x0100U];

    mysmb_game_initialize(&game);
    source.prg = prg;
    source.prg_size = (mysmb_u16)sizeof(prg);
    prg[0x20U] = 0x0eU;
    prg[0x21U] = 0xc2U;
    prg[0x22U] = 0x51U;
    prg[0x23U] = 0xffU;
    game.ram[0x00e9U] = 0x20U;
    game.ram[0x00eaU] = 0x80U;
    game.ram[0x0739U] = 0U;
    game.ram[0x073bU] = 1U;
    game.ram[0x0750U] = 0x25U;
    game.ram[0x0751U] = 0U;
    game.ram[0x075fU] = 2U;
    if (mysmb_enemy_stream_process_next(&game, &source) != 0U ||
        game.ram[0x0750U] != 0xc2U || game.ram[0x0751U] != 0x11U ||
        game.ram[0x0739U] != 3U || game.ram[0x073bU] != 0U) return 1;

    game.ram[0x0739U] = 0U;
    game.ram[0x073bU] = 1U;
    game.ram[0x0750U] = 0x25U;
    game.ram[0x0751U] = 0U;
    game.ram[0x075fU] = 1U;
    if (mysmb_enemy_stream_process_next(&game, &source) != 0U ||
        game.ram[0x0750U] != 0x25U || game.ram[0x0751U] != 0U ||
        game.ram[0x0739U] != 3U || game.ram[0x073bU] != 0U) return 1;

    prg[0x20U] = 0x8bU;
    prg[0x21U] = 0x86U;
    game.ram[0x0739U] = 0U;
    game.ram[0x073aU] = 1U;
    game.ram[0x073bU] = 0U;
    game.ram[0x071bU] = 1U;
    game.ram[0x071dU] = 0x30U;
    if (mysmb_enemy_stream_process_next(&game, &source) != 0U ||
        game.ram[0x0739U] != 0U || game.ram[0x073aU] != 2U ||
        game.ram[0x073bU] != 1U) return 1;
    if (mysmb_enemy_stream_process_next(&game, &source) != 0U ||
        game.ram[0x0739U] != 0U || game.ram[0x073aU] != 2U ||
        game.ram[0x073bU] != 1U) return 1;
    /* ProcELoop passes its current ObjectOffset: an earlier empty slot
     * must not be selected while the requested slot is being initialized. */
    prg[0x20U] = 0x10U;
    prg[0x21U] = 6U;
    prg[0x22U] = 0xffU;
    game.ram[0x000fU] = 1U;
    game.ram[0x0010U] = 0U;
    game.ram[0x0011U] = 0U;
    game.ram[0x0739U] = 0U;
    game.ram[0x073aU] = 0U;
    game.ram[0x073bU] = 0U;
    game.ram[0x071bU] = 0U;
    game.ram[0x071dU] = 0U;
    if (mysmb_enemy_stream_process_slot(&game, &source, 2U) != 1U ||
        game.ram[0x000fU] != 1U || game.ram[0x0010U] != 0U ||
        game.ram[0x0011U] != 1U || game.ram[0x0018U] != 6U) return 1;
    /* ProcessEnemyData consumes an ordinary record that has already passed
     * ScreenRight.  It leaves its position in the current empty slot but
     * advances EnemyDataOffset so later slots cannot replay it. */
    prg[0x20U] = 0x10U;
    prg[0x21U] = 6U;
    prg[0x22U] = 0xffU;
    game.ram[0x000fU] = 0U;
    game.ram[0x0010U] = 1U;
    game.ram[0x0739U] = 0U;
    game.ram[0x073aU] = 0U;
    game.ram[0x073bU] = 0U;
    game.ram[0x071bU] = 0U;
    game.ram[0x071dU] = 0x20U;
    if (mysmb_enemy_stream_process_slot(&game, &source, 0U) != 0U ||
        game.ram[0x0739U] != 2U || game.ram[0x006eU] != 0U ||
        game.ram[0x0087U] != 0x10U) return 2;
    /* ROM PositionEnemyObj writes the requested current slot before
     * ParseRow0e consumes its third byte.  Use slot two so fixed stream
     * state cannot mask the ObjectOffset destination. */
    prg[0x20U] = 0x4eU;
    prg[0x21U] = 2U;
    prg[0x22U] = 0x51U;
    prg[0x23U] = 0xffU;
    game.ram[0x0739U] = 0U;
    game.ram[0x073aU] = 2U;
    game.ram[0x073bU] = 1U;
    game.ram[0x071bU] = 2U;
    game.ram[0x071dU] = 0x10U;
    game.ram[0x075fU] = 2U;
    game.ram[0x0011U] = 0U;
    game.ram[0x0070U] = 0U;
    game.ram[0x0089U] = 0U;
    game.ram[0x00b8U] = 0U;
    game.ram[0x00d1U] = 0U;
    if (mysmb_enemy_stream_process_slot(&game, &source, 2U) != 0U) return 31;
    if (game.ram[0x0739U] != 3U) return 32;
    if (game.ram[0x073bU] != 0U) return 33;
    if (game.ram[0x0070U] != 2U) return 34;
    if (game.ram[0x0089U] != 0x40U) return 35;
    if (game.ram[0x00b8U] != 1U) return 36;
    if (game.ram[0x00d1U] != 0xe0U) return 37;
    if (game.ram[0x0750U] != 2U) return 38;
    if (game.ram[0x0751U] != 0x11U) return 39;
    /* ROM HandleGroupEnemies: $37 creates two Goombas from ScreenRight,
     * scanning slots zero through four rather than using ObjectOffset. */
    prg[0x20U] = 0x10U;
    prg[0x21U] = 0x37U;
    prg[0x22U] = 0xffU;
    game.ram[0x0739U] = 0U;
    game.ram[0x073aU] = 2U;
    game.ram[0x073bU] = 1U;
    game.ram[0x071bU] = 1U;
    game.ram[0x071dU] = 0xf8U;
    game.ram[0x076aU] = 0U;
    game.ram[0x000fU] = 0U;
    game.ram[0x0010U] = 0U;
    game.ram[0x0011U] = 0U;
    game.ram[0x0012U] = 0U;
    game.ram[0x0013U] = 0U;
    if (mysmb_enemy_stream_process_slot(&game, &source, 2U) != 1U ||
        game.ram[0x0739U] != 2U || game.ram[0x073bU] != 0U ||
        game.ram[0x06d3U] != 0U ||
        game.ram[0x000fU] != 1U || game.ram[0x0010U] != 1U ||
        game.ram[0x0016U] != 6U || game.ram[0x0017U] != 6U ||
        game.ram[0x006eU] != 1U || game.ram[0x006fU] != 2U ||
        game.ram[0x0087U] != 0xf8U || game.ram[0x0088U] != 0x10U ||
        game.ram[0x00cfU] != 0xb0U || game.ram[0x00d0U] != 0xb0U ||
        game.ram[0x00b6U] != 1U || game.ram[0x00b7U] != 1U) return 4;
    /* ChkEnemyFrenzy precedes stream parsing and accepts slot five. */
    game.ram[0x06cdU] = 23U;
    game.ram[0x0014U] = 0U;
    game.ram[0x001bU] = 0U;
    if (mysmb_enemy_stream_process_current(&game, &source, 5U) != 1U ||
        game.ram[0x06cdU] != 0U || game.ram[0x001bU] != 23U ||
        game.ram[0x0014U] != 1U) return 5;
    /* CheckFrenzyBuffer runs when the source has reached EOD. */
    prg[0x20U] = 0xffU;
    game.ram[0x0739U] = 0U;
    game.ram[0x06cbU] = 21U;
    game.ram[0x0013U] = 0U;
    if (mysmb_enemy_stream_process_current(&game, &source, 4U) != 1U ||
        game.ram[0x001aU] != 21U || game.ram[0x0013U] != 1U) return 6;
    game.ram[0x06cbU] = 0U;
    game.ram[0x0398U] = 1U;
    game.ram[0x0012U] = 0U;
    if (mysmb_enemy_stream_process_current(&game, &source, 3U) != 1U ||
        game.ram[0x0019U] != 0x2fU || game.ram[0x0012U] != 1U) return 7;
    /* ROM BuzzyBeetleMutate changes a stream Goomba in primary hard mode. */
    prg[0x20U] = 0x10U;
    prg[0x21U] = 6U;
    prg[0x22U] = 0xffU;
    game.ram[0x0739U] = 0U;
    game.ram[0x073aU] = 1U;
    game.ram[0x073bU] = 1U;
    game.ram[0x071bU] = 1U;
    game.ram[0x071dU] = 0U;
    game.ram[0x076aU] = 1U;
    game.ram[0x000fU] = 0U;
    if (mysmb_enemy_stream_process_slot(&game, &source, 0U) != 1U ||
        game.ram[0x0016U] != 2U) return 8;
    /* ROM CheckEndofBuffer admits only power-up ID 0x2e in slot five. */
    prg[0x20U] = 0x10U;
    prg[0x21U] = 0x2eU;
    prg[0x22U] = 0xffU;
    game.ram[0x0739U] = 0U;
    game.ram[0x073aU] = 1U;
    game.ram[0x073bU] = 1U;
    game.ram[0x071bU] = 1U;
    game.ram[0x071dU] = 0U;
    game.ram[0x0014U] = 0U;
    if (mysmb_enemy_stream_process_current(&game, &source, 5U) != 1U ||
        game.ram[0x001bU] != 0x2eU || game.ram[0x0014U] != 1U) return 9;
    return 0;
}
