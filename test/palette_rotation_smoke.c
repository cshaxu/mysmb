#include <string.h>

#include "game/area.h"
#include "game/game.h"
#include "smb1_local_rom.h"

static int verify_rotation(mysmb_u8 area_type, mysmb_u8 rotation,
                           mysmb_u8 buffer_offset)
{
    struct mysmb_game game;
    mysmb_u8 index;

    mysmb_game_initialize(&game);
    mysmb_game_bind_area_source(&game, mysmb_local_prg, MYSMB_LOCAL_PRG_SIZE);
    memset(&game.ram[0x0301U], 0xa5, 0xffU);
    game.ram[0x0009U] = 0U;
    game.ram[0x074eU] = area_type;
    game.ram[0x06d4U] = rotation;
    game.ram[0x0300U] = buffer_offset;
    game.ram[0x0000U] = 0x5aU;
    mysmb_area_step_palette_rotation(&game);
    if (game.ram[0x0000U] != 0xffU ||
        game.ram[0x0300U] != (mysmb_u8)(buffer_offset + 7U) ||
        game.ram[0x06d4U] != (mysmb_u8)((rotation + 1U) % 6U)) return 1;
    for (index = 0U; index < 8U; ++index) {
        mysmb_u8 expected;

        expected = mysmb_local_prg[0x09c9U + index];
        if (index >= 3U && index <= 6U)
            expected = mysmb_local_prg[0x09d1U + (mysmb_u16)area_type * 4U +
                index - 3U];
        if (index == 4U) expected = mysmb_local_prg[0x09c3U + rotation];
        if (game.ram[0x0301U + buffer_offset + index] != expected) return 1;
    }
    return 0;
}

int main(void)
{
    struct mysmb_game game;

    if (verify_rotation(0U, 0U, 0U) != 0 ||
        verify_rotation(1U, 1U, 7U) != 0 ||
        verify_rotation(2U, 4U, 0x29U) != 0 ||
        verify_rotation(3U, 5U, 0U) != 0) return 1;

    mysmb_game_initialize(&game);
    mysmb_game_bind_area_source(&game, mysmb_local_prg, MYSMB_LOCAL_PRG_SIZE);
    memset(&game.ram[0x0301U], 0xa5, 0xffU);
    game.ram[0x0009U] = 1U;
    game.ram[0x0300U] = 7U;
    game.ram[0x06d4U] = 2U;
    game.ram[0x0000U] = 0x5aU;
    mysmb_area_step_palette_rotation(&game);
    if (game.ram[0x0000U] != 0x5aU ||
        game.ram[0x0300U] != 7U || game.ram[0x06d4U] != 2U ||
        game.ram[0x0308U] != 0xa5U) return 1;
    game.ram[0x0009U] = 0U;
    game.ram[0x0300U] = 0x31U;
    mysmb_area_step_palette_rotation(&game);
    if (game.ram[0x0000U] != 0x5aU ||
        game.ram[0x0300U] != 0x31U || game.ram[0x06d4U] != 2U ||
        game.ram[0x0332U] != 0xa5U) return 1;
    return 0;
}
