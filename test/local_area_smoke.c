#include <stdio.h>

#include "game/area.h"
#include "game/game.h"
#include "smb1_local_rom.h"

int main(void)
{
    struct mysmb_game game;
    struct mysmb_area_source source;
    struct mysmb_area_object object;
    mysmb_u8 count;

    mysmb_game_initialize(&game);
    source.prg = mysmb_local_prg;
    source.prg_size = MYSMB_LOCAL_PRG_SIZE;
    if (mysmb_area_load_pointers(&game, &source) == 0U ||
        game.ram[0x0750U] != 0x25U || game.ram[0x074eU] != 1U ||
        mysmb_area_parse_header(&game, &source) == 0U) {
        return 1;
    }
    count = 0U;
    while (count < 32U && mysmb_area_next_object(&game, &source, &object) != 0U) {
        count++;
    }
    if (count == 0U) {
        return 1;
    }
    printf("area_pointer=%02x type=%u enemy=%02x%02x area=%02x%02x header=%u/%u/%u objects=%u\n",
           game.ram[0x0750U], game.ram[0x074eU], game.ram[0x00eaU],
           game.ram[0x00e9U], game.ram[0x00e8U], game.ram[0x00e7U],
           game.ram[0x0710U], game.ram[0x0727U], game.ram[0x0742U], count);
    return 0;
}
