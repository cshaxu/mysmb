#include "game/oam/oam.h"
#include "game/player.h"

enum {
    MYSMB_PLAYER_X_SPEED = 0x0057U,
    MYSMB_PLAYER_PAGE = 0x006dU,
    MYSMB_PLAYER_X = 0x0086U,
    MYSMB_PLAYER_Y_SPEED = 0x009fU,
    MYSMB_PLAYER_Y_HIGH = 0x00b5U,
    MYSMB_PLAYER_Y = 0x00ceU,
    MYSMB_PLAYER_STATE = 0x001dU,
    MYSMB_PLAYER_X_SPEED_ABSOLUTE = 0x0700U,
    MYSMB_SWIMMING = 0x0704U,
    MYSMB_PLAYER_CHANGE_SIZE = 0x070bU,
    MYSMB_FIREBALL_THROWING_TIMER = 0x0711U,
    MYSMB_PLAYER_ANIM_TIMER_SET = 0x070cU,
    MYSMB_PLAYER_ANIMATION = 0x070dU,
    MYSMB_PLAYER_CROUCHING = 0x0714U,
    MYSMB_PLAYER_LEFT_RIGHT_BUTTONS = 0x000cU,
    MYSMB_PLAYER_MOVING_DIRECTION = 0x0045U,
    MYSMB_PLAYER_SIZE = 0x0754U,
    MYSMB_PLAYER_POS_FOR_SCROLL = 0x0755U,
    MYSMB_GAME_ENGINE_SUBROUTINE = 0x000eU,
    MYSMB_PLAYER_FACING = 0x0033U,
    MYSMB_PLAYER_SPRITE_ATTRIBUTES = 0x03c4U,
    MYSMB_SCREEN_LEFT_X = 0x071cU,
    MYSMB_PLAYER_RELATIVE_X = 0x03adU,
    MYSMB_PLAYER_RELATIVE_Y = 0x03b8U,
    MYSMB_PLAYER_OFFSCREEN_BITS = 0x03d0U,
    MYSMB_PLAYER_GFX_OFFSET = 0x06d5U,
    MYSMB_PLAYER_SPRITE_OFFSET = 0x06e4U,
    MYSMB_PLAYER_INJURY_TIMER = 0x079eU,
    MYSMB_PLAYER_ANIM_TIMER = 0x0781U,
    MYSMB_JUMP_SWIM_TIMER = 0x0782U,
    MYSMB_A_B_BUTTONS = 0x000aU,
    MYSMB_PLAYER_FRAME_COUNTER = 0x0009U,
    MYSMB_PLAYER_GFX_TABLE_OFFSETS = 0x6e07U,
    MYSMB_PLAYER_GRAPHICS_TABLE = 0x6e17U,
    MYSMB_PLAYER_GRAPHICS_TABLE_END = 0x6ee7U,
    MYSMB_SWIM_KICK_TILE_NUM = 0x6ee7U,
    MYSMB_SWIM_KICK_TABLE_END = 0x6ee9U,
    MYSMB_SWIM_TILE_REP_OFFSET = 0x6eb5U,
    MYSMB_INTERMEDIATE_PLAYER_DATA = 0x6f9eU,
    MYSMB_INTERMEDIATE_PLAYER_DATA_END = 0x6fa4U
};
/* ROM $ee35-$ef25 action selection.  The source table remains in the
 * owner-local PRG binding, rather than becoming tracked C data. */
