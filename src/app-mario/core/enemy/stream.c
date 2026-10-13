#include "core/enemy/stream.h"
#include "core/enemy/init.h"
#include "core/enemy/loop.h"
#include "core/enemy/group.h"

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

/* ROM $C25E Inc2B, also the group handler's tail successor. */
void mysmb_enemy_stream_advance_record(struct mysmb_game *game)
{
    ++game->ram[MYSMB_ENEMY_DATA_OFFSET];
    ++game->ram[MYSMB_ENEMY_DATA_OFFSET];
    game->ram[MYSMB_ENEMY_OBJECT_PAGE_SELECT] = 0U;
}

/* ROM CheckFrenzyBuffer -> StrFre -> InitEnemyObject. */
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
/* Local probe adapter; production enters the current source slot. */
/* The restricted slot probe preserves its legacy five-slot API. */
mysmb_u8 mysmb_enemy_stream_process_slot(struct mysmb_game *game,
                                         const struct mysmb_area_source *source,
                                         mysmb_u8 slot)
{
    if (slot >= 5U || game->ram[MYSMB_ENEMY_FLAG + slot] != 0U) return 0U;
    return mysmb_enemy_stream_process_current(game, source, slot);
}

/* ROM $C144-$C26B. Reads use an eight-bit Y offset, including INY wrap. */
static mysmb_u8 mysmb_enemy_stream_read(const struct mysmb_game *game,
    const struct mysmb_area_source *source, mysmb_u8 offset)
{
    mysmb_u16 address;
    address = (mysmb_u16)(((mysmb_u16)game->ram[MYSMB_ENEMY_DATA_HIGH] << 8U) |
        game->ram[MYSMB_ENEMY_DATA_LOW]);
    address = (mysmb_u16)(address + offset);
    if (address < 0x8000U || (mysmb_u16)(address - 0x8000U) >= source->prg_size)
        return 0xffU;
    return source->prg[(mysmb_u16)(address - 0x8000U)];
}

mysmb_u8 mysmb_enemy_stream_process_current(struct mysmb_game *game,
    const struct mysmb_area_source *source, mysmb_u8 slot)
{
    mysmb_u8 first, second, third, row, id, offset;
    mysmb_u16 extended;
    mysmb_u16 world, right;
    if (source == 0 || source->prg == 0 ||
        game->ram[MYSMB_ENEMY_DATA_HIGH] < 0x80U) return 0U;
    offset = game->ram[MYSMB_ENEMY_DATA_OFFSET];
    first = mysmb_enemy_stream_read(game, source, offset);
    if (first == 0xffU) goto frenzy;
    row = (mysmb_u8)(first & 0x0fU);
    second = mysmb_enemy_stream_read(game, source, (mysmb_u8)(offset + 1U));
    if (row != 0x0eU && slot >= 5U && (second & 0x3fU) != 0x2eU)
        return 0U;
    extended = (mysmb_u16)(game->ram[MYSMB_AREA_SCREEN_RIGHT_X] + 0x30U);
    game->ram[7U] = (mysmb_u8)(extended & 0xf0U);
    game->ram[6U] = (mysmb_u8)(game->ram[MYSMB_AREA_SCREEN_RIGHT_PAGE] +
        (extended > 0xffU ? 1U : 0U));
    if ((second & 0x80U) != 0U && game->ram[MYSMB_ENEMY_OBJECT_PAGE_SELECT] == 0U) {
        ++game->ram[MYSMB_ENEMY_OBJECT_PAGE_SELECT];
        ++game->ram[MYSMB_ENEMY_OBJECT_PAGE];
    }
    if (row == 0x0fU && game->ram[MYSMB_ENEMY_OBJECT_PAGE_SELECT] == 0U) {
        game->ram[MYSMB_ENEMY_OBJECT_PAGE] = (mysmb_u8)(second & 0x3fU);
        ++game->ram[MYSMB_ENEMY_DATA_OFFSET];
        ++game->ram[MYSMB_ENEMY_DATA_OFFSET];
        ++game->ram[MYSMB_ENEMY_OBJECT_PAGE_SELECT];
        /* Original tail JMP re-enters loop commands before the next record. */
        mysmb_enemy_process_loop_command(game, source, slot);
        return game->ram[MYSMB_ENEMY_FLAG + slot] != 0U ? 1U : 0U;
    }
    game->ram[MYSMB_ENEMY_PAGE + slot] = game->ram[MYSMB_ENEMY_OBJECT_PAGE];
    game->ram[MYSMB_ENEMY_X + slot] = (mysmb_u8)(first & 0xf0U);
    world = (mysmb_u16)(((mysmb_u16)game->ram[MYSMB_ENEMY_PAGE + slot] << 8U) |
        game->ram[MYSMB_ENEMY_X + slot]);
    right = (mysmb_u16)(((mysmb_u16)game->ram[MYSMB_AREA_SCREEN_RIGHT_PAGE] << 8U) |
        game->ram[MYSMB_AREA_SCREEN_RIGHT_X]);
    if (world < right) {
        if (row == 0x0eU) goto parse_row;
        goto increment_two;
    }
    extended = (mysmb_u16)(((mysmb_u16)game->ram[6U] << 8U) | game->ram[7U]);
    if (world > extended) goto frenzy;
    game->ram[MYSMB_ENEMY_Y_HIGH + slot] = 1U;
    game->ram[MYSMB_ENEMY_Y + slot] = (mysmb_u8)(first << 4U);
    if (row == 0x0eU) goto parse_row;
    if ((second & 0x40U) != 0U && game->ram[MYSMB_SECONDARY_HARD] == 0U)
        goto increment_two;
    id = (mysmb_u8)(second & 0x3fU);
    if (id >= 0x37U && id < 0x3fU) {
        /* Existing group body retains its separate semantic obligation. */
        mysmb_enemy_stream_handle_group(game, id);
        return 1U;
    }
    if (id == 6U && game->ram[MYSMB_PRIMARY_HARD] != 0U) id = 2U;
    game->ram[MYSMB_ENEMY_ID + slot] = id;
    game->ram[MYSMB_ENEMY_FLAG + slot] = 1U;
    game->ram[MYSMB_ENEMY_STATE + slot] = 0U;
    mysmb_enemy_checkpoint_loaded(game, slot);
    if (game->ram[MYSMB_ENEMY_FLAG + slot] == 0U) return 0U;
    mysmb_enemy_stream_advance_record(game);
    return 1U;
parse_row:
    third = mysmb_enemy_stream_read(game, source, (mysmb_u8)(offset + 2U));
    if ((third >> 5U) == game->ram[MYSMB_WORLD_NUMBER]) {
        game->ram[MYSMB_AREA_POINTER] = second;
        game->ram[MYSMB_AREA_ENTRANCE_PAGE] = (mysmb_u8)(third & 0x1fU);
    }
    ++game->ram[MYSMB_ENEMY_DATA_OFFSET];
increment_two:
    mysmb_enemy_stream_advance_record(game);
    return 0U;
frenzy:
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
