#include "game/enemy/stream.h"

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
    MYSMB_ENEMY_FRENZY_BUFFER = 0x06cbU
};

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

    if (source == 0 || source->prg == 0 || game->ram[MYSMB_ENEMY_DATA_HIGH] < 0x80U) return 0U;
    address = (mysmb_u16)(((mysmb_u16)(game->ram[MYSMB_ENEMY_DATA_HIGH] - 0x80U) << 8U) |
                          game->ram[MYSMB_ENEMY_DATA_LOW]);
    address = (mysmb_u16)(address + game->ram[MYSMB_ENEMY_DATA_OFFSET]);
    while (address < source->prg_size && source->prg[address] != 0xffU) {
        first = source->prg[address];
        /* ROM CheckEndofBuffer rejects ordinary records in slot five. */
        if ((first & 0x0fU) != 0x0eU && slot == 5U) return 0U;
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
        if (row >= 0x0eU || ((second & 0x40U) != 0U && game->ram[MYSMB_SECONDARY_HARD] == 0U)) {
            /* ROM ParseRow0e consumes a three-byte area-entry record.  It
             * preserves its destination for a later pipe entry only when
             * the record's three high bits select this world. */
            if (row == 0x0eU) {
                if ((mysmb_u16)(address + 2U) >= source->prg_size) return 0U;
                third = source->prg[(mysmb_u16)(address + 2U)];
                if ((third >> 5U) == game->ram[MYSMB_WORLD_NUMBER]) {
                    game->ram[MYSMB_AREA_POINTER] = second;
                    game->ram[MYSMB_AREA_ENTRANCE_PAGE] = (mysmb_u8)(third & 0x1fU);
                }
            }
            game->ram[MYSMB_ENEMY_DATA_OFFSET] = (mysmb_u8)(game->ram[MYSMB_ENEMY_DATA_OFFSET] + (row == 0x0eU ? 3U : 2U));
            game->ram[MYSMB_ENEMY_OBJECT_PAGE_SELECT] = 0U;
            return 0U;
        }
        /* ROM PositionEnemyObj writes the current ObjectOffset before bounds. */
        game->ram[MYSMB_ENEMY_PAGE + slot] = game->ram[MYSMB_ENEMY_OBJECT_PAGE];
        game->ram[MYSMB_ENEMY_X + slot] = (mysmb_u8)(first & 0xf0U);
        world = (mysmb_u16)(((mysmb_u16)game->ram[MYSMB_ENEMY_OBJECT_PAGE] << 8U) | (first & 0xf0U));
        right = (mysmb_u16)(((mysmb_u16)game->ram[MYSMB_AREA_SCREEN_RIGHT_PAGE] << 8U) | game->ram[MYSMB_AREA_SCREEN_RIGHT_X]);
        if (world > (mysmb_u16)(right + 0x30U)) return 0U;
        /* ProcessEnemyData writes the current ObjectOffset's page/X before
         * the right-boundary decision.  A record already left of the active
         * right edge is not spawned, but CheckThreeBytes still consumes it.
         * Leaving EnemyDataOffset unchanged here pins the stream to an old
         * object until a slot happens to free, which then shifts every later
         * spawn and visible OAM state. */
        if (world < right) {

            game->ram[MYSMB_ENEMY_DATA_OFFSET] =
                (mysmb_u8)(game->ram[MYSMB_ENEMY_DATA_OFFSET] + 2U);
            game->ram[MYSMB_ENEMY_OBJECT_PAGE_SELECT] = 0U;
            return 0U;
        }
        /* ROM InitEnemyFrenzy routes IDs $12 and $14 to persistent frenzy
         * controllers.  Neither byte denotes an ordinary stream enemy. */
        if ((second & 0x3fU) == 18U || (second & 0x3fU) == 20U) {
            game->ram[MYSMB_ENEMY_FRENZY_BUFFER] = (mysmb_u8)(second & 0x3fU);
            game->ram[MYSMB_ENEMY_DATA_OFFSET] =
                (mysmb_u8)(game->ram[MYSMB_ENEMY_DATA_OFFSET] + 2U);
            game->ram[MYSMB_ENEMY_OBJECT_PAGE_SELECT] = 0U;
            return 1U;
        }

        game->ram[MYSMB_ENEMY_Y_HIGH + slot] = 1U;
        game->ram[MYSMB_ENEMY_Y + slot] = (mysmb_u8)((row << 4U) + 8U);
        game->ram[MYSMB_ENEMY_ID + slot] = (mysmb_u8)(second & 0x3fU);
        /* ROM CheckpointEnemyID marks ordinary objects before their first
         * RunNormalEnemies pass. */
        if (game->ram[MYSMB_ENEMY_ID + slot] < 0x15U) {
            game->ram[0x03d8U + slot] = 1U;
        }
        game->ram[MYSMB_ENEMY_FLAG + slot] = 1U;
        game->ram[MYSMB_ENEMY_STATE + slot] = game->ram[MYSMB_ENEMY_ID + slot] == 3U ? 1U : 0U;
        game->ram[MYSMB_ENEMY_X_SPEED + slot] = game->ram[MYSMB_PRIMARY_HARD] != 0U ? 0xf4U : 0xf8U;
        game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] = 2U;
        game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 0U;
        game->ram[MYSMB_ENEMY_Y_FORCE + slot] = 0U;
        game->ram[MYSMB_ENEMY_BOUND_BOX + slot] = 3U;
        /* InitGoomba calls InitNormalEnemy, then SmallBBox. */
        if (game->ram[MYSMB_ENEMY_ID + slot] == 6U) {
            game->ram[MYSMB_ENEMY_BOUND_BOX + slot] = 9U;
        }
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
