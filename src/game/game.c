#include "game/game.h"

void mysmb_game_initialize(struct mysmb_game *game)
{
    mysmb_u16 index;

    for (index = 0U; index < 0x0800U; ++index) {
        game->ram[index] = 0xffU;
    }
    mysmb_game_initialize_memory(game, 0xfeU);
    mysmb_game_move_all_sprites_offscreen(game);
    mysmb_game_initialize_name_tables(game);
    game->frame_number = 0UL;
}

/* Translation of ROM $90cc-$90e6 (InitializeMemory). */
void mysmb_game_initialize_memory(struct mysmb_game *game, mysmb_u8 initial_y)
{
    mysmb_u8 page;
    mysmb_u8 offset;

    page = 0x07U;
    offset = initial_y;
    do {
        do {
            if (page != 0x01U || offset < 0x60U) {
                game->ram[(mysmb_u16)((mysmb_u16)page * 0x0100U + offset)] = 0U;
            }
            offset = (mysmb_u8)(offset - 1U);
        } while (offset != 0xffU);
        page = (mysmb_u8)(page - 1U);
    } while (page != 0xffU);
}

/* Translation of ROM $8220-$8230 (MoveAllSpritesOffscreen). */
void mysmb_game_move_all_sprites_offscreen(struct mysmb_game *game)
{
    mysmb_u8 offset;

    offset = 0U;
    do {
        game->ram[(mysmb_u16)(0x0200U + offset)] = 0xf8U;
        offset = (mysmb_u8)(offset + 4U);
    } while (offset != 0U);
}

/* Translation of ROM $8e19-$8e5b (InitializeNameTables). */
void mysmb_game_initialize_name_tables(struct mysmb_game *game)
{
    mysmb_u8 table;
    mysmb_u16 offset;

    for (table = 0U; table < 2U; ++table) {
        for (offset = 0U; offset < 0x0300U; ++offset) {
            game->name_table[table][offset] = 0x24U;
        }
        for (offset = 0x0300U; offset < 0x0340U; ++offset) {
            game->name_table[table][offset] = 0U;
        }
    }
    game->ram[0x0300U] = 0U;
    game->ram[0x0301U] = 0U;
    game->ram[0x073fU] = 0U;
    game->ram[0x0740U] = 0U;
}

/* Translation of the name-table portion of ROM $8e92-$8eec. */
mysmb_u8 mysmb_game_apply_title_commands(struct mysmb_game *game,
                                         const mysmb_u8 *commands,
                                         mysmb_u16 command_size)
{
    mysmb_u16 cursor;
    mysmb_u16 address;
    mysmb_u16 offset;
    mysmb_u8 control;
    mysmb_u8 count;
    mysmb_u8 index;
    mysmb_u8 table;
    mysmb_u8 value;

    cursor = 0U;
    while (cursor < command_size && commands[cursor] != 0U) {
        if ((mysmb_u16)(command_size - cursor) < 3U) {
            return 0U;
        }
        address = (mysmb_u16)(((mysmb_u16)commands[cursor] << 8) |
                              commands[(mysmb_u16)(cursor + 1U)]);
        control = commands[(mysmb_u16)(cursor + 2U)];
        count = (mysmb_u8)(control & 0x3fU);
        if (count == 0U || (mysmb_u16)(command_size - cursor) <
            (mysmb_u16)(3U + ((control & 0x40U) != 0U ? 1U : count))) {
            return 0U;
        }
        if (address < 0x2000U || address >= 0x2800U) {
            return 0U;
        }
        table = (mysmb_u8)((address - 0x2000U) / 0x0400U);
        offset = (mysmb_u16)(address & 0x03ffU);
        value = commands[(mysmb_u16)(cursor + 3U)];
        for (index = 0U; index < count; ++index) {
            if (offset >= 0x0400U) {
                return 0U;
            }
            game->name_table[table][offset] = value;
            if ((control & 0x80U) != 0U) {
                offset = (mysmb_u16)(offset + 32U);
            }
            else {
                offset++;
            }
            if ((control & 0x40U) == 0U && (mysmb_u8)(index + 1U) < count) {
                value = commands[(mysmb_u16)(cursor + 3U + index + 1U)];
            }
        }
        cursor = (mysmb_u16)(cursor + 3U +
                              ((control & 0x40U) != 0U ? 1U : count));
    }
    return cursor < command_size ? 1U : 0U;
}

void mysmb_game_tick(struct mysmb_game *game, const struct mysmb_input *input,
                     struct mysmb_frame *frame)
{
    game->frame_number++;
    frame->sprite0_y = game->ram[0x0200U];
    frame->sprite0_x = game->ram[0x0203U];
    frame->start_pressed = (input->buttons & MYSMB_BUTTON_START) != 0U;
}
