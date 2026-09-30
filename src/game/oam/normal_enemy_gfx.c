#include "game/oam/oam.h"
#include "game/oam/enemy_offscreen_tail.h"
#include "game/objects.h"

enum {
    MYSMB_NORMAL_FLAG = 0x000fU,
    MYSMB_NORMAL_ID = 0x0016U,
    MYSMB_NORMAL_STATE = 0x001eU,
    MYSMB_NORMAL_DIRECTION = 0x0046U,
    MYSMB_PIRANHA_Y_SPEED = 0x0058U,
    MYSMB_NORMAL_PAGE = 0x006eU,
    MYSMB_NORMAL_X = 0x0087U,
    MYSMB_NORMAL_Y = 0x00cfU,
    MYSMB_NORMAL_REL_X = 0x03aeU,
    MYSMB_NORMAL_REL_Y = 0x03b9U,
    MYSMB_NORMAL_OFFSCREEN = 0x03d1U,
    MYSMB_NORMAL_ATTRIBUTES = 0x03c5U,
    MYSMB_NORMAL_SPRITE = 0x06e5U,
    MYSMB_NORMAL_SCREEN_PAGE = 0x071aU,
    MYSMB_NORMAL_SCREEN_X = 0x071cU,
    MYSMB_NORMAL_TIMER_CONTROL = 0x0747U,
    MYSMB_NORMAL_FRAME_COUNTER = 0x0009U,
    MYSMB_NORMAL_WORLD = 0x075fU
};

static void mysmb_normal_apply_offscreen(struct mysmb_game *game,
                                         mysmb_u8 oam, mysmb_u8 bits)
{
    mysmb_oam_enemy_offscreen_tail(game, oam, bits);
}

