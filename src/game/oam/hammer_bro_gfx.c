#include "game/oam/oam.h"
#include "game/oam/enemy_offscreen_tail.h"
#include "game/objects.h"

enum { F=0x000fU,I=0x0016U,S=0x001eU,D=0x0046U,P=0x006eU,X=0x0087U,Y=0x00cfU,
       RX=0x03aeU,RY=0x03b9U,O=0x03d1U,A=0x03c5U,SO=0x06e5U,SP=0x071aU,SX=0x071cU,
       TC=0x0747U,FC=0x0009U };

static void hide(struct mysmb_game *g,mysmb_u8 o,mysmb_u8 b)
{
    mysmb_oam_enemy_offscreen_tail(g, o, b);
}

/* ROM EnemyGfxHandler, CheckForHammerBro, and DrawEnemyObject for ID $05. */
mysmb_u8 mysmb_objects_draw_hammer_bro(struct mysmb_game *g,mysmb_u8 n)
{
    static const mysmb_u8 tile[4][6]={{0x7dU,0x7cU,0xd1U,0x8cU,0xd3U,0xd2U},
        {0x7dU,0x7cU,0x89U,0x88U,0x8bU,0x8aU},{0xd5U,0xd4U,0xe3U,0xe2U,0xd3U,0xd2U},
        {0xd5U,0xd4U,0xe3U,0xe2U,0x8bU,0x8aU}};
    const mysmb_u8 *t; mysmb_u16 w,z; mysmb_u8 st,b,o,r,q,l,rr,at,frame,sl,sr;
    if(g->ram[F+n]==0U||g->ram[I+n]!=5U)return 0U;
    w=(mysmb_u16)(((mysmb_u16)g->ram[P+n]<<8U)|g->ram[X+n]);
    z=(mysmb_u16)(((mysmb_u16)g->ram[SP]<<8U)|g->ram[SX]);
    g->ram[A+n]=0U;g->ram[RX+n]=(mysmb_u8)(w-z);g->ram[RY+n]=g->ram[Y+n];
    b=mysmb_objects_get_enemy_x_offscreen_bits(g,n);g->ram[O+n]=b;st=g->ram[S+n];
    frame=(st&8U)!=0U?2U:0U;
    if((st&8U)!=0U||st==0U){if((st&0xa0U)==0U&&g->ram[TC]==0U&&(g->ram[FC]&8U)==0U)frame++;}
    t=tile[frame];o=g->ram[SO+n];
    for(r=0U;r<3U;++r){q=(mysmb_u8)(o+r*8U);l=t[r*2U];rr=t[r*2U+1U];at=1U;
        if((g->ram[D+n]&2U)!=0U){g->ram[0x0201U+q]=rr;g->ram[0x0205U+q]=l;at|=0x40U;}
        else{g->ram[0x0201U+q]=l;g->ram[0x0205U+q]=rr;}
        g->ram[0x0202U+q]=at;g->ram[0x0206U+q]=at;g->ram[0x0200U+q]=(mysmb_u8)(g->ram[RY+n]+r*8U);
        g->ram[0x0204U+q]=g->ram[0x0200U+q];g->ram[0x0203U+q]=g->ram[RX+n];g->ram[0x0207U+q]=(mysmb_u8)(g->ram[RX+n]+8U);}
    if((st&0x20U)!=0U){for(r=0U;r<3U;++r){q=(mysmb_u8)(o+r*8U);g->ram[0x0202U+q]|=0x80U;g->ram[0x0206U+q]|=0x80U;}
        sl=g->ram[0x0201U+o];sr=g->ram[0x0205U+o];g->ram[0x0201U+o]=g->ram[0x0211U+o];g->ram[0x0205U+o]=g->ram[0x0215U+o];g->ram[0x0211U+o]=sl;g->ram[0x0215U+o]=sr;}
    hide(g,o,b);return 1U;
}

