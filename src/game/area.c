#include "game/area.h"
#include "game/objects.h"

enum {
    MYSMB_AREA_SCREEN_LEFT_PAGE = 0x071aU,
    MYSMB_AREA_SCREEN_RIGHT_PAGE = 0x071bU,
    MYSMB_AREA_SCREEN_LEFT_X = 0x071cU,
    MYSMB_AREA_SCREEN_RIGHT_X = 0x071dU,
    MYSMB_AREA_COLUMN_SETS = 0x071eU,
    MYSMB_AREA_NT_HIGH = 0x0720U,
    MYSMB_AREA_NT_LOW = 0x0721U,
    MYSMB_AREA_CURRENT_PAGE = 0x0725U,
    MYSMB_AREA_BACKLOADING = 0x0728U,
    MYSMB_AREA_OBJECT_LENGTH = 0x0730U,
    MYSMB_AREA_SCROLL_X = 0x073fU,
    MYSMB_AREA_SCROLL_Y = 0x0740U,
    MYSMB_AREA_TIMERS = 0x0780U,
    MYSMB_AREA_DISABLE_SCREEN = 0x0774U,
    MYSMB_AREA_OPER_MODE_TASK = 0x0772U,
    MYSMB_AREA_BLOCK_COLUMN = 0x06a0U
};

enum {
    MYSMB_AREA_POINTER = 0x0750U,
    MYSMB_AREA_TYPE = 0x074eU,
    MYSMB_AREA_LOW_OFFSET = 0x074fU,
    MYSMB_AREA_DATA_LOW = 0x00e7U,
    MYSMB_AREA_DATA_HIGH = 0x00e8U,
    MYSMB_ENEMY_DATA_LOW = 0x00e9U,
    MYSMB_ENEMY_DATA_HIGH = 0x00eaU,
    MYSMB_WORLD_NUMBER = 0x075fU,
    MYSMB_AREA_NUMBER = 0x0760U,
    MYSMB_ROM_WORLD_OFFSETS = 0x1cb4U,
    MYSMB_ROM_AREA_OFFSETS = 0x1cbcU,
    MYSMB_ROM_ENEMY_HIGH_OFFSETS = 0x1ce0U,
    MYSMB_ROM_ENEMY_LOW = 0x1ce4U,
    MYSMB_ROM_ENEMY_HIGH = 0x1d06U,
    MYSMB_ROM_AREA_HIGH_OFFSETS = 0x1d28U,
    MYSMB_ROM_AREA_LOW = 0x1d2cU,
    MYSMB_ROM_AREA_HIGH = 0x1d4eU
};

enum {
    MYSMB_AREA_ENTRANCE = 0x0710U,
    MYSMB_AREA_TIMER_SETTING = 0x0715U,
    MYSMB_AREA_TERRAIN = 0x0727U,
    MYSMB_AREA_STYLE = 0x0733U,
    MYSMB_AREA_FOREGROUND = 0x0741U,
    MYSMB_AREA_BACKGROUND = 0x0742U,
    MYSMB_AREA_CLOUD_OVERRIDE = 0x0743U,
    MYSMB_AREA_BACKGROUND_COLOR = 0x0744U
};

enum {
    MYSMB_AREA_PARSER_BEHIND = 0x0729U,
    MYSMB_AREA_OBJECT_PAGE = 0x072aU,
    MYSMB_AREA_OBJECT_PAGE_SELECT = 0x072bU,
    MYSMB_AREA_DATA_OFFSET = 0x072cU
};

enum {
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
    MYSMB_ENEMY_FRENZY_BUFFER = 0x06cbU
};

/* Translation of ROM InitializeArea within the $92b0 area task route.
 * Header and stream reads are deliberately owned by the following T3 part. */