/* ROM EnemyGfxHandler/DrawEnemyObject for walking Koopas and Buzzy Beetles. */
mysmb_u8 mysmb_objects_draw_koopa_buzzy(struct mysmb_game *game, mysmb_u8 slot)
{
    static const mysmb_u8 buzzy_frame1[6] =
        { 0xfcU, 0xfcU, 0xaaU, 0xabU, 0xacU, 0xadU };
    static const mysmb_u8 buzzy_frame2[6] =
        { 0xfcU, 0xfcU, 0xaeU, 0xafU, 0xb0U, 0xb1U };
    static const mysmb_u8 koopa_frame1[6] =
        { 0xfcU, 0xa5U, 0xa6U, 0xa7U, 0xa8U, 0xa9U };
    static const mysmb_u8 koopa_frame2[6] =
        { 0xfcU, 0xa0U, 0xa1U, 0xa2U, 0xa3U, 0xa4U };
    static const mysmb_u8 koopa_upside1[6] =
        { 0xfcU, 0xfcU, 0x6eU, 0x6eU, 0x6fU, 0x6fU };
    static const mysmb_u8 koopa_upside2[6] =
        { 0xfcU, 0xfcU, 0x6dU, 0x6dU, 0x6fU, 0x6fU };
    static const mysmb_u8 koopa_upright1[6] =
        { 0xfcU, 0xfcU, 0x6fU, 0x6fU, 0x6eU, 0x6eU };
    static const mysmb_u8 koopa_upright2[6] =
        { 0xfcU, 0xfcU, 0x6fU, 0x6fU, 0x6dU, 0x6dU };
    static const mysmb_u8 buzzy_upright[6] =
        { 0xfcU, 0xfcU, 0xf4U, 0xf4U, 0xf5U, 0xf5U };
    static const mysmb_u8 buzzy_upside[6] =
        { 0xfcU, 0xfcU, 0xf5U, 0xf5U, 0xf4U, 0xf4U };
    const mysmb_u8 *tiles;
    mysmb_u8 id;
    mysmb_u8 state;
    mysmb_u8 state_low;
    mysmb_u8 direction;
    mysmb_u8 attributes;
    mysmb_u8 offscreen;
    mysmb_u8 oam;
    mysmb_u8 row;
    mysmb_u8 offset;
    mysmb_u8 y;
    mysmb_u8 left;
    mysmb_u8 right;
    mysmb_u16 world;
    mysmb_u16 screen;

    if (game->ram[MYSMB_NORMAL_FLAG + slot] == 0U) return 0U;
    id = game->ram[MYSMB_NORMAL_ID + slot];
    if (id != 0U && id != 2U && id != 3U) return 0U;

    world = (mysmb_u16)(((mysmb_u16)game->ram[MYSMB_NORMAL_PAGE + slot] << 8U) |
                         game->ram[MYSMB_NORMAL_X + slot]);
    screen = (mysmb_u16)(((mysmb_u16)game->ram[MYSMB_NORMAL_SCREEN_PAGE] << 8U) |
                          game->ram[MYSMB_NORMAL_SCREEN_X]);
    game->ram[MYSMB_NORMAL_ATTRIBUTES + slot] = 0U;
    game->ram[MYSMB_NORMAL_REL_X] = (mysmb_u8)(world - screen);
    game->ram[MYSMB_NORMAL_REL_Y] = game->ram[MYSMB_NORMAL_Y + slot];
    offscreen = mysmb_objects_get_enemy_offscreen_bits(game, slot);
    game->ram[MYSMB_NORMAL_OFFSCREEN] = offscreen;
    state = game->ram[MYSMB_NORMAL_STATE + slot];
    state_low = (mysmb_u8)(state & 0x1fU);
    y = game->ram[MYSMB_NORMAL_REL_Y];

    if (id == 2U) {
        tiles = buzzy_frame1;
        attributes = 3U;
    }
    else {
        tiles = koopa_frame1;
        attributes = id == 0U ? 1U : 2U;
    }
    if (state_low >= 2U) {
        if (id == 2U) {
            tiles = buzzy_upside;
            y++;
        }
        else tiles = koopa_upside1;
        if (state_low == 4U) {
            if (id == 2U) tiles = buzzy_upright;
            else tiles = koopa_upright1;
            y++;
            if (id != 2U) y++;
        }
    }
    if ((state & 0xa0U) == 0U &&
        game->ram[MYSMB_NORMAL_TIMER_CONTROL] == 0U &&
        (game->ram[MYSMB_NORMAL_FRAME_COUNTER] & 8U) == 0U) {
        if (state_low >= 2U) {
            if (state_low == 4U) {
                if (id != 2U) tiles = koopa_upright2;
            }
            else {
                if (id == 2U) tiles = buzzy_upside;
                else tiles = koopa_upside2;
            }
        }
        else {
            if (id == 2U) tiles = buzzy_frame2;
            else tiles = koopa_frame2;
        }
    }
    direction = game->ram[MYSMB_NORMAL_DIRECTION + slot];
    oam = game->ram[MYSMB_NORMAL_SPRITE + slot];
    for (row = 0U; row < 3U; ++row) {
        offset = (mysmb_u8)(oam + row * 8U);
        left = tiles[row * 2U];
        right = tiles[row * 2U + 1U];
        if ((direction & 2U) != 0U) {
            game->ram[0x0201U + offset] = right;
            game->ram[0x0205U + offset] = left;
            game->ram[0x0202U + offset] = (mysmb_u8)(attributes | 0x40U);
            game->ram[0x0206U + offset] = (mysmb_u8)(attributes | 0x40U);
        }
        else {
            game->ram[0x0201U + offset] = left;
            game->ram[0x0205U + offset] = right;
            game->ram[0x0202U + offset] = attributes;
            game->ram[0x0206U + offset] = attributes;
        }
        game->ram[0x0200U + offset] = (mysmb_u8)(y + row * 8U);
        game->ram[0x0204U + offset] = (mysmb_u8)(y + row * 8U);
        game->ram[0x0203U + offset] = game->ram[MYSMB_NORMAL_REL_X];
        game->ram[0x0207U + offset] =
            (mysmb_u8)(game->ram[MYSMB_NORMAL_REL_X] + 8U);
    }
    mysmb_normal_apply_offscreen(game, oam, offscreen);
    return 1U;
}

/* ROM $e87d-$eaf2 EnemyGfxHandler: the ordinary enemy branch.  The final
 * two bytes are the start of EnemyGfxTableOffsets, reached by offset $ff. */
