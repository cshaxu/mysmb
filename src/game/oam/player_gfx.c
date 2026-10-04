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
    MYSMB_CHANGE_SIZE_OFFSET_ADDER = 0x709cU,
    MYSMB_SWIM_KICK_TILE_NUM = 0x6ee7U,
    MYSMB_SWIM_KICK_TABLE_END = 0x6ee9U,
    MYSMB_SWIM_TILE_REP_OFFSET = 0x6eb5U,
    MYSMB_INTERMEDIATE_PLAYER_DATA = 0x6f9eU,
    MYSMB_INTERMEDIATE_PLAYER_DATA_END = 0x6fa4U
};

/* ROM GetGfxOffsetAdder/SzOfs and GetOffsetFromAnimCtrl.  The third
 * 6502 ASL supplies ADC's carry from source bit five. */
static mysmb_u8 mysmb_oam_get_gfx_offset_adder(struct mysmb_game *game,
                                                mysmb_u8 action)
{
    if (game->ram[MYSMB_PLAYER_SIZE] != 0U)
        action = (mysmb_u8)(action + 8U);
    return action;
}

static mysmb_u8 mysmb_oam_get_offset_from_anim_ctrl(struct mysmb_game *game,
                                                     mysmb_u8 action,
                                                     mysmb_u8 frame)
{
    mysmb_u8 shifted;
    mysmb_u8 carry;
    shifted = (mysmb_u8)(frame << 3U);
    carry = (mysmb_u8)((frame & 0x20U) != 0U);
    return (mysmb_u8)(game->area_prg[MYSMB_PLAYER_GFX_TABLE_OFFSETS + action] +
                      shifted + carry);
}

/* ROM ProcessPlayerAction through ExAnimC.  The source table remains in the
 * owner-local PRG binding, rather than becoming tracked C data. */
mysmb_u8 mysmb_oam_process_player_action(struct mysmb_game *game)
{
    mysmb_u8 action;
    mysmb_u8 animation;
    mysmb_u8 extent;
    mysmb_u8 animated;
    mysmb_u8 offset;

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
    action = mysmb_oam_get_gfx_offset_adder(game, action);
    offset = game->area_prg[MYSMB_PLAYER_GFX_TABLE_OFFSETS + action];
    /* ROM ActionFalling jumps straight from GetCurrentAnimOffset to
     * GetOffsetFromAnimCtrl.  It retains PlayerAnimCtrl and does not run
     * AnimationControl, so the fall frame is the one selected while rising. */
    if (game->ram[MYSMB_PLAYER_STATE] == 2U) {
        return mysmb_oam_get_offset_from_anim_ctrl(game, action,
            game->ram[MYSMB_PLAYER_ANIMATION]);
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
    /* AnimationControl stores its frame extent in zero-page $00 before
     * reading the current offset, even while the timer is running. */
    game->ram[0x0000U] = extent;
    animation = game->ram[MYSMB_PLAYER_ANIMATION];
    offset = mysmb_oam_get_offset_from_anim_ctrl(game, action, animation);
    if (game->ram[MYSMB_PLAYER_ANIM_TIMER] == 0U) {
        game->ram[MYSMB_PLAYER_ANIM_TIMER] = game->ram[MYSMB_PLAYER_ANIM_TIMER_SET];
        animation++;
        if (animation >= extent) animation = 0U;
        game->ram[MYSMB_PLAYER_ANIMATION] = animation;
    }
    return offset;
}

/* ROM HandleChangeSize through ShrPlF.  The twenty source bytes are read
 * from the bound owner PRG at $f09c rather than copied into tracked C. */
mysmb_u8 mysmb_oam_handle_change_size(struct mysmb_game *game)
{
    mysmb_u8 action;
    mysmb_u8 animation;
    mysmb_u8 adder;

    animation = game->ram[MYSMB_PLAYER_ANIMATION];
    if ((game->ram[MYSMB_PLAYER_FRAME_COUNTER] & 3U) == 0U) {
        animation++;
        if (animation >= 10U) {
            animation = 0U;
            game->ram[MYSMB_PLAYER_CHANGE_SIZE] = 0U;
        }
        game->ram[MYSMB_PLAYER_ANIMATION] = animation;
    }
    if (game->ram[MYSMB_PLAYER_SIZE] == 0U) {
        adder = game->area_prg[MYSMB_CHANGE_SIZE_OFFSET_ADDER + animation];
        return mysmb_oam_get_offset_from_anim_ctrl(game, 15U, adder);
    }
    animation = (mysmb_u8)(animation + 10U);
    adder = game->area_prg[MYSMB_CHANGE_SIZE_OFFSET_ADDER + animation];
    action = adder == 0U ? 1U : 9U;
    return game->area_prg[MYSMB_PLAYER_GFX_TABLE_OFFSETS + action];
}

/* ROM PlayerGfxHandler death and size-change branches precede the
 * ProcessPlayerAction call. */
static mysmb_u8 mysmb_oam_player_select_gfx(struct mysmb_game *game)
{
    if (game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] == 0x0bU) {
        return game->area_prg[MYSMB_PLAYER_GFX_TABLE_OFFSETS + 14U];
    }
    if (game->ram[MYSMB_PLAYER_CHANGE_SIZE] != 0U)
        return mysmb_oam_handle_change_size(game);
    return mysmb_oam_process_player_action(game);
}