void mysmb_area_initialize(struct mysmb_game *game)
{
    mysmb_u8 index;

    mysmb_game_initialize_memory(game, 0x4bU);
    for (index = 0U; index < 0x22U; ++index) {
        game->ram[(mysmb_u16)(MYSMB_AREA_TIMERS + index)] = 0U;
    }
    game->ram[MYSMB_AREA_SCREEN_LEFT_PAGE] = 0U;
    game->ram[MYSMB_AREA_CURRENT_PAGE] = 0U;
    game->ram[MYSMB_AREA_BACKLOADING] = 0U;
    game->ram[MYSMB_AREA_SCREEN_LEFT_X] = 0U;
    game->ram[MYSMB_AREA_SCREEN_RIGHT_PAGE] = 1U;
    game->ram[MYSMB_AREA_SCREEN_RIGHT_X] = 0U;
    game->ram[MYSMB_AREA_NT_HIGH] = 0x20U;
    game->ram[MYSMB_AREA_NT_LOW] = 0x80U;
    game->ram[MYSMB_AREA_BLOCK_COLUMN] = 0U;
    game->ram[MYSMB_AREA_OBJECT_LENGTH] = 0xffU;
    game->ram[(mysmb_u16)(MYSMB_AREA_OBJECT_LENGTH + 1U)] = 0xffU;
    game->ram[(mysmb_u16)(MYSMB_AREA_OBJECT_LENGTH + 2U)] = 0xffU;
    game->ram[MYSMB_AREA_COLUMN_SETS] = 0x0bU;
    game->ram[MYSMB_AREA_SCROLL_X] = 0U;
    game->ram[MYSMB_AREA_SCROLL_Y] = 0U;
    game->ram[MYSMB_AREA_DISABLE_SCREEN] = 1U;
    game->ram[MYSMB_AREA_OPER_MODE_TASK]++;
}

void mysmb_game_bind_area_source(struct mysmb_game *game,
                                 const mysmb_u8 *prg, mysmb_u16 prg_size)
{
    game->area_prg = prg;
    game->area_prg_size = prg_size;
}

/* One neutral command per game frame, derived from the original area stream. */
mysmb_u8 mysmb_area_emit_next_command(struct mysmb_game *game)
{
    struct mysmb_area_source source;
    struct mysmb_area_object object;
    struct mysmb_area_command *command;

    if (game->area_prg == 0 || game->area_command_count >= 16U) {
        return 0U;
    }
    source.prg = game->area_prg;
    source.prg_size = game->area_prg_size;
    if (mysmb_area_next_object(game, &source, &object) == 0U) {
        return 0U;
    }
    command = &game->area_commands[game->area_command_count];
    command->column = object.column;
    command->row = object.row;
    command->page = object.page;
    command->dispatch_id = object.dispatch_id;
    game->area_command_count++;
    return 1U;
}

/* ROM $c0f7-$c1f4 ProcessEnemyData through InitNormalEnemy, limited to
 * ordinary enemy IDs.  Special objects retain their dedicated initializers. */