static const mysmb_u8 mysmb_enemy_graphics_table[] = {
    0xfcU,0xfcU,0xaaU,0xabU,0xacU,0xadU, 0xfcU,0xfcU,0xaeU,0xafU,0xb0U,0xb1U,
    0xfcU,0xa5U,0xa6U,0xa7U,0xa8U,0xa9U, 0xfcU,0xa0U,0xa1U,0xa2U,0xa3U,0xa4U,
    0x69U,0xa5U,0x6aU,0xa7U,0xa8U,0xa9U, 0x6bU,0xa0U,0x6cU,0xa2U,0xa3U,0xa4U,
    0xfcU,0xfcU,0x96U,0x97U,0x98U,0x99U, 0xfcU,0xfcU,0x9aU,0x9bU,0x9cU,0x9dU,
    0xfcU,0xfcU,0x8fU,0x8eU,0x8eU,0x8fU, 0xfcU,0xfcU,0x95U,0x94U,0x94U,0x95U,
    0xfcU,0xfcU,0xdcU,0xdcU,0xdfU,0xdfU, 0xdcU,0xdcU,0xddU,0xddU,0xdeU,0xdeU,
    0xfcU,0xfcU,0xb2U,0xb3U,0xb4U,0xb5U, 0xfcU,0xfcU,0xb6U,0xb3U,0xb7U,0xb5U,
    0xfcU,0xfcU,0x70U,0x71U,0x72U,0x73U, 0xfcU,0xfcU,0x6eU,0x6eU,0x6fU,0x6fU,
    0xfcU,0xfcU,0x6dU,0x6dU,0x6fU,0x6fU, 0xfcU,0xfcU,0x6fU,0x6fU,0x6eU,0x6eU,
    0xfcU,0xfcU,0x6fU,0x6fU,0x6dU,0x6dU, 0xfcU,0xfcU,0xf4U,0xf4U,0xf5U,0xf5U,
    0xfcU,0xfcU,0xf4U,0xf4U,0xf5U,0xf5U, 0xfcU,0xfcU,0xf5U,0xf5U,0xf4U,0xf4U,
    0xfcU,0xfcU,0xf5U,0xf5U,0xf4U,0xf4U, 0xfcU,0xfcU,0xfcU,0xfcU,0xefU,0xefU,
    0xb9U,0xb8U,0xbbU,0xbaU,0xbcU,0xbcU, 0xfcU,0xfcU,0xbdU,0xbdU,0xbcU,0xbcU,
    0x7aU,0x7bU,0xdaU,0xdbU,0xd8U,0xd8U, 0xcdU,0xcdU,0xceU,0xceU,0xcfU,0xcfU,
    0x7dU,0x7cU,0xd1U,0x8cU,0xd3U,0xd2U, 0x7dU,0x7cU,0x89U,0x88U,0x8bU,0x8aU,
    0xd5U,0xd4U,0xe3U,0xe2U,0xd3U,0xd2U, 0xd5U,0xd4U,0xe3U,0xe2U,0x8bU,0x8aU,
    0xe5U,0xe5U,0xe6U,0xe6U,0xebU,0xebU, 0xecU,0xecU,0xedU,0xedU,0xeeU,0xeeU,
    0xfcU,0xfcU,0xd0U,0xd0U,0xd7U,0xd7U, 0xbfU,0xbeU,0xc1U,0xc0U,0xc2U,0xfcU,
    0xc4U,0xc3U,0xc6U,0xc5U,0xc8U,0xc7U, 0xbfU,0xbeU,0xcaU,0xc9U,0xc2U,0xfcU,
    0xc4U,0xc3U,0xc6U,0xc5U,0xccU,0xcbU, 0xfcU,0xfcU,0xe8U,0xe7U,0xeaU,0xe9U,
    0xf2U,0xf2U,0xf3U,0xf3U,0xf2U,0xf2U, 0xf1U,0xf1U,0xf1U,0xf1U,0xfcU,0xfcU,
    0xf0U,0xf0U,0xfcU,0xfcU,0xfcU,0xfcU, 0x0cU,0x0cU,0x00U,0x0cU
};
/* These 6502 indexed loads may read past the named table.  Preserve the
 * contiguous following bytes through ID $35 instead of indexing C memory
 * out of bounds or inventing a clamp. */
