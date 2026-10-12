#include "core/enemy/init.h"
#include <string.h>

int main(void)
{
    static struct mysmb_game game;
    static mysmb_u8 expected[2048];
    static const mysmb_u8 ids[14]={4U,9U,19U,25U,26U,32U,33U,
        34U,35U,48U,49U,50U,51U,52U};
    unsigned int i,slot,y;
    for(i=0U;i<14U;++i) for(slot=0U;slot<6U;++slot) for(y=0U;y<256U;++y) {
        memset(&game,0,sizeof(game));
        memset(game.ram,0x5a,sizeof(game.ram));
        game.ram[0x16U+slot]=ids[i];game.ram[0xcfU+slot]=(mysmb_u8)y;
        memcpy(expected,game.ram,sizeof(expected));
        if(ids[i]<0x15U) {
            expected[0xcfU+slot]=(mysmb_u8)(y+8U);
            expected[0x3d8U+slot]=1U;
        }
        expected[4U]=0x81U;expected[5U]=0xc2U;
        expected[6U]=0xf0U;expected[7U]=0xc2U;
        mysmb_enemy_checkpoint_loaded(&game,(mysmb_u8)slot);
        if(memcmp(game.ram,expected,sizeof(expected))) return 1;
    }
    return 0;
}
