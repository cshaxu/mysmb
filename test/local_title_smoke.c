#include "game/game.h"
#include "smb1_local_title.h"

int main(void)
{
    struct mysmb_game game;
    unsigned short index;
    unsigned short changed;

    mysmb_game_initialize(&game);
    if (mysmb_game_apply_title_commands(&game, mysmb_local_title_data,
                                        MYSMB_LOCAL_TITLE_DATA_SIZE) == 0U) {
        return 1;
    }
    changed = 0U;
    for (index = 0U; index < 0x0300U; ++index) {
        if (game.name_table[0][index] != 0x24U) {
            changed++;
        }
    }
    return changed != 0U ? 0 : 1;
}
