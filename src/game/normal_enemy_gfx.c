#include "game/objects.h"

enum {
    MYSMB_NORMAL_FLAG = 0x000fU,
    MYSMB_NORMAL_ID = 0x0016U,
    MYSMB_NORMAL_STATE = 0x001eU,
    MYSMB_NORMAL_DIRECTION = 0x0046U,
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
    MYSMB_NORMAL_FRAME_COUNTER = 0x0009U
};

static void mysmb_normal_apply_offscreen(struct mysmb_game *game,
                                         mysmb_u8 oam, mysmb_u8 bits)
{
    mysmb_u8 row;
    mysmb_u8 offset;

    for (row = 0U; row < 3U; ++row) {
        offset = (mysmb_u8)(oam + row * 8U);
        if ((bits & 0x80U) != 0U ||
            ((bits & 0x40U) != 0U && row >= 1U) ||
            ((bits & 0x20U) != 0U && row == 2U)) {
            game->ram[0x0200U + offset] = 0xf8U;
            game->ram[0x0204U + offset] = 0xf8U;
        }
        else {
            if ((bits & 8U) != 0U) game->ram[0x0200U + offset] = 0xf8U;
            if ((bits & 4U) != 0U) game->ram[0x0204U + offset] = 0xf8U;
        }
    }
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
    game->ram[MYSMB_NORMAL_REL_X + slot] = (mysmb_u8)(world - screen);
    game->ram[MYSMB_NORMAL_REL_Y + slot] = game->ram[MYSMB_NORMAL_Y + slot];
    offscreen = mysmb_objects_get_enemy_x_offscreen_bits(game, slot);
    game->ram[MYSMB_NORMAL_OFFSCREEN + slot] = offscreen;
    state = game->ram[MYSMB_NORMAL_STATE + slot];
    state_low = (mysmb_u8)(state & 0x1fU);
    y = game->ram[MYSMB_NORMAL_REL_Y + slot];

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
        game->ram[0x0203U + offset] = game->ram[MYSMB_NORMAL_REL_X + slot];
        game->ram[0x0207U + offset] =
            (mysmb_u8)(game->ram[MYSMB_NORMAL_REL_X + slot] + 8U);
    }
    mysmb_normal_apply_offscreen(game, oam, offscreen);
    return 1U;
}

/* ROM EnemyGfxHandler: IDs $09/$0e/$0f/$10 share Paratroopa rows. */
static mysmb_u8 mysmb_draw_paratroopa(struct mysmb_game *g, mysmb_u8 n)
{
    static const mysmb_u8 f1[6]={0x69U,0xa5U,0x6aU,0xa7U,0xa8U,0xa9U};
    static const mysmb_u8 f2[6]={0x6bU,0xa0U,0x6cU,0xa2U,0xa3U,0xa4U};
    mysmb_u16 w,z; mysmb_u8 id,at,dir,bits,o,r,q,l,rr; const mysmb_u8 *t;
    if(g->ram[MYSMB_NORMAL_FLAG+n]==0U) return 0U;
    id=g->ram[MYSMB_NORMAL_ID+n];
    if(id!=9U && id!=14U && id!=15U && id!=16U) return 0U;
    w=(mysmb_u16)(((mysmb_u16)g->ram[MYSMB_NORMAL_PAGE+n]<<8U)|g->ram[MYSMB_NORMAL_X+n]);
    z=(mysmb_u16)(((mysmb_u16)g->ram[MYSMB_NORMAL_SCREEN_PAGE]<<8U)|g->ram[MYSMB_NORMAL_SCREEN_X]);
    g->ram[MYSMB_NORMAL_ATTRIBUTES+n]=0U;
    g->ram[MYSMB_NORMAL_REL_X+n]=(mysmb_u8)(w-z); g->ram[MYSMB_NORMAL_REL_Y+n]=g->ram[MYSMB_NORMAL_Y+n];
    bits=mysmb_objects_get_enemy_x_offscreen_bits(g,n); g->ram[MYSMB_NORMAL_OFFSCREEN+n]=bits;
    at=id==15U?2U:1U; dir=g->ram[MYSMB_NORMAL_DIRECTION+n];
    t=((g->ram[MYSMB_NORMAL_STATE+n]&0xa0U)==0U && g->ram[MYSMB_NORMAL_TIMER_CONTROL]==0U &&
       (g->ram[MYSMB_NORMAL_FRAME_COUNTER]&8U)==0U)?f2:f1;
    o=g->ram[MYSMB_NORMAL_SPRITE+n];
    for(r=0U;r<3U;++r){q=(mysmb_u8)(o+r*8U);l=t[r*2U];rr=t[r*2U+1U];
      if((dir&2U)!=0U){g->ram[0x0201U+q]=rr;g->ram[0x0205U+q]=l;g->ram[0x0202U+q]=(mysmb_u8)(at|0x40U);g->ram[0x0206U+q]=(mysmb_u8)(at|0x40U);}
      else {g->ram[0x0201U+q]=l;g->ram[0x0205U+q]=rr;g->ram[0x0202U+q]=at;g->ram[0x0206U+q]=at;}
      g->ram[0x0200U+q]=(mysmb_u8)(g->ram[MYSMB_NORMAL_REL_Y+n]+r*8U);g->ram[0x0204U+q]=g->ram[0x0200U+q];
      g->ram[0x0203U+q]=g->ram[MYSMB_NORMAL_REL_X+n];g->ram[0x0207U+q]=(mysmb_u8)(g->ram[MYSMB_NORMAL_REL_X+n]+8U);}
    mysmb_normal_apply_offscreen(g,o,bits); return 1U;
}

