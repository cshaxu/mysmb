#include "game/game.h"

int main(void)
{
    struct mysmb_game game;
    mysmb_u16 address;
    mysmb_u8 first_offset;
    mysmb_u8 expected;

    mysmb_game_initialize(&game);
    /* InitializeMemory starts at page seven and deliberately skips page-one
     * bytes $60-$ff; the owner-local cold RAM supplies zero there. */
    if (game.ram[0x0160U] != 0U || game.ram[0x01ffU] != 0U) return 1;
    /* The OAM offscreen pass still owns its Y coordinates after cold boot. */
    if (game.ram[0x0200U] != 0xf8U || game.ram[0x02fcU] != 0xf8U) return 2;

    /* ROM InitializeMemory begins at page $07, writes Y down through zero,
     * then decrements X.  Test both source callers ($fe cold, $d6 warm)
     * against every original CPU-RAM byte, including the stack window that
     * the source explicitly skips. */
    for (first_offset = 0xfeU; ; first_offset = 0xd6U) {
        for (address = 0U; address < 0x0800U; ++address)
            game.ram[address] = 0x5aU;
        mysmb_game_initialize_memory(&game, first_offset);
        for (address = 0U; address < 0x0800U; ++address) {
            mysmb_u8 page;
            mysmb_u8 offset;

            page = (mysmb_u8)(address >> 8U);
            offset = (mysmb_u8)address;
            expected = 0x5aU;
            if ((page == 7U && offset <= first_offset) || page < 7U) {
                if (page != 1U || offset < 0x60U) expected = 0U;
            }
            if (game.ram[address] != expected) return 3;
        }
        if (first_offset == 0xd6U) break;
    }
    return 0;
}