static mysmb_u8 mysmb_oam_player_select_gfx(struct mysmb_game *game)
{
    mysmb_u8 action;
    mysmb_u8 animation;
    mysmb_u8 extent;
    mysmb_u8 animated;
    mysmb_u8 offset;

    if (game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] == 0x0bU) {
        return game->area_prg[MYSMB_PLAYER_GFX_TABLE_OFFSETS + 14U];
    }
    if (game->ram[MYSMB_PLAYER_CHANGE_SIZE] != 0U) {
        static const mysmb_u8 change_size_offset[20] = {
            0U, 1U, 0U, 1U, 0U, 1U, 2U, 0U, 1U, 2U,
            2U, 0U, 2U, 0U, 2U, 0U, 2U, 0U, 2U, 0U
        };

        animation = game->ram[MYSMB_PLAYER_ANIMATION];
        if ((game->ram[MYSMB_PLAYER_FRAME_COUNTER] & 3U) == 0U) {
            animation++;
            if (animation == 10U) {
                animation = 0U;
                game->ram[MYSMB_PLAYER_CHANGE_SIZE] = 0U;
            }
            game->ram[MYSMB_PLAYER_ANIMATION] = animation;
        }
        if (game->ram[MYSMB_PLAYER_SIZE] == 0U) {
            return (mysmb_u8)(game->area_prg[MYSMB_PLAYER_GFX_TABLE_OFFSETS + 15U] +
                change_size_offset[animation] * 8U);
        }
        animation = (mysmb_u8)(animation + 10U);
        action = change_size_offset[animation] == 0U ? 1U : 9U;
        return game->area_prg[MYSMB_PLAYER_GFX_TABLE_OFFSETS + action];
    }
    action = 2U;
    animated = 0U;
    extent = 0U;
    if (game->ram[MYSMB_PLAYER_STATE] == 3U) {
        action = 5U;
        if (game->ram[MYSMB_PLAYER_Y_SPEED] != 0U) {
            animated = 1U;
            extent = 2U;
        }
    }
    else if (game->ram[MYSMB_PLAYER_STATE] == 2U) {
        action = 4U;
        animated = 1U;
        extent = 0U;
    }
    else if (game->ram[MYSMB_PLAYER_STATE] == 1U) {
        if (game->ram[MYSMB_SWIMMING] != 0U) {
            action = 1U;
            animated = 1U;
            extent = 3U;
        }
        else if (game->ram[MYSMB_PLAYER_CROUCHING] != 0U) {
            action = 6U;
        }
        else {
            action = 0U;
        }
    }
    else if (game->ram[MYSMB_PLAYER_CROUCHING] != 0U) {
        action = 6U;
    }
    else if (game->ram[MYSMB_PLAYER_X_SPEED] != 0U ||
             game->ram[MYSMB_PLAYER_LEFT_RIGHT_BUTTONS] != 0U) {
        action = 4U;
        if (game->ram[MYSMB_PLAYER_X_SPEED_ABSOLUTE] >= 9U &&
            (game->ram[MYSMB_PLAYER_MOVING_DIRECTION] &
             game->ram[MYSMB_PLAYER_FACING]) == 0U) action = 3U;
        if (action == 4U) {
            animated = 1U;
            extent = 3U;
        }
    }
    if (game->ram[MYSMB_PLAYER_SIZE] != 0U) action = (mysmb_u8)(action + 8U);
    offset = game->area_prg[MYSMB_PLAYER_GFX_TABLE_OFFSETS + action];
    /* ROM ActionFalling jumps straight from GetCurrentAnimOffset to
     * GetOffsetFromAnimCtrl.  It retains PlayerAnimCtrl and does not run
     * AnimationControl, so the fall frame is the one selected while rising. */
    if (game->ram[MYSMB_PLAYER_STATE] == 2U) {
        return (mysmb_u8)(offset + game->ram[MYSMB_PLAYER_ANIMATION] * 8U);
    }
    /* ActionSwimming goes to GetCurrentAnimOffset without advancing the
     * animation unless JumpSwimTimer, PlayerAnimCtrl or button A is set. */
    if (game->ram[MYSMB_PLAYER_STATE] == 1U &&
        game->ram[MYSMB_SWIMMING] != 0U &&
        game->ram[MYSMB_JUMP_SWIM_TIMER] == 0U &&
        game->ram[MYSMB_PLAYER_ANIMATION] == 0U &&
        (game->ram[MYSMB_A_B_BUTTONS] & MYSMB_BUTTON_A) == 0U)
        return offset;
    if (animated == 0U) {
        game->ram[MYSMB_PLAYER_ANIMATION] = 0U;
        return offset;
    }
    animation = game->ram[MYSMB_PLAYER_ANIMATION];
    offset = (mysmb_u8)(offset + animation * 8U);
    if (game->ram[MYSMB_PLAYER_ANIM_TIMER] == 0U) {
        game->ram[MYSMB_PLAYER_ANIM_TIMER] = game->ram[MYSMB_PLAYER_ANIM_TIMER_SET];
        animation++;
        if (animation >= extent) animation = 0U;
        game->ram[MYSMB_PLAYER_ANIMATION] = animation;
    }
    return offset;
}

