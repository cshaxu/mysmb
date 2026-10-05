#include "game/enemy/actor_slots.h"
#include "game/oam/oam.h"
#include "game/score.h"
#include "core/status.h"
#include "game/presentation/text/observation.h"

/* ROM $D2CD-$D2D8: StarFlagYPosAdder, StarFlagXPosAdder, StarFlagTileData. */
static const mysmb_u8 y_adder[4] = {0U,0U,8U,8U};
static const mysmb_u8 x_adder[4] = {0U,8U,0U,8U};
static const mysmb_u8 tiles[4] = {0x54U,0x55U,0x56U,0x57U};

/* ROM $D336-$D34D EndAreaPoints / ELPGive; also the fireworks score tail. */
void mysmb_objects_end_area_points(struct mysmb_game *game)
{
    mysmb_status_apply_digit_modifier(game,
        game->ram[0x0753U] == 0U ? 0x0bU : 0x11U);
    (void)mysmb_score_update_number(game,
        (mysmb_u8)((mysmb_u8)(game->ram[0x0753U] << 4U) | 4U));
}

/* ROM $D365-$D395 DrawStarFlag / DSFLoop. Y wraps between sprites;
 * each absolute indexed sprite field address itself does not wrap. */
static void draw_star_flag(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 oam, index;
    mysmb_oam_relative_enemy_position(game, slot);
    slot = game->ram[8U];
    oam = game->ram[0x06e5U + slot];
    index = 4U;
    do {
        --index;
        game->ram[0x0200U + oam] =
            (mysmb_u8)(game->ram[0x03b9U] + y_adder[index]);
        game->ram[0x0201U + oam] = tiles[index];
        game->ram[0x0202U + oam] = 0x22U;
        game->ram[0x0203U + oam] =
            (mysmb_u8)(game->ram[0x03aeU] + x_adder[index]);
        oam = (mysmb_u8)(oam + 4U);
    } while (index != 0U);
    /* The four entries were emitted in reverse tile order. Record the
     * completed span at its original offset,not the advanced loop cursor. */
    mysmb_text_observer_record(game,MYSMB_TEXT_OBSERVE_STAR_FLAG,
        0U,slot,0U,0U,game->ram[0x06e5U+slot],4U,0U);
}

/* ROM $D2D9-$D3AF RunStarFlagObj and its five native task paths.
 * Original $D2E8 vector values retain JumpEngine RAM scratch semantics. */
void mysmb_objects_step_star_flags_slot(struct mysmb_game *game, mysmb_u8 slot)
{
    static const mysmb_u16 targets[5] = {
        0xd311U,0xd2f2U,0xd312U,0xd34eU,0xd3a2U
    };
    mysmb_u8 task, digit, state;
    mysmb_u16 target;

    game->ram[0x06cbU] = 0U;
    task = game->ram[0x0746U];
    if (task >= 5U) return;
    target = targets[task];
    game->ram[4U] = 0xe7U;
    game->ram[5U] = 0xd2U;
    game->ram[6U] = (mysmb_u8)target;
    game->ram[7U] = (mysmb_u8)(target >> 8U);
    switch (task) {
    case 0U:
        return;
    case 1U:
        digit = game->ram[0x07faU];
        state = 5U;
        if (digit != 1U) {
            state = 3U;
            if (digit != 3U) {
                state = 0U;
                if (digit != 6U) digit = 0xffU;
            }
        }
        game->ram[0x06d7U] = digit;
        game->ram[0x001eU + slot] = state;
        ++game->ram[0x0746U];
        return;
    case 2U:
        if ((game->ram[0x07f8U] | game->ram[0x07f9U] |
             game->ram[0x07faU]) == 0U) {
            ++game->ram[0x0746U];
            return;
        }
        if ((game->ram[9U] & 4U) != 0U) game->ram[0x00feU] = 0x10U;
        game->ram[0x0139U] = 0xffU;
        mysmb_status_apply_digit_modifier(game, 0x23U);
        game->ram[0x0139U] = 5U;
        mysmb_objects_end_area_points(game);
        return;
    case 3U:
        if (game->ram[0x00cfU + slot] >= 0x72U) {
            --game->ram[0x00cfU + slot];
        } else {
            digit = game->ram[0x06d7U];
            if (digit == 0U || (digit & 0x80U) != 0U) {
                draw_star_flag(game, slot);
                game->ram[0x0796U + game->ram[8U]] = 6U;
                ++game->ram[0x0746U];
                return;
            }
            game->ram[0x06cbU] = 0x16U;
        }
        draw_star_flag(game, slot);
        return;
    default:
        draw_star_flag(game, slot);
        if (game->ram[0x0796U + game->ram[8U]] == 0U &&
            game->ram[0x07b1U] == 0U) ++game->ram[0x0746U];
        return;
    }
}
