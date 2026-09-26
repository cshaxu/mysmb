#include "game/enemy/stream.h"
#include "game/enemy/init.h"

enum {
    MYSMB_AREA_SCREEN_RIGHT_PAGE = 0x071bU,
    MYSMB_AREA_SCREEN_RIGHT_X = 0x071dU,
    MYSMB_AREA_POINTER = 0x0750U,
    MYSMB_AREA_ENTRANCE_PAGE = 0x0751U,
    MYSMB_AREA_TYPE = 0x074eU,
    MYSMB_ENEMY_DATA_LOW = 0x00e9U,
    MYSMB_ENEMY_DATA_HIGH = 0x00eaU,
    MYSMB_WORLD_NUMBER = 0x075fU,
    MYSMB_ENEMY_DATA_OFFSET = 0x0739U,
    MYSMB_ENEMY_OBJECT_PAGE = 0x073aU,
    MYSMB_ENEMY_OBJECT_PAGE_SELECT = 0x073bU,
    MYSMB_ENEMY_FLAG = 0x000fU,
    MYSMB_ENEMY_ID = 0x0016U,
    MYSMB_ENEMY_STATE = 0x001eU,
    MYSMB_ENEMY_MOVING_DIRECTION = 0x0046U,
    MYSMB_ENEMY_X_SPEED = 0x0058U,
    MYSMB_ENEMY_PAGE = 0x006eU,
    MYSMB_ENEMY_X = 0x0087U,
    MYSMB_ENEMY_Y_SPEED = 0x00a0U,
    MYSMB_ENEMY_Y_HIGH = 0x00b6U,
    MYSMB_ENEMY_Y = 0x00cfU,
    MYSMB_ENEMY_X_FORCE = 0x0401U,
    MYSMB_ENEMY_Y_DUMMY = 0x0417U,
    MYSMB_ENEMY_Y_FORCE = 0x0434U,
    MYSMB_ENEMY_BOUND_BOX = 0x049aU,
    MYSMB_FIREBAR_SPIN_SPEED = 0x0388U,
    MYSMB_FIREBAR_SPIN_DIRECTION = 0x0034U,
    MYSMB_BOWSER_BODY_CONTROLS = 0x0363U,
    MYSMB_BOWSER_FEET_TIMER = 0x0364U,
    MYSMB_BOWSER_MOVE_SPEED = 0x0365U,
    MYSMB_BOWSER_ORIGIN_X = 0x0366U,
    MYSMB_BOWSER_FLAME_TIMER = 0x0367U,
    MYSMB_BOWSER_BREATH_TIMER = 0x0790U,
    MYSMB_BOWSER_FRONT_SLOT = 0x0368U,
    MYSMB_BOWSER_HIT_POINTS = 0x0483U,
    MYSMB_ENEMY_INTERVAL_TIMER = 0x078aU,
    MYSMB_BALANCE_PLATFORM_ALIGNMENT = 0x03a0U,
    MYSMB_PLATFORM_COLLISION_FLAG = 0x03a2U,
    MYSMB_PLATFORM_TOP_Y = 0x0401U,
    MYSMB_PLATFORM_CENTER_Y = 0x0058U,
    MYSMB_PRIMARY_HARD = 0x076aU,
    MYSMB_SECONDARY_HARD = 0x06ccU,
    MYSMB_ENEMY_FRENZY_BUFFER = 0x06cbU,
    MYSMB_GROUP_ENEMY_COUNT = 0x06d3U,
    MYSMB_ENEMY_FRENZY_QUEUE = 0x06cdU,
    MYSMB_VINE_FLAG_OFFSET = 0x0398U
};

/* ROM HandleGroupEnemies.  Group records scan regular slots zero through
 * four and enter CheckpointEnemyID for every allocated member. */