/* ROM DrawSpriteObject: write a two-sprite OAM row and advance the row. */
static void mysmb_oam_player_draw_row(struct mysmb_game *game, mysmb_u8 *oam_offset,
                                  mysmb_u8 *y, mysmb_u8 x, mysmb_u8 left_tile,
                                  mysmb_u8 right_tile, mysmb_u8 attributes,
                                  mysmb_u8 facing)
{
    mysmb_u16 first;
    mysmb_u16 second;

    first = (mysmb_u16)(0x0200U + *oam_offset);
    second = (mysmb_u16)(first + 4U);
    if (facing == MYSMB_BUTTON_LEFT) {
        game->ram[(mysmb_u16)(first + 1U)] = right_tile;
        game->ram[(mysmb_u16)(second + 1U)] = left_tile;
        attributes = (mysmb_u8)(attributes | 0x40U);
    }
    else {
        game->ram[(mysmb_u16)(first + 1U)] = left_tile;
        game->ram[(mysmb_u16)(second + 1U)] = right_tile;
    }
    game->ram[first] = *y;
    game->ram[second] = *y;
    game->ram[(mysmb_u16)(first + 2U)] = attributes;
    game->ram[(mysmb_u16)(second + 2U)] = attributes;
    game->ram[(mysmb_u16)(first + 3U)] = x;
    game->ram[(mysmb_u16)(second + 3U)] = (mysmb_u8)(x + 8U);
    *y = (mysmb_u8)(*y + 8U);
    *oam_offset = (mysmb_u8)(*oam_offset + 8U);
}

/* ROM GetPlayerOffscreenBits.  GetOffScreenBitsSet combines the horizontal
 * low nibble and vertical high nibble before PlayerGfxHandler writes OAM. */
