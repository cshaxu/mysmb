#include "core/oam/oam.h"

/* ROM $ec46 ChkLeftCo falls through the shared MoveColOffscreen leaf. */
void mysmb_oam_check_block_left_column(struct mysmb_game *game,
                                      mysmb_u8 bits, mysmb_u8 oam)
{
    if ((bits & 8U) != 0U)
        (void)mysmb_oam_move_column_offscreen(game, oam);
}