static void mysmb_enemy_stream_handle_group(struct mysmb_game *game,
                                            mysmb_u8 group_id)
{
    mysmb_u8 group;
    mysmb_u8 enemy_id;
    mysmb_u8 y;
    mysmb_u8 page;
    mysmb_u8 x;
    mysmb_u8 count;
    mysmb_u8 slot;
    mysmb_u8 old_x;

    group = (mysmb_u8)(group_id - 0x37U);
    enemy_id = group < 4U ?
        (game->ram[MYSMB_PRIMARY_HARD] == 0U ? 6U : 2U) : 0U;
    y = (group & 2U) == 0U ? 0xb0U : 0x70U;
    page = game->ram[MYSMB_AREA_SCREEN_RIGHT_PAGE];
    x = game->ram[MYSMB_AREA_SCREEN_RIGHT_X];
    count = (mysmb_u8)(2U + (group & 1U));
    game->ram[MYSMB_GROUP_ENEMY_COUNT] = count;
    while (count != 0U) {
        for (slot = 0U; slot < 5U; ++slot) {
            if (game->ram[MYSMB_ENEMY_FLAG + slot] == 0U) break;
        }
        if (slot >= 5U) break;
        game->ram[MYSMB_ENEMY_ID + slot] = enemy_id;
        game->ram[MYSMB_ENEMY_PAGE + slot] = page;
        game->ram[MYSMB_ENEMY_X + slot] = x;
        old_x = x;
        x = (mysmb_u8)(x + 0x18U);
        if (x < old_x) page++;
        game->ram[MYSMB_ENEMY_Y + slot] = y;
        game->ram[MYSMB_ENEMY_Y_HIGH + slot] = 1U;
        game->ram[MYSMB_ENEMY_FLAG + slot] = 1U;
        mysmb_enemy_checkpoint_loaded(game, slot);
        count--;
        game->ram[MYSMB_GROUP_ENEMY_COUNT] = count;
    }
}
/* ROM ChkEnemyFrenzy and CheckFrenzyBuffer. */
static mysmb_u8 mysmb_enemy_stream_activate_fallback(struct mysmb_game *game,
                                                      mysmb_u8 slot)
{
    mysmb_u8 id;

    id = game->ram[MYSMB_ENEMY_FRENZY_BUFFER];
    if (id == 0U) {
        if (game->ram[MYSMB_VINE_FLAG_OFFSET] != 1U) return 0U;
        id = 0x2fU;
    }
    game->ram[MYSMB_ENEMY_ID + slot] = id;
    game->ram[MYSMB_ENEMY_STATE + slot] = 0U;
    mysmb_enemy_checkpoint_loaded(game, slot);
    return 1U;
}
/* ROM $c0f7-$c1f4 ProcessEnemyData through InitNormalEnemy, limited to
 * ordinary enemy IDs.  Special objects retain their dedicated initializers. */
/* ProcessEnemyData is called with the current ObjectOffset.  This adapter
 * keeps the original public stream probe while reserving earlier empty slots
 * so a GameEngine pass can initialize exactly the requested normal slot. */
mysmb_u8 mysmb_enemy_stream_process_slot(struct mysmb_game *game,
                                         const struct mysmb_area_source *source,
                                         mysmb_u8 slot)
{
    if (slot >= 5U || game->ram[MYSMB_ENEMY_FLAG + slot] != 0U) return 0U;
    return mysmb_enemy_stream_process_current(game, source, slot);
}