static mysmb_u8 mysmb_oam_player_get_offscreen_bits(const struct mysmb_game *game)
{
    static const mysmb_u8 x_offscreen_bits[16] = {
        0x7fU, 0x3fU, 0x1fU, 0x0fU, 0x07U, 0x03U, 0x01U, 0x00U,
        0x80U, 0xc0U, 0xe0U, 0xf0U, 0xf8U, 0xfcU, 0xfeU, 0xffU
    };
    static const mysmb_u8 y_offscreen_bits[9] = {
        0x00U, 0x08U, 0x0cU, 0x0eU, 0x0fU, 0x07U, 0x03U, 0x01U, 0x00U
    };
    static const mysmb_u8 default_x[3] = { 0x07U, 0x0fU, 0x07U };
    static const mysmb_u8 default_y[3] = { 0x04U, 0x00U, 0x04U };
    static const mysmb_u8 vertical_edge[2] = { 0xffU, 0x00U };
    mysmb_u8 edge;
    mysmb_u8 difference;
    mysmb_u8 borrow;
    mysmb_u8 page_difference;
    mysmb_u8 index;
    mysmb_u8 x_bits;
    mysmb_u8 y_bits;

    x_bits = 0U;
    edge = 1U;
    for (;;) {
        difference = (mysmb_u8)(game->ram[(mysmb_u16)(0x071cU + edge)] -
                                game->ram[MYSMB_PLAYER_X]);
        borrow = game->ram[(mysmb_u16)(0x071cU + edge)] <
            game->ram[MYSMB_PLAYER_X] ? 1U : 0U;
        page_difference = (mysmb_u8)(game->ram[(mysmb_u16)(0x071aU + edge)] -
                                      game->ram[MYSMB_PLAYER_PAGE] - borrow);
        index = default_x[edge];
        if ((page_difference & 0x80U) == 0U) {
            index = default_x[(mysmb_u8)(edge + 1U)];
            if (page_difference == 0U && difference < 0x38U) {
                index = (mysmb_u8)(difference >> 3U);
                if (edge == 0U) index = (mysmb_u8)(index + 8U);
            }
        }
        x_bits = x_offscreen_bits[index];
        if (x_bits != 0U || edge == 0U) break;
        edge--;
    }

    y_bits = 0U;
    edge = 1U;
    for (;;) {
        difference = (mysmb_u8)(vertical_edge[edge] - game->ram[MYSMB_PLAYER_Y]);
        borrow = vertical_edge[edge] < game->ram[MYSMB_PLAYER_Y] ? 1U : 0U;
        page_difference = (mysmb_u8)(1U - game->ram[MYSMB_PLAYER_Y_HIGH] - borrow);
        index = default_y[edge];
        if ((page_difference & 0x80U) == 0U) {
            index = default_y[(mysmb_u8)(edge + 1U)];
            if (page_difference == 0U && difference < 0x20U) {
                index = (mysmb_u8)(difference >> 3U);
                if (edge == 0U) index = (mysmb_u8)(index + 4U);
            }
        }
        y_bits = y_offscreen_bits[index];
        if (y_bits != 0U || edge == 0U) break;
        edge--;
    }
    return (mysmb_u8)((x_bits >> 4U) | (y_bits << 4U));
}
/* ROM GetPlayerOffscreenBits.  Keep this entry distinct from the graphics
 * handler: VictoryMode reaches RelativePlayerPosition and PlayerGfxHandler
 * without this GameEngine-only predecessor. */
void mysmb_oam_get_player_offscreen_bits(struct mysmb_game *game)
{
    game->ram[MYSMB_PLAYER_OFFSCREEN_BITS] =
        mysmb_oam_player_get_offscreen_bits(game);
}

/* ROM RenderPlayerSub/DrawPlayerLoop: consume a selected graphics offset and
 * publish the source scratch while drawing the requested top rows. */
static void mysmb_oam_player_render_rows(struct mysmb_game *game,
                                         mysmb_u8 graphics_offset,
                                         mysmb_u8 row_count)
{
    mysmb_u8 row;
    mysmb_u8 oam_offset;
    mysmb_u8 y;
    mysmb_u8 attributes;
    oam_offset = game->ram[MYSMB_PLAYER_SPRITE_OFFSET];
    y = game->ram[MYSMB_PLAYER_RELATIVE_Y];
    attributes = game->ram[MYSMB_PLAYER_SPRITE_ATTRIBUTES];
    /* RenderPlayerSub publishes these source scratch bytes before
     * DrawPlayerLoop consumes the indexed PlayerGraphicsTable rows. */
    game->ram[MYSMB_PLAYER_POS_FOR_SCROLL] = game->ram[MYSMB_PLAYER_RELATIVE_X];
    game->ram[5U] = game->ram[MYSMB_PLAYER_RELATIVE_X];
    game->ram[2U] = y;
    game->ram[3U] = game->ram[MYSMB_PLAYER_FACING];
    game->ram[4U] = attributes;
    game->ram[7U] = row_count;
    for (row = 0U; row < row_count; ++row) {
        game->ram[0U] = game->area_prg[(mysmb_u16)(
            MYSMB_PLAYER_GRAPHICS_TABLE + graphics_offset + row * 2U)];
        game->ram[1U] = game->area_prg[(mysmb_u16)(
            MYSMB_PLAYER_GRAPHICS_TABLE + graphics_offset + row * 2U + 1U)];
        mysmb_oam_player_draw_row(game, &oam_offset, &y,
            game->ram[MYSMB_PLAYER_RELATIVE_X],
            game->ram[0U], game->ram[1U],
            attributes, game->ram[MYSMB_PLAYER_FACING]);
        game->ram[2U] = y;
        game->ram[7U]--;
    }
}

