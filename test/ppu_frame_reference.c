/* Project-owned T14 compositor retained solely as a regression reference. */
#include "game/ppu_frame.h"

#ifdef MYSMB_DOS16_TARGET
void mysmb_ppu_frame_bind_pixels(struct mysmb_ppu_frame *frame,
                                 mysmb_u8 MYSMB_PPU_FRAME_FAR *pixels)
{
    frame->pixels = pixels;
}
#endif
static const mysmb_u8 mysmb_ppu_master_color[64] = {
    0x00U,0x01U,0x02U,0x03U,0x04U,0x05U,0x06U,0x07U,
    0x08U,0x09U,0x0aU,0x0bU,0x0cU,0x0dU,0x0eU,0x0fU,
    0x10U,0x11U,0x12U,0x13U,0x14U,0x15U,0x16U,0x17U,
    0x18U,0x19U,0x1aU,0x1bU,0x1cU,0x1dU,0x1eU,0x1fU,
    0x20U,0x21U,0x22U,0x23U,0x24U,0x25U,0x26U,0x27U,
    0x28U,0x29U,0x2aU,0x2bU,0x2cU,0x2dU,0x2eU,0x2fU,
    0x30U,0x31U,0x32U,0x33U,0x34U,0x35U,0x36U,0x37U,
    0x38U,0x39U,0x3aU,0x3bU,0x3cU,0x3dU,0x3eU,0x3fU
};

static mysmb_u8 mysmb_ppu_pattern(const struct mysmb_game *game,
                                   mysmb_u16 offset)
{
    if (game->chr_data == 0 || offset >= game->chr_data_size) return 0U;
    return game->chr_data[offset];
}

static mysmb_u8 mysmb_ppu_background_pixel(const struct mysmb_game *game,
                                            mysmb_u16 screen_x,
                                            mysmb_u16 screen_y,
                                            mysmb_u8 scroll_x,
                                            mysmb_u8 scroll_y,
                                            mysmb_u8 name_table,
                                            mysmb_u8 *opaque)
{
    mysmb_u16 source_x;
    mysmb_u16 source_y;
    mysmb_u16 row;
    mysmb_u16 column;
    mysmb_u16 table;
    mysmb_u16 attribute;
    mysmb_u16 pattern;
    mysmb_u8 palette;
    mysmb_u8 low;
    mysmb_u8 high;
    mysmb_u8 color;

    source_x = (mysmb_u16)((screen_x + scroll_x) & 0x01ffU);
    source_y = (mysmb_u16)((screen_y + scroll_y) % 480U);
    table = (mysmb_u16)(name_table & 3U);
    if (source_x >= 256U) table ^= 1U;
    if (source_y >= 240U) table ^= 2U;
    /* SMB1 vertical mirroring: logical 0/2 and 1/3 share CIRAM. */
    table &= 1U;
    row = (source_y % 240U) / 8U;
    column = (source_x & 0xffU) / 8U;
    attribute = game->name_table[table][0x03c0U + (row / 4U) * 8U + column / 4U];
    palette = (mysmb_u8)((attribute >> (((row & 2U) << 1U) + (column & 2U))) & 3U);
    pattern = (mysmb_u16)(((game->visible_ppu_control_0 & 0x10U) != 0U ?
        0x1000U : 0U) + game->name_table[table][row * 32U + column] * 16U +
        (source_y & 7U));
    low = mysmb_ppu_pattern(game, pattern);
    high = mysmb_ppu_pattern(game, (mysmb_u16)(pattern + 8U));
    color = (mysmb_u8)(((low >> (7U - (source_x & 7U))) & 1U) |
                        (((high >> (7U - (source_x & 7U))) & 1U) << 1U));
    *opaque = color == 0U ? 0U : 1U;
    return game->palette[color == 0U ? 0U : (mysmb_u16)(palette * 4U + color)];
}

void mysmb_ppu_frame_reference(const struct mysmb_game *game,
                           struct mysmb_ppu_frame *frame)
{
    mysmb_u16 x;
    mysmb_u16 y;
    mysmb_u16 sprite;
    mysmb_u16 fixed_top_height;
    mysmb_u16 sprite_x;
    mysmb_u16 sprite_y;
    mysmb_u16 pixel_x;
    mysmb_u16 pixel_y;
    mysmb_u16 pattern;
    mysmb_u8 attributes;
    mysmb_u8 low;
    mysmb_u8 high;
    mysmb_u8 color;
    mysmb_u8 opaque;
    mysmb_u8 scroll_x;
    mysmb_u8 scroll_y;

