#include "core/world/world.h"

/* ROM $e1fd BoundBoxCtrlData and $e29c-$e2dd BoundingBoxCore.
 * Each control value selects four original bytes: UL-X, UL-Y, LR-X and
 * LR-Y.  All source callers select the valid 0..11 control domain. */
void mysmb_world_set_bounding_box(struct mysmb_game *game,
                                  mysmb_u16 address, mysmb_u8 control,
                                  mysmb_u8 x, mysmb_u8 y)
{
    static const mysmb_u8 bound_box_ctrl_data[48] = {
        0x02U, 0x08U, 0x0eU, 0x20U, 0x03U, 0x14U, 0x0dU, 0x20U,
        0x02U, 0x14U, 0x0eU, 0x20U, 0x02U, 0x09U, 0x0eU, 0x15U,
        0x00U, 0x00U, 0x18U, 0x06U, 0x00U, 0x00U, 0x20U, 0x0dU,
        0x00U, 0x00U, 0x30U, 0x0dU, 0x00U, 0x00U, 0x08U, 0x08U,
        0x06U, 0x04U, 0x0aU, 0x08U, 0x03U, 0x0eU, 0x0dU, 0x14U,
        0x00U, 0x02U, 0x10U, 0x15U, 0x04U, 0x04U, 0x0cU, 0x1cU
    };
    mysmb_u8 table_offset;

    /* BoundingBoxCore retains the source SprObject offset and relative
     * coordinates in scratch before computing the four corner bytes. */
    game->ram[0U] = (mysmb_u8)((address - 0x04acU) >> 2U);
    game->ram[2U] = y;
    game->ram[1U] = x;

    /* The original uses ASL twice.  The admitted callers are constrained by
     * SprObj_BoundBoxCtrl to the 12-entry source table. */
    if (control >= 12U) control = 0U;
    table_offset = (mysmb_u8)(control << 2U);
    game->ram[address] = (mysmb_u8)(x + bound_box_ctrl_data[table_offset]);
    game->ram[(mysmb_u16)(address + 2U)] =
        (mysmb_u8)(x + bound_box_ctrl_data[(mysmb_u8)(table_offset + 2U)]);
    game->ram[(mysmb_u16)(address + 1U)] =
        (mysmb_u8)(y + bound_box_ctrl_data[(mysmb_u8)(table_offset + 1U)]);
    game->ram[(mysmb_u16)(address + 3U)] =
        (mysmb_u8)(y + bound_box_ctrl_data[(mysmb_u8)(table_offset + 3U)]);
}

/* ROM $e2de CheckRightScreenBBox through $e324 NoOfs2 return.
 * CMP object-X followed by SBC object-page is the source's unsigned
 * world-coordinate comparison against ScreenLeft + $80. */
void mysmb_world_clip_bounding_box_to_screen(struct mysmb_game *game,
                                             mysmb_u16 address,
                                             mysmb_u8 object_page,
                                             mysmb_u8 object_x)
{
    mysmb_u8 middle_x;
    mysmb_u8 middle_page;
    mysmb_u8 page_carry;

    middle_x = (mysmb_u8)(game->ram[0x071cU] + 0x80U);
    page_carry = game->ram[0x071cU] >= 0x80U ? 1U : 0U;
    middle_page = (mysmb_u8)(game->ram[0x071aU] + page_carry);
    /* CheckRightScreenBBox writes the midpoint low byte, then its page. */
    game->ram[2U] = middle_x;
    game->ram[1U] = middle_page;

    if (((mysmb_u16)object_page << 8U | object_x) >=
        ((mysmb_u16)middle_page << 8U | middle_x)) {
        /* CheckRightScreenBBox / SORte / NoOfs. */
        if ((game->ram[(mysmb_u16)(address + 2U)] & 0x80U) == 0U) {
            if ((game->ram[address] & 0x80U) == 0U)
                game->ram[address] = 0xffU;
            game->ram[(mysmb_u16)(address + 2U)] = 0xffU;
        }
        return;
    }

    /* CheckLeftScreenBBox / SOLft / NoOfs2.  $80-$9f is a near-left
     * wrapped box and intentionally remains visible; $a0-$ff is offscreen. */
    if ((game->ram[address] & 0x80U) != 0U && game->ram[address] >= 0xa0U) {
        if ((game->ram[(mysmb_u16)(address + 2U)] & 0x80U) != 0U)
            game->ram[(mysmb_u16)(address + 2U)] = 0U;
        game->ram[address] = 0U;
    }
}
