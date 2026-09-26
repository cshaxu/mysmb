#include "game/objects.h"
#include "game/area.h"

enum {
    MYSMB_ENDGAME_ENEMY_FLAG = 0x000fU,
    MYSMB_ENDGAME_ENEMY_ID = 0x0016U,
    MYSMB_ENDGAME_ENEMY_STATE = 0x001eU,
    MYSMB_ENDGAME_ENEMY_PAGE = 0x006eU,
    MYSMB_ENDGAME_ENEMY_X = 0x0087U,
    MYSMB_ENDGAME_ENEMY_Y_HIGH = 0x00b6U,
    MYSMB_ENDGAME_ENEMY_Y = 0x00cfU,
    MYSMB_ENDGAME_ENEMY_X_SPEED = 0x0058U,
    MYSMB_ENDGAME_ENEMY_Y_SPEED = 0x00a0U,
    MYSMB_ENDGAME_ENEMY_Y_FORCE = 0x0434U,
    MYSMB_ENDGAME_ENEMY_SPRITE_OFFSET = 0x06e5U,
    MYSMB_ENDGAME_SCREEN_LEFT_X = 0x071cU,
    MYSMB_ENDGAME_FRENZY_BUFFER = 0x06cbU,
    MYSMB_ENDGAME_FIREWORKS_COUNTER = 0x06d7U,
    MYSMB_ENDGAME_FRENZY_TIMER = 0x078fU,
    MYSMB_ENDGAME_ENEMY_INTERVAL_TIMER = 0x0796U,
    MYSMB_ENDGAME_STAR_FLAG_TASK = 0x0746U,
    MYSMB_ENDGAME_FRAME_COUNTER = 0x0009U,
    MYSMB_ENDGAME_EVENT_MUSIC = 0x00fcU,
    MYSMB_ENDGAME_SQUARE2_SOUND = 0x00feU,
    MYSMB_ENDGAME_CURRENT_PLAYER = 0x0753U,
    MYSMB_ENDGAME_DISPLAY_DIGITS = 0x07d7U,
    MYSMB_ENDGAME_DIGIT_MODIFIER = 0x0134U,
    MYSMB_ENDGAME_GAME_TIMER = 0x07f8U
};

/* ROM $8f6f DigitsMathRoutine, local because this endgame object owns the
 * same score/timer call sites as RunStarFlagObj. */
static void mysmb_endgame_apply_digits(struct mysmb_game *game, mysmb_u8 offset)
{
    mysmb_u8 index;
    mysmb_u8 value;

    index = 5U;
    while (1) {
        value = (mysmb_u8)(game->ram[MYSMB_ENDGAME_DIGIT_MODIFIER + index] +
                           game->ram[MYSMB_ENDGAME_DISPLAY_DIGITS + offset]);
        if (value >= 0x80U) {
            game->ram[MYSMB_ENDGAME_DIGIT_MODIFIER + index - 1U]--;
            value = 9U;
        }
        else if (value >= 10U) {
            value = (mysmb_u8)(value - 10U);
            game->ram[MYSMB_ENDGAME_DIGIT_MODIFIER + index - 1U]++;
        }
        game->ram[MYSMB_ENDGAME_DISPLAY_DIGITS + offset] = value;
        if (index == 0U) break;
        --index;
        --offset;
    }
    for (index = 0U; index <= 6U; ++index)
        game->ram[MYSMB_ENDGAME_DIGIT_MODIFIER + index] = 0U;
}

static void mysmb_endgame_award_score(struct mysmb_game *game, mysmb_u8 amount)
{
    game->ram[MYSMB_ENDGAME_DIGIT_MODIFIER + 4U] = amount;
    mysmb_endgame_apply_digits(game,
        game->ram[MYSMB_ENDGAME_CURRENT_PLAYER] == 0U ? 0x0bU : 0x11U);
    (void)mysmb_area_queue_score_coin_status(game);
}

