#include "game/oam/oam.h"

/* ROM $e5c1 DumpTwoSpr through $e5c7 ExitDumpSpr. */
void mysmb_oam_dump_two_sprites(struct mysmb_game *game,
                                 mysmb_u8 value, mysmb_u8 oam)
{
    game->ram[(mysmb_u16)(0x0204U + oam)] = value;
    game->ram[(mysmb_u16)(0x0200U + oam)] = value;
}

/* ROM $e5be DumpThreeSpr falls through DumpTwoSpr. */
void mysmb_oam_dump_three_sprites(struct mysmb_game *game,
                                   mysmb_u8 value, mysmb_u8 oam)
{
    game->ram[(mysmb_u16)(0x0208U + oam)] = value;
    mysmb_oam_dump_two_sprites(game, value, oam);
}

/* ROM $e5bb DumpFourSpr falls through DumpThreeSpr. */
void mysmb_oam_dump_four_sprites(struct mysmb_game *game,
                                  mysmb_u8 value, mysmb_u8 oam)
{
    game->ram[(mysmb_u16)(0x020cU + oam)] = value;
    mysmb_oam_dump_three_sprites(game, value, oam);
}

/* ROM $e5b5 DumpSixSpr falls through DumpFourSpr. */
void mysmb_oam_dump_six_sprites(struct mysmb_game *game,
                                 mysmb_u8 value, mysmb_u8 oam)
{
    game->ram[(mysmb_u16)(0x0214U + oam)] = value;
    game->ram[(mysmb_u16)(0x0210U + oam)] = value;
    mysmb_oam_dump_four_sprites(game, value, oam);
}

/* ROM $e5b3 MoveSixSpritesOffscreen enters DumpSixSpr with A=$f8. */
void mysmb_oam_move_six_sprites_offscreen(struct mysmb_game *game,
                                          mysmb_u8 oam)
{
    mysmb_oam_dump_six_sprites(game, 0xf8U, oam);
}

/* ROM $ec4a MoveColOffscreen; Y is a byte, absolute indexed stores are not. */
mysmb_u8 mysmb_oam_move_column_offscreen(struct mysmb_game *game, mysmb_u8 oam)
{
    game->ram[0x0200U + oam] = 0xf8U;
    game->ram[0x0208U + oam] = 0xf8U;
    return 0xf8U;
}
