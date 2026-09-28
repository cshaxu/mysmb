#include "game/enemy/group.h"
#include "game/enemy/init.h"
#include "game/enemy/stream.h"

enum {
    MYSMB_AREA_SCREEN_RIGHT_PAGE = 0x071bU,
    MYSMB_AREA_SCREEN_RIGHT_X = 0x071dU,
    MYSMB_ENEMY_FLAG = 0x000fU,
    MYSMB_ENEMY_ID = 0x0016U,
    MYSMB_ENEMY_PAGE = 0x006eU,
    MYSMB_ENEMY_X = 0x0087U,
    MYSMB_ENEMY_Y = 0x00cfU,
    MYSMB_ENEMY_Y_HIGH = 0x00b6U,
    MYSMB_GROUP_ENEMY_COUNT = 0x06d3U,
    MYSMB_PRIMARY_HARD = 0x076aU
};

/* ROM HandleGroupEnemies.  Group records scan regular slots zero through
 * four and enter CheckpointEnemyID for every allocated member. */
void mysmb_enemy_stream_handle_group(struct mysmb_game *game,
                                            mysmb_u8 group_id)
{
    mysmb_u8 group;
    mysmb_u8 slot;
    mysmb_u8 old_x;

    group = (mysmb_u8)(group_id - 0x37U);
    game->ram[1U] = group < 4U ?
        (game->ram[MYSMB_PRIMARY_HARD] == 0U ? 6U : 2U) : 0U;
    game->ram[0U] = (group & 2U) == 0U ? 0xb0U : 0x70U;
    game->ram[2U] = game->ram[MYSMB_AREA_SCREEN_RIGHT_PAGE];
    game->ram[3U] = game->ram[MYSMB_AREA_SCREEN_RIGHT_X];
    game->ram[MYSMB_GROUP_ENEMY_COUNT] = (mysmb_u8)(2U + (group & 1U));
    while (game->ram[MYSMB_GROUP_ENEMY_COUNT] != 0U) {
        for (slot = 0U; slot < 5U; ++slot) {
            if (game->ram[MYSMB_ENEMY_FLAG + slot] == 0U) break;
        }
        if (slot >= 5U) break;
        game->ram[MYSMB_ENEMY_ID + slot] = game->ram[1U];
        game->ram[MYSMB_ENEMY_PAGE + slot] = game->ram[2U];
        game->ram[MYSMB_ENEMY_X + slot] = game->ram[3U];
        old_x = game->ram[3U];
        game->ram[3U] = (mysmb_u8)(old_x + 0x18U);
        game->ram[2U] = (mysmb_u8)(game->ram[2U] +
            (game->ram[3U] < old_x ? 1U : 0U));
        game->ram[MYSMB_ENEMY_Y + slot] = game->ram[0U];
        game->ram[MYSMB_ENEMY_Y_HIGH + slot] = 1U;
        game->ram[MYSMB_ENEMY_FLAG + slot] = 1U;
        mysmb_enemy_checkpoint_loaded(game, slot);
        game->ram[MYSMB_GROUP_ENEMY_COUNT]--;
    }
    mysmb_enemy_stream_advance_record(game);
}
