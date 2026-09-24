#include "game/area.h"
#include "game/audio.h"
#include "game/game.h"
#include "smb1_local_rom.h"

int main(void)
{
    struct mysmb_game game;
    unsigned int index;

    mysmb_game_initialize(&game);
    mysmb_game_bind_area_source(&game, mysmb_local_prg, MYSMB_LOCAL_PRG_SIZE);
    game.ram[0x0770U] = 1U;
    game.ram[0x00fcU] = 1U;
    mysmb_audio_step(&game);
    if (game.ram[0x07b1U] != 1U || game.ram[0x07b4U] == 0U) return 1;
    for (index = 0U; index < 179U; ++index) mysmb_audio_step(&game);
    if (game.ram[0x07b1U] != 1U) return 1;
    mysmb_audio_step(&game);
    if (game.ram[0x07b1U] != 0U || game.ram[0x00f4U] != 0U) return 1;
    return 0;
}