mysmb_u8 mysmb_area_spawn_next_enemy(struct mysmb_game *game,
                                     const struct mysmb_area_source *source)
{
    mysmb_u16 address;
    mysmb_u16 world;
    mysmb_u16 right;
    mysmb_u8 first;
    mysmb_u8 second;
    mysmb_u8 slot;
    mysmb_u8 row;

    if (source == 0 || source->prg == 0 || game->ram[MYSMB_ENEMY_DATA_HIGH] < 0x80U) return 0U;
    address = (mysmb_u16)(((mysmb_u16)(game->ram[MYSMB_ENEMY_DATA_HIGH] - 0x80U) << 8U) |
                          game->ram[MYSMB_ENEMY_DATA_LOW]);
    address = (mysmb_u16)(address + game->ram[MYSMB_ENEMY_DATA_OFFSET]);
    while (address < source->prg_size && source->prg[address] != 0xffU) {
        first = source->prg[address];
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
        if ((second & 0x80U) != 0U && game->ram[MYSMB_ENEMY_OBJECT_PAGE_SELECT] == 0U) game->ram[MYSMB_ENEMY_OBJECT_PAGE]++;
        row = (mysmb_u8)(first & 0x0fU);
        if (row >= 0x0eU || ((second & 0x40U) != 0U && game->ram[MYSMB_SECONDARY_HARD] == 0U)) {
            game->ram[MYSMB_ENEMY_DATA_OFFSET] = (mysmb_u8)(game->ram[MYSMB_ENEMY_DATA_OFFSET] + (row == 0x0eU ? 3U : 2U));
            game->ram[MYSMB_ENEMY_OBJECT_PAGE_SELECT] = 0U;
            return 0U;
        }
        world = (mysmb_u16)(((mysmb_u16)game->ram[MYSMB_ENEMY_OBJECT_PAGE] << 8U) | (first & 0xf0U));
        right = (mysmb_u16)(((mysmb_u16)game->ram[MYSMB_AREA_SCREEN_RIGHT_PAGE] << 8U) | game->ram[MYSMB_AREA_SCREEN_RIGHT_X]);
        if (world > (mysmb_u16)(right + 0x30U)) return 0U;
        if (world < right) return 0U;
        /* ROM InitEnemyFrenzy routes IDs $12 and $14 to persistent frenzy
         * controllers.  Neither byte denotes an ordinary stream enemy. */
        if ((second & 0x3fU) == 18U || (second & 0x3fU) == 20U) {
            game->ram[MYSMB_ENEMY_FRENZY_BUFFER] = (mysmb_u8)(second & 0x3fU);
            game->ram[MYSMB_ENEMY_DATA_OFFSET] =
                (mysmb_u8)(game->ram[MYSMB_ENEMY_DATA_OFFSET] + 2U);
            game->ram[MYSMB_ENEMY_OBJECT_PAGE_SELECT] = 0U;
            return 1U;
        }
        for (slot = 0U; slot < 5U && game->ram[MYSMB_ENEMY_FLAG + slot] != 0U; ++slot) {}
        if (slot == 5U) return 0U;
        game->ram[MYSMB_ENEMY_PAGE + slot] = game->ram[MYSMB_ENEMY_OBJECT_PAGE];
        game->ram[MYSMB_ENEMY_X + slot] = (mysmb_u8)(first & 0xf0U);
        game->ram[MYSMB_ENEMY_Y_HIGH + slot] = 1U;
        game->ram[MYSMB_ENEMY_Y + slot] = (mysmb_u8)((row << 4U) + 8U);
        game->ram[MYSMB_ENEMY_ID + slot] = (mysmb_u8)(second & 0x3fU);
        game->ram[MYSMB_ENEMY_FLAG + slot] = 1U;
        game->ram[MYSMB_ENEMY_STATE + slot] = game->ram[MYSMB_ENEMY_ID + slot] == 3U ? 1U : 0U;
        game->ram[MYSMB_ENEMY_X_SPEED + slot] = game->ram[MYSMB_PRIMARY_HARD] != 0U ? 0xf4U : 0xf8U;
        game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] = 2U;
        game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 0U;
        game->ram[MYSMB_ENEMY_Y_FORCE + slot] = 0U;
        game->ram[MYSMB_ENEMY_BOUND_BOX + slot] = 3U;
        /* ROM InitHammerBro.  Its independent movement route owns the
         * jump/throw timers after this source-side object initialization. */
        if (game->ram[MYSMB_ENEMY_ID + slot] == 5U) {
            game->ram[MYSMB_ENEMY_X_SPEED + slot] = 0U;
            game->ram[0x03a2U + slot] = 0U;
            game->ram[0x0796U + slot] =
                game->ram[MYSMB_SECONDARY_HARD] != 0U ? 0x50U : 0x80U;
            game->ram[MYSMB_ENEMY_BOUND_BOX + slot] = 0x0bU;
        }
        if (game->ram[MYSMB_ENEMY_ID + slot] == 8U) {
            game->ram[MYSMB_ENEMY_X_SPEED + slot] = 0U;
            game->ram[MYSMB_ENEMY_BOUND_BOX + slot] = 9U;
        }
        if (game->ram[MYSMB_ENEMY_ID + slot] == 13U) {
            game->ram[MYSMB_ENEMY_X_SPEED + slot] = 1U;
            game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 0U;
            game->ram[MYSMB_ENEMY_Y_FORCE + slot] = game->ram[MYSMB_ENEMY_Y + slot];
            game->ram[MYSMB_ENEMY_Y_DUMMY + slot] =
                (mysmb_u8)(game->ram[MYSMB_ENEMY_Y + slot] - 0x18U);
            game->ram[MYSMB_ENEMY_BOUND_BOX + slot] = 9U;
        }
        if (game->ram[MYSMB_ENEMY_ID + slot] == 10U ||
            game->ram[MYSMB_ENEMY_ID + slot] == 11U) {
            game->ram[MYSMB_ENEMY_X_SPEED + slot] = 0U;
            game->ram[MYSMB_ENEMY_X_FORCE + slot] = 0U;
            game->ram[MYSMB_ENEMY_Y_DUMMY + slot] = 0U;
            game->ram[MYSMB_ENEMY_Y_FORCE + slot] = game->ram[MYSMB_ENEMY_Y + slot];
            game->ram[MYSMB_ENEMY_BOUND_BOX + slot] = 9U;
        }
        if (game->ram[MYSMB_ENEMY_ID + slot] == 12U) {
            game->ram[MYSMB_ENEMY_Y_HIGH + slot] = 2U;
            game->ram[MYSMB_ENEMY_Y + slot] = 2U;
            game->ram[0x0796U + slot] = 1U;
            game->ram[MYSMB_ENEMY_STATE + slot] = 0U;
            game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 0U;
            game->ram[MYSMB_ENEMY_Y_FORCE + slot] = 0U;
            game->ram[MYSMB_ENEMY_BOUND_BOX + slot] = 9U;
        }
        if (game->ram[MYSMB_ENEMY_ID + slot] == 7U) {
            game->ram[MYSMB_ENEMY_X_SPEED + slot] = 0U;
            game->ram[MYSMB_ENEMY_BOUND_BOX + slot] = 9U;
        }
        if (game->ram[MYSMB_ENEMY_ID + slot] == 14U) {
            game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] = 2U;
            game->ram[MYSMB_ENEMY_X_SPEED + slot] = 0xf8U;
            game->ram[MYSMB_ENEMY_BOUND_BOX + slot] = 3U;
        }
        if (game->ram[MYSMB_ENEMY_ID + slot] == 15U) {
            game->ram[MYSMB_ENEMY_X_FORCE + slot] = game->ram[MYSMB_ENEMY_Y + slot];
            game->ram[MYSMB_ENEMY_X_SPEED + slot] = (mysmb_u8)(
                game->ram[MYSMB_ENEMY_Y + slot] +
                (game->ram[MYSMB_ENEMY_Y + slot] < 0x80U ? 0x30U : 0xe0U));
            game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] = 2U;
            game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 0U;
            game->ram[MYSMB_ENEMY_Y_FORCE + slot] = 0U;
            game->ram[MYSMB_ENEMY_BOUND_BOX + slot] = 3U;
        }
        if (game->ram[MYSMB_ENEMY_ID + slot] == 16U) {
            game->ram[MYSMB_ENEMY_X_SPEED + slot] = 0U;
            game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 0U;
            game->ram[MYSMB_ENEMY_Y_FORCE + slot] = 0U;
            game->ram[MYSMB_ENEMY_BOUND_BOX + slot] = 3U;
        }
        /* ROM InitLakitu -> SetupLakitu -> InitHorizFlySwimEnemy/TallBBox2. */
        if (game->ram[MYSMB_ENEMY_ID + slot] == 17U) {
            game->ram[MYSMB_ENEMY_X_SPEED + slot] = 0U;
            game->ram[0x06d1U] = 0U;
            game->ram[MYSMB_ENEMY_BOUND_BOX + slot] = 3U;
        }
        /* ROM InitShortFirebar/InitLongFirebar.  The long variant's
         * duplicate slot is OAM-only; its physical balls share this anchor. */
        if (game->ram[MYSMB_ENEMY_ID + slot] >= 27U &&
            game->ram[MYSMB_ENEMY_ID + slot] <= 31U) {
            static const mysmb_u8 spin_speed[5] = { 0x28U, 0x38U, 0x28U, 0x38U, 0x28U };
            static const mysmb_u8 spin_direction[5] = { 0U, 0U, 0x10U, 0x10U, 0U };
            mysmb_u8 old_x = game->ram[MYSMB_ENEMY_X + slot];
            mysmb_u8 index = (mysmb_u8)(game->ram[MYSMB_ENEMY_ID + slot] - 27U);
            game->ram[MYSMB_ENEMY_X_SPEED + slot] = 0U;
            game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 0U;
            game->ram[MYSMB_FIREBAR_SPIN_SPEED + slot] = spin_speed[index];
            game->ram[MYSMB_FIREBAR_SPIN_DIRECTION + slot] = spin_direction[index];
            game->ram[MYSMB_ENEMY_Y + slot] = (mysmb_u8)(game->ram[MYSMB_ENEMY_Y + slot] + 4U);
            game->ram[MYSMB_ENEMY_X + slot] = (mysmb_u8)(old_x + 4U);
            if (game->ram[MYSMB_ENEMY_X + slot] < old_x) game->ram[MYSMB_ENEMY_PAGE + slot]++;
            game->ram[MYSMB_ENEMY_BOUND_BOX + slot] = 3U;
        }
        /* ROM InitBalPlatform through InitSmallPlatform.  The drawing-only
         * rope partner is absent; each physical deck keeps its 6502 state. */
        if (game->ram[MYSMB_ENEMY_ID + slot] >= 36U &&
            game->ram[MYSMB_ENEMY_ID + slot] <= 44U) {
            mysmb_u8 platform_id;
            mysmb_u8 old_x;

            platform_id = game->ram[MYSMB_ENEMY_ID + slot];
            game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 0U;
            game->ram[MYSMB_ENEMY_Y_FORCE + slot] = 0U;
            game->ram[MYSMB_ENEMY_Y_DUMMY + slot] = 0U;
            game->ram[MYSMB_ENEMY_X_FORCE + slot] = 0U;
            game->ram[MYSMB_ENEMY_BOUND_BOX + slot] =
                (platform_id == 43U || platform_id == 44U) ? 4U : 5U;
            if (platform_id != 43U && platform_id != 44U &&
                game->ram[MYSMB_AREA_TYPE] != 3U &&
                game->ram[MYSMB_SECONDARY_HARD] == 0U) {
                game->ram[MYSMB_ENEMY_BOUND_BOX + slot] = 6U;
            }
            if (platform_id == 38U || platform_id == 39U) {
                game->ram[MYSMB_ENEMY_BOUND_BOX + slot] = 5U;
            }
            if (platform_id == 36U) {
                old_x = game->ram[MYSMB_ENEMY_X + slot];
                game->ram[MYSMB_ENEMY_Y + slot] =
                    (mysmb_u8)(game->ram[MYSMB_ENEMY_Y + slot] - 2U);
                if (game->ram[MYSMB_SECONDARY_HARD] == 0U) {
                    game->ram[MYSMB_ENEMY_X + slot] = (mysmb_u8)(old_x - 8U);
                    if (old_x < 8U) game->ram[MYSMB_ENEMY_PAGE + slot]--;
                    old_x = game->ram[MYSMB_ENEMY_X + slot];
                }
                game->ram[MYSMB_ENEMY_X + slot] = (mysmb_u8)(old_x + 8U);
                if (game->ram[MYSMB_ENEMY_X + slot] < old_x) game->ram[MYSMB_ENEMY_PAGE + slot]++;
                game->ram[MYSMB_ENEMY_STATE + slot] = game->ram[MYSMB_BALANCE_PLATFORM_ALIGNMENT];
                game->ram[MYSMB_BALANCE_PLATFORM_ALIGNMENT] =
                    game->ram[MYSMB_BALANCE_PLATFORM_ALIGNMENT] >= 0x80U ? slot : 0xffU;
                game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] = 0U;
            }
            else if (platform_id == 37U) {
                game->ram[MYSMB_PLATFORM_TOP_Y + slot] = game->ram[MYSMB_ENEMY_Y + slot];
                game->ram[MYSMB_PLATFORM_CENTER_Y + slot] =
                    (mysmb_u8)(game->ram[MYSMB_ENEMY_Y + slot] + 0x40U);
                if (game->ram[MYSMB_ENEMY_Y + slot] >= 0x80U) {
                    game->ram[MYSMB_ENEMY_Y + slot] = 0xc0U;
                }
            }
            else if (platform_id == 38U || platform_id == 43U) {
                game->ram[MYSMB_ENEMY_Y_FORCE + slot] = 0x10U;
                game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 0xffU;
            }
            else if (platform_id == 39U || platform_id == 44U) {
                game->ram[MYSMB_ENEMY_Y_FORCE + slot] = 0xf0U;
                game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 0U;
            }
            else if (platform_id == 40U || platform_id == 42U) {
                game->ram[MYSMB_ENEMY_X_SPEED + slot] = 0x10U;
                game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] = 2U;
            }
            else if (platform_id == 41U) {
                game->ram[MYSMB_PLATFORM_COLLISION_FLAG + slot] = 0xffU;
            }
        }
        /* ROM InitBowser, excluding its OAM-only duplicate rear half. */
        if (game->ram[MYSMB_ENEMY_ID + slot] == 45U) {
            game->ram[MYSMB_BOWSER_BODY_CONTROLS] = 0U;
            game->ram[MYSMB_BOWSER_ORIGIN_X] = game->ram[MYSMB_ENEMY_X + slot];
            game->ram[MYSMB_BOWSER_FLAME_TIMER] = 0U;
            game->ram[MYSMB_BOWSER_BREATH_TIMER] = 0xdfU;
            game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] = 0xdfU;
            game->ram[MYSMB_BOWSER_FEET_TIMER] = 0x20U;
            game->ram[MYSMB_ENEMY_INTERVAL_TIMER + slot] = 0x20U;
            game->ram[MYSMB_BOWSER_HIT_POINTS] = 5U;
            game->ram[MYSMB_BOWSER_MOVE_SPEED] = 2U;
            game->ram[MYSMB_BOWSER_FRONT_SLOT] = slot;
            game->ram[MYSMB_ENEMY_BOUND_BOX + slot] = 10U;
        }
        game->ram[MYSMB_ENEMY_DATA_OFFSET] = (mysmb_u8)(game->ram[MYSMB_ENEMY_DATA_OFFSET] + 2U);
        game->ram[MYSMB_ENEMY_OBJECT_PAGE_SELECT] = 0U;
        return 1U;
    }
    return 0U;
}

