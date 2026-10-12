#include <string.h>
#include "core/area.h"
#include "core/enemy/stream.h"
#include "smb1_local_rom.h"

enum {
    ENEMY_BASES = 0x1ce0U,
    ENEMY_LOW = 0x1ce4U,
    ENEMY_HIGH = 0x1d06U,
    AREA_POINTER = 0x0750U,
    ENEMY_DATA_LOW = 0x00e9U,
    ENEMY_DATA_HIGH = 0x00eaU,
    ENEMY_DATA_OFFSET = 0x0739U,
    SCREEN_RIGHT_PAGE = 0x071bU
};

/* This is deliberately data-neutral: the local ROM supplies every stream.
 * It verifies the shared selection and consumer boundary without retaining
 * any owner ROM byte or derived stream table in tracked source. */
int main(void)
{
    static struct mysmb_game game;
    struct mysmb_area_source source;
    mysmb_u8 type, number, index, first, expected_low, expected_high;
    mysmb_u16 offset;

    source.prg = mysmb_local_prg;
    source.prg_size = MYSMB_LOCAL_PRG_SIZE;
    for (type = 0U; type < 4U; ++type) {
        mysmb_u8 count;
        count = (mysmb_u8)(type == 0U ? 3U : type == 1U ? 22U :
                            type == 2U ? 3U : 6U);
        for (number = 0U; number < count; ++number) {
            mysmb_game_initialize(&game);
            game.ram[AREA_POINTER] = (mysmb_u8)((type << 5U) | number);
            if (mysmb_area_get_data_addresses(&game, &source) == 0U) return 1;
            index = (mysmb_u8)(source.prg[ENEMY_BASES + type] + number);
            expected_low = source.prg[ENEMY_LOW + index];
            expected_high = source.prg[ENEMY_HIGH + index];
            if (game.ram[ENEMY_DATA_LOW] != expected_low ||
                game.ram[ENEMY_DATA_HIGH] != expected_high) return 2;
            offset = (mysmb_u16)(((mysmb_u16)expected_high << 8U) | expected_low);
            first = source.prg[offset - 0x8000U];
            game.ram[SCREEN_RIGHT_PAGE] = 0xffU;
            (void)mysmb_enemy_stream_process_current(&game, &source, 0U);
            if (first == 0xffU) {
                if (game.ram[ENEMY_DATA_OFFSET] != 0U) return 3;
            } else if (game.ram[ENEMY_DATA_OFFSET] == 0U &&
                       game.ram[0x000fU] == 0U) {
                return 4;
            }
        }
    }
    return 0;
}