static const mysmb_u8 mysmb_enemy_graphics_offsets[54] = {
    0x0cU,0x0cU,0x00U,0x0cU,0x0cU,0xa8U,0x54U,0x3cU,0xeaU,
    0x18U,0x48U,0x48U,0xccU,0xc0U,0x18U,0x18U,0x18U,0x90U,
    0x24U,0xffU,0x48U,0x9cU,0xd2U,0xd8U,0xf0U,0xf6U,0xfcU,
    1U,2U,3U,2U,1U,1U,3U,3U,3U,1U,1U,2U,2U,0x21U,
    1U,2U,1U,1U,2U,0xffU,2U,2U,1U,1U,2U,2U,2U
};
static const mysmb_u8 mysmb_enemy_attribute_data[54] = {
    1U,2U,3U,2U,1U,1U,3U,3U,3U,1U,1U,2U,2U,0x21U,
    1U,2U,1U,1U,2U,0xffU,2U,2U,1U,1U,2U,2U,2U,
    0x08U,0x18U,0x18U,0x19U,0x1aU,0x19U,0x18U,
    0xb5U,0xcfU,0x85U,0x02U,0xadU,0xaeU,0x03U,0x85U,0x05U,
    0xbcU,0xe5U,0x06U,0x84U,0xebU,0xa9U,0x00U,0x8dU,0x09U,0x01U,0xb5U
};

static void mysmb_enemy_draw_row(struct mysmb_game *g, mysmb_u8 *oam,
                                 mysmb_u8 *tile_offset)
{
    g->ram[0U] = mysmb_enemy_graphics_table[*tile_offset];
    g->ram[1U] = mysmb_enemy_graphics_table[(mysmb_u8)(*tile_offset + 1U)];
    mysmb_oam_draw_sprite_object(g, tile_offset, oam);
}

/* ROM $e87d-$eaf2 ordinary EnemyGfxHandler control flow and OAM tail.
 * The caller continues the remaining normal-enemy phases after this call. */