/* ROM GetPlayerOffscreenBits.  Keep this entry distinct from the graphics
 * handler: VictoryMode reaches RelativePlayerPosition and PlayerGfxHandler
 * without this GameEngine-only predecessor. */
void mysmb_oam_get_player_offscreen_bits(struct mysmb_game *game)
{
    mysmb_oam_get_offscreen_bits_set(game, 0U, 0U);
}

/* ROM DrawPlayerLoop is shared by ordinary and intermediate rendering. */
static void mysmb_oam_player_draw_loop(struct mysmb_game *game,
                                       mysmb_u8 tile_index,
                                       mysmb_u8 oam_offset)
{
    do {
        game->ram[0U] = game->area_prg[(mysmb_u16)(
            MYSMB_PLAYER_GRAPHICS_TABLE + tile_index)];
        mysmb_oam_draw_one_sprite_row(game, game->area_prg[(mysmb_u16)(
            MYSMB_PLAYER_GRAPHICS_TABLE + tile_index + 1U)],
            &tile_index, &oam_offset);
        game->ram[7U]--;
    } while (game->ram[7U] != 0U);
}

/* ROM RenderPlayerSub publishes scratch before the shared DrawPlayerLoop. */
static void mysmb_oam_player_render_rows(struct mysmb_game *game,
                                         mysmb_u8 graphics_offset,
                                         mysmb_u8 row_count)
{
    /* RenderPlayerSub publishes these source scratch bytes before
     * DrawPlayerLoop consumes the indexed PlayerGraphicsTable rows. */
    game->ram[7U] = row_count;
    game->ram[MYSMB_PLAYER_POS_FOR_SCROLL] = game->ram[MYSMB_PLAYER_RELATIVE_X];
    game->ram[5U] = game->ram[MYSMB_PLAYER_RELATIVE_X];
    game->ram[2U] = game->ram[MYSMB_PLAYER_RELATIVE_Y];
    game->ram[3U] = game->ram[MYSMB_PLAYER_FACING];
    game->ram[4U] = game->ram[MYSMB_PLAYER_SPRITE_ATTRIBUTES];
    mysmb_oam_player_draw_loop(game, graphics_offset,
        game->ram[MYSMB_PLAYER_SPRITE_OFFSET]);
}

