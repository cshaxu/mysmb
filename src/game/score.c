#include "game/score.h"
#include "game/status.h"
#include "game/objects.h"

/* ROM $BBF8-$BBFD: CoinTallyOffsets, ScoreOffsets, StatusBarNybbles. */
const mysmb_u8 mysmb_score_coin_offsets[2] = { 0x17U, 0x1dU };
const mysmb_u8 mysmb_score_offsets[2] = { 0x0bU, 0x11U };
const mysmb_u8 mysmb_score_status_nybbles[2] = { 0x02U, 0x13U };

/* ROM $BC36-$BC48 UpdateNumber/NoZSup. The indexed address adds a byte
 * offset to $02FB; the address calculation itself must not wrap at 256. */
mysmb_u8 mysmb_score_update_number(struct mysmb_game *game, mysmb_u8 nybbles)
{
    mysmb_u16 address;

    (void)mysmb_status_print_numbers(game, nybbles);
    address = (mysmb_u16)(0x02fbU + game->ram[0x0300U]);
    if (game->ram[address] == 0U) game->ram[address] = 0x24U;
    return game->ram[0x0008U];
}

/* ROM $BC30 GetSBNybbles. Read the player at this entry, after math. */
mysmb_u8 mysmb_score_get_status(struct mysmb_game *game)
{
    return mysmb_score_update_number(game,
        mysmb_score_status_nybbles[game->ram[0x0753U]]);
}

/* ROM $BC27 AddToScore. Modifiers belong to each original caller. */
mysmb_u8 mysmb_score_add(struct mysmb_game *game)
{
    mysmb_status_apply_digit_modifier(game,
        mysmb_score_offsets[game->ram[0x0753U]]);
    return mysmb_score_get_status(game);
}

/* ROM $BBFE-$BC26 GiveOneCoin/CoinPoints, then the shared score tail.
 * Keep the established coin caller ABI; the implementation has one owner. */
void mysmb_objects_give_one_coin(struct mysmb_game *game)
{
    game->ram[0x0139U] = 1U;
    mysmb_status_apply_digit_modifier(game,
        mysmb_score_coin_offsets[game->ram[0x0753U]]);
    game->ram[0x075eU]++;
    if (game->ram[0x075eU] == 100U) {
        game->ram[0x075eU] = 0U;
        game->ram[0x075aU]++;
        game->ram[0x00feU] = 0x40U;
    }
    game->ram[0x0138U] = 2U;
    (void)mysmb_score_add(game);
}

/* Existing status facade success values are distinct from source return X. */
mysmb_u8 mysmb_status_queue_score_coin(struct mysmb_game *game)
{
    (void)mysmb_score_get_status(game);
    return 1U;
}

mysmb_u8 mysmb_status_queue_title_score(struct mysmb_game *game)
{
    (void)mysmb_score_update_number(game, 0xfaU);
    return 1U;
}

mysmb_u8 mysmb_status_queue_bottom_line(struct mysmb_game *game)
{
    mysmb_u8 offset;
    /* ROM $865a-$8692 WriteBottomStatusLine always calls GetSBNybbles.
     * X stays fixed for all absolute indexed writes, even near page end. */
    (void)mysmb_status_queue_score_coin(game);
    offset = game->ram[0x0300U];
    game->ram[0x0301U + offset] = 0x20U;
    game->ram[0x0302U + offset] = 0x73U;
    game->ram[0x0303U + offset] = 3U;
    game->ram[0x0304U + offset] = (mysmb_u8)(game->ram[0x075fU] + 1U);
    game->ram[0x0305U + offset] = 0x28U;
    game->ram[0x0306U + offset] = (mysmb_u8)(game->ram[0x075cU] + 1U);
    game->ram[0x0307U + offset] = 0U;
    game->ram[0x0300U] = (mysmb_u8)(offset + 6U);
    return 1U;
}