mysmb_u8 mysmb_objects_draw_normal_enemy_graphics(struct mysmb_game *game,
                                                   mysmb_u8 slot)
{
    mysmb_u8 id, state, code, tile, oam, first, a, y, swap_row;
    mysmb_u8 row;

    game->ram[2U] = game->ram[MYSMB_NORMAL_Y + slot];
    game->ram[5U] = game->ram[MYSMB_NORMAL_REL_X];
    game->ram[0x00ebU] = game->ram[MYSMB_NORMAL_SPRITE + slot];
    game->ram[0x0109U] = 0U;
    game->ram[3U] = game->ram[MYSMB_NORMAL_DIRECTION + slot];
    game->ram[4U] = game->ram[MYSMB_NORMAL_ATTRIBUTES + slot];
    id = game->ram[MYSMB_NORMAL_ID + slot];
    if (id == 13U && (game->ram[MYSMB_PIRANHA_Y_SPEED + slot] & 0x80U) == 0U &&
        game->ram[0x078aU + slot] != 0U) return 1U;

    state = game->ram[MYSMB_NORMAL_STATE + slot];
    game->ram[0x00edU] = state;
    game->ram[0x00ecU] = (mysmb_u8)(state & 0x1fU);
    code = id;
    if (id == 53U) {
        game->ram[0x00ecU] = 0U;
        game->ram[3U] = 1U;
        code = 0x15U;
    }
    if (code == 51U) {
        --game->ram[2U];
        game->ram[4U] = game->ram[0x078aU + slot] == 0U ? 3U : 0x23U;
        game->ram[0x00edU] = 0U;
        game->ram[0x00ecU] = 0U;
        code = 8U;
    }
    if (code == 50U) {
        static const mysmb_u8 spring[5] = {0x18U,0x19U,0x1aU,0x19U,0x18U};
        game->ram[0x00ecU] = 3U;
        code = spring[game->ram[0x070eU]];
    }
    game->ram[0x00efU] = code;
    if (code == 12U && (game->ram[0x00a0U+slot] & 0x80U) == 0U)
        ++game->ram[0x0109U];
    if (game->ram[0x036aU] != 0U) return 0U;

    if (code == 6U && (state & 0x20U) == 0U &&
        game->ram[MYSMB_NORMAL_TIMER_CONTROL] == 0U &&
        (game->ram[MYSMB_NORMAL_FRAME_COUNTER] & 8U) == 0U)
        game->ram[3U] ^= 3U;
    if (code == 6U && state >= 2U) game->ram[0x00ecU] = 4U;
    game->ram[4U] = (mysmb_u8)(game->ram[4U] |
                                  mysmb_enemy_attribute_data[code]);
    tile = mysmb_enemy_graphics_offsets[code];
    if (tile == 0x24U && game->ram[0x00ecU] == 5U) {
        tile = 0x30U;
        game->ram[3U] = 2U;
        game->ram[0x00ecU] = 5U;
        goto hammer;
    }
    if (tile == 0x90U) {
        if ((game->ram[0x00edU] & 0x20U) == 0U &&
            game->ram[0x078fU] < 0x10U) tile = 0x96U;
        goto defeated;
    }
    if (code < 4U && game->ram[0x00ecU] >= 2U) {
        tile = 0x5aU;
        if (code == 2U) { tile = 0x7eU; ++game->ram[2U]; }
    }
    if (game->ram[0x00ecU] == 4U) {
        tile = 0x72U;
        ++game->ram[2U];
        if (code != 2U) {
            tile = 0x66U;
            ++game->ram[2U];
            if (code == 6U) {
                tile = 0x54U;
                if ((game->ram[0x00edU] & 0x20U) == 0U) {
                    tile = 0x8aU;
                    --game->ram[2U];
                }
            }
        }
    }
hammer:
    if (code == 5U && game->ram[0x00edU] != 0U) {
        if ((game->ram[0x00edU] & 8U) == 0U) goto defeated;
        tile = 0xb4U;
        goto animate;
    }
    if (tile != 0x48U) {
        a = game->ram[0x0796U+slot];
        if (a >= 5U) goto defeated;
        if (tile == 0x3cU) {
            if (a == 1U) goto defeated;
            game->ram[2U] = (mysmb_u8)(game->ram[2U]+3U);
            goto animation_stop;
        }
    }
animate:
    if (code == 6U || code == 8U || code == 12U || code >= 0x18U)
        goto defeated;
    if (code == 0x15U) {
        if (game->ram[MYSMB_NORMAL_WORLD] >= 7U) goto defeated;
        tile = 0xa2U;
        game->ram[0x00ecU] = 3U;
        goto defeated;
    }
    if ((game->ram[MYSMB_NORMAL_FRAME_COUNTER] & 8U) != 0U)
        goto defeated;
animation_stop:
    if ((game->ram[0x00edU] & 0xa0U) == 0U &&
        game->ram[MYSMB_NORMAL_TIMER_CONTROL] == 0U)
        tile = (mysmb_u8)(tile+6U);
defeated:
    if ((game->ram[0x00edU] & 0x20U) != 0U && code >= 4U) {
        game->ram[0x0109U] = 1U;
        game->ram[0x00ecU] = 0U;
    }
    oam = game->ram[MYSMB_NORMAL_SPRITE + slot];
    first = oam;
    for (row=0U;row<3U;++row) mysmb_enemy_draw_row(game,&oam,&tile);

    if (code != 8U && game->ram[0x0109U] != 0U) {
        a = (mysmb_u8)(game->ram[0x0202U+first] | 0x80U);
        for (row=0U;row<3U;++row) {
            y=(mysmb_u8)(first+row*8U);
            game->ram[0x0202U+y]=a; game->ram[0x0206U+y]=a;
        }
        swap_row = (code == 5U || code == 17U || code >= 0x15U) ? 0U : 8U;
        y=(mysmb_u8)(first+swap_row);
        a=game->ram[0x0201U+y];
        game->ram[0x0201U+y]=game->ram[0x0211U+first];
        game->ram[0x0211U+first]=a;
        a=game->ram[0x0205U+y];
        game->ram[0x0205U+y]=game->ram[0x0215U+first];
        game->ram[0x0215U+first]=a;
    }
    if (code != 8U && code != 5U) {
        if ((code != 18U || game->ram[0x00ecU] == 5U) &&
            (code == 7U || code == 13U || code == 12U ||
             game->ram[0x00ecU] >= 2U)) {
            a=(mysmb_u8)(game->ram[0x0202U+first] & 0xa3U);
            for (row=0U;row<3U;++row) {
                y=(mysmb_u8)(first+row*8U);
                game->ram[0x0202U+y]=a;
                game->ram[0x0206U+y]=(mysmb_u8)(a | 0x40U |
                    (game->ram[0x00ecU]==5U ? 0x80U : 0U));
            }
            if (game->ram[0x00ecU] == 4U) {
                a=(mysmb_u8)(game->ram[0x020aU+first] | 0x80U);
                game->ram[0x020aU+first]=a;
                game->ram[0x0212U+first]=a;
                game->ram[0x020eU+first]=(mysmb_u8)(a|0x40U);
                game->ram[0x0216U+first]=(mysmb_u8)(a|0x40U);
            }
        } else if (code == 0x15U) game->ram[0x0216U+first]=0x42U;
        if (code == 17U) {
            if (game->ram[0x0109U] == 0U) {
                game->ram[0x0212U+first] &= 0x81U;
                a=(mysmb_u8)(game->ram[0x0216U+first]|0x41U);
                game->ram[0x0216U+first]=a;
                if (game->ram[0x078fU] < 0x10U) {
                    game->ram[0x020eU+first]=a;
                    game->ram[0x020aU+first]=(mysmb_u8)(a&0x81U);
                }
            } else {
                game->ram[0x0202U+first] &= 0x81U;
                game->ram[0x0206U+first] |= 0x41U;
            }
        }
        if (code >= 0x18U) {
            game->ram[0x020aU+first]=0x82U;
            game->ram[0x0212U+first]=0x82U;
            game->ram[0x020eU+first]=0xc2U;
            game->ram[0x0216U+first]=0xc2U;
        }
    }
    mysmb_normal_apply_offscreen(game,first,game->ram[MYSMB_NORMAL_OFFSCREEN]);
    if ((game->ram[MYSMB_NORMAL_OFFSCREEN] & 0x80U) != 0U &&
        id != 12U && game->ram[0x00b6U+slot] == 2U)
        mysmb_objects_erase_enemy(game,slot);
    return 1U;
}

