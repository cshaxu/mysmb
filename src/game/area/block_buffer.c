#include "game/area/block_buffer.h"

/* ROM $9bdd BlockBufferAddr; $9be1-$9bf5 GetBlockBufferAddr.
 * RendBBuf maintains a 0..31 column; BlockBufferCollision constructs it
 * from page parity and the horizontal high nibble. */
mysmb_u16 mysmb_area_get_block_buffer_address(struct mysmb_game *game,
                                               mysmb_u8 column)
{
    static const mysmb_u8 block_buffer_addr[4] = { 0x00U, 0xd0U, 0x05U, 0x05U };
    mysmb_u8 selector;

    if (column >= 32U) return 0U; /* Outside both original caller contracts. */
    selector = (mysmb_u8)(column >> 4U);
    game->ram[7U] = block_buffer_addr[selector + 2U];
    game->ram[6U] = (mysmb_u8)((column & 0x0fU) + block_buffer_addr[selector]);
    return (mysmb_u16)(((mysmb_u16)game->ram[7U] << 8U) | game->ram[6U]);
}