/* Translation of ROM $9c03-$9c2b (LoadAreaPointer/GetAreaDataAddrs).
 * ROM CPU addresses are converted to NROM PRG offsets at this owner boundary. */
mysmb_u8 mysmb_area_load_pointers(struct mysmb_game *game,
                                  const struct mysmb_area_source *source)
{
    mysmb_u16 table_index;
    mysmb_u8 area_pointer;
    mysmb_u8 area_type;

    if (source == 0 || source->prg == 0 || source->prg_size < 0x1d70U ||
        game->ram[MYSMB_WORLD_NUMBER] >= 8U) {
        return 0U;
    }
    table_index = (mysmb_u16)(source->prg[(mysmb_u16)(MYSMB_ROM_WORLD_OFFSETS +
                                                       game->ram[MYSMB_WORLD_NUMBER])] +
                               game->ram[MYSMB_AREA_NUMBER]);
    if (table_index >= 0x0041U) {
        return 0U;
    }
    area_pointer = source->prg[(mysmb_u16)(MYSMB_ROM_AREA_OFFSETS + table_index)];
    area_type = (mysmb_u8)((area_pointer & 0x60U) >> 5U);
    table_index = (mysmb_u16)(source->prg[(mysmb_u16)(MYSMB_ROM_ENEMY_HIGH_OFFSETS +
                                                       area_type)] +
                               (area_pointer & 0x1fU));
    if (table_index >= 0x0022U) {
        return 0U;
    }
    game->ram[MYSMB_AREA_POINTER] = area_pointer;
    game->ram[MYSMB_AREA_TYPE] = area_type;
    game->ram[MYSMB_AREA_LOW_OFFSET] = (mysmb_u8)(area_pointer & 0x1fU);
    game->ram[MYSMB_ENEMY_DATA_LOW] = source->prg[(mysmb_u16)(MYSMB_ROM_ENEMY_LOW + table_index)];
    game->ram[MYSMB_ENEMY_DATA_HIGH] = source->prg[(mysmb_u16)(MYSMB_ROM_ENEMY_HIGH + table_index)];
    table_index = (mysmb_u16)(source->prg[(mysmb_u16)(MYSMB_ROM_AREA_HIGH_OFFSETS +
                                                       area_type)] +
                               game->ram[MYSMB_AREA_LOW_OFFSET]);
    if (table_index >= 0x0022U) {
        return 0U;
    }
    game->ram[MYSMB_AREA_DATA_LOW] = source->prg[(mysmb_u16)(MYSMB_ROM_AREA_LOW + table_index)];
    game->ram[MYSMB_AREA_DATA_HIGH] = source->prg[(mysmb_u16)(MYSMB_ROM_AREA_HIGH + table_index)];
    return 1U;
}