/* ROM PlayerGfxHandler and its PlayerGfxProcessing/RenderPlayerSub tail.
 * The caller owns the source-order relative-position and offscreen-bit calls. */
void mysmb_oam_render_player(struct mysmb_game *game)
{
    mysmb_u8 graphics_offset;
    mysmb_u8 row;
    mysmb_u8 oam_offset;
    mysmb_u8 offscreen;

    if (game->area_prg == 0 ||
        game->area_prg_size < MYSMB_PLAYER_GRAPHICS_TABLE_END) return;
    if (game->ram[MYSMB_PLAYER_INJURY_TIMER] != 0U &&
        (game->ram[MYSMB_PLAYER_FRAME_COUNTER] & 1U) != 0U) return;
    graphics_offset = mysmb_oam_player_select_gfx(game);
    game->ram[MYSMB_PLAYER_GFX_OFFSET] = graphics_offset;
    mysmb_oam_player_render_rows(game, graphics_offset, 4U);
    oam_offset = game->ram[MYSMB_PLAYER_SPRITE_OFFSET];
    if (game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] == 0x0bU ||
        graphics_offset == 0xc8U) {
        oam_offset = (mysmb_u8)(oam_offset + 16U);
        game->ram[(mysmb_u16)(0x0202U + oam_offset)] &= 0x3fU;
        game->ram[(mysmb_u16)(0x0206U + oam_offset)] =
            (mysmb_u8)((game->ram[(mysmb_u16)(0x0206U + oam_offset)] & 0x3fU) |
                      0x40U);
    }
    if (game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] == 0x0bU ||
        graphics_offset == 0x50U || graphics_offset == 0xb8U ||
        graphics_offset == 0xc0U || graphics_offset == 0xc8U) {
        oam_offset = (mysmb_u8)(game->ram[MYSMB_PLAYER_SPRITE_OFFSET] + 24U);
        game->ram[(mysmb_u16)(0x0202U + oam_offset)] &= 0x3fU;
        game->ram[(mysmb_u16)(0x0206U + oam_offset)] =
            (mysmb_u8)((game->ram[(mysmb_u16)(0x0206U + oam_offset)] & 0x3fU) |
                      0x40U);
    }
    if (game->ram[MYSMB_FIREBALL_THROWING_TIMER] != 0U) {
        mysmb_u8 animation_timer;
        mysmb_u8 throw_timer;
        mysmb_u8 rows;
        animation_timer = game->ram[MYSMB_PLAYER_ANIM_TIMER];
        throw_timer = game->ram[MYSMB_FIREBALL_THROWING_TIMER];
        game->ram[MYSMB_FIREBALL_THROWING_TIMER] = 0U;
        if (animation_timer < throw_timer) {
            game->ram[MYSMB_FIREBALL_THROWING_TIMER] = animation_timer;
            graphics_offset = game->area_prg[MYSMB_PLAYER_GFX_TABLE_OFFSETS + 7U];
            game->ram[MYSMB_PLAYER_GFX_OFFSET] = graphics_offset;
            rows = (game->ram[MYSMB_PLAYER_X_SPEED] |
                    game->ram[MYSMB_PLAYER_LEFT_RIGHT_BUTTONS]) == 0U ? 4U : 3U;
            mysmb_oam_player_render_rows(game, graphics_offset, rows);
        }
    }
    /* PlayerOffscreenChk consumes the vertical nibble prepared by the source
     * offscreen route.  Preserve its one-row-at-a-time mask when present. */
    offscreen = (mysmb_u8)(game->ram[MYSMB_PLAYER_OFFSCREEN_BITS] >> 4U);
    game->ram[0U] = offscreen;
    oam_offset = (mysmb_u8)(game->ram[MYSMB_PLAYER_SPRITE_OFFSET] + 24U);
    for (row = 0U; row < 4U; ++row) {
        if ((offscreen & 1U) != 0U) {
            game->ram[(mysmb_u16)(0x0200U + oam_offset)] = 0xf8U;
            game->ram[(mysmb_u16)(0x0204U + oam_offset)] = 0xf8U;
        }
        offscreen >>= 1U;
        game->ram[0U] = offscreen;
        oam_offset = (mysmb_u8)(oam_offset - 8U);
    }
    /* PlayerGfxHandler's swimming continuation follows FindPlayerAction,
     * not the ordinary render return path.  The two source bytes at $eee7
     * select the seventh/eighth sprite kick tile. */
    if (game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] != 0x0bU &&
        game->ram[MYSMB_PLAYER_CHANGE_SIZE] == 0U &&
        game->ram[MYSMB_SWIMMING] != 0U &&
        game->ram[MYSMB_PLAYER_STATE] != 0U &&
        (game->ram[MYSMB_PLAYER_FRAME_COUNTER] & 4U) == 0U &&
        game->area_prg_size >= MYSMB_SWIM_KICK_TABLE_END) {
        mysmb_u8 kick_offset;
        mysmb_u8 tile_index;
        kick_offset = (mysmb_u8)(game->ram[MYSMB_PLAYER_SPRITE_OFFSET] + 24U +
            ((game->ram[MYSMB_PLAYER_FACING] & 1U) == 0U ? 4U : 0U));
        tile_index = 0U;
        if (game->ram[MYSMB_PLAYER_SIZE] != 0U) {
            if (game->ram[(mysmb_u16)(0x0201U + kick_offset)] ==
                game->area_prg[MYSMB_SWIM_TILE_REP_OFFSET]) return;
            tile_index = 1U;
        }
        game->ram[(mysmb_u16)(0x0201U + kick_offset)] =
            game->area_prg[MYSMB_SWIM_KICK_TILE_NUM + tile_index];
    }
}