/* ROM EnemyGfxHandler: RunRetainerObj reaches the same branch tree. */
void mysmb_oam_draw_retainer(struct mysmb_game *game, mysmb_u8 slot)
{
    if (game->ram[0x036aU] != 0U)
        mysmb_oam_draw_bowser_half(game, slot);
    else
        (void)mysmb_objects_draw_normal_enemy_graphics(game, slot);
}

/* ROM $e87d-$eaf2 EnemyGfxHandler, spring route through EggExc.
 * DrawJSpr has already written relative position and offscreen bits. */
void mysmb_oam_draw_jumpspring(struct mysmb_game *game, mysmb_u8 slot)
{
    static const mysmb_u8 graphics[18] = {
        0xf2U, 0xf2U, 0xf3U, 0xf3U, 0xf2U, 0xf2U,
        0xf1U, 0xf1U, 0xf1U, 0xf1U, 0xfcU, 0xfcU,
        0xf0U, 0xf0U, 0xfcU, 0xfcU, 0xfcU, 0xfcU
    };
    static const mysmb_u8 frame_offsets[5] = { 0U, 1U, 2U, 1U, 0U };
    const mysmb_u8 *tiles;
    mysmb_u8 animation;
    mysmb_u8 row;
    mysmb_u8 offset;
    mysmb_u8 bits;
    mysmb_u8 attributes;
    mysmb_u8 left;
    mysmb_u8 right;
    mysmb_u8 x;
    mysmb_u8 y;
    mysmb_u8 state;
    mysmb_u8 direction;
    mysmb_u8 first;
    mysmb_u8 last;

    /* EnemyGfxHandler entry and CheckForJumpspring use these work bytes. */
    game->ram[2U] = game->ram[MYSMB_NORMAL_Y + slot];
    game->ram[5U] = game->ram[MYSMB_NORMAL_REL_X];
    game->ram[0x00ebU] = game->ram[MYSMB_NORMAL_SPRITE + slot];
    game->ram[0x0109U] = 0U;
    game->ram[3U] = game->ram[MYSMB_NORMAL_DIRECTION + slot];
    game->ram[4U] = game->ram[MYSMB_NORMAL_ATTRIBUTES + slot];
    state = game->ram[MYSMB_NORMAL_STATE + slot];
    game->ram[0x00edU] = state;
    animation = game->ram[0x070eU];
    game->ram[0x00efU] = (mysmb_u8)(0x18U + frame_offsets[animation]);
    game->ram[0x00ecU] = 3U;
    tiles = graphics + frame_offsets[animation] * 6U;
    x = game->ram[5U];
    y = game->ram[2U];
    bits = game->ram[MYSMB_NORMAL_OFFSCREEN];
    attributes = (mysmb_u8)(game->ram[4U] | 2U);
    game->ram[4U] = attributes;
    direction = game->ram[3U];
    if ((state & 0x20U) != 0U) {
        game->ram[0x0109U] = 1U;
        game->ram[0x00ecU] = 0U;
    }
    offset = game->ram[MYSMB_NORMAL_SPRITE + slot];
    for (row = 0U; row < 3U; ++row) {
        left = tiles[row * 2U];
        right = tiles[row * 2U + 1U];
        game->ram[0U] = left;
        game->ram[1U] = right;
        if ((direction & 2U) != 0U) {
            game->ram[0x0201U + offset] = right;
            game->ram[0x0205U + offset] = left;
            game->ram[0x0202U + offset] = (mysmb_u8)(attributes | 0x40U);
            game->ram[0x0206U + offset] = (mysmb_u8)(attributes | 0x40U);
        } else {
            game->ram[0x0201U + offset] = left;
            game->ram[0x0205U + offset] = right;
            game->ram[0x0202U + offset] = attributes;
            game->ram[0x0206U + offset] = attributes;
        }
        game->ram[0x0200U + offset] = y;
        game->ram[0x0204U + offset] = game->ram[0x0200U + offset];
        game->ram[0x0203U + offset] = x;
        game->ram[0x0207U + offset] = (mysmb_u8)(x + 8U);
        y = (mysmb_u8)(y + 8U);
        offset = (mysmb_u8)(offset + 8U);
    }
    game->ram[2U] = y;
    offset = game->ram[MYSMB_NORMAL_SPRITE + slot];
    if (game->ram[0x0109U] != 0U) {
        for (row = 0U; row < 3U; ++row) {
            mysmb_u8 row_offset = (mysmb_u8)(offset + row * 8U);
            game->ram[0x0202U + row_offset] |= 0x80U;
            game->ram[0x0206U + row_offset] |= 0x80U;
        }
        first = game->ram[0x0201U + offset];
        last = game->ram[0x0211U + offset];
        game->ram[0x0201U + offset] = last;
        game->ram[0x0211U + offset] = first;
        first = game->ram[0x0205U + offset];
        last = game->ram[0x0215U + offset];
        game->ram[0x0205U + offset] = last;
        game->ram[0x0215U + offset] = first;
    }
    if (game->ram[0x00ecU] >= 2U && game->ram[0x036aU] == 0U) {
        attributes = (mysmb_u8)(game->ram[0x0202U + offset] & 0xa3U);
        for (row = 0U; row < 3U; ++row) {
            mysmb_u8 row_offset = (mysmb_u8)(offset + row * 8U);
            game->ram[0x0202U + row_offset] = attributes;
            game->ram[0x0206U + row_offset] = (mysmb_u8)(attributes | 0x40U);
        }
    }
    /* CheckToMirrorJSpring overwrites the lower two attribute rows. */
    game->ram[0x020aU + offset] = 0x82U;
    game->ram[0x0212U + offset] = 0x82U;
    game->ram[0x020eU + offset] = 0xc2U;
    game->ram[0x0216U + offset] = 0xc2U;
    mysmb_normal_apply_offscreen(game, game->ram[MYSMB_NORMAL_SPRITE + slot], bits);
    if ((bits & 0x80U) != 0U && game->ram[MYSMB_NORMAL_ID + slot] != 12U &&
        game->ram[0x00b5U + slot] == 2U) {
        mysmb_objects_erase_enemy(game, slot);
    }
}