/* Translation of the area-header tail of ROM $9c1c-$9c4a. */
mysmb_u8 mysmb_area_parse_header(struct mysmb_game *game,
                                 const struct mysmb_area_source *source)
{
    mysmb_u16 address;
    mysmb_u8 first;
    mysmb_u8 second;
    mysmb_u8 value;

    if (source == 0 || source->prg == 0 || game->ram[MYSMB_AREA_DATA_HIGH] < 0x80U) {
        return 0U;
    }
    address = (mysmb_u16)(((mysmb_u16)(game->ram[MYSMB_AREA_DATA_HIGH] - 0x80U) << 8) |
                           game->ram[MYSMB_AREA_DATA_LOW]);
    if (address >= source->prg_size || (mysmb_u16)(source->prg_size - address) < 2U) {
        return 0U;
    }
    first = source->prg[address];
    second = source->prg[(mysmb_u16)(address + 1U)];
    value = (mysmb_u8)(first & 0x07U);
    game->ram[MYSMB_AREA_BACKGROUND_COLOR] = value >= 4U ? value : 0U;
    game->ram[MYSMB_AREA_FOREGROUND] = value < 4U ? value : 0U;
    game->ram[MYSMB_AREA_ENTRANCE] = (mysmb_u8)((first & 0x38U) >> 3U);
    game->ram[MYSMB_AREA_TIMER_SETTING] = (mysmb_u8)(first >> 6U);
    game->ram[MYSMB_AREA_TERRAIN] = (mysmb_u8)(second & 0x0fU);
    game->ram[MYSMB_AREA_BACKGROUND] = (mysmb_u8)((second & 0x30U) >> 4U);
    value = (mysmb_u8)(second >> 6U);
    game->ram[MYSMB_AREA_CLOUD_OVERRIDE] = value == 3U ? value : 0U;
    game->ram[MYSMB_AREA_STYLE] = value == 3U ? 0U : value;
    address = (mysmb_u16)(address + 2U);
    game->ram[MYSMB_AREA_DATA_LOW] = (mysmb_u8)address;
    game->ram[MYSMB_AREA_DATA_HIGH] = (mysmb_u8)(0x80U + (address >> 8U));
    return 1U;
}

