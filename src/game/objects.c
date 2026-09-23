#include "game/objects.h"

enum {
    MYSMB_VRAM_BUFFER1 = 0x0301U,
    MYSMB_BLOCK_ORIGINAL_Y = 0x03e4U,
    MYSMB_BLOCK_BUFFER_LOW = 0x03e6U,
    MYSMB_BLOCK_METATILE = 0x03e8U,
    MYSMB_BLOCK_REPLACE_FLAG = 0x03ecU,
    MYSMB_BLOCK_STATE = 0x0026U,
    MYSMB_BLOCK_Y_SPEED = 0x00a8U,
    MYSMB_BLOCK_Y_HIGH = 0x00beU,
    MYSMB_BLOCK_Y = 0x00d7U,
    MYSMB_BLOCK_Y_DUMMY = 0x0420U,
    MYSMB_BLOCK_Y_FORCE = 0x043cU
};

/* ROM $bfa4 ImposeGravityBlock / ImposeGravity for a block-object slot.
 * Block objects use downward force $50 and maximum speed $08. */
static void mysmb_objects_impose_block_gravity(struct mysmb_game *game,
                                               mysmb_u8 slot)
{
    mysmb_u8 old_value;
    mysmb_u8 carry_dummy;
    mysmb_u8 carry_y;
    mysmb_u8 page_delta;

    old_value = game->ram[MYSMB_BLOCK_Y_DUMMY + slot];
    game->ram[MYSMB_BLOCK_Y_DUMMY + slot] =
        (mysmb_u8)(old_value + game->ram[MYSMB_BLOCK_Y_FORCE + slot]);
    carry_dummy = game->ram[MYSMB_BLOCK_Y_DUMMY + slot] < old_value ? 1U : 0U;
    page_delta = game->ram[MYSMB_BLOCK_Y_SPEED + slot] >= 0x80U ? 0xffU : 0U;
    old_value = game->ram[MYSMB_BLOCK_Y + slot];
    game->ram[MYSMB_BLOCK_Y + slot] =
        (mysmb_u8)(old_value + game->ram[MYSMB_BLOCK_Y_SPEED + slot] + carry_dummy);
    carry_y = game->ram[MYSMB_BLOCK_Y + slot] < old_value ? 1U : 0U;
    game->ram[MYSMB_BLOCK_Y_HIGH + slot] =
        (mysmb_u8)(game->ram[MYSMB_BLOCK_Y_HIGH + slot] + page_delta + carry_y);
    old_value = game->ram[MYSMB_BLOCK_Y_FORCE + slot];
    game->ram[MYSMB_BLOCK_Y_FORCE + slot] = (mysmb_u8)(old_value + 0x50U);
    if (game->ram[MYSMB_BLOCK_Y_FORCE + slot] < old_value) {
        game->ram[MYSMB_BLOCK_Y_SPEED + slot]++;
    }
    if (game->ram[MYSMB_BLOCK_Y_SPEED + slot] < 0x80U &&
        game->ram[MYSMB_BLOCK_Y_SPEED + slot] >= 8U &&
        game->ram[MYSMB_BLOCK_Y_FORCE + slot] >= 0x80U) {
        game->ram[MYSMB_BLOCK_Y_SPEED + slot] = 8U;
        game->ram[MYSMB_BLOCK_Y_FORCE + slot] = 0U;
    }
}

/* Translation of ROM $be70 BlockObjectsCore's bouncing-block branch.  Brick chunks
 * use its separate multi-object branch and remain with the brick route. */
void mysmb_objects_step_blocks(struct mysmb_game *game)
{
    mysmb_u8 slot;
    mysmb_u8 state;

    for (slot = 0U; slot < 2U; ++slot) {
        state = game->ram[MYSMB_BLOCK_STATE + slot];
        if ((state & 0x0fU) != 1U) continue;
        mysmb_objects_impose_block_gravity(game, slot);
        if ((game->ram[MYSMB_BLOCK_Y + slot] & 0x0fU) < 5U) {
            game->ram[MYSMB_BLOCK_REPLACE_FLAG + slot] = 1U;
            game->ram[MYSMB_BLOCK_STATE + slot] = 0U;
        }
    }
}

/* Translation of ROM $bed4 BlockObjMT_Updater's two block-object replacement slots.
 * ReplaceBlockMetatile's name-table write belongs to the later renderer. */
void mysmb_objects_apply_block_replacements(struct mysmb_game *game)
{
    mysmb_u8 slot;
    mysmb_u16 address;

    for (slot = 2U; slot != 0U; --slot) {
        mysmb_u8 index = (mysmb_u8)(slot - 1U);
        if (game->ram[MYSMB_VRAM_BUFFER1] != 0U) continue;
        if (game->ram[MYSMB_BLOCK_REPLACE_FLAG + index] == 0U) continue;
        address = (mysmb_u16)(0x0500U + game->ram[MYSMB_BLOCK_BUFFER_LOW + index] +
                              game->ram[MYSMB_BLOCK_ORIGINAL_Y + index]);
        if (address < 0x0800U) game->ram[address] =
            game->ram[MYSMB_BLOCK_METATILE + index];
        game->ram[MYSMB_BLOCK_REPLACE_FLAG + index] = 0U;
    }
}