/* ROM ChkForPlayerAttrib through C_S_IGAtt. */
void mysmb_oam_check_player_attributes(struct mysmb_game *game)
{
    mysmb_u8 graphics_offset;
    mysmb_u8 oam_offset;

    graphics_offset = game->ram[MYSMB_PLAYER_GFX_OFFSET];
    oam_offset = game->ram[MYSMB_PLAYER_SPRITE_OFFSET];
    if (game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] == 0x0bU ||
        graphics_offset == 0xc8U) {
        game->ram[(mysmb_u16)(0x0212U + oam_offset)] &= 0x3fU;
        game->ram[(mysmb_u16)(0x0216U + oam_offset)] =
            (mysmb_u8)((game->ram[(mysmb_u16)(0x0216U + oam_offset)] & 0x3fU) |
                      0x40U);
    }
    if (game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] == 0x0bU ||
        graphics_offset == 0x50U || graphics_offset == 0xb8U ||
        graphics_offset == 0xc0U || graphics_offset == 0xc8U) {
        game->ram[(mysmb_u16)(0x021aU + oam_offset)] &= 0x3fU;
        game->ram[(mysmb_u16)(0x021eU + oam_offset)] =
            (mysmb_u8)((game->ram[(mysmb_u16)(0x021eU + oam_offset)] & 0x3fU) |
                      0x40U);
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
    mysmb_u8 swimming_continuation;

    if (game->area_prg == 0 ||
        game->area_prg_size < MYSMB_PLAYER_GRAPHICS_TABLE_END) return;
    if (game->ram[MYSMB_PLAYER_INJURY_TIMER] != 0U &&
        (game->ram[MYSMB_PLAYER_FRAME_COUNTER] & 1U) != 0U) return;
    /* CntPl chooses the swimming return before HandleChangeSize can clear
     * its flag. DoChangeSize jumps away and never reaches that return. */
    swimming_continuation = (mysmb_u8)(
        game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] != 0x0bU &&
        game->ram[MYSMB_PLAYER_CHANGE_SIZE] == 0U &&
        game->ram[MYSMB_SWIMMING] != 0U &&
        game->ram[MYSMB_PLAYER_STATE] != 0U);
    graphics_offset = mysmb_oam_player_select_gfx(game);
    game->ram[MYSMB_PLAYER_GFX_OFFSET] = graphics_offset;
    mysmb_oam_player_render_rows(game, graphics_offset, 4U);
    mysmb_oam_check_player_attributes(game);
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
            /* PROfsLoop shifts its scratch before entering DumpTwoSpr. */
            game->ram[0U] = (mysmb_u8)(offscreen >> 1U);
            mysmb_oam_dump_two_sprites(game, 0xf8U, oam_offset);
        }
        offscreen >>= 1U;
        game->ram[0U] = offscreen;
        oam_offset = (mysmb_u8)(oam_offset - 8U);
    }
    /* PlayerGfxHandler's swimming continuation follows FindPlayerAction,
     * not the ordinary render return path.  The two source bytes at $eee7
     * select the seventh/eighth sprite kick tile. */
    if (swimming_continuation != 0U &&
        (game->ram[MYSMB_PLAYER_FRAME_COUNTER] & 4U) == 0U &&
        game->area_prg_size >= MYSMB_SWIM_KICK_TABLE_END) {
        mysmb_u8 kick_offset;
        mysmb_u8 tile_index;
        kick_offset = (mysmb_u8)(game->ram[MYSMB_PLAYER_SPRITE_OFFSET] +
            ((game->ram[MYSMB_PLAYER_FACING] & 1U) == 0U ? 4U : 0U));
        tile_index = 0U;
        if (game->ram[MYSMB_PLAYER_SIZE] != 0U) {
            if (game->ram[(mysmb_u16)(0x0219U + kick_offset)] ==
                game->area_prg[MYSMB_SWIM_TILE_REP_OFFSET]) {
                mysmb_text_observer_record(game, MYSMB_TEXT_OBSERVE_PLAYER,
                    game->ram[0x0753U], 0U, graphics_offset,
                    game->ram[MYSMB_PLAYER_FACING],
                    game->ram[MYSMB_PLAYER_SPRITE_OFFSET], 8U,
                    game->ram[MYSMB_PLAYER_SIZE]);
                return;
            }
            tile_index = 1U;
        }
        game->ram[(mysmb_u16)(0x0219U + kick_offset)] =
            game->area_prg[MYSMB_SWIM_KICK_TILE_NUM + tile_index];
    }
    mysmb_text_observer_record(game, MYSMB_TEXT_OBSERVE_PLAYER,
        game->ram[0x0753U], 0U, graphics_offset,
        game->ram[MYSMB_PLAYER_FACING],
        game->ram[MYSMB_PLAYER_SPRITE_OFFSET], 8U,
        game->ram[MYSMB_PLAYER_SIZE]);
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

    if (game->area_prg == 0 ||
        game->area_prg_size < MYSMB_INTERMEDIATE_PLAYER_DATA_END) return;
    /* Original PIntLoop copies six PRG data bytes into $02-$07 in
     * reverse index order before the shared DrawPlayerLoop. */
    for (row = 6U; row != 0U; ) {
        row--;
        game->ram[(mysmb_u16)(2U + row)] =
            game->area_prg[(mysmb_u16)(MYSMB_INTERMEDIATE_PLAYER_DATA + row)];
    }
    mysmb_oam_player_draw_loop(game, 0xb8U, 4U);
    /* The source reads the next sprite's attribute at +36 and stores its
     * horizontal-flip result in the preceding sprite at +32. */
    game->ram[0x0222U] = (mysmb_u8)(game->ram[0x0226U] | 0x40U);
}