/* ROM AreaParserCore RenderSceneryTerrain through RendBBuf, restricted to the
 * initial 24 columns completed before normal player control.  The two terrain
 * bytes describe the upper eight and lower five metatile rows respectively;
 * their least-significant-bit-first scan is preserved here. */
void mysmb_area_render_initial_terrain(struct mysmb_game *game)
{
    static const mysmb_u8 terrain_metatiles[4] = { 0x69U, 0x54U, 0x52U, 0x62U };
    static const mysmb_u8 terrain_render_bits[32] = {
        0x00U, 0x00U, 0x00U, 0x18U, 0x01U, 0x18U, 0x07U, 0x18U,
        0x0fU, 0x18U, 0xffU, 0x18U, 0x01U, 0x1fU, 0x07U, 0x1fU,
        0x0fU, 0x1fU, 0x81U, 0x1fU, 0x01U, 0x00U, 0x8fU, 0x1fU,
        0xf1U, 0x18U, 0xf9U, 0x18U, 0xf1U, 0x18U, 0xffU, 0x1fU
    };
    mysmb_u8 terrain;
    mysmb_u8 column;
    mysmb_u8 row;
    mysmb_u8 bits;
    mysmb_u16 address;

    terrain = terrain_metatiles[game->ram[MYSMB_AREA_TYPE] & 3U];
    if (game->ram[MYSMB_AREA_CLOUD_OVERRIDE] != 0U) terrain = 0x88U;
    for (column = 0U; column < 24U; ++column) {
        for (row = 0U; row < 13U; ++row) {
            bits = terrain_render_bits[(mysmb_u16)((game->ram[MYSMB_AREA_TERRAIN] & 0x0fU) * 2U +
                                                    (row < 8U ? 0U : 1U))];
            address = (mysmb_u16)(column < 16U ? 0x0500U + column :
                                  0x05d0U + (column - 16U));
            address = (mysmb_u16)(address + (mysmb_u16)row * 16U);
            if ((bits & (mysmb_u8)(1U << (row & 7U))) != 0U) {
                game->ram[address] = terrain;
            }
        }
    }
}