/* ROM RunFireworks / DrawExplosion_Fireworks. */
void mysmb_objects_step_fireworks(struct mysmb_game *game)
{
    static const mysmb_u8 tiles[3] = { 0x68U, 0x67U, 0x66U };
    mysmb_u8 slot;
    mysmb_u8 oam;
    mysmb_u8 x;
    mysmb_u8 y;
    mysmb_u8 frame;

    for (slot = 0U; slot < 5U; ++slot) {
        if (game->ram[MYSMB_ENDGAME_ENEMY_FLAG + slot] == 0U ||
            game->ram[MYSMB_ENDGAME_ENEMY_ID + slot] != 22U) continue;
        game->ram[MYSMB_ENDGAME_ENEMY_Y_SPEED + slot]--;
        if (game->ram[MYSMB_ENDGAME_ENEMY_Y_SPEED + slot] == 0U) {
            game->ram[MYSMB_ENDGAME_ENEMY_Y_SPEED + slot] = 8U;
            game->ram[MYSMB_ENDGAME_ENEMY_X_SPEED + slot]++;
            if (game->ram[MYSMB_ENDGAME_ENEMY_X_SPEED + slot] >= 3U) {
                game->ram[MYSMB_ENDGAME_ENEMY_FLAG + slot] = 0U;
                game->ram[MYSMB_ENDGAME_SQUARE2_SOUND] = 0x08U;
                mysmb_endgame_award_score(game, 5U);
                continue;
            }
        }
        frame = game->ram[MYSMB_ENDGAME_ENEMY_X_SPEED + slot];
        x = (mysmb_u8)(game->ram[MYSMB_ENDGAME_ENEMY_X + slot] -
                       game->ram[MYSMB_ENDGAME_SCREEN_LEFT_X]);
        y = game->ram[MYSMB_ENDGAME_ENEMY_Y + slot];
        game->ram[0x03aeU] = x;
        game->ram[0x03b9U] = y;
        game->ram[0x03baU] = y;
        game->ram[0x03afU] = x;
        oam = game->ram[MYSMB_ENDGAME_ENEMY_SPRITE_OFFSET + slot];
        game->ram[0x0200U + oam] = (mysmb_u8)(y - 4U);
        game->ram[0x0204U + oam] = (mysmb_u8)(y + 4U);
        game->ram[0x0208U + oam] = (mysmb_u8)(y - 4U);
        game->ram[0x020cU + oam] = (mysmb_u8)(y + 4U);
        game->ram[0x0201U + oam] = tiles[frame];
        game->ram[0x0205U + oam] = tiles[frame];
        game->ram[0x0209U + oam] = tiles[frame];
        game->ram[0x020dU + oam] = tiles[frame];
        game->ram[0x0202U + oam] = 2U;
        game->ram[0x0206U + oam] = 0x82U;
        game->ram[0x020aU + oam] = 0x42U;
        game->ram[0x020eU + oam] = 0xc2U;
        game->ram[0x0203U + oam] = (mysmb_u8)(x - 4U);
        game->ram[0x0207U + oam] = (mysmb_u8)(x - 4U);
        game->ram[0x020bU + oam] = (mysmb_u8)(x + 4U);
        game->ram[0x020fU + oam] = (mysmb_u8)(x + 4U);
    }
}