/* ROM EnemyGfxHandler Lakitu branch: $90/$96 plus cloud-row mirroring. */
static mysmb_u8 mysmb_draw_lakitu(struct mysmb_game *g, mysmb_u8 n)
{
    static const mysmb_u8 first[6]={0xb9U,0xb8U,0xbbU,0xbaU,0xbcU,0xbcU};
    static const mysmb_u8 second[6]={0xfcU,0xfcU,0xbdU,0xbdU,0xbcU,0xbcU};
    const mysmb_u8 *t; mysmb_u16 w,z; mysmb_u8 st,b,o,r,q,l,rr;
    if(g->ram[MYSMB_NORMAL_FLAG+n]==0U || g->ram[MYSMB_NORMAL_ID+n]!=17U)return 0U;
    w=(mysmb_u16)(((mysmb_u16)g->ram[MYSMB_NORMAL_PAGE+n]<<8U)|g->ram[MYSMB_NORMAL_X+n]);
    z=(mysmb_u16)(((mysmb_u16)g->ram[MYSMB_NORMAL_SCREEN_PAGE]<<8U)|g->ram[MYSMB_NORMAL_SCREEN_X]);
    g->ram[MYSMB_NORMAL_ATTRIBUTES+n]=0U; g->ram[MYSMB_NORMAL_REL_X+n]=(mysmb_u8)(w-z);g->ram[MYSMB_NORMAL_REL_Y+n]=g->ram[MYSMB_NORMAL_Y+n];
    b=mysmb_objects_get_enemy_x_offscreen_bits(g,n);g->ram[MYSMB_NORMAL_OFFSCREEN+n]=b;st=g->ram[MYSMB_NORMAL_STATE+n];
    t=((st&0x20U)==0U && g->ram[0x078fU]<0x10U)?second:first;o=g->ram[MYSMB_NORMAL_SPRITE+n];
    for(r=0U;r<3U;++r){q=(mysmb_u8)(o+r*8U);l=t[r*2U];rr=t[r*2U+1U];g->ram[0x0201U+q]=l;g->ram[0x0205U+q]=rr;g->ram[0x0202U+q]=1U;g->ram[0x0206U+q]=1U;g->ram[0x0200U+q]=(mysmb_u8)(g->ram[MYSMB_NORMAL_REL_Y+n]+r*8U);g->ram[0x0204U+q]=g->ram[0x0200U+q];g->ram[0x0203U+q]=g->ram[MYSMB_NORMAL_REL_X+n];g->ram[0x0207U+q]=(mysmb_u8)(g->ram[MYSMB_NORMAL_REL_X+n]+8U);}
    q=(mysmb_u8)(o+16U);g->ram[0x0202U+q]&=0x81U;g->ram[0x0206U+q]|=0x41U;
    if(g->ram[0x078fU]<0x10U){g->ram[0x0202U+o+8U]=g->ram[0x0202U+q];g->ram[0x0206U+o+8U]=g->ram[0x0206U+q];}
    mysmb_normal_apply_offscreen(g,o,b);return 1U;
}
/* Shared RunNormalEnemies graphics phase.  A return value of one means this
 * slot belongs to a separately scheduled movement owner. */
mysmb_u8 mysmb_objects_draw_normal_enemy_graphics(struct mysmb_game *game,
                                                   mysmb_u8 slot)
{
    if (mysmb_objects_draw_special_enemy(game, slot) != 0U) return 1U;
    (void)mysmb_objects_draw_koopa_buzzy(game, slot);
    if (mysmb_objects_draw_spiny(game, slot) == 2U) return 1U;
    if (mysmb_draw_paratroopa(game, slot) != 0U) return 1U;
    if (mysmb_draw_lakitu(game, slot) != 0U) return 1U;
    return 0U;
}