/* Translation of the selection/control portion of ROM $9508-$958f.
 * Each successful call consumes one two-byte stream entry. */
mysmb_u8 mysmb_area_next_object(struct mysmb_game *game,
                                const struct mysmb_area_source *source,
                                struct mysmb_area_object *object)
{
    mysmb_u16 address;
    mysmb_u8 first;
    mysmb_u8 second;

    if (source == 0 || source->prg == 0 || object == 0 ||
        game->ram[MYSMB_AREA_DATA_HIGH] < 0x80U) {
        return 0U;
    }
    address = (mysmb_u16)(((mysmb_u16)(game->ram[MYSMB_AREA_DATA_HIGH] - 0x80U) << 8) |
                           game->ram[MYSMB_AREA_DATA_LOW]);
    address = (mysmb_u16)(address + game->ram[MYSMB_AREA_DATA_OFFSET]);
    if (address >= source->prg_size || (mysmb_u16)(source->prg_size - address) < 2U) {
        return 0U;
    }
    first = source->prg[address];
    if (first == 0xfdU) {
        return 0U;
    }
    second = source->prg[(mysmb_u16)(address + 1U)];
    if ((second & 0x80U) != 0U && game->ram[MYSMB_AREA_OBJECT_PAGE_SELECT] == 0U) {
        game->ram[MYSMB_AREA_OBJECT_PAGE_SELECT]++;
        game->ram[MYSMB_AREA_OBJECT_PAGE]++;
    }
    object->first = first;
    object->second = second;
    object->is_page_control = 0U;
    object->is_loop_command = 0U;
    if ((first & 0x0fU) == 0x0dU && (second & 0x40U) == 0U &&
        game->ram[MYSMB_AREA_OBJECT_PAGE_SELECT] == 0U) {
        game->ram[MYSMB_AREA_OBJECT_PAGE] = (mysmb_u8)(second & 0x1fU);
        game->ram[MYSMB_AREA_OBJECT_PAGE_SELECT]++;
        object->is_page_control = 1U;
    }
    object->page = game->ram[MYSMB_AREA_OBJECT_PAGE];
    object->behind_current_page = object->page < game->ram[MYSMB_AREA_CURRENT_PAGE] ? 1U : 0U;
    mysmb_area_decode_object(object);
    game->ram[MYSMB_AREA_PARSER_BEHIND] = object->behind_current_page;
    game->ram[MYSMB_AREA_DATA_OFFSET] =
        (mysmb_u8)(game->ram[MYSMB_AREA_DATA_OFFSET] + 2U);
    game->ram[MYSMB_AREA_OBJECT_PAGE_SELECT] = 0U;
    return 1U;
}