/* ROM RunStarFlagObj / DrawStarFlag. */
void mysmb_objects_step_star_flags(struct mysmb_game *game)
{
    static const mysmb_u8 y_adder[4] = { 0U, 0U, 8U, 8U };
    static const mysmb_u8 x_adder[4] = { 0U, 8U, 0U, 8U };
    static const mysmb_u8 tiles[4] = { 0x54U, 0x55U, 0x56U, 0x57U };
    mysmb_u8 slot;
    mysmb_u8 index;
    mysmb_u8 oam;
    mysmb_u8 x;
    mysmb_u8 y;
    mysmb_u8 task;
    mysmb_u8 rom_index;

    for (slot = 0U; slot < 5U; ++slot) {
        if (game->ram[MYSMB_ENDGAME_ENEMY_FLAG + slot] == 0U ||
            game->ram[MYSMB_ENDGAME_ENEMY_ID + slot] != 49U) continue;
        game->ram[MYSMB_ENDGAME_FRENZY_BUFFER] = 0U;
        task = game->ram[MYSMB_ENDGAME_STAR_FLAG_TASK];
        if (task >= 5U) continue;
        if (task == 1U) {
            game->ram[MYSMB_ENDGAME_ENEMY_STATE + slot] = 5U;
            if (game->ram[MYSMB_ENDGAME_GAME_TIMER + 2U] == 1U) game->ram[MYSMB_ENDGAME_FIREWORKS_COUNTER] = 1U;
            else if (game->ram[MYSMB_ENDGAME_GAME_TIMER + 2U] == 3U) {
                game->ram[MYSMB_ENDGAME_ENEMY_STATE + slot] = 3U;
                game->ram[MYSMB_ENDGAME_FIREWORKS_COUNTER] = 3U;
            }
            else if (game->ram[MYSMB_ENDGAME_GAME_TIMER + 2U] == 6U) {
                game->ram[MYSMB_ENDGAME_ENEMY_STATE + slot] = 0U;
                game->ram[MYSMB_ENDGAME_FIREWORKS_COUNTER] = 6U;
            }
            else game->ram[MYSMB_ENDGAME_FIREWORKS_COUNTER] = 0xffU;
            game->ram[MYSMB_ENDGAME_STAR_FLAG_TASK]++;
        }
        else if (task == 2U) {
            if ((game->ram[MYSMB_ENDGAME_GAME_TIMER] |
                 game->ram[MYSMB_ENDGAME_GAME_TIMER + 1U] |
                 game->ram[MYSMB_ENDGAME_GAME_TIMER + 2U]) == 0U)
                game->ram[MYSMB_ENDGAME_STAR_FLAG_TASK]++;
            else if ((game->ram[MYSMB_ENDGAME_FRAME_COUNTER] & 4U) != 0U) {
                game->ram[MYSMB_ENDGAME_SQUARE2_SOUND] = 2U;
                game->ram[MYSMB_ENDGAME_DIGIT_MODIFIER + 5U] = 0xffU;
                mysmb_endgame_apply_digits(game, 0x23U);
                mysmb_endgame_award_score(game, 5U);
            }
        }
        else if (task == 3U) {
            if (game->ram[MYSMB_ENDGAME_ENEMY_Y + slot] >= 0x72U)
                game->ram[MYSMB_ENDGAME_ENEMY_Y + slot]--;
            else if (game->ram[MYSMB_ENDGAME_FIREWORKS_COUNTER] != 0U &&
                     (game->ram[MYSMB_ENDGAME_FIREWORKS_COUNTER] & 0x80U) == 0U)
                game->ram[MYSMB_ENDGAME_FRENZY_BUFFER] = 22U;
            else {
                game->ram[MYSMB_ENDGAME_ENEMY_INTERVAL_TIMER + slot] = 6U;
                game->ram[MYSMB_ENDGAME_STAR_FLAG_TASK]++;
            }
        }
        else if (task == 4U && game->ram[MYSMB_ENDGAME_ENEMY_INTERVAL_TIMER + slot] == 0U &&
                 game->ram[MYSMB_ENDGAME_EVENT_MUSIC] == 0U)
            game->ram[MYSMB_ENDGAME_STAR_FLAG_TASK]++;
        x = (mysmb_u8)(game->ram[MYSMB_ENDGAME_ENEMY_X + slot] -
                       game->ram[MYSMB_ENDGAME_SCREEN_LEFT_X]);
        y = game->ram[MYSMB_ENDGAME_ENEMY_Y + slot];
        game->ram[0x03aeU] = x;
        game->ram[0x03b9U] = y;
        oam = game->ram[MYSMB_ENDGAME_ENEMY_SPRITE_OFFSET + slot];
        for (index = 0U; index < 4U; ++index) {
            rom_index = (mysmb_u8)(3U - index);
            game->ram[0x0200U + oam + index * 4U] = (mysmb_u8)(y + y_adder[rom_index]);
            game->ram[0x0201U + oam + index * 4U] = tiles[rom_index];
            game->ram[0x0202U + oam + index * 4U] = 0x22U;
            game->ram[0x0203U + oam + index * 4U] = (mysmb_u8)(x + x_adder[rom_index]);
        }
    }
}