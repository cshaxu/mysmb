#include "game/score.h"
#include "game/oam/oam.h"
#include "game/objects.h"
#include "core/area.h"
#include "core/status.h"

enum {
    MYSMB_FLAG_ENEMY_FLAG = 0x000fU, MYSMB_FLAG_ENEMY_ID = 0x0016U,
    MYSMB_FLAG_ENEMY_PAGE = 0x006eU, MYSMB_FLAG_ENEMY_X = 0x0087U,
    MYSMB_FLAG_ENEMY_Y = 0x00cfU, MYSMB_FLAG_ENEMY_Y_DUMMY = 0x0417U,
    MYSMB_FLAG_ENEMY_OFFSCREEN = 0x03d1U, MYSMB_FLAG_ENEMY_REL_X = 0x03aeU,
    MYSMB_FLAG_ENEMY_REL_Y = 0x03b9U, MYSMB_FLAG_ENEMY_SPRITE_OFFSET = 0x06e5U,
    MYSMB_FLAG_OBJECT_OFFSET = 0x0008U,
    MYSMB_FLAG_GAME_SUBROUTINE = 0x000eU, MYSMB_FLAG_PLAYER_STATE = 0x001dU,
    MYSMB_FLAG_PLAYER_Y = 0x00ceU, MYSMB_FLAG_CURRENT_PLAYER = 0x0753U,
    MYSMB_FLAG_DIGIT_MODIFIER = 0x0134U,
    MYSMB_FLAG_FNUM_Y = 0x010dU, MYSMB_FLAG_FNUM_Y_DUMMY = 0x010eU,
    MYSMB_FLAG_SCORE = 0x010fU, MYSMB_FLAG_COLLISION_Y = 0x070fU
};

void mysmb_objects_start_flagpole(struct mysmb_game *game, mysmb_u8 page,
                                  mysmb_u8 x)
{
    mysmb_u8 flag_x;

    flag_x = (mysmb_u8)(x - 8U);
    game->ram[MYSMB_FLAG_ENEMY_X + 5U] = flag_x;
    game->ram[MYSMB_FLAG_ENEMY_PAGE + 5U] =
        (mysmb_u8)(page - (x < 8U ? 1U : 0U));
    game->ram[MYSMB_FLAG_ENEMY_Y + 5U] = 0x30U;
    game->ram[MYSMB_FLAG_FNUM_Y] = 0xb0U;
    game->ram[MYSMB_FLAG_ENEMY_ID + 5U] = 48U;
    game->ram[MYSMB_FLAG_ENEMY_FLAG + 5U]++;
}

/* ROM $e541 FlagpoleScoreNumTiles through $e5b2 ChkFlagOffscreen. */
void mysmb_objects_draw_flagpole_graphics(struct mysmb_game *game)
{
    static const mysmb_u8 score_tiles[10] = {
        0xf9U, 0x50U, 0xf7U, 0x50U, 0xfaU,
        0xfbU, 0xf8U, 0xfbU, 0xf6U, 0xfbU
    };
    mysmb_u8 slot;
    mysmb_u8 oam;
    mysmb_u8 x;
    mysmb_u8 y;
    mysmb_u8 carry;
    mysmb_u8 index;
    mysmb_u8 graphics_index;
    mysmb_u8 score_oam;

    slot = game->ram[MYSMB_FLAG_OBJECT_OFFSET];
    oam = game->ram[MYSMB_FLAG_ENEMY_SPRITE_OFFSET + slot];
    x = game->ram[MYSMB_FLAG_ENEMY_REL_X];
    game->ram[(mysmb_u16)(0x0203U + oam)] = x;
    x = (mysmb_u8)(x + 8U);
    game->ram[(mysmb_u16)(0x0207U + oam)] = x;
    game->ram[(mysmb_u16)(0x020bU + oam)] = x;
    carry = x >= 0xf4U ? 1U : 0U;
    game->ram[0x0005U] = (mysmb_u8)(x + 12U);
    y = game->ram[MYSMB_FLAG_ENEMY_Y + slot];
    mysmb_oam_dump_two_sprites(game, y, oam);
    /* DumpTwoSpr preserves carry from the preceding X ADC #$0c. */
    game->ram[(mysmb_u16)(0x0208U + oam)] = (mysmb_u8)(
        y + 8U + carry);
    /* $e56c-$e575 initializes DrawOneSpriteRow's scratch arguments before
     * testing FlagpoleCollisionYPos. */
    game->ram[0x0002U] = game->ram[MYSMB_FLAG_FNUM_Y];
    game->ram[0x0003U] = 1U;
    game->ram[0x0004U] = 1U;
    game->ram[(mysmb_u16)(0x0202U + oam)] = game->ram[0x0004U];
    game->ram[(mysmb_u16)(0x0206U + oam)] = game->ram[0x0004U];
    game->ram[(mysmb_u16)(0x020aU + oam)] = game->ram[0x0004U];
    game->ram[(mysmb_u16)(0x0201U + oam)] = 0x7eU;
    game->ram[(mysmb_u16)(0x0209U + oam)] = 0x7eU;
    game->ram[(mysmb_u16)(0x0205U + oam)] = 0x7fU;
    if (game->ram[MYSMB_FLAG_COLLISION_Y] != 0U) {
        index = (mysmb_u8)(game->ram[MYSMB_FLAG_SCORE] << 1U);
        game->ram[0x0000U] = score_tiles[index];
        graphics_index = index;
        score_oam = (mysmb_u8)(oam + 12U);
        mysmb_oam_draw_one_sprite_row(game, score_tiles[index + 1U],
            &graphics_index, &score_oam);
    }
    slot = game->ram[MYSMB_FLAG_OBJECT_OFFSET];
    oam = game->ram[MYSMB_FLAG_ENEMY_SPRITE_OFFSET + slot];
    if ((game->ram[MYSMB_FLAG_ENEMY_OFFSCREEN] & 0x0eU) != 0U)
        mysmb_oam_move_six_sprites_offscreen(game, oam);
    mysmb_text_observer_record(game, MYSMB_TEXT_OBSERVE_FLAG,
        0U, slot, game->ram[MYSMB_FLAG_SCORE], 1U, oam,
        game->ram[MYSMB_FLAG_COLLISION_Y] != 0U ? 5U : 3U, 0U);
}