/* Translation of ROM DecodeAreaData's object-ID selection, before JumpEngine. */
void mysmb_area_decode_object(struct mysmb_area_object *object)
{
    mysmb_u8 code;

    object->column = (mysmb_u8)(object->first >> 4U);
    object->row = (mysmb_u8)(object->first & 0x0fU);
    object->dispatch_id = 0xffU;
    if (object->row == 0x0dU) {
        if ((object->second & 0x40U) == 0U) {
            object->is_page_control = 1U;
            return;
        }
        code = (mysmb_u8)(object->second & 0x3fU);
        object->is_loop_command = (object->second & 0x7fU) == 0x4bU ? 1U : 0U;
        object->dispatch_id = (mysmb_u8)(code + 0x22U);
        return;
    }
    if (object->row == 0x0eU) {
        object->dispatch_id = 0x2eU;
        return;
    }
    if (object->row == 0x0cU) {
        object->dispatch_id = (mysmb_u8)(((object->second & 0x70U) >> 4U) + 0x08U);
        return;
    }
    if (object->row == 0x0fU) {
        object->dispatch_id = (mysmb_u8)(((object->second & 0x70U) >> 4U) + 0x10U);
        return;
    }
    code = (mysmb_u8)((object->second & 0x70U) >> 4U);
    if (code == 0U) {
        object->dispatch_id = (mysmb_u8)((object->second & 0x0fU) + 0x16U);
    }
    else {
        if (code == 7U && (object->second & 0x08U) != 0U) {
            code = 0U;
        }
        object->dispatch_id = code;
    }
}