    /* Source flag zero reaches SkipSprite0 during VBlank, so the entire
     * visible frame uses scene scroll. A synchronized frame retains its
     * fixed top region; never reread the following frame's RAM flag here. */
    fixed_top_height = game->visible_sprite0_split != 0U ?
        MYSMB_PPU_STATUS_BAR_HEIGHT : 0U;
    for (y = 0U; y < MYSMB_SCREEN_HEIGHT; ++y) {
        scroll_x = y < fixed_top_height ? 0U : game->visible_scroll_x;
        scroll_y = y < fixed_top_height ? 0U : game->visible_scroll_y;
        for (x = 0U; x < MYSMB_SCREEN_WIDTH; ++x) {
            if ((game->visible_ppu_mask & 0x08U) != 0U &&
                (x >= 8U || (game->visible_ppu_mask & 0x02U) != 0U)) {
                frame->pixels[y * MYSMB_SCREEN_WIDTH + x] =
                    mysmb_ppu_background_pixel(game, x, y, scroll_x, scroll_y,
                        y < fixed_top_height ? 0U : game->visible_ppu_name_table,
                        &opaque);
            }
            else frame->pixels[y * MYSMB_SCREEN_WIDTH + x] = game->palette[0U];
        }
    }
    if ((game->visible_ppu_mask & 0x10U) == 0U) return;
    for (sprite = 64U; sprite != 0U;) {
        --sprite;
        sprite_y = (mysmb_u16)game->visible_oam[sprite * 4U] + 1U;
        sprite_x = game->visible_oam[sprite * 4U + 3U];
        attributes = game->visible_oam[sprite * 4U + 2U];
        if (sprite_y >= MYSMB_SCREEN_HEIGHT) continue;
        for (pixel_y = 0U; pixel_y < 8U && sprite_y + pixel_y < MYSMB_SCREEN_HEIGHT;
             ++pixel_y) {
            pattern = (mysmb_u16)(((game->visible_ppu_control_0 & 0x08U) != 0U ?
                0x1000U : 0U) + game->visible_oam[sprite * 4U + 1U] * 16U +
                ((attributes & 0x80U) != 0U ? 7U - pixel_y : pixel_y));
            low = mysmb_ppu_pattern(game, pattern);
            high = mysmb_ppu_pattern(game, (mysmb_u16)(pattern + 8U));
            for (pixel_x = 0U; pixel_x < 8U && sprite_x + pixel_x < MYSMB_SCREEN_WIDTH;
                 ++pixel_x) {
                color = (mysmb_u8)(((low >> ((attributes & 0x40U) != 0U ? pixel_x :
                    7U - pixel_x)) & 1U) | (((high >> ((attributes & 0x40U) != 0U ?
                    pixel_x : 7U - pixel_x)) & 1U) << 1U));
                if (color == 0U) continue;
                y = (mysmb_u16)(sprite_y + pixel_y);
                x = (mysmb_u16)(sprite_x + pixel_x);
                if (x < 8U && (game->visible_ppu_mask & 0x04U) == 0U) continue;
                if ((attributes & 0x20U) != 0U &&
                    (game->visible_ppu_mask & 0x08U) != 0U &&
                    (x >= 8U || (game->visible_ppu_mask & 0x02U) != 0U)) {
                    scroll_x = y < fixed_top_height ? 0U : game->visible_scroll_x;
                    scroll_y = y < fixed_top_height ? 0U : game->visible_scroll_y;
                    (void)mysmb_ppu_background_pixel(game, x, y, scroll_x, scroll_y,
                        y < fixed_top_height ? 0U : game->visible_ppu_name_table,
                        &opaque);
                    if (opaque != 0U) continue;
                }
                frame->pixels[y * MYSMB_SCREEN_WIDTH + x] = game->palette[
                    0x10U + (mysmb_u16)((attributes & 3U) * 4U + color)];
            }
        }
    }
    (void)mysmb_ppu_master_color[0];
}