mysmb_u8 mysmb_enemy_stream_process_current(struct mysmb_game *game,
                                             const struct mysmb_area_source *source,
                                             mysmb_u8 slot)
{
    mysmb_u16 address;
    mysmb_u16 world;
    mysmb_u16 right;
    mysmb_u8 first;
    mysmb_u8 second;
    mysmb_u8 third;
    mysmb_u8 row;
    mysmb_u8 id;

    if (game->ram[MYSMB_ENEMY_FRENZY_QUEUE] != 0U) {
        game->ram[MYSMB_ENEMY_ID + slot] = game->ram[MYSMB_ENEMY_FRENZY_QUEUE];
        game->ram[MYSMB_ENEMY_STATE + slot] = 0U;
        game->ram[MYSMB_ENEMY_FRENZY_QUEUE] = 0U;
        mysmb_enemy_checkpoint_loaded(game, slot);
        return 1U;
    }
    if (source == 0 || source->prg == 0 || game->ram[MYSMB_ENEMY_DATA_HIGH] < 0x80U) return 0U;
    address = (mysmb_u16)(((mysmb_u16)(game->ram[MYSMB_ENEMY_DATA_HIGH] - 0x80U) << 8U) |
                          game->ram[MYSMB_ENEMY_DATA_LOW]);
    address = (mysmb_u16)(address + game->ram[MYSMB_ENEMY_DATA_OFFSET]);
    while (address < source->prg_size && source->prg[address] != 0xffU) {
        first = source->prg[address];
        /* ROM CheckEndofBuffer permits only power-up ID 0x2e in slot five. */
        if ((first & 0x0fU) != 0x0eU && slot == 5U) {
            if ((mysmb_u16)(address + 1U) >= source->prg_size) return 0U;
            if ((source->prg[address + 1U] & 0x3fU) != 0x2eU) return 0U;
        }
        if ((first & 0x0fU) == 0x0fU && game->ram[MYSMB_ENEMY_OBJECT_PAGE_SELECT] == 0U) {
            if ((mysmb_u16)(address + 1U) >= source->prg_size) return 0U;
            game->ram[MYSMB_ENEMY_OBJECT_PAGE] = (mysmb_u8)(source->prg[address + 1U] & 0x3fU);
            game->ram[MYSMB_ENEMY_OBJECT_PAGE_SELECT] = 1U;
            game->ram[MYSMB_ENEMY_DATA_OFFSET] = (mysmb_u8)(game->ram[MYSMB_ENEMY_DATA_OFFSET] + 2U);
            address = (mysmb_u16)(address + 2U);
            continue;
        }
        if ((mysmb_u16)(address + 1U) >= source->prg_size) return 0U;
        second = source->prg[address + 1U];
        if ((second & 0x80U) != 0U && game->ram[MYSMB_ENEMY_OBJECT_PAGE_SELECT] == 0U) {
            game->ram[MYSMB_ENEMY_OBJECT_PAGE_SELECT]++;
            game->ram[MYSMB_ENEMY_OBJECT_PAGE]++;
        }
        row = (mysmb_u8)(first & 0x0fU);
        /* ROM PositionEnemyObj executes before the row-$0e parser.  Even an
         * area-entry row therefore leaves its page/X in the current inactive
         * ObjectOffset, and an in-range row also writes YHigh/Y before
         * ParseRow0e consumes its third byte. */
        game->ram[MYSMB_ENEMY_PAGE + slot] = game->ram[MYSMB_ENEMY_OBJECT_PAGE];
        game->ram[MYSMB_ENEMY_X + slot] = (mysmb_u8)(first & 0xf0U);
        world = (mysmb_u16)(((mysmb_u16)game->ram[MYSMB_ENEMY_OBJECT_PAGE] << 8U) | (first & 0xf0U));
        right = (mysmb_u16)(((mysmb_u16)game->ram[MYSMB_AREA_SCREEN_RIGHT_PAGE] << 8U) | game->ram[MYSMB_AREA_SCREEN_RIGHT_X]);
        if (world < right) {
            if (row == 0x0eU) {
                if ((mysmb_u16)(address + 2U) >= source->prg_size) return 0U;
                third = source->prg[(mysmb_u16)(address + 2U)];
                if ((third >> 5U) == game->ram[MYSMB_WORLD_NUMBER]) {
                    game->ram[MYSMB_AREA_POINTER] = second;
                    game->ram[MYSMB_AREA_ENTRANCE_PAGE] = (mysmb_u8)(third & 0x1fU);
                }
                game->ram[MYSMB_ENEMY_DATA_OFFSET] =
                    (mysmb_u8)(game->ram[MYSMB_ENEMY_DATA_OFFSET] + 3U);
            }
            else {
                game->ram[MYSMB_ENEMY_DATA_OFFSET] =
                    (mysmb_u8)(game->ram[MYSMB_ENEMY_DATA_OFFSET] + 2U);
            }
            game->ram[MYSMB_ENEMY_OBJECT_PAGE_SELECT] = 0U;
            return 0U;
        }
        if (world > (mysmb_u16)(right + 0x30U))
            return mysmb_enemy_stream_activate_fallback(game, slot);
        game->ram[MYSMB_ENEMY_Y_HIGH + slot] = 1U;
        game->ram[MYSMB_ENEMY_Y + slot] = (mysmb_u8)(row << 4U);
        if (row == 0x0eU) {
            if ((mysmb_u16)(address + 2U) >= source->prg_size) return 0U;
            third = source->prg[(mysmb_u16)(address + 2U)];
            if ((third >> 5U) == game->ram[MYSMB_WORLD_NUMBER]) {
                game->ram[MYSMB_AREA_POINTER] = second;
                game->ram[MYSMB_AREA_ENTRANCE_PAGE] = (mysmb_u8)(third & 0x1fU);
            }
            game->ram[MYSMB_ENEMY_DATA_OFFSET] =
                (mysmb_u8)(game->ram[MYSMB_ENEMY_DATA_OFFSET] + 3U);
            game->ram[MYSMB_ENEMY_OBJECT_PAGE_SELECT] = 0U;
            return 0U;
        }
        if ((second & 0x40U) != 0U && game->ram[MYSMB_SECONDARY_HARD] == 0U) {
            game->ram[MYSMB_ENEMY_DATA_OFFSET] =
                (mysmb_u8)(game->ram[MYSMB_ENEMY_DATA_OFFSET] + 2U);
            game->ram[MYSMB_ENEMY_OBJECT_PAGE_SELECT] = 0U;
            return 0U;
        }
        if ((second & 0x3fU) >= 0x37U && (second & 0x3fU) < 0x3fU) {
            mysmb_enemy_stream_handle_group(game, (mysmb_u8)(second & 0x3fU));
            game->ram[MYSMB_ENEMY_DATA_OFFSET] =
                (mysmb_u8)(game->ram[MYSMB_ENEMY_DATA_OFFSET] + 2U);
            game->ram[MYSMB_ENEMY_OBJECT_PAGE_SELECT] = 0U;
            return 1U;
        }
        /* $12 remains the separately admitted Lakitu/Spiny controller.
         * $14 follows InitEnemyObject, which dispatches the current slot. */
        if ((second & 0x3fU) == 18U) {
            game->ram[MYSMB_ENEMY_FRENZY_BUFFER] = (mysmb_u8)(second & 0x3fU);
            game->ram[MYSMB_ENEMY_DATA_OFFSET] =
                (mysmb_u8)(game->ram[MYSMB_ENEMY_DATA_OFFSET] + 2U);
            game->ram[MYSMB_ENEMY_OBJECT_PAGE_SELECT] = 0U;
            return 1U;
        }

        id = (mysmb_u8)(second & 0x3fU);
        if (id == 6U && game->ram[MYSMB_PRIMARY_HARD] != 0U) id = 2U;
        mysmb_enemy_initialize_loaded(game, slot, row, id);
        game->ram[MYSMB_ENEMY_DATA_OFFSET] = (mysmb_u8)(game->ram[MYSMB_ENEMY_DATA_OFFSET] + 2U);
        game->ram[MYSMB_ENEMY_OBJECT_PAGE_SELECT] = 0U;
        return 1U;
    }
    return mysmb_enemy_stream_activate_fallback(game, slot);
}
/* Convenience probe for isolated tests.  GameEngine must enter the current
 * ObjectOffset directly through mysmb_enemy_stream_process_current. */
mysmb_u8 mysmb_enemy_stream_process_next(struct mysmb_game *game,
                                         const struct mysmb_area_source *source)
{
    mysmb_u8 slot;

    for (slot = 0U; slot < 5U; ++slot) {
        if (game->ram[MYSMB_ENEMY_FLAG + slot] == 0U) {
            return mysmb_enemy_stream_process_current(game, source, slot);
        }
    }
    return 0U;
}

/* Translation of ROM $9c03-$9c2b (LoadAreaPointer/GetAreaDataAddrs).
 * ROM CPU addresses are converted to NROM PRG offsets at this owner boundary. */