/* GameEngine convenience only.  Its original order is
 * GetPlayerOffscreenBits, RelativePlayerPosition, PlayerGfxHandler.  Callers
 * such as VictoryMode must use the three individual entries above instead. */
void mysmb_oam_draw_player(struct mysmb_game *game)
{
    mysmb_oam_get_player_offscreen_bits(game);
    mysmb_oam_relative_player_position(game);
    mysmb_oam_render_player(game);
}

void mysmb_oam_draw_intermediate_player(struct mysmb_game *game)
{
    mysmb_u8 row;
    mysmb_u8 oam_offset;
    mysmb_u8 y;

    if (game->area_prg == 0 ||
        game->area_prg_size < MYSMB_INTERMEDIATE_PLAYER_DATA_END) return;
    /* Original PIntLoop copies six PRG data bytes into $02-$07 in
     * reverse index order before the shared DrawPlayerLoop. */
    for (row = 6U; row != 0U; ) {
        row--;
        game->ram[(mysmb_u16)(2U + row)] =
            game->area_prg[(mysmb_u16)(MYSMB_INTERMEDIATE_PLAYER_DATA + row)];
    }
    oam_offset = 4U;
    y = game->ram[2U];
    for (row = 0U; row < 4U; ++row) {
        game->ram[0U] = game->area_prg[(mysmb_u16)(
            MYSMB_PLAYER_GRAPHICS_TABLE + 0xb8U + row * 2U)];
        game->ram[1U] = game->area_prg[(mysmb_u16)(
            MYSMB_PLAYER_GRAPHICS_TABLE + 0xb8U + row * 2U + 1U)];
        mysmb_oam_player_draw_row(game, &oam_offset, &y, game->ram[5U],
            game->ram[0U], game->ram[1U],
            game->ram[4U], game->ram[3U]);
        game->ram[2U] = y;
        game->ram[7U]--;
    }
    /* The source reads the next sprite's attribute at +36 and stores its
     * horizontal-flip result in the preceding sprite at +32. */
    game->ram[0x0222U] = (mysmb_u8)(game->ram[0x0226U] | 0x40U);
}