void mysmb_objects_step_flagpole(struct mysmb_game *game)
{
    static const mysmb_u8 score_modifiers[5] = { 5U, 2U, 8U, 4U, 1U };
    static const mysmb_u8 score_digits[5] = { 3U, 3U, 4U, 4U, 4U };
    mysmb_u8 carry, score_index;

    /* FlagpoleRoutine: LDX #$05 / STX ObjectOffset precedes its ID check. */
    game->ram[MYSMB_FLAG_OBJECT_OFFSET] = 5U;
    if (game->ram[MYSMB_FLAG_ENEMY_ID + 5U] != 48U) return;
    if (game->ram[MYSMB_FLAG_GAME_SUBROUTINE] == 4U &&
        game->ram[MYSMB_FLAG_PLAYER_STATE] == 3U) {
        if (game->ram[MYSMB_FLAG_ENEMY_Y + 5U] >= 0xaaU ||
            game->ram[MYSMB_FLAG_PLAYER_Y] >= 0xa2U) {
            score_index = game->ram[MYSMB_FLAG_SCORE];
            game->ram[MYSMB_FLAG_DIGIT_MODIFIER + score_digits[score_index]] =
                score_modifiers[score_index];
            (void)mysmb_score_add(game);
            game->ram[MYSMB_FLAG_GAME_SUBROUTINE] = 5U;
        } else {
            carry = game->ram[MYSMB_FLAG_ENEMY_Y_DUMMY + 5U] != 0U ? 1U : 0U;
            game->ram[MYSMB_FLAG_ENEMY_Y_DUMMY + 5U]--;
            game->ram[MYSMB_FLAG_ENEMY_Y + 5U] = (mysmb_u8)(
                game->ram[MYSMB_FLAG_ENEMY_Y + 5U] + 1U + carry);
            carry = game->ram[MYSMB_FLAG_FNUM_Y_DUMMY] == 0xffU ? 1U : 0U;
            game->ram[MYSMB_FLAG_FNUM_Y_DUMMY]++;
            game->ram[MYSMB_FLAG_FNUM_Y] = (mysmb_u8)(
                game->ram[MYSMB_FLAG_FNUM_Y] - 1U - (carry == 0U ? 1U : 0U));
        }
    }
    /* ROM FPGfx writes fixed Enemy_OffscreenBits then calls
     * RelativeEnemyPosition with ObjectOffset=$05. */
    mysmb_oam_get_enemy_offscreen_bits(game, 5U);
    mysmb_oam_relative_enemy_position(game, 5U);
    mysmb_objects_draw_flagpole_graphics(game);
}

