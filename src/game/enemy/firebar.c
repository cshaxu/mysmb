#include "game/enemy/firebar.h"
#include "game/enemy/actor_slots.h"
#include "game/objects.h"

/* The original residual position call can address table-adjacent bytes up
 * through $CE2D. Binding the immutable PRG data view avoids array overrun or
 * invented lookup values. A missing binding is an unmet resource prerequisite. */
static mysmb_u8 data_ready(const struct mysmb_game *game)
{
    return game->area_prg != 0 && game->area_prg_size >= 0x4e2eU ? 1U : 0U;
}
static mysmb_u8 data_at(const struct mysmb_game *game, mysmb_u16 address)
{
    return game->area_prg[address - 0x8000U];
}

/* $CE8E-$CED4 GetFirebarPosition / GetHAdder / GetVAdder. */
mysmb_u8 mysmb_firebar_get_position(struct mysmb_game *game, mysmb_u8 phase)
{
    mysmb_u8 value, index;
    if (data_ready(game) == 0U) return 0U;
    value = (mysmb_u8)(phase & 0x0fU);
    if (value >= 9U) value = (mysmb_u8)((value ^ 0x0fU) + 1U);
    game->ram[1U] = value;
    index = (mysmb_u8)(data_at(game, (mysmb_u16)(0xcd2eU + game->ram[0U])) + game->ram[1U]);
    game->ram[1U] = data_at(game, (mysmb_u16)(0xccc7U + index));
    value = (mysmb_u8)((phase + 8U) & 0x0fU);
    if (value >= 9U) value = (mysmb_u8)((value ^ 0x0fU) + 1U);
    game->ram[2U] = value;
    index = (mysmb_u8)(data_at(game, (mysmb_u16)(0xcd2eU + game->ram[0U])) + game->ram[2U]);
    game->ram[2U] = data_at(game, (mysmb_u16)(0xccc7U + index));
    game->ram[3U] = data_at(game, (mysmb_u16)(0xcd2aU + (phase >> 3U)));
    return 1U;
}

/* $CE08-$CE8D FirebarCollision and its probe/injury labels. */
mysmb_u8 mysmb_firebar_collision(struct mysmb_game *game, mysmb_u8 oam)
{
    mysmb_u8 saved_oam, player_y, difference, loop_count, injured;
    saved_oam = mysmb_oam_draw_firebar(game, oam);
    injured = 0U;
    if ((game->ram[0x079fU] | game->ram[0x0747U]) != 0U) goto done;
    game->ram[5U] = 0U;
    if (game->ram[0x00b5U] != 1U) goto done;
    player_y = game->ram[0x00ceU];
    if (game->ram[0x0754U] != 0U || game->ram[0x0714U] != 0U) {
        game->ram[5U] = 2U;
        player_y = (mysmb_u8)(player_y + 0x18U);
    }
    for (;;) {
        difference = (mysmb_u8)(player_y - game->ram[7U]);
        if ((difference & 0x80U) != 0U) difference = (mysmb_u8)(0U - difference);
        if (difference < 8U && game->ram[6U] < 0xf0U) {
            game->ram[4U] = (mysmb_u8)(game->ram[0x0207U] + 4U);
            difference = (mysmb_u8)(game->ram[4U] - game->ram[6U]);
            if ((difference & 0x80U) != 0U) difference = (mysmb_u8)(0U - difference);
            if (difference < 8U) {
                game->ram[0x0046U] = game->ram[4U] >= game->ram[6U] ? 1U : 2U;
                loop_count = game->ram[0U];
                mysmb_objects_force_injury(game);
                game->ram[0U] = loop_count;
                injured = 1U;
                break;
            }
        }
        if (game->ram[5U] == 2U) break;
        player_y = (mysmb_u8)(game->ram[0x00ceU] +
            data_at(game, (mysmb_u16)(0xcd3aU + game->ram[5U])));
        ++game->ram[5U];
    }
done:
    game->ram[6U] = (mysmb_u8)(saved_oam + 4U);
    return injured;
}

/* $CDBB-$CE07 DrawFirebar_Collision, falling through to FirebarCollision. */
mysmb_u8 mysmb_firebar_draw_collision(struct mysmb_game *game)
{
    mysmb_u8 oam, value, difference, mirror;
    game->ram[5U] = game->ram[3U];
    oam = game->ram[6U];
    value = game->ram[1U];
    mirror = (mysmb_u8)(game->ram[5U] & 1U);
    game->ram[5U] >>= 1U;
    if (mirror == 0U) value = (mysmb_u8)(0U - value);
    value = (mysmb_u8)(value + game->ram[0x03aeU]);
    game->ram[0x0203U + oam] = value;
    game->ram[6U] = value;
    difference = value >= game->ram[0x03aeU] ?
        (mysmb_u8)(value - game->ram[0x03aeU]) :
        (mysmb_u8)(game->ram[0x03aeU] - value);
    value = 0xf8U;
    if (difference < 0x59U && game->ram[0x03b9U] != 0xf8U) {
        value = game->ram[2U];
        mirror = (mysmb_u8)(game->ram[5U] & 1U);
        game->ram[5U] >>= 1U;
        if (mirror == 0U) value = (mysmb_u8)(0U - value);
        value = (mysmb_u8)(value + game->ram[0x03b9U]);
    }
    game->ram[0x0200U + oam] = value;
    game->ram[7U] = value;
    return mysmb_firebar_collision(game, oam);
}

/* $CD3C-$CDBA ProcFirebar through SkipFBar. Return value is only the old
 * bulk caller's injury signal, not an emulated CPU register. */
mysmb_u8 mysmb_enemy_proc_firebar(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 phase, oam, injured;
    mysmb_firebar_offscreen(game, slot);
    if ((game->ram[0x03d1U] & 8U) != 0U) return 0U;
    if (data_ready(game) == 0U) return 0U;
    slot = game->ram[8U];
    if (game->ram[0x0747U] == 0U) {
        phase = mysmb_firebar_spin(game, slot, game->ram[0x0388U + slot]);
        game->ram[0x00a0U + slot] = (mysmb_u8)(phase & 0x1fU);
    }
    phase = game->ram[0x00a0U + slot];
    if (game->ram[0x0016U + slot] >= 0x1fU && (phase == 8U || phase == 0x18U)) {
        ++phase;
        game->ram[0x00a0U + slot] = phase;
    }
    game->ram[0xefU] = phase;
    phase = mysmb_firebar_relative(game, slot);
    (void)mysmb_firebar_get_position(game, phase);
    slot = game->ram[8U];
    oam = game->ram[0x06e5U + slot];
    game->ram[0x0200U + oam] = game->ram[0x03b9U];
    game->ram[7U] = game->ram[0x03b9U];
    game->ram[0x0203U + oam] = game->ram[0x03aeU];
    game->ram[6U] = game->ram[0x03aeU];
    game->ram[0U] = 1U;
    injured = mysmb_firebar_collision(game, oam);
    slot = game->ram[8U];
    game->ram[0xedU] = game->ram[0x0016U + slot] < 0x1fU ? 5U : 11U;
    game->ram[0U] = 0U;
    do {
        (void)mysmb_firebar_get_position(game, game->ram[0xefU]);
        injured |= mysmb_firebar_draw_collision(game);
        if (game->ram[0U] == 4U)
            game->ram[6U] = game->ram[0x06e5U + game->ram[0x06cfU]];
        ++game->ram[0U];
    } while (game->ram[0U] < game->ram[0xedU]);
    return injured;
}
